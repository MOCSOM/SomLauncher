#include "GameArguments.h"

bool gamearguments::loadGameArguments(GameProfile& profile)
{
	auto& instance_path = profile.getInstancePath();
	auto& version = profile.getMinecraftVersion();
	auto json_path = instance_path / L"versions" / version.toStdWString() / (version + ".json").toStdWString();

	Json::JsonValue data = Json::JsonParcer::ParseFile(json_path);

	if (data.is_exist("minecraftArguments"))
	{
		// For older versions
		profile.setGameArgs(utils::getArguments(profile, data, instance_path));
		return true;
	}
	else
	{
		profile.setGameArgs(utils::getArguments(profile, data["arguments"]["game"], data, instance_path));
		return true;
	}

	return false;
}

QVector<GameProfile::GameArg> gamearguments::utils::getArguments(GameProfile& profile, Json::JsonValue& data, Json::JsonValue& version_data, const std::filesystem::path& path)
{
	/*
	Returns all arguments from the version.json
	*/

	QVector<GameProfile::GameArg> arglist;
	if (data.get_type() == Json::JsonTypes::Array)
	{
		QString key, value;
		for (auto& var : data.get_array())
		{
			QString replace;
			if (var.get_type() == Json::JsonTypes::String)
			{
				replace = var.to_string().c_str();
				if (replaceArguments(replace, version_data, path, profile))
				{
					value = replace;
				}
				else
				{
					key = replace;
				}
			}
			else
			{
				// Rules might has 2 different names in different versions.json
				if (var.is_exist("compatibilityRules") && !rules::utils::parseRuleList(var, "compatibilityRules"))
				{
					continue;
				}
				if (var.is_exist("rules") && !rules::utils::parseRuleList(var, "rules"))
				{
					continue;
				}

				// var could be the argument
				if (var["value"].get_type() == Json::JsonTypes::String)
				{
					replace = var["value"].to_string().c_str();
					if (replaceArguments(replace, version_data, path, profile))
					{
						value = replace;
					}
					else
					{
						key = replace;
					}
				}
				else
				{
					for (auto& v : var["value"].get_object())
					{
						replace = v.second.to_string().c_str();
						if (replaceArguments(replace, version_data, path, profile))
						{
							value = replace;
						}
						else
						{
							key = replace;
						}
					}
				}
			}
			if (!(value.isEmpty() || key.isEmpty()))
			{
				arglist += GameProfile::GameArg(key, value);
				value.clear();
				key.clear();
			}
		}
	}
	else
	{
		qFatal() << "data is not array";
		//for (auto& var : data.get_array())
		//{
		//	if (var.get_type() == Json::JsonTypes::String)
		//	{
		//		QString replace = var.to_string().c_str();
		//		if (replaceArguments(replace, version_data, path, profile))
		//		{
		//			arglist += GameProfile::GameArg(QString(), "\"" + replace + "\"");
		//		}
		//		else
		//		{
		//			arglist += GameProfile::GameArg(replace, QString());
		//		}
		//	}
		//	else
		//	{
		//		// Rules might has 2 different names in different versions.json
		//		if (var.is_exist("compatibilityRules") && !rules::utils::parseRuleList(var, "compatibilityRules"))
		//		{
		//			continue;
		//		}
		//		if (var.is_exist("rules") && !rules::utils::parseRuleList(var, "rules"))
		//		{
		//			continue;
		//		}

		//		// var could be the argument
		//		if (var["value"].get_type() == Json::JsonTypes::String)
		//		{
		//			qDebug() << "data " << data.to_string();
		//			qDebug() << "var " << var.to_string();

		//			QString replace = var["value"].to_string().c_str();
		//			if (replaceArguments(replace, version_data, path, profile))
		//			{
		//				arglist += GameProfile::GameArg(QString(), "\"" + replace + "\"");
		//			}
		//			else
		//			{
		//				arglist += GameProfile::GameArg(replace, QString());
		//			}
		//		}
		//		else
		//		{
		//			for (auto& v : var["value"].get_object())
		//			{
		//				QString replace = v.second.to_string().c_str();
		//				if (replaceArguments(replace, version_data, path, profile))
		//				{
		//					arglist += GameProfile::GameArg(QString(), "\"" + replace + "\"");
		//				}
		//				else
		//				{
		//					arglist += GameProfile::GameArg(replace, QString());
		//				}
		//			}
		//		}
		//	}
		//}
	}
	return arglist;
}

QVector<GameProfile::GameArg> gamearguments::utils::getArguments(GameProfile& profile, Json::JsonValue& version_data, const std::filesystem::path& path)
{
	/*
	Turns the argument string from the version.json into a list
	*/
	QVector<GameProfile::GameArg> arglist;

	for (auto& var : Additionals::String::split(version_data["minecraftArguments"].to_string(), ' '))
	{
		QString replace = var.c_str();
		QString key, value;
		if (replaceArguments(replace, version_data, path, profile))
		{
			value = replace;
		}
		else
		{
			key = replace;
		}
		arglist += GameProfile::GameArg(key, value);

	}
	// Custom resolution is not in the list
	arglist += GameProfile::GameArg("--width", QString::number(profile.getWindowWidth()));
	arglist += GameProfile::GameArg("--height", QString::number(profile.getWindowHeight()));

	if (profile.isDemo())
	{
		arglist += GameProfile::GameArg("--demo", "true");
	}

	return arglist;
}

bool gamearguments::utils::replaceArguments(QString& argstr, Json::JsonValue& versionData, const std::filesystem::path& path, const GameProfile& profile)
{
	QString replace_result = argstr;
	argstr.replace("${natives_directory}", profile.getNativesPath().string().c_str());
	argstr.replace("${launcher_name}", profile.getName());
	argstr.replace("${launcher_version}", profile.getVersionName());
	argstr.replace("${classpath}", profile.getMainClass());
	argstr.replace("${auth_player_name}", profile.getUsername());
	argstr.replace("${version_name}", versionData["id"].to_string().c_str());
	argstr.replace("${game_directory}", profile.getInstancePath().string().c_str());
	argstr.replace("${assets_root}", (path / "assets").string().c_str());
	argstr.replace("${assets_index_name}", versionData["assets"] != nullptr ? versionData["assets"].to_string().c_str() : versionData["id"].to_string().c_str());
	argstr.replace("${auth_uuid}", profile.getUuid().toString());
	argstr.replace("${auth_access_token}", "uuu");
	argstr.replace("${user_type}", "mojang");
	argstr.replace("${version_type}", versionData["type"].to_string().c_str());
	argstr.replace("${user_properties}", "{}");
	argstr.replace("${resolution_width}", QString::number(profile.getWindowWidth()));
	argstr.replace("${resolution_height}", QString::number(profile.getWindowHeight()));
	argstr.replace("${game_assets}", (path / "assets" / "virtual" / "legacy").string().c_str());
	argstr.replace("${auth_session}", "uuu");
	argstr.replace("${library_directory}", (path / "libraries").string().c_str());
	argstr.replace("${classpath_separator}", QChar(GameProfile::ClasspathEntry::classpath_separator));
	argstr.replace("${quickPlayPath}", "quickPlayPath");
	argstr.replace("${quickPlaySingleplayer}", "quickPlaySingleplayer");
	argstr.replace("${quickPlayMultiplayer}", "quickPlayMultiplayer");
	argstr.replace("${quickPlayRealms}", "quickPlayRealms");

	if (replace_result != argstr)
	{
		//argstr = replace_result;
		return true;
	}

	return false;
}

