#include "FileDownloader.h"

FileDownloader::FileDownloader(QUrl imageUrl, QObject* parent)
	: QObject(parent)
{
	connect(
		&m_WebCtrl, &QNetworkAccessManager::finished,
		this, &FileDownloader::fileDownloaded
	);

	QNetworkRequest request(imageUrl);
	m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
	m_DownloadedData = pReply->readAll();
	//emit a signal
	pReply->deleteLater();
	emit downloaded();
}

QByteArray FileDownloader::downloadedData() const
{
	return m_DownloadedData;
}
