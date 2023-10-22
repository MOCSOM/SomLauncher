#include "Mods.h"

bool MinecraftCpp::modpacks::download::database::installModPack(const Json::JsonValue& json_from_server,
	const std::filesystem::path& path_to_download, std::unique_ptr<CallbackNull> callback) noexcept
{
	Json::JsonValue urls = json_from_server;
	for (std::pair<const std::string, Json::JsonValue> elem : urls.get_object())
	{
		std::string downloaded_path = DownloadFile(elem.second.to_string(),
			path_to_download.u8string(), callback.get());
	}

	return true;
}

bool MinecraftCpp::modpacks::deletemods::deleteSingleMod(const std::filesystem::path& mod_path) noexcept
{
	try
	{
		std::filesystem::remove(mod_path);

		return true;
	}
	catch (const std::filesystem::filesystem_error& ex)
	{
		std::cerr
			<< "what:  " << ex.what() << std::endl
			<< "path1: " << ex.path1() << std::endl
			<< "path2: " << ex.path2() << std::endl
			<< "code.value:    " << ex.code().value() << std::endl
			<< "code.message:  " << ex.code().message() << std::endl
			<< "code.category: " << ex.code().category().name() << std::endl;

		return false;
	}
}

bool MinecraftCpp::modpacks::deletemods::deleteAllMods(const std::filesystem::path& directory_mods_path) noexcept
{
	std::string folder_path = directory_mods_path.string();

	std::filesystem::path dir_path(folder_path);

	if (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(folder_path))
		{
			if (std::filesystem::is_regular_file(entry))
			{
				deleteSingleMod(entry.path());
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

bool MinecraftCpp::modpacks::download::manual::installModPackManualy(const std::string& archive_url,
	const std::filesystem::path& path, std::unique_ptr<CallbackNull> callback) noexcept
{
	std::string downloaded_arhcive_path = DownloadFile(archive_url,
		Additionals::TempFile::get_tempdir_SYSTEM(), callback.get());
	if (downloaded_arhcive_path == "")
	{
		return false;
	}

	callback->OnProgress(0, 1, NULL, L"Start extracting archive");
	callback->OnProgress(0, 1, 6, NULL);

	QZipReader archive(downloaded_arhcive_path.c_str());
	Additionals::archives::decompressArchive(archive, path.string());

	callback->OnProgress(1, 1, NULL, L"Extracting archive completed");
	callback->OnProgress(1, 1, 6, NULL);

	return true;
}