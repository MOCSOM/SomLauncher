#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class FileDownloader : public QObject
{
	Q_OBJECT
public:
	explicit FileDownloader(QUrl imageUrl, QObject* parent = nullptr);
	virtual ~FileDownloader() = default;

public:
	QByteArray downloadedData() const;
	void download() const;

signals:
	void downloaded();

private slots:
	void fileDownloaded(QNetworkReply* pReply);

private:
	QNetworkAccessManager* m_WebCtrl;
	QByteArray m_DownloadedData;
	QUrl url;
};

#endif // FILEDOWNLOADER_H