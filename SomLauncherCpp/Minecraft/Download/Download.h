#ifndef DOWNLOAD_DOWNLOAD_H_
#define DOWNLOAD_DOWNLOAD_H_

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QThreadPool>

#include "DownloadEntry.h"
#include "DownloadHelper.h"
#include "../Utils/Crypto.h"

class Download
{
	Q_OBJECT

private:
	QNetworkAccessManager mNetwork;

public:
	void installPackage(const QUrl& url);
};

#endif // !DOWNLOAD_DOWNLOAD_H_