#include "Mods.h"

bool MinecraftCpp::modpacks::installModPack(Json::JsonValue json_from_server, const std::string& path, CallbackNull* callback)
{
	return false;
}

bool MinecraftCpp::modpacks::deleteSingleMod(const std::string& mod_path)
{
	try
	{
		std::filesystem::remove(mod_path);

		return true;
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		std::cout << "what():  " << ex.what() << std::endl
			<< "path1(): " << ex.path1() << std::endl
			<< "path2(): " << ex.path2() << std::endl
			<< "code().value():    " << ex.code().value() << std::endl
			<< "code().message():  " << ex.code().message() << std::endl
			<< "code().category(): " << ex.code().category().name() << std::endl;

		return false;
	}


}

bool MinecraftCpp::modpacks::deleteAllMods(const std::string& directory_mods_path)
{
	std::string folder_path = directory_mods_path;

	std::filesystem::path dir_path(folder_path);

	if (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(folder_path))
		{
			if (std::filesystem::is_regular_file(entry))
			{
				deleteSingleMod(entry.path().string());
			}
		}
	}
	else
	{
		std::cerr << "Не удалось открыть папку." << std::endl;

		return false;
	}

	return true;
}
