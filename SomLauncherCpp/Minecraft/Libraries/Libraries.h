#ifndef LIBRARIES_LIBRARIES_H_
#define LIBRARIES_LIBRARIES_H_

#include <QStringList>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QVector>
#include <QDir>

//#include <variant>

#include "../Launcher/GameProfile.h"
#include "../Minecraftus.h"
#include "../Rules/Rules.h"

namespace libraries
{
	QVector<GameProfile::ClasspathEntry> getLibraries(
		Json::JsonValue& json_data, const std::filesystem::path& instance_path);

	bool loadLibraries(GameProfile& profile);

	namespace utils
	{
		std::filesystem::path getLibraryPath(const QString& lib_name, const std::filesystem::path& instance_path);
		Json::JsonValue inheritJson(Json::JsonValue& original_data, const std::filesystem::path& path);
	}
}


#endif // !LIBRARIES_LIBRARIES_H_