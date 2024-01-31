#include "Download.h"

bool download::loadDownloads(GameProfile& profile)
{
	auto& name = profile.getVersionName();
	QFile file = std::filesystem::absolute(
		profile.getInstancePath() / "versions" / name.toStdU16String() / (name + ".json").toStdString());
	if (file.exists())
	{
		file.open(QIODevice::ReadOnly);
		QVector<DownloadEntry> downloads = utils::getDownloads(QJsonDocument::fromJson(file.readAll()).object());
		profile.setDownloads(downloads);
		file.close();
		return true;
	}
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
