#ifndef GAMEARGS_GAMEARGUMENTS_H_
#define GAMEARGS_GAMEARGUMENTS_H_

#include "../Launcher/GameProfile.h"
#include "../Rules/Rules.h"

namespace gamearguments
{
	bool loadGameArguments(GameProfile& profile);

	namespace utils
	{
		QVector<GameProfile::GameArg> getArguments(GameProfile& profile, Json::JsonValue& data, Json::JsonValue& version_data, const std::filesystem::path& path);
		// For older versions
		QVector<GameProfile::GameArg> getArguments(GameProfile& profile, Json::JsonValue& version_data, const std::filesystem::path& path);

		bool replaceArguments(QString& argstr, Json::JsonValue& versionData, const std::filesystem::path& path, const GameProfile& profile);
	}
}

#endif // !GAMEARGS_GAMEARGUMENTS_H_