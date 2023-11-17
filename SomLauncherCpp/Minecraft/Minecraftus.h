#ifndef MINECRAFTUS_H_     // equivalently, #if !defined HEADER_H_
#define MINECRAFTUS_H_

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../../MocJsonLib/SomJson.h"
#include "../../SomAdditionalsLib/Additionals.h"
#include "../Hashes/sha1.h"
#include "../Exceptions/FileOutsideMinecraftDirectoryException.h"
#include "CommandBuilder.h"
#include "MinecraftOptions.h"
#include "Utils/StringUtils.h"
#include "Game/Arguments.h"
#include "Utils/Auth/AuthInfo.h"
#include "Game/RuledArgument.h"
#include "Game/CompatibilityRule.h"
#include "Version.h"
#include "Utils/Lang.h"
#include "NativesInstaller.h"
#include "../Client/StartProcess.h"

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

namespace MinecraftCpp
{
	namespace option
	{
		struct MinecraftOptions
		{
			MinecraftOptions() {}
			~MinecraftOptions() {}

			std::string username = "";
			std::string uuid = "";
			std::string token = "";
			std::string executablePath = "";
			std::string jvmArguments = "";
			std::string launcherName = "";
			std::string launcherVersion = "";
			std::string gameDirectory = "";
			bool		demo = NULL;
			bool		customResolution = NULL;
			std::string resolutionWidth = "";
			std::string resolutionHeight = "";
			std::string server = "";
			std::string port = "";
			std::string nativesDirectory = "";
			bool		enableLoggingConfig = NULL;
			std::string classpath = "";
			std::string NULLES = "";
			ProcessPriority process_priority = NORMAL;

			// get (поле, стандарт)
			std::string get(const std::string& param, const std::string& writ = "");
			bool get(const std::string& param, bool writ = NULL);
			bool is_exist(const std::string& param);
		};
	}

	Json::JsonValue get_version_list();

	std::vector<std::string> generateCommandLine(const std::filesystem::path& nativeFolder, MinecraftCpp::option::LaunchOptions& options);

	std::vector<std::string> get_minecraft_command__(
		const std::string& version,
		const std::string& minecraft_directory,
		MinecraftCpp::option::MinecraftOptions options);

	std::string get_classpath_separator();
	bool parse_single_rule(Json::JsonValue rule, MinecraftCpp::option::MinecraftOptions options);
	bool parse_rule_list(Json::JsonValue data, const std::string& rule_string, MinecraftCpp::option::MinecraftOptions options);
	std::string get_library_path(const std::string& name, const std::string& path);
	std::string get_natives(Json::JsonValue data);
	std::string _get_jvm_platform_string();
	std::string replace_arguments(std::string argstr, Json::JsonValue versionData,
		const std::string& path, MinecraftCpp::option::MinecraftOptions options);

	std::string get_executable_path(const std::string& jvm_version, const std::string& minecraft_directory);
	bool install_libraries(Json::JsonValue data, const std::string& path, CallbackNull* callback);
	bool extract_natives_file(const std::string& filename, const std::string& extract_path, Json::JsonValue extract_data);
	bool install_assets(Json::JsonValue data, const std::string& path, CallbackNull* callback);

	/// <summary>
	/// Installs the given jvm runtime. callback is the same dict as in the install module.
	/// </summary>
	/// <param name="jvm_version">- The Name of the JVM version</param>
	/// <param name="minecraft_directory">- The path to your Minecraft directory</param>
	/// <param name="callback">- the same dict as for :func:`~minecraft_launcher_lib.install.install_minecraft_version`</param>
	/// <returns>void</returns>
	bool install_jvm_runtime(const std::string& jvm_version, const std::string& minecraft_directory,
		CallbackNull* callback = new CallbackNull());

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
		bool install_forge_version(const std::string& versionid, const std::string& path,
			CallbackNull* callback = new CallbackNull(), const std::string& java = "");

		bool extract_file(const QZipReader& handler, const std::string& zip_path, const std::string& extract_path);
		std::string get_data_library_path(const std::string& libname, const std::string& path);
		std::string get_jar_mainclass(const std::string& path);

		bool forge_processors(
			Json::JsonValue data,
			const std::string& minecraft_directory,
			const std::string& lzma_path,
			const std::string& installer_path,
			CallbackNull* callback,
			const std::string& java);
	}

	namespace fabric
	{
		int install_fabric_version(const std::string& minecraft_version, const std::string& minecraft_directory,
			const std::string& loader_version = "", CallbackNull* callback = new CallbackNull(), const std::string& java = "");

		bool _is_version_valid(const std::string& version, const std::string& minecraft_directory);
		bool _is_minecraft_version_supported(const std::string& version);
		Json::JsonValue get_all_minecraft_versions();
		std::string get_latest_loader_version();
		Json::JsonValue get_all_loader_versions();
		std::string get_latest_installer_version();
		Json::JsonValue parse_maven_metadata(const std::string& url);
	}

	std::string get_arguments(
		Json::JsonValue& data,
		Json::JsonValue versionData,
		const std::string& path,
		MinecraftCpp::option::MinecraftOptions options);

	std::string get_arguments_string(
		Json::JsonValue versionData,
		const std::string& path,
		MinecraftCpp::option::MinecraftOptions options);

	bool install_minecraft_version(
		const std::string& versionid,
		const std::string& minecraft_directory,
		CallbackNull* callback = new CallbackNull());

	bool do_version_install(
		const std::string& versionid,
		const std::string& path,
		CallbackNull* callback,
		const std::string& url = "");

	Json::JsonValue inherit_json(
		Json::JsonValue original_data,
		const std::string& path);

	std::string get_libraries(
		Json::JsonValue data,
		const std::string& path);

	std::chrono::system_clock::time_point _parseDateTime(const std::string& isoDateTime);
}

#endif  /*MINECRAFTUS_H_*/