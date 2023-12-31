#include "Version.h"

Version::Version(const std::string& id)
	: resolved(false), id(id), version(),
	priority(0), minecraft_arguments(), arguments(),
	main_class(), inherits_from(), jar(),
	asset_index(), assets(), compliance_level(0),
	java_version(), libraries(), compatibility_rules(),
	type(), time(), release_time(), minimum_launcher_version(),
	hidden(false), root(true), patches()
{
}

Version::Version(const std::string& id, const std::string& version, int priority,
	Arguments arguments, const std::string& mainClass, std::vector<Library> libraries)
	: resolved(false), id(id), version(),
	priority(priority), minecraft_arguments(), arguments(arguments),
	main_class(), inherits_from(), jar(),
	asset_index(), assets(), compliance_level(0),
	java_version(), libraries(libraries), compatibility_rules(),
	type(), time(), release_time(), minimum_launcher_version(),
	hidden(false), root(true), patches()
{
}

Version::Version(
	bool resolved,
	const std::string& id,
	const std::string& version,
	int priority,
	const std::string& minecraft_arguments,
	const Arguments& arguments,
	const std::string& main_class,
	const std::string& inherits_from,
	const std::string& jar,
	const AssetIndexInfo& asset_index,
	const std::string& assets,
	int compliance_level,
	const GameJavaVersion& java_version,
	const std::vector<Library>& libraries,
	const std::vector<CompatibilityRule>& compatibility_rules,
	const std::string& type,
	const std::string& time,
	const std::string& release_time,
	int minimum_launcher_version,
	bool hidden,
	bool root,
	const std::vector<Version>& patches)
	: resolved(resolved), id(id), version(version),
	priority(priority), minecraft_arguments(minecraft_arguments), arguments(arguments),
	main_class(main_class), inherits_from(inherits_from), jar(jar),
	asset_index(asset_index), assets(assets), compliance_level(compliance_level),
	java_version(java_version), libraries(libraries), compatibility_rules(compatibility_rules),
	type(type), time(boost::posix_time::time_from_string(time)), release_time(boost::posix_time::time_from_string(release_time)),
	minimum_launcher_version(minimum_launcher_version),
	hidden(hidden), root(root), patches(patches)
{
}

Version::Version(bool resolved, const std::string& id, const std::string& version,
	int priority, const std::string& minecraft_arguments, const Arguments& arguments,
	const std::string& main_class, const std::string& inherits_from, const std::string& jar,
	const AssetIndexInfo& asset_index, const std::string& assets, int compliance_level,
	const GameJavaVersion& java_version, const std::vector<Library>& libraries,
	const std::vector<CompatibilityRule>& compatibility_rules,
	const std::unordered_map<DownloadType, DownloadInfo>& downloads,
	const std::unordered_map<DownloadType, LoggingInfo>& logging, const ReleaseType& type, const boost::posix_time::ptime& time,
	const boost::posix_time::ptime& release_time, int minimum_launcher_version, bool hidden,
	bool root, const std::vector<Version>& patches)
	: resolved(resolved), id(id), version(version),
	priority(priority), minecraft_arguments(minecraft_arguments), arguments(arguments),
	main_class(main_class), inherits_from(inherits_from), jar(jar),
	asset_index(asset_index), assets(assets), compliance_level(compliance_level),
	java_version(java_version), libraries(libraries), compatibility_rules(compatibility_rules),
	downloads(downloads), logging(logging),
	type(type), time(time), release_time(release_time),
	minimum_launcher_version(minimum_launcher_version),
	hidden(hidden), root(root), patches(patches)
{
}

const std::string& Version::getMinecraftArguments() const
{
	return this->minecraft_arguments;
}

const Arguments& Version::getArguments() const
{
	return this->arguments;
}

const std::string& Version::getMainClass() const
{
	return this->main_class;
}

const boost::posix_time::ptime& Version::getTime() const
{
	return this->time;
}

const std::string& Version::getId() const
{
	return this->id;
}

const std::string& Version::getVersion() const
{
	return this->version;
}

const int& Version::getPriority() const
{
	return this->priority == 0 ? INT16_MIN : this->priority;
}

const ReleaseType& Version::getType() const
{
	return this->type.getId().empty() ? ReleaseType() : this->type;
}

const boost::posix_time::ptime& Version::getReleaseTime() const
{
	return this->release_time;
}

const std::string& Version::getJar() const
{
	return this->jar;
}

const std::string& Version::getInheritsFrom() const
{
	return this->inherits_from;
}

const int& Version::getMinimumLauncherVersion() const
{
	return this->minimum_launcher_version == 0 ? 0 : this->minimum_launcher_version; //from java cringe
}

const int& Version::getComplianceLevel() const
{
	return this->compliance_level;
}

const GameJavaVersion& Version::getJavaVersion() const
{
	return this->java_version;
}

const bool& Version::isHidden() const
{
	return this->hidden;
}

const bool& Version::isRoot() const
{
	return this->root;
}

