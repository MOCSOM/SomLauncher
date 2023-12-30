#ifndef VERSION_H_
#define VERSION_H_

#include <string>
#include <map>
#include <vector>
#include <optional>
#include <rpcdce.h>

#pragma comment(lib, "rpcrt4.lib")

#include "Game/Library.h"
#include "Game/Command/Arguments.h"
#include "Utils/Validation.h"
#include "Minecraftus.h"

class Version : public Validation {
public:
	bool resolved;
	std::string id;
	std::string version;
	int priority;
	std::string minecraftArguments;
	Arguments arguments;
	std::string mainClass;
	std::string inheritsFrom;
	std::string jar;
	std::string assetIndex;
	std::string assets;
	int complianceLevel;
	std::string javaVersion;
	std::vector<Library> libraries;
	std::vector<CompatibilityRule> compatibilityRules;
	/*std::map<DownloadType, DownloadInfo> downloads;
	std::map<DownloadType, LoggingInfo> logging;*/
	std::string type;
	std::string time;
	std::string releaseTime;
	int minimumLauncherVersion;
	bool hidden;
	bool root;
	std::vector<Version> patches;

	Version(bool resolved, const std::string& id, const std::string& version, int priority, const std::string& minecraftArguments, const Arguments& arguments, const std::string& mainClass, const std::string& inheritsFrom, const std::string& jar, const std::string& assetIndex, const std::string& assets, int complianceLevel, const std::string& javaVersion, const std::vector<Library>& libraries, const std::vector<CompatibilityRule>& compatibilityRules, const std::string& type, const std::string& time, const std::string& releaseTime, int minimumLauncherVersion, bool hidden, bool root, const std::vector<Version>& patches)
		: resolved(resolved), id(id), version(version), priority(priority), minecraftArguments(minecraftArguments), arguments(arguments), mainClass(mainClass), inheritsFrom(inheritsFrom), jar(jar), assetIndex(assetIndex), assets(assets), complianceLevel(complianceLevel), javaVersion(javaVersion), libraries(libraries), compatibilityRules(compatibilityRules), type(type), time(time), releaseTime(releaseTime), minimumLauncherVersion(minimumLauncherVersion), hidden(hidden), root(root), patches(patches)
	{
	}

	Version() = default;

	static std::string get_classpath_separator()
	{
		/*
		Returns the classpath seperator for the current os
		*/
		if (OS == "windows")
		{
			return ";";
		}
		else
		{
			return ":";
		}
	}

	static std::map<std::string, std::string> getConfigurations(const AuthInfo& authInfo, const MinecraftCpp::option::LaunchOptions& options, const std::filesystem::path& repository, const Version& version) {
		std::map<std::string, std::string> configurations;

		/*std::string guid(authInfo.getUUID().begin(), authInfo.getUUID().end());

		configurations["${auth_player_name}"] = authInfo.getUsername();
		configurations["${auth_session}"] = authInfo.getAccessToken();
		configurations["${auth_access_token}"] = authInfo.getAccessToken();
		configurations["${auth_uuid}"] = guid;
		configurations["${version_name}"] = std::optional(options.versionName).value_or(version.id);
		configurations["${profile_name}"] = std::optional(options.profileName).value_or("Minecraft");
		configurations["${version_type}"] = std::optional(options.versionType).value_or(version.type);
		configurations["${game_directory}"] = repository.u8string() + "\\" + version.id;
		configurations["${user_type}"] = authInfo.getUserType();
		configurations["${assets_index_name}"] = version.assetIndex;
		configurations["${user_properties}"] = authInfo.getUserProperties();
		configurations["${resolution_width}"] = std::to_string(options.width);
		configurations["${resolution_height}"] = std::to_string(options.height);
		configurations["${library_directory}"] = repository.u8string() + "\\" + version.id + "\\" + "libraries";
		configurations["${classpath_separator}"] = get_classpath_separator();
		configurations["${primary_jar}"] = repository.u8string() + "\\" + version.id + "\\" + "versions" + "\\" + version.version + "\\" + version.version + ".jar";
		configurations["${language}"] = "en";*/

		// Дополнительные параметры, определенные HMCL
		/*configurations["${libraries_directory}"] = repository.getLibrariesDirectory(version).string();
		configurations["${file_separator}"] = "\\";
		configurations["${primary_jar_name}"] = FileUtils::getName(repository.getVersionJar(version).c_str());*/

		return configurations;
	}
};

#endif // !VERSION_H_