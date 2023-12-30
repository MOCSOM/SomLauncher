#include "DownloadInfo.h"

DownloadInfo::DownloadInfo(const std::string& url, const std::string& sha1, int size)
	: url(url), sha1(sha1), size(size)
{
}

const std::string& DownloadInfo::getUrl() const
{
	return this->url;
}

const std::string& DownloadInfo::getSha1() const
{
	return this->sha1;
}

const int& DownloadInfo::getSize() const
{
	return this->size;
}

bool DownloadInfo::validateChecksum(const std::string& file_path, bool default_value) const
{
	if (this->sha1.empty())
	{
		return default_value;
	}

	std::ifstream file(file_path, std::ios::binary);
	if (!file)
	{
		return false;
	}

	SHA1 sha_context;
	sha_context.update(file);

	std::string hash = sha_context.final();
	file.close();

	return hash == this->sha1;
}