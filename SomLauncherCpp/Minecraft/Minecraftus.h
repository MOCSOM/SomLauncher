﻿#ifndef MINECRAFTUS_H_     // equivalently, #if !defined HEADER_H_
#define MINECRAFTUS_H_

#include <QMessageBox>
#include <QUrlQuery>

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../Json/SomJson.h"
#include "../Additionals/Additionals.h"
#include "../Encryption/Hashes/sha1.h"
#include "../Exceptions/FileOutsideMinecraftDirectoryException.h"
//#include "CommandBuilder.h"
#include "MinecraftOptions.h"
//#include "Utils/StringUtils.h"
//#include "Game/Arguments.h"
//#include "Utils/Auth/AuthInfo.h"
//#include "Game/RuledArgument.h"
//#include "Game/CompatibilityRule.h"
//#include "Version.h"
//#include "Utils/Lang.h"
#include "NativesInstaller.h"
#include "../Client/StartProcess.h"
#include "../Callbacks/QCallback.h"
#include "../Web/Utils/WebUtils.h"

#include <initializer_list>
//#include <stdio.h>

#include <filesystem>

//#include "../Archives/qzipreader_p.h"
//#include "../Archives/qzipwriter_p.h"

#include <qdir.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <regex>
#include <set>

#include <nlohmann/json.hpp>

namespace MinecraftCpp
{
	namespace option
	{
		struct MinecraftOptions
		{
			MinecraftOptions() {}
			~MinecraftOptions() {}

			std::wstring username = L"";
			std::string uuid = "";
			std::string token = "";
			std::filesystem::path executablePath = "";
			std::string jvmArguments = "";
			std::string launcherName = "";
			std::string launcherVersion = "";
			std::filesystem::path gameDirectory = "";
			bool		demo = NULL;
			bool		customResolution = NULL;
			std::string resolutionWidth = "";
			std::string resolutionHeight = "";
			std::string server = "";
			std::string port = "";
			std::filesystem::path nativesDirectory = "";
			bool		enableLoggingConfig = NULL;
			std::wstring classpath = L"";
			std::string NULLES = "";
			ProcessPriority process_priority = NORMAL;

			// get (поле, стандарт)
			std::string get(const std::string& param, const std::string& writ = "") const;
			bool get(const std::string& param, bool writ = NULL) const;
			bool is_exist(const std::string& param);
		};
	}

	SJson::JsonValue get_version_list();

	std::vector<std::string> generateCommandLine(const std::filesystem::path& nativeFolder, MinecraftCpp::option::LaunchOptions& options);

	std::vector<std::variant<std::string, std::filesystem::path, std::wstring>> get_minecraft_command__(
		const std::string& version,
		const std::filesystem::path& minecraft_directory,
		MinecraftCpp::option::MinecraftOptions options);

	std::string get_classpath_separator();
	std::wstring getWClasspathSeparator();
	bool parse_single_rule(nlohmann::json rule, MinecraftCpp::option::MinecraftOptions options);
	bool parse_rule_list(nlohmann::json data, const std::string& rule_string, MinecraftCpp::option::MinecraftOptions options);
	std::filesystem::path get_library_path(const std::string& name, const std::filesystem::path& path);
	std::filesystem::path getLibraryPath(const std::wstring& name, const std::filesystem::path& path);
	std::string get_natives(nlohmann::json data);
	std::string _get_jvm_platform_string();
	std::string replace_arguments(std::string argstr, nlohmann::json versionData,
		const std::filesystem::path& path, MinecraftCpp::option::MinecraftOptions options);
	std::wstring replace_arguments(std::wstring argstr, nlohmann::json versionData,
		const std::filesystem::path& path, MinecraftCpp::option::MinecraftOptions options);

	std::filesystem::path get_executable_path(const std::string& jvm_version, const std::filesystem::path& minecraft_directory);
	bool install_libraries(nlohmann::json& data, const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback);
	bool extract_natives_file(const std::filesystem::path& filename, const std::filesystem::path& extract_path, nlohmann::json& extract_data);
	bool install_assets(nlohmann::json& data, const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback);

	/// <summary>
	/// Installs the given jvm runtime. callback is the same dict as in the install module.
	/// </summary>
	/// <param name="jvm_version">- The Name of the JVM version</param>
	/// <param name="minecraft_directory">- The path to your Minecraft directory</param>
	/// <param name="callback">- the same dict as for :func:`~minecraft_launcher_lib.install.install_minecraft_version`</param>
	/// <returns>void</returns>
	bool install_jvm_runtime(const std::string& jvm_version, const std::string& minecraft_directory,
		std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>());

	/// <summary>
	/// Raises a FileOutsideMinecraftDirectory if the Path is not in the given Directory
	/// </summary>
	/// <param name="minecraft_directory"></param>
	/// <param name="path"></param>
	/// <returns></returns>
	void check_path_inside_minecraft_directory(const std::string& minecraft_directory, const std::string& path);

	/// <summary>
	/// Calculate the sha1 checksum of a file
	/// Source: https://stackoverflow.com/questions/22058048/hashing-a-file-in-python
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	std::string get_sha1_hash(const std::filesystem::path& path);

	namespace forge
	{
		bool install_forge_version(const std::string& versionid, const std::filesystem::path& path,
			std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>(), const std::filesystem::path& java = "");

		bool extract_file(const QZipReader& handler, const std::string& zip_path, const std::filesystem::path& extract_path);
		std::filesystem::path get_data_library_path(const std::string& libname, const std::filesystem::path& path);
		std::string get_jar_mainclass(const std::filesystem::path& path);

		bool forge_processors(
			nlohmann::json& data,
			const std::filesystem::path& minecraft_directory,
			const std::filesystem::path& lzma_path,
			const std::filesystem::path& installer_path,
			std::shared_ptr<CallbackNull> callback,
			const std::filesystem::path& java);
	}

	namespace fabric
	{
		int install_fabric_version(const std::string& minecraft_version, const std::filesystem::path& minecraft_directory,
			const std::string& loader_version = "", std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>(),
			const std::filesystem::path& java = "");

		bool _is_version_valid(const std::string& version, const std::string& minecraft_directory);
		bool _is_minecraft_version_supported(const std::string& version);
		SJson::JsonValue get_all_minecraft_versions();
		std::string get_latest_loader_version();
		SJson::JsonValue get_all_loader_versions();
		std::string get_latest_installer_version();
		SJson::JsonValue parse_maven_metadata(const std::string& url);
	}

	std::vector<std::wstring> get_arguments(
		nlohmann::json& data,
		nlohmann::json versionData,
		const std::filesystem::path& path,
		MinecraftCpp::option::MinecraftOptions options);

	std::string get_arguments_string(
		nlohmann::json versionData,
		const std::filesystem::path& path,
		MinecraftCpp::option::MinecraftOptions options);

	bool install_minecraft_version(
		const std::string& versionid,
		const std::filesystem::path& minecraft_directory,
		std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>());

	bool do_version_install(
		const std::string& versionid,
		const std::filesystem::path& path,
		std::shared_ptr<CallbackNull> callback,
		const std::string& url = "");

	nlohmann::json inherit_json(
		nlohmann::json original_data,
		const std::filesystem::path& path);

	std::wstring get_libraries(
		nlohmann::json data,
		const std::filesystem::path& path);

	std::chrono::system_clock::time_point _parseDateTime(const std::string& isoDateTime);
}

#endif  /*MINECRAFTUS_H_*/