#ifndef LIBRARYDOWNLOADINFO_H_
#define LIBRARYDOWNLOADINFO_H_

#include <string>

#include "DownloadInfo.h"

class LibraryDownloadInfo : public DownloadInfo
{
public:
	LibraryDownloadInfo() {}

	LibraryDownloadInfo(const std::string& path) : path(path) {}

	LibraryDownloadInfo(const std::string& path, const std::string& url) : DownloadInfo(url), path(path) {}

	LibraryDownloadInfo(const std::string& path, const std::string& url, const std::string& sha1) : DownloadInfo(url, sha1), path(path) {}

	LibraryDownloadInfo(const std::string& path, const std::string& url, const std::string& sha1, int size) : DownloadInfo(url, sha1, size), path(path) {}

	const std::string& getPath() const {
		return path;
	}

	bool empty() const {
		return path.empty();
	}

private:
	std::string path;
};

#endif // !LIBRARYDOWNLOADINFO_H_