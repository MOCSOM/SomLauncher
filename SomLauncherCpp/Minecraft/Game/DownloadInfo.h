#ifndef DOWNLOADINFO_H_
#define DOWNLOADINFO_H_

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "../../../Hashes/sha1.h"
#include "../Utils/Validation.h"

class DownloadInfo : public Validation {
public:
	DownloadInfo() {}
	DownloadInfo(const std::string& url) : url(url), sha1(""), size(0) {}
	DownloadInfo(const std::string& url, const std::string& sha1) : url(url), sha1(sha1), size(0) {}
	DownloadInfo(const std::string& url, const std::string& sha1, int size) : url(url), sha1(sha1), size(size) {}

	const std::string& getUrl() const {
		return url;
	}

	const std::string& getSha1() const {
		return sha1;
	}

	int getSize() const {
		return size;
	}

	bool validateChecksum(const std::string& filePath, bool defaultValue) const {
		if (sha1.empty()) {
			return defaultValue;
		}

		std::ifstream file(filePath, std::ios::binary);
		if (!file) {
			return false;
		}

		SHA1 shaContext;
		shaContext.update(file);

		std::string hash = shaContext.final();
		file.close();

		return hash == sha1;
	}

private:
	std::string url;
	std::string sha1;
	int size;
};

#endif // !DOWNLOADINFO_H_
