#ifndef DOWNLOAD_DOWNLOADMANAGER_H_
#define DOWNLOAD_DOWNLOADMANAGER_H_

#include <QObject>
#include <QUrl>
#include <QFile>

#include "FileDownloader.h"

class DownloadManager : public QObject
{
	Q_OBJECT

public:
	DownloadManager(const std::filesystem::path& download_path, QObject* parent = nullptr);
	~DownloadManager() = default;

public:
	bool downloadFile(const QUrl& url);

public slots:
	void saveFile();

private:
	FileDownloader* downloader;
	std::filesystem::path download_path;
};

#endif // !DOWNLOAD_DOWNLOADMANAGER_H_
