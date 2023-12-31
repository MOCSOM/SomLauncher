#ifndef VERSION_H_
#define VERSION_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <sstream>
#include <variant>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>

#include "Game/Library.h"
#include "Game/DownloadType.h"
#include "Game/DownloadInfo.h"
#include "Game/LoggingInfo.h"
#include "Game/GameJavaVersion.h"
#include "Game/Command/Arguments.h"
#include "Utils/Validation.h"
#include "Minecraftus.h"
#include "Game/ReleaseType.h"
#include "Game/AssetIndexInfo.h"
#include "Utils/Constants.h"
#include "Game/VersionProvider.h"

#undef max

class Version : public Validation
{
private:
	bool resolved;
	std::string id;
	std::string version;
	int priority;
	std::string minecraft_arguments;
	Arguments arguments;
	std::string main_class;
	std::string inherits_from;
	std::string jar;
	AssetIndexInfo asset_index;
	std::string assets;
	int compliance_level;
	GameJavaVersion java_version;
	std::vector<Library> libraries;
	std::vector<CompatibilityRule> compatibility_rules;
	std::unordered_map<DownloadType, DownloadInfo> downloads;
	std::unordered_map<DownloadType, LoggingInfo> logging;
	ReleaseType type;
	boost::posix_time::ptime time;
	boost::posix_time::ptime release_time;
	int minimum_launcher_version;
	bool hidden;
	bool root;
	std::vector<Version> patches;

private:
	bool resolved;

public:
	Version() = default;
	Version(const std::string& id);
	Version(const std::string& id, const std::string& version, int priority,
		Arguments arguments, const std::string& mainClass, std::vector<Library> libraries);
	Version(bool resolved, const std::string& id, const std::string& version,
		int priority, const std::string& minecraft_arguments, const Arguments& arguments,
		const std::string& main_class, const std::string& inherits_from, const std::string& jar,
		const AssetIndexInfo& asset_index, const std::string& assets, int compliance_level,
		const GameJavaVersion& java_version, const std::vector<Library>& libraries,
		const std::vector<CompatibilityRule>& compatibility_rules, const std::string& type, const std::string& time,
		const std::string& release_time, int minimum_launcher_version, bool hidden,
		bool root, const std::vector<Version>& patches);
	Version(bool resolved, const std::string& id, const std::string& version,
		int priority, const std::string& minecraft_arguments, const Arguments& arguments,
		const std::string& main_class, const std::string& inherits_from, const std::string& jar,
		const AssetIndexInfo& asset_index, const std::string& assets, int compliance_level,
		const GameJavaVersion& java_version, const std::vector<Library>& libraries,
		const std::vector<CompatibilityRule>& compatibility_rules,
		const std::unordered_map<DownloadType, DownloadInfo>& downloads,
		const std::unordered_map<DownloadType, LoggingInfo>& logging, const ReleaseType& type, const boost::posix_time::ptime& time,
		const boost::posix_time::ptime& release_time, int minimum_launcher_version, bool hidden,
		bool root, const std::vector<Version>& patches);
	~Version() = default;

public:
	const std::string& getMinecraftArguments() const;
	const Arguments& getArguments() const;
	const std::string& getMainClass() const;
	const boost::posix_time::ptime& getTime() const;
	const std::string& getId() const;
	const std::string& getVersion() const;
	const int& getPriority() const;
	const ReleaseType& getType() const;
	const boost::posix_time::ptime& getReleaseTime() const;
	const std::string& getJar() const;
	const std::string& getInheritsFrom() const;
	const int& getMinimumLauncherVersion() const;
	const int& getComplianceLevel() const;
	const GameJavaVersion& getJavaVersion() const;
	const bool& isHidden() const;
	const bool& isRoot() const;
	const bool& isResolved() const;
	const bool& isResolvedPreservingPatches() const;
	const std::vector<Version>& getPatches() const;
	const std::unordered_map<DownloadType, LoggingInfo>& getLogging() const;
	const std::vector<Library>& getLibraries() const;
	const std::vector<CompatibilityRule>& getCompatibilityRules() const;
	const std::unordered_map<DownloadType, DownloadInfo>& getDownloads() const;
	const DownloadInfo& getDownloadInfo() const;
	const AssetIndexInfo& getAssetIndex() const;

public:
	bool appliesToCurrentEnvironment() const;
	Version resolve(const VersionProvider& provider) const;

protected:
	Version merge(const Version& parent, bool is_patch) const;
	Version resolve(const VersionProvider& provider, std::set<std::string>& resolved_so_far) const;

private:
	Version toPatch() const;

public:
	Version resolvePreservingPatches(const VersionProvider& provider) const;

protected:
	Version mergePreservingPatches(const Version& parent) const;
	Version resolvePreservingPatches(const VersionProvider& provider, std::set<std::string>& resolvedSoFar) const;

private:
	Version markAsResolved() const;

public:
	Version markAsUnresolved() const;

private:
	Version setHidden(bool hidden) const;
	Version setId(const std::string& id) const;
	Version setVersion(const std::string& version) const;
	Version setPriority(int priority) const;
	Version setMinecraftArguments(const std::string& minecraft_arguments) const;
	Version setArguments(const Arguments& arguments) const;
	Version setMainClass(const std::string& mainClass) const;
	Version setInheritsFrom(const std::string& inheritsFrom) const;
	Version setJar(const std::string& jar) const;
	Version setLibraries(const std::vector<Library>& libraries) const;
	Version setLogging(const std::unordered_map<DownloadType, LoggingInfo>& logging) const;
	Version setPatches(const std::vector<Version>& patches) const;

public:
	Version addPatch(std::initializer_list<Version> additional) const;
	Version addPatches(const std::vector<Version>& additional) const;
	Version clearPatches() const;
	Version removePatchById(const std::string& patch_id) const;
	bool hasPatch(const std::string& patch_id) const;

public:
	int hashCode() const;

public:
	std::string toString() const;

public:
	// Унаследовано через Validation
	void validate() override;
};

#endif // !VERSION_H_