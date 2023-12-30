#include "LibraryDownloadInfo.h"

LibraryDownloadInfo::LibraryDownloadInfo(const std::string& path)
	: path(path)
{
}

LibraryDownloadInfo::LibraryDownloadInfo(const std::string& path, const std::string& url, const std::string& sha1, int size)
	: DownloadInfo(url, sha1, size), path(path)
{
}

const std::string& LibraryDownloadInfo::getPath() const
{
	return this->path;
}

bool LibraryDownloadInfo::empty() const
{
	return this->path.empty();
}