#include "GameProfile.h"

#ifdef Q_OS_WINDOWS
char GameProfile::ClasspathEntry::classpath_separator = ';';
#else
char GameProfile::ClasspathEntry::classpath_separator = ':';
#endif // Q_OS_WINDOWS

DownloadEntry downloadEntryFromJson(const QString& path, Json::JsonValue& v)
{
	return DownloadEntry{
			path, v["url"].to_string().c_str(),
			uint64_t(v["size"].to_int()), false, v["sha1"].to_string().c_str()
	};
}

void GameProfile::makeClean()
{
	// remove duplicating java args
	for (auto i = 0; i < mJavaArgs.size(); ++i)
	{
		const auto& name = mJavaArgs[i].name;
		if (name.startsWith("--"))
		{ // --add-exports
			continue;
		}
		mJavaArgs.erase(std::remove_if(mJavaArgs.begin() + i + 1, mJavaArgs.end(),
			[&name](const auto& p)
			{
				return p.name == name;
			}), mJavaArgs.end());
	}

	// remove duplicating game args
	for (auto i = 0; i < mGameArgs.size(); ++i)
	{
		const auto& name = mGameArgs[i].name;
		mGameArgs.erase(std::remove_if(mGameArgs.begin() + i + 1, mGameArgs.end(),
			[&name](const auto& p)
			{
				return p.name == name;
			}), mGameArgs.end());
	}

	// remove duplicating libraries
	for (auto i = 0; i < classpath_libraries.size(); ++i)
	{
		const auto& name = classpath_libraries[i].name;
		classpath_libraries.erase(std::remove_if(classpath_libraries.begin() + i + 1, classpath_libraries.end(),
			[&name](const auto& p)
			{
				return p.name == name;
			}), classpath_libraries.end());
	}
}

std::filesystem::path GameProfile::instancePath(const std::filesystem::path& minecraft_path) noexcept
{
	std::filesystem::path instance_path = minecraft_path;

	if (instance_path.empty())
	{
		auto path = std::filesystem::temp_directory_path()
			.parent_path()
			.parent_path();

		path /= "Roaming";

		instance_path = path / ".SomSomSom";
		this->instance_path = instance_path;
		return instance_path;
	}

	this->instance_path = instance_path;
	return this->instance_path;
}

std::filesystem::path GameProfile::setupNativesPath(const std::filesystem::path& minecraft_path) noexcept
{
	std::filesystem::path instance_path = minecraft_path;

	if (instance_path.empty())
	{
		auto path = std::filesystem::temp_directory_path()
			.parent_path()
			.parent_path();

		path /= "Roaming";

		instance_path = path / ".SomSomSom" / "versions" / this->version_name.toStdWString() / "natives";
		this->natives_path = instance_path;
		return instance_path;
	}

	this->natives_path = instance_path / "versions" / this->version_name.toStdWString() / "natives";
	return this->instance_path;
}

GameProfile::ClasspathEntry::ClasspathEntry(const std::filesystem::path& path, const QString& name)
	: path(path), name(name)
{
}

GameProfile::GameArg::GameArg(const QString& name, const QString& value)
	: name(name), value(value)
{
}
