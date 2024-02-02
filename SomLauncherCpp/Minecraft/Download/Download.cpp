#include "Download.h"

bool download::loadDownloads(GameProfile& profile)
{
	if (profile.isLoader())
	{
		download::utils::versionjson::fabric::downloadJsonFabric(profile);
	}
	download::utils::versionjson::downloadJsons(profile);

	auto& name = profile.getVersionName();
	auto& vanilla_name = profile.getMinecraftVersion();
	QFile version_name_file = std::filesystem::absolute(
		profile.getInstancePath() / "versions" / name.toStdU16String() / (name + ".json").toStdString());
	if (version_name_file.exists())
	{
		QVector<DownloadEntry> downloads;
		QFile vanilla_name_file = std::filesystem::absolute(
			profile.getInstancePath() / "versions" / vanilla_name.toStdU16String() / (vanilla_name + ".json").toStdString());
		if (vanilla_name_file.exists())
		{
			vanilla_name_file.open(QIODevice::ReadOnly);

			//Download minecraft.jar
			const QJsonObject json_vanilla = QJsonDocument::fromJson(vanilla_name_file.readAll()).object();
			QUrl minecraft_jar_url = json_vanilla["downloads"]["client"]["url"].toString();
			if (json_vanilla["downloads"].type() != QJsonValue::Null)
			{
				downloads += DownloadEntry{
					(profile.getInstancePath() / "versions" / vanilla_name.toStdU16String() / (vanilla_name + ".jar").toStdString()),
					minecraft_jar_url
				};
				downloads += DownloadEntry{
					(profile.getInstancePath() / "versions" / name.toStdU16String() / (name + ".jar").toStdString()),
					minecraft_jar_url
				};
			}

			downloads += utils::getDownloads(QJsonDocument::fromJson(vanilla_name_file.readAll()).object());

			vanilla_name_file.close();
		}

		version_name_file.open(QIODevice::ReadOnly);

		downloads += utils::getDownloads(QJsonDocument::fromJson(version_name_file.readAll()).object());

		profile.setDownloads(downloads);
		version_name_file.close();
		return true;
	}


	//else
	//{
	//}
	return false;
}

QVector<DownloadEntry> download::utils::getDownloads(const QJsonObject& object)
{
	QVector<DownloadEntry> downloads;

	// Java libraries
	for (QJsonValue v : object["libraries"].toArray())
	{
		if (v["rules"].isArray())
		{
			bool allowed = false;
			for (auto r : v["rules"].toArray())
			{
				auto rule = r.toObject();
				bool rulePassed = true;
				for (auto& k : rule.keys())
				{
					if (k != "action")
					{
						if (rule[k].isObject())
						{
							auto x = rule[k].toObject();
							for (auto& v : x.keys())
							{
								/*if (VariableHelper::getVariableValue(launcher, k + '.' + v).toString() != x[v]
									.
									toVariant()
									.
									toString()
									)
								{
									rulePassed = false;
									break;
								}*/
							}
						}
						else
						{
							/*if (VariableHelper::getVariableValue(launcher, k).toString() != rule[k]
								.toVariant().toString())
							{
								rulePassed = false;
							}*/
						}
						if (!rulePassed)
							break;
					}
				}
				if (rulePassed)
					allowed = rule["action"] == "allow";
			}
			if (!allowed)
				continue;
		}

		QString name = v["name"].toString();

		if (v["downloads"].isObject())
		{
			downloads << downloadEntryFromJson("libraries/" + v["downloads"]["artifact"]["path"].toString(),
				v["downloads"]["artifact"].toObject());

			bool extract = v["extract"].isObject();
			downloads.last().mExtract = extract;

			if (v["downloads"]["classifiers"].isObject())
			{
				auto k = v["downloads"]["classifiers"]["natives-windows"];
				if (k.isObject())
				{
					downloads.last().mExtract = false;
					downloads << downloadEntryFromJson("libraries/" + k["path"].toString(), k.toObject());
					downloads.last().mExtract = extract;
					//p.mClasspath << GameProfile::ClasspathEntry{ "libraries/" + k["path"].toString() };
				}
			}
		}
		else
		{
			// Minecraft Forge-style entry
			QString url = "https://libraries.minecraft.net/";
			if (v["url"].isString())
			{
				url = v["url"].toString();
				if (!url.endsWith("/"))
				{
					url += "/";
				}
			}
			downloads << DownloadEntry{
				("libraries/" + javaLibNameToPath(name)).toStdString(), url + javaLibNameToPath(name), 0, false, ""
			};
		}

		/*if (v["downloads"].isObject())
			p.mClasspath << ClasspathEntry{ "libraries/" + v["downloads"]["artifact"]["path"].toString() };
		else
			p.mClasspath << ClasspathEntry{ "libraries/" + javaLibNameToPath(name) };*/
	}


	return downloads;
}

QString download::utils::javaLibNameToPath(const QString& name)
{
	auto colonSplitted = name.split(':');
	if (colonSplitted.size() == 3)
	{
		colonSplitted[0].replace('.', '/');
		return colonSplitted[0] + '/' + colonSplitted[1] + '/' + colonSplitted[2]
			+ '/' + colonSplitted[1] + '-' + colonSplitted[2] + ".jar";
	}
	return "INVALID:" + name;
}

bool download::utils::versionjson::downloadJsons(const GameProfile& profile)
{
	QUrl version_manifest_url = QUrl::fromUserInput("https://launchermeta.mojang.com/mc/game/version_manifest.json");
	DownloadHelper helper;
	helper.addDownloadList(
		{ DownloadEntry {profile.getInstancePath() / "version_manifest.json", version_manifest_url, 0, false, "" } },
		profile.getInstancePath() / "version_manifest.json", false);
	helper.performDownload();

	Json::JsonValue version_list = Json::JsonParcer::ParseFile(profile.getInstancePath() / "version_manifest.json");

	if (version_list == nullptr)
	{
		qFatal() << "error in version list";
	}

	for (auto& var : version_list["versions"].get_array())
	{
		//qInfo() << "doversion install" << std::endl;
		if (var["id"].to_string() == profile.getMinecraftVersion().toStdString())
		{
			QUrl version_url = QUrl::fromUserInput(var["url"].to_string().c_str());
			auto file = std::filesystem::absolute(
				profile.getInstancePath() / "versions" / profile.getMinecraftVersion().toStdString() / (profile.getMinecraftVersion() + ".json").toStdString());

			DownloadHelper helper;
			helper.addDownloadList({ DownloadEntry {file, version_url, 0, false, "" } }, file, false);
			helper.performDownload();
			return true;
		}
	}
	return false;
}

bool download::utils::versionjson::fabric::downloadJsonFabric(const GameProfile& profile)
{
	QUrl version_url = QUrl::fromUserInput("https://meta.fabricmc.net/v2/versions/loader/"
		+ profile.getMinecraftVersion() + "/" + profile.getLoaderVersion() + "/profile/json");
	auto file = std::filesystem::absolute(
		profile.getInstancePath() / "versions" / profile.getVersionName().toStdString() / (profile.getVersionName() + ".json").toStdString());

	DownloadHelper helper;
	helper.addDownloadList({ DownloadEntry {file, version_url, 0, false, "" } }, file, false);
	helper.performDownload();
	//return true;

	return true;
}
