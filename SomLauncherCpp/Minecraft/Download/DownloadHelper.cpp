#include "DownloadHelper.h"

DownloadHelper::DownloadHelper(SomLauncherMainWindow* launcher)
	: mLauncher(launcher)
{
}

void DownloadHelper::addDownloadList(const QList<DownloadEntry>& downloads, bool withHashCheck)
{
	for (auto& d : downloads)
	{
		auto absPath = std::filesystem::absolute(d.mLocalPath);
		QFile local = absPath;
		if (local.exists())
		{
			if (!withHashCheck
				|| d.mHash.isEmpty()
				|| crypto::sha1(local) == d.mHash // check file's sha1
				)
			{
				continue;
			}
		}

		mTotalDownloadSize += d.mSize;
		mDownloadList << D{ absPath, d.mUrl };
	}
}

void DownloadHelper::performDownload()
{
	if (!mDownloadList.isEmpty())
	{
		setStatusUI(QObject::tr("Downloading..."));

		UIThread::run([&]()
			{
				//mLauncher->ui.total->setText(StringHelper::prettySize(mTotalDownloadSize));
				//mLauncher->ui.label_download_status_change->setText(StringHelper::prettySize(0));
				mLauncher->ui.label_download_status_change->setText(QObject::tr("Calculating..."));
				//mLauncher->ui.speed->setText(StringHelper::prettySize(0, true));
				mLauncher->ui.progressBar_ahtung->setMaximum(1000);
				mLauncher->ui.progressBar_ahtung->setValue(0);
			});
		QNetworkAccessManager network;
		QEventLoop zaloop;

		quint64 downloaded = 0;
		unsigned downloadTasks = 0;

		auto dummy = new QObject(&network);

		for (auto& d : mDownloadList)
		{
			auto reply = network.get(QNetworkRequest(d.second));
			auto file = new QFile(d.first, &network);

			QObject::connect(reply, &QNetworkReply::readyRead, dummy,
				[&, reply, file]()
				{
					if (!file->isOpen())
					{
						auto absDir = QFileInfo(*file).absoluteDir();
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
								return;
							}
						}
					}
					auto buf = reply->readAll();
					downloaded += file->write(buf);
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
		}

		QTimer t;
		unsigned counter = 0;
		quint64 lastPeriodDownloaded = 0;
		float averangeDelta = 0.f;
		QObject::connect(&t, &QTimer::timeout, dummy,
			[&]()
			{
				if (QThread::currentThread()->isInterruptionRequested())
				{
					zaloop.exit();
					return;
				}
				unsigned delta = downloaded - lastPeriodDownloaded;
				if (++counter % 10 == 0)
				{
					averangeDelta += (delta - averangeDelta) * 0.2f;
					if (counter >= 50)
					{
						// it's time to show up the speed
						float time = (mTotalDownloadSize - downloaded) / averangeDelta;
						UIThread::run([&, time]()
							{
								auto k = QDateTime::fromMSecsSinceEpoch(time * 1000).toUTC().toString("HH:mm:ss");
								mLauncher->ui.label_download_status_change->setText(k);
							});
					}

					lastPeriodDownloaded = downloaded;
				}

				// copy this value to prevent data racing
				quint64 d = downloaded;
				UIThread::run(
					[&, d]()
					{
						//mLauncher->ui.downloaded->setText(StringHelper::prettySize(d));
						//mLauncher->ui.speed->setText(StringHelper::prettySize(averangeDelta, true));
						if (mTotalDownloadSize)
						{
							mLauncher->ui.progressBar_ahtung->setValue(d * 1000 / mTotalDownloadSize);
						}
						else
						{

							mLauncher->ui.progressBar_ahtung->setValue(0);
						}
					});
			});
		t.setInterval(100);
		t.start();
		//interruptionCheck();
		zaloop.exec();
	}
}

void DownloadHelper::gameDownload(const::GameProfile& profile, bool withUpdate)
{
	mGameDir = QDir(mLauncher->minecraft_core_dir_path.c_str());

	// Determine download list and count total download size
	// running twice because of asset index
	for (int i = 0; i < 2; ++i)
	{
		mTotalDownloadSize = 0;
		auto assetJsonPath = mGameDir.absoluteFilePath("assets/indexes/" + profile.getAssetsIndex() + ".json");
		bool assetIndexExists = QFile(assetJsonPath).exists();

		addDownloadList(profile.getDownloads(), withUpdate);

		if (assetIndexExists)
		{
			QFile f(assetJsonPath);
			f.open(QIODevice::ReadOnly);
			auto objects = QJsonDocument::fromJson(f.readAll()).object()["objects"].toObject();
			f.close();

			QDir objectsDir = mGameDir.absoluteFilePath("assets/objects");

			for (QJsonValue object : objects)
			{
				auto hash = object["hash"].toString();
				QString path = QString(hash.at(0)) + hash.at(1) + '/' + hash;
				QFile local = objectsDir.absoluteFilePath(path);

				if (local.exists())
				{
					if (!withUpdate
						|| crypto::sha1(local) == hash // check file's sha1
						)
					{
						continue;
					}
				}

				mTotalDownloadSize += object["size"].toInt();
				mDownloadList << D{
					std::filesystem::absolute(path.toStdString()), QUrl("http://resources.download.minecraft.net/" + path)
				};
			}
		}
		performDownload();
		if (assetIndexExists)
			break;
	}
	UIThread::run([&]()
		{
			//mLauncher->resetDownloadIndicators();
			qDebug() << "resetDownloadIndicators";
		});
}

void DownloadHelper::setStatusUI(const QString& status)
{
	UIThread::run(
		[&, status]()
		{
			mLauncher->ui.label_download_status_change->setText(status);
		});
}
