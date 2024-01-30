#include "Download.h"

void Download::installPackage(const QUrl& url)
{
	auto reply = mNetwork.get(QNetworkRequest(url));

	QObject::connect(reply, &QNetworkReply::finished,
		[&, reply]()
		{
			reply->deleteLater();
			auto buffer = reply->readAll();
			auto hash = crypto::sha1(buffer);
			QJsonObject manifest = QJsonDocument::fromJson(buffer).object();

			auto performDownload =
				[&, manifest, hash]()
				{
					QThreadPool::globalInstance()->start(
						[&, manifest, hash]()
						{
							QDir installDir = getSettings()->getGameDir().absoluteFilePath("packages/" + hash);
							if (!installDir.exists())
							{
								installDir.mkpath(installDir.absolutePath());
							}
							// compose the download list
							QList<DownloadEntry> downloads;
							for (auto& key : manifest["files"].toObject().keys())
							{
								auto file = manifest["files"].toObject()[key].toObject();
								// necessary directories will be created automatically
								if (file["type"].toString() == "file")
								{
									auto raw = file["downloads"].toObject()["raw"].toObject();
									downloads << DownloadEntry{ installDir.absoluteFilePath(key).toStdString(), raw["url"].toString(),
										quint64(raw["size"].toInt()), false, raw["sha1"].toString() };
								}
							}
							DownloadHelper d(this);
							d.addDownloadList(downloads, true);
							d.performDownload();
							//UIThread::run([&]()
							//	{
							//		ui.play->setEnabled(true); // play will work only if ui.play is enabled
							//		play(false);
							//	});
						});
				};


			// check for the license file
			if (manifest["files"].toObject()["LICENSE"].isObject())
			{
				auto url =
					manifest["files"].toObject()["LICENSE"].toObject()["downloads"].toObject()["raw"].toObject()["url"].toString();
				auto licenseReply = mNetwork.get(QNetworkRequest(url));
				QObject::connect(licenseReply, &QNetworkReply::finished,
					[&, performDownload, licenseReply]()
					{
						licenseReply->deleteLater();

						LicenseForm f(QString::fromUtf8(licenseReply->readAll()), this);
						if (f.exec())
						{
							performDownload();
						}
						else
						{
							//setDownloadMode(false);
						}
					});
			}
			else
			{
				performDownload();
			}
		});
}
