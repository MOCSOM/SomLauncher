#include "Mods.h"

bool MinecraftCpp::modpacks::installModPack(Json::JsonValue json_from_server,
	const std::filesystem::path& path, std::unique_ptr<CallbackNull> callback) noexcept
{
	return false;
}

bool MinecraftCpp::modpacks::deleteSingleMod(const std::filesystem::path& mod_path) noexcept
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

bool MinecraftCpp::modpacks::deleteAllMods(const std::filesystem::path& directory_mods_path) noexcept
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

bool MinecraftCpp::modpacks::installModPackManualy(const std::string& archive_url,
	const std::filesystem::path& path, std::unique_ptr<CallbackNull> callback) noexcept
{
	std::string downloaded_arhcive_path = DownloadFile(archive_url,
		Additionals::TempFile::get_tempdir_SYSTEM(), callback.get());
	if (downloaded_arhcive_path == "")
	{
		return false;
	}

	callback->OnProgress(0, 1, NULL, L"Start extracting archive");

	QZipReader archive(downloaded_arhcive_path.c_str());
	Additionals::archives::decompressArchive(archive, path.string());

	callback->OnProgress(1, 1, NULL, L"Extracting archive completed");

	return true;
}