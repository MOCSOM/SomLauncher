#ifndef GAME_IDDOWNLOADINFO_H_
#define GAME_IDDOWNLOADINFO_H_

#include <string>

#include "DownloadInfo.h"

class IdDownloadInfo : public DownloadInfo
{
private:
	std::string id;

public:
	IdDownloadInfo(const std::string& id = "", const std::string& url = "", const std::string& sha1 = "", int size = 0);
	~IdDownloadInfo();

public:
	const std::string& getId();

public:
	// Унаследовано через DownloadInfo
	void validate() override;

};

#endif // !GAME_IDDOWNLOADINFO_H_
