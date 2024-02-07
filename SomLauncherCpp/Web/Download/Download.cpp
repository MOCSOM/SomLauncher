#include "Download.h"

std::filesystem::path web::download::downloadFile(const std::string& url, const std::filesystem::path& destanation_file,
	std::shared_ptr<CallbackNull> callback, const std::string& sha1, bool lzma_compressed)
{
	QFileInfo fi(destanation_file);
	fi.dir().mkdir(".");

	/*DownloadManager download_manager(destanation_file, new QObject());
	download_manager.downloadFile(QUrl::fromUserInput(url.c_str()));*/

	/*FileDownloader* downloader = new FileDownloader(QUrl::fromUserInput(url.c_str()));
	downloader->download();*/

	quint64 mTotalDownloadSize = callback->getTotalDownloadSize();
	QEventLoop zaloop;
	QNetworkAccessManager network;
	quint64 downloaded = 0;
	unsigned downloadTasks = 0;

	QObject* dummy = new QObject(&network);

	QNetworkReply* reply = network.get(QNetworkRequest(QUrl::fromUserInput(url.c_str())));

	QFile* file = new QFile(destanation_file, &network);

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
			quint64 d = downloaded;
			if (mTotalDownloadSize)
			{
				callback->setQProgressValue(d * 1000 / mTotalDownloadSize);
			}
			else
			{
				callback->setQProgressValue(0);
			}
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

	quint64 d = downloaded;
	if (mTotalDownloadSize)
	{
		callback->setQProgressValue(d * 1000 / mTotalDownloadSize);
	}
	else
	{
		callback->setQProgressValue(0);
	}

	//QUrl qurl = QUrl::fromUserInput(url.c_str());
	//QNetworkReply* reply = network.get(QNetworkRequest(qurl));
	zaloop.exec();
	return destanation_file;
}
