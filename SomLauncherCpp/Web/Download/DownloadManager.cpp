#include "DownloadManager.h"

DownloadManager::DownloadManager(const std::filesystem::path& download_path, QObject* parent)
	: QObject(parent), download_path(download_path), downloader(nullptr)
{
}

void DownloadManager::saveFile()
{
	QFile new_file(this->download_path);
	new_file.write(this->downloader->downloadedData());
}

bool DownloadManager::downloadFile(const QUrl& url)
{
	this->downloader = new FileDownloader(url, this);

	connect(this->downloader, &FileDownloader::downloaded, this, &DownloadManager::saveFile);
	this->downloader->download();
	return false;
}
