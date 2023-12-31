#ifndef GAME_ASSETINDEXINFO_H_
#define GAME_ASSETINDEXINFO_H_

#include <string>

#include "IdDownloadInfo.h"

class AssetIndexInfo : public IdDownloadInfo
{
private:
	long total_size;

public:
	AssetIndexInfo();
	AssetIndexInfo(const std::string& id, const std::string& url, const std::string& sha1 = "", int size = 0, long total_size = 0);
	~AssetIndexInfo() = default;

public:
	const long& getTotalSize() const;

	//public:
	//	bool empty() const;
};

#endif // !GAME_ASSETINDEXINFO_H_