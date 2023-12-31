#include "AssetIndexInfo.h"

AssetIndexInfo::AssetIndexInfo()
	: IdDownloadInfo("", ""), total_size(0)
{
}

AssetIndexInfo::AssetIndexInfo(const std::string& id, const std::string& url, const std::string& sha1, int size, long total_size)
	: IdDownloadInfo(id, url, sha1, size), total_size(total_size)
{
}

const long& AssetIndexInfo::getTotalSize() const
{
	return this->total_size;
}

//bool AssetIndexInfo::empty() const
//{
//	return this->total_size == 0;
//}
