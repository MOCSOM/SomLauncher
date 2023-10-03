#ifndef MODS_H_
#define MODS_H_

#include <filesystem>
#include <memory> // for shared_ptr and unique_ptr

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../../SomJsonLib/SomJson.h"
#include "../../SomAdditionalsLib/Additionals.h"
#include "../Archives/Archives.h"

namespace MinecraftCpp
{
	namespace modpacks
	{
		bool installModPack(Json::JsonValue json_from_server, const std::filesystem::path& path,
			std::unique_ptr<CallbackNull> callback = std::make_unique<CallbackNull>()) noexcept;

		bool deleteSingleMod(const std::filesystem::path& mod_path) noexcept;
		bool deleteAllMods(const std::filesystem::path& directory_mods_path) noexcept;

		bool installModPackManualy(const std::string& archive_url, const std::filesystem::path& path,
			std::unique_ptr<CallbackNull> callback = std::make_unique<CallbackNull>()) noexcept;
	}
}

#endif /*MODS_H_*/