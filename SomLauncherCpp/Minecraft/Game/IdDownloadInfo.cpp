#include "IdDownloadInfo.h"

IdDownloadInfo::IdDownloadInfo(const std::string& id, const std::string& url, const std::string& sha1, int size)
	: DownloadInfo(url, sha1, size), id(id)
{
}

IdDownloadInfo::~IdDownloadInfo()
{
}

const std::string& IdDownloadInfo::getId()
{
	return this->id;
}

void IdDownloadInfo::validate()
{
	if (this->id.empty() || this->id == "")
	{
		throw JsonParseException("IdDownloadInfo id can not be null");
	}
}
