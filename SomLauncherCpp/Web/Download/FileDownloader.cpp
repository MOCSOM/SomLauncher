#include "FileDownloader.h"

FileDownloader::FileDownloader(QUrl imageUrl, QObject* parent)
	: QObject(parent)
{
	this->url = imageUrl;
	this->m_WebCtrl = new QNetworkAccessManager();
	connect(
		this->m_WebCtrl, &QNetworkAccessManager::finished,
		this, &FileDownloader::fileDownloaded
	);


	/*QEventLoop zaloop;

	quint64 downloaded = 0;
	unsigned downloadTasks = 0;

	QObject* dummy = new QObject(&m_WebCtrl);*/


}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
	if (pReply->error())
	{
		// We inform about it and show the error information
		qDebug() << "ERROR";
		qDebug() << pReply->errorString();
	}

	this->m_DownloadedData = pReply->readAll();
	//emit a signal
	pReply->deleteLater();
	emit downloaded();
}

QByteArray FileDownloader::downloadedData() const
{
	return this->m_DownloadedData;
}

void FileDownloader::download() const
{
	QNetworkRequest request(this->url);
	QNetworkReply* reply = this->m_WebCtrl->get(request);
}


