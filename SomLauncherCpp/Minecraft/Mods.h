#ifndef MODS_H_
#define MODS_H_

#include <filesystem>

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../../SomJsonLib/SomJson.h"
#include "../../SomAdditionalsLib/Additionals.h"

namespace MinecraftCpp
{
	namespace modpacks
	{
		bool installModPack(Json::JsonValue json_from_server, const std::string& path, CallbackNull* callback = new CallbackNull());
		bool deleteSingleMod(const std::string& mod_path);
		bool deleteAllMods(const std::string& directory_mods_path);
	}
}

#endif /*MODS_H_*/