#ifndef LIBRARYDOWNLOADINFO_H_
#define LIBRARYDOWNLOADINFO_H_

#include <string>

#include "DownloadInfo.h"

class LibraryDownloadInfo : public DownloadInfo
{
private:
	std::string path;

public:
	LibraryDownloadInfo() = default;
	LibraryDownloadInfo(const std::string& path);
	LibraryDownloadInfo(const std::string& path, const std::string& url, const std::string& sha1 = "", int size = 0);
	~LibraryDownloadInfo() = default;

public:
	const std::string& getPath() const;

public:
	bool empty() const;
};

#endif // !LIBRARYDOWNLOADINFO_H_