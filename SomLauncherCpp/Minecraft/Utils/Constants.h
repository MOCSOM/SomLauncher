#ifndef UTILS_CONSTATS_H_
#define UTILS_CONSTATS_H_

#include <string>

struct Constants
{
	static const std::string DEFAULT_LIBRARY_URL;
	static const std::string DEFAULT_VERSION_DOWNLOAD_URL;
	static const std::string DEFAULT_INDEX_URL;
};

const std::string Constants::DEFAULT_LIBRARY_URL = "https://libraries.minecraft.net/";
const std::string Constants::DEFAULT_VERSION_DOWNLOAD_URL = "https://bmclapi2.bangbang93.com/versions/";
const std::string Constants::DEFAULT_INDEX_URL = "https://launchermeta.mojang.com/mc-staging/assets/legacy/c0fd82e8ce9fbc93119e40d96d5a4e62cfa3f729/";

#endif // !UTILS_CONSTATS_H_
