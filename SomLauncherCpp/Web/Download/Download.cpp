#include "Download.h"

std::filesystem::path web::download::downloadFile(const std::string& url, const std::filesystem::path& dist,
	std::shared_ptr<CallbackNull> callback, const std::string& sha1, bool lzma_compressed)
{
	//d.first = path
	//d.second = url

	std::filesystem::path destanation_file = dist;
	QFileInfo fi(destanation_file);
	if (!fi.isFile() && fi.isDir())
	{
		destanation_file /= QUrl::fromUserInput(url.c_str()).fileName().toStdString();
	}

	QFile qfile = QFile(destanation_file);
	if (!sha1.empty() && sha1 == crypto::sha1(qfile).toStdString())
	{
		callback->setQLabelProggressValue("Checking hashes..");
		return destanation_file;
	}

	quint64 mTotalDownloadSize = callback->getTotalDownloadSize();

	QNetworkAccessManager network;
	QEventLoop zaloop;

	quint64 downloaded = 0;
	unsigned downloadTasks = 0;

	QObject* dummy = new QObject(&network);

	QNetworkReply* reply = network.get(QNetworkRequest(QUrl::fromUserInput(url.c_str())));

	QFile* file = new QFile(destanation_file, &network);

	auto prettySize = [](quint64 size, bool isSpeed)
		{
			long double fsize = size;
			long double power = log(fsize) / log(2);
			long double index = std::max(int(std::floor(power / 10 - 0.01)), 0);

			QVector<QString> strs;
			if (isSpeed)
			{
				strs = {
					QObject::tr("B/sec"),
					QObject::tr("Kb/sec"),
					QObject::tr("Mb/sec"),
					QObject::tr("Gb/sec"),
					QObject::tr("Tb/sec"),
					QObject::tr("Pb/sec")
				};
			}
			else
			{
				strs = {
					QObject::tr("B"),
					QObject::tr("Kb"),
					QObject::tr("Mb"),
					QObject::tr("Gb"),
					QObject::tr("Tb"),
					QObject::tr("Pb")
				};
			}

			uint32_t i = index;

			return QString("%1 %2").arg(double(size / pow(1024, index)), 0, 'f', 1).arg(i < strs.size() ? strs[i] : "??");
		};

	QObject::connect(reply, &QNetworkReply::readyRead, dummy,
		[&, reply, file]()
		{
			if (!file->isOpen())
			{
				QDir absDir = QFileInfo(*file).absoluteDir();
				if (!absDir.exists())
				{
					absDir.mkpath(absDir.absolutePath());
				}
				if (!file->open(QIODevice::WriteOnly))
				{
					// try to delete existing file.
					file->remove();

					if (!file->open(QIODevice::WriteOnly))
					{
						qWarning("Could not open file: %s", file->fileName().toStdString().c_str());
						reply->close();
						return "";
					}
				}
			}
			downloaded += file->write(reply->readAll());
		});

	QObject::connect(reply, &QNetworkReply::finished, dummy,
		[&, file]()
		{
			if (file->isOpen())
			{
				file->deleteLater();
				file->close();
			}
			downloadTasks -= 1;

			if (downloadTasks == 0)
			{
				zaloop.exit();
			}
		});
	downloadTasks += 1;


	QTimer t;
	unsigned counter = 0;
	quint64 lastPeriodDownloaded = 0;
	float averangeDelta = 0.f;
	QObject::connect(&t, &QTimer::timeout, dummy,
		[&, destanation_file]()
		{
			if (QThread::currentThread()->isInterruptionRequested())
			{
				zaloop.exit();
				return "";
			}
			unsigned delta = downloaded - lastPeriodDownloaded;
			if (++counter % 10 == 0)
			{
				averangeDelta += (delta - averangeDelta) * 0.2f;
				if (counter >= 50)
				{
					// it's time to show up the speed
					float time = (mTotalDownloadSize - downloaded) / averangeDelta;
					//auto k = QDateTime::fromMSecsSinceEpoch(time * 1000).toUTC().toString("HH:mm:ss");
					UIThread::run([&, time]()
						{
							auto k = QDateTime::fromMSecsSinceEpoch(time * 1000).toUTC().toString("HH:mm:ss");
							//mLauncher->ui.eta->setText(k);
							callback->setQLabelDownloadTime(k);
						});


				}

				lastPeriodDownloaded = downloaded;
			}
			//mLauncher->ui.downloaded->setText(StringHelper::prettySize(d));
			callback->setQLabelDownloadSpeed(prettySize(averangeDelta, true));

			// copy this value to prevent data racing
			quint64 d = downloaded;
			if (mTotalDownloadSize)
			{
				callback->setQProgressValue(d * 1000 / mTotalDownloadSize);
			}
			else
			{
				callback->setQProgressValue(0);
			}

			callback->setQLabelProggressValue(destanation_file.u8string().c_str());
			/*UIThread::run([&, d]()
				{
					mLauncher->ui.downloaded->setText(StringHelper::prettySize(d));
					mLauncher->ui.speed->setText(StringHelper::prettySize(averangeDelta, true));
					if (mTotalDownloadSize)
					{
						mLauncher->ui.progressBar->setValue(d * 1000 / mTotalDownloadSize);
					}
					else
					{

						mLauncher->ui.progressBar->setValue(0);
					}
				});*/
		});
	t.setInterval(100);
	t.start();
	interruptionCheck();
	zaloop.exec();


	return destanation_file;
}