const bool& Version::isResolved() const
{
	return this->resolved;
}

const bool& Version::isResolvedPreservingPatches() const
{
	return this->inherits_from.empty() && !this->resolved;
}

const std::vector<Version>& Version::getPatches() const
{
	return this->patches;
}

const std::unordered_map<DownloadType, LoggingInfo>& Version::getLogging() const
{
	return this->logging;
}

const std::vector<Library>& Version::getLibraries() const
{
	return this->libraries;
}

const std::vector<CompatibilityRule>& Version::getCompatibilityRules() const
{
	return this->compatibility_rules;
}

const std::unordered_map<DownloadType, DownloadInfo>& Version::getDownloads() const
{
	return this->downloads;
}

const DownloadInfo& Version::getDownloadInfo() const
{
	auto fount_iter = this->downloads.find(DownloadType::CLIENT);
	std::string jar_name = this->jar.empty() ? this->id : this->jar;

	if (fount_iter == this->downloads.end())
	{
		return DownloadInfo((boost::format("%s%s/%s.jar") % Constants::DEFAULT_VERSION_DOWNLOAD_URL % jar_name % jar_name).str());
	}
	else
	{
		return fount_iter->second;
	}
}

const AssetIndexInfo& Version::getAssetIndex() const
{
	std::string assets_id = this->assets.empty() ? "legacy" : this->assets;

	if (this->asset_index.empty())
	{
		return AssetIndexInfo(assets_id, Constants::DEFAULT_INDEX_URL + assets_id + ".json");
	}
	else
	{
		return this->asset_index;
	}
}

bool Version::appliesToCurrentEnvironment() const
{
	return CompatibilityRule::appliesToCurrentEnvironment(this->compatibility_rules);
}

Version Version::resolve(const VersionProvider& provider) const
{
	if (isResolved())
	{
		return *this;
	}
	std::set<std::string> ses;
	return resolve(provider, ses).markAsResolved();
}

Version Version::merge(const Version& parent, bool is_patch) const
{
	return Version(
		true,
		this->id,
		"",
		0,
		this->minecraft_arguments.empty() ? parent.minecraft_arguments : this->minecraft_arguments,
		Arguments::merge(parent.arguments, this->arguments),
		this->main_class.empty() ? parent.main_class : this->main_class,
		"", // inheritsFrom
		this->jar.empty() ? parent.jar : this->jar,
		this->asset_index.empty() ? parent.asset_index : this->asset_index,
		this->assets.empty() ? parent.assets : this->assets,
		this->compliance_level,
		this->java_version.empty() ? parent.java_version : this->java_version,
		Lang::merge(this->libraries, parent.libraries),
		Lang::merge(parent.compatibility_rules, this->compatibility_rules),
		this->downloads.empty() ? parent.downloads : this->downloads,
		this->logging.empty() ? parent.logging : logging,
		this->type.empty() ? parent.type : type,
		this->time.is_not_a_date_time() ? parent.time : this->time,
		this->release_time.is_not_a_date_time() ? parent.release_time : this->release_time,
		std::max<int>(this->minimum_launcher_version, parent.minimum_launcher_version),
		this->hidden,
		true,
		is_patch ? parent.patches : Lang::merge(Lang::merge(parent.patches, { toPatch() }), patches)
	);
}

Version Version::resolve(const VersionProvider& provider, std::set<std::string>& resolved_so_far) const
{
	Version this_version;

	if (this->inherits_from.empty())
	{
		if (isRoot())
		{
			this_version = Version(this->id).setPatches(this->patches);
		}
		else
		{
			this_version = *this;
		}

		this_version = this->jar.empty() ? this_version.setJar(this->id) : this_version.setJar(this->jar);
	}
	else
	{
		// To maximize the compatibility.
		if (!(resolved_so_far.insert(this->id).second))
		{
			qWarning() << "Found circular dependency versions: ";
			for (auto& elem : resolved_so_far)
			{
				qWarning() << elem;
			}
			this_version = this->jar.empty() ? this->setJar(this->id) : *this;
		}
		else
		{
			// It is supposed to auto install an version in getVersion.
			this_version = merge(provider.getVersion(this->inherits_from).resolve(provider, resolved_so_far), false);
		}
	}

	if (!this->patches.empty())
	{
		// Assume patches themselves do not have patches recursively.
		std::vector<Version> sorted_patches = this->patches;

		std::sort(sorted_patches.begin(), sorted_patches.end(),
			[=](Version i1, Version i2) -> bool
			{
				return i1.getPriority() > i2.getPriority();
			}
		);

		for (auto& patch : sorted_patches)
		{
			this_version = patch.setJar("").merge(this_version, true);
		}
	}

	return this_version.setId(this->id);
}

Version Version::toPatch() const
{
	return this->clearPatches().setHidden(true).setId("resolved." + getId());
}

Version Version::resolvePreservingPatches(const VersionProvider& provider) const
{
	std::set<std::string> ses;
	return resolvePreservingPatches(provider, ses);
}

