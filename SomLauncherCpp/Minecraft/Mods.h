#ifndef MODS_H_
#define MODS_H_

#include <filesystem>
#include <memory> // for shared_ptr and unique_ptr

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../../MocJsonLib/SomJson.h"
#include "../../SomAdditionalsLib/Additionals.h"
#include "../Archives/Archives.h"

namespace MinecraftCpp
{
	namespace modpacks
	{
		namespace download
		{
			namespace manual
			{
				/// <summary>
				/// Скачивает моды архивом и распаковывает по пути
				/// </summary>
				/// <param name="archive_url">- url архива с модами</param>
				/// <param name="path">- путь куда распоковывать</param>
				/// <param name="callback">- callback</param>
				/// <returns>true - если всё нормально
				/// false - если произошла ошибка</returns>
				bool installModPackManualy(const std::string& archive_url, const std::filesystem::path& path,
					std::unique_ptr<CallbackNull> callback = std::make_unique<CallbackNull>()) noexcept;
			}
			namespace database
			{
				bool installModPack(
					const Json::JsonValue& json_from_server, const std::filesystem::path& path_to_download,
					std::unique_ptr<CallbackNull> callback = std::make_unique<CallbackNull>()) noexcept;
			}
		}

		namespace deletemods
		{
			bool deleteSingleMod(const std::filesystem::path& mod_path) noexcept;
			bool deleteAllMods(const std::filesystem::path& directory_mods_path) noexcept;
		}
	}
}

#endif /*MODS_H_*/