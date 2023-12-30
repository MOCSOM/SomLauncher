#ifndef DOWNLOADINFO_H_
#define DOWNLOADINFO_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "../../../Hashes/sha1.h"
#include "../Utils/Validation.h"

class DownloadInfo : public Validation
{
private:
	std::string url;
	std::string sha1;
	int size = 0;

public:
	DownloadInfo() = default;
	DownloadInfo(const std::string& url, const std::string& sha1 = "", int size = 0);

public:
	const std::string& getUrl() const;
	const std::string& getSha1() const;
	const int& getSize() const;

public:
	bool validateChecksum(const std::string& file_path, bool default_value) const;
};

#endif // !DOWNLOADINFO_H_