Version Version::mergePreservingPatches(const Version& parent) const
{
	return parent.addPatches({ toPatch() }).addPatches(patches);
}

Version Version::resolvePreservingPatches(const VersionProvider& provider, std::set<std::string>& resolved_so_far) const
{
	Version this_version = isRoot() ? *this : Version(this->id).addPatch({ toPatch() }).addPatches(getPatches());

	if (this->inherits_from.empty())
	{
		// keep thisVersion
	}
	else
	{
		// To maximize the compatibility.
		if (!resolved_so_far.insert(id).second)
		{
			qWarning() << "Found circular dependency versions: ";
			for (auto& elem : resolved_so_far)
			{
				qWarning() << elem;
			}
			// keep thisVersion
		}
		else
		{
			// It is supposed to auto install an version in getVersion.
			this_version = mergePreservingPatches(provider.getVersion(this->inherits_from).resolvePreservingPatches(provider, resolved_so_far));
		}
	}

	return this_version.setId(id).setJar(resolve(provider).getJar());
}

Version Version::markAsResolved() const
{
	return Version(true, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);;
}

Version Version::markAsUnresolved() const
{
	return Version(false, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setHidden(bool hidden) const
{
	return Version(true, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, hidden, this->root, this->patches);
}

Version Version::setId(const std::string& id) const
{
	return Version(this->resolved, id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setVersion(const std::string& version) const
{
	return Version(this->resolved, this->id, version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setPriority(int priority) const
{
	return Version(this->resolved, this->id, this->version, priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setMinecraftArguments(const std::string& minecraft_arguments) const
{
	return Version(this->resolved, this->id, this->version, this->priority, minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setArguments(const Arguments& arguments) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setMainClass(const std::string& main_class) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setInheritsFrom(const std::string& inherits_from) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setJar(const std::string& jar) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setLibraries(const std::vector<Library>& libraries) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setLogging(const std::unordered_map<DownloadType, LoggingInfo>& logging) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, this->patches);
}

Version Version::setPatches(const std::vector<Version>& patches) const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, patches);
}

Version Version::addPatch(std::initializer_list<Version> additional) const
{
	return addPatches(additional);
}

Version Version::addPatches(const std::vector<Version>& additional) const
{
	std::unordered_set<std::string> patchIds;

	for (const auto& patch : additional)
	{
		patchIds.insert(patch.getId());
	}

	std::vector<Version> updatedPatches;

	if (!this->patches.empty())
	{
		std::copy_if(
			this->patches.begin(), this->patches.end(),
			std::back_inserter(updatedPatches),
			[&patchIds](const Version& patch) -> bool
			{
				return patchIds.find(patch.getId()) == patchIds.end();
			}
		);
	}

	std::copy(additional.begin(), additional.end(), std::back_inserter(updatedPatches));

	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, updatedPatches);
}

Version Version::clearPatches() const
{
	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root, std::vector<Version>());
}

Version Version::removePatchById(const std::string& patch_id) const
{
	std::vector<Version> filtered_patches;

	if (!patches.empty())
	{
		std::copy_if(patches.begin(), patches.end(), std::back_inserter(filtered_patches),
			[&patch_id](const Version& patch)
			{
				return patch_id != patch.getId();
			});
	}

	return Version(this->resolved, this->id, this->version, this->priority, this->minecraft_arguments, this->arguments,
		this->main_class, this->inherits_from, this->jar, this->asset_index, this->assets, this->compliance_level,
		this->java_version, this->libraries, this->compatibility_rules, this->downloads, this->logging, this->type,
		this->time, this->release_time, this->minimum_launcher_version, this->hidden, this->root,
		this->patches.empty() ? std::vector<Version>() : filtered_patches
	);
}

bool Version::hasPatch(const std::string& patch_id) const
{
	if (!this->patches.empty())
	{
		return std::any_of(this->patches.begin(), this->patches.end(),
			[&patch_id](const Version& patch)
			{
				return patch_id == patch.getId();
			}
		);
	}
	return false;
}

int Version::hashCode() const
{
	return std::hash<std::string>{}(this->id);
}

std::string Version::toString() const
{
	std::stringstream ss;
	ss << "id: " << id;
	return ss.str();
}

void Version::validate()
{
	if (this->id.empty())
	{
		throw JsonParseException("Version ID cannot be blank");
	}

	if (!this->downloads.empty())
	{
		for (auto& entry : this->downloads)
		{
			if (entry.first == DownloadType::UNKNOW)
			{
				throw JsonParseException("Version downloads key must be DownloadType");
			}

			if (entry.second.empty())
			{
				throw JsonParseException("Version downloads value must be DownloadInfo");
			}
		}
	}

	if (!this->logging.empty())
	{
		for (auto& entry : this->logging)
		{
			if (entry.first == DownloadType::UNKNOW)
			{
				throw JsonParseException("Version logging key must be DownloadType");
			}

			if (entry.second.empty())
			{
				throw JsonParseException("Version logging value must be LoggingInfo");
			}
		}
	}
}


