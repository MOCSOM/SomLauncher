#include "Libraries.h"

QVector<GameProfile::ClasspathEntry> libraries::getLibraries(Json::JsonValue& json_data, const std::filesystem::path& instance_path)
{
	using namespace libraries::utils;

	QVector<GameProfile::ClasspathEntry> libraries;

	/*
	Returns the argument with all libs that come after -cp
	*/

	std::string libstr = "";
	std::string native = "";

	for (auto& elem : json_data["libraries"].get_array())
	{
		if (elem.is_exist("rules") && !(rules::utils::parseRuleList(elem, "rules")))
		{
			continue;
		}

		libraries += GameProfile::ClasspathEntry(
			getLibraryPath(elem["name"].to_string().c_str(), instance_path).string()
			/*+ GameProfile::ClasspathEntry::classpath_separator*/, elem["name"].to_string().c_str());


		native = MinecraftCpp::get_natives(elem);

		if (native != "")
		{
			if (elem.is_exist("downloads"))
			{
				libraries += GameProfile::ClasspathEntry(
					(instance_path / "libraries" / elem["downloads"]["classifiers"][native]["path"].to_string()).string()
					/*+ GameProfile::ClasspathEntry::classpath_separator*/, elem["name"].to_string().c_str());
			}
			else
			{
				libraries += GameProfile::ClasspathEntry(
					getLibraryPath((elem["name"].to_string() + ("-" + native)).c_str(), instance_path).string()
					/*+ GameProfile::ClasspathEntry::classpath_separator*/, elem["name"].to_string().c_str());
			}
		}
	}

	if (json_data.is_exist("jar"))
	{
		libraries += GameProfile::ClasspathEntry(
			instance_path / "versions" / json_data["jar"].to_string() / (json_data["jar"].to_string() + ".jar"));
	}
	else
	{
		libraries += GameProfile::ClasspathEntry(
			instance_path / "versions" / json_data["id"].to_string() / (json_data["id"].to_string() + ".jar"));
	}

	return libraries;
}

bool libraries::loadLibraries(GameProfile& profile)
{
	auto& instance_path = profile.getInstancePath();
	auto& version = profile.getVersionName();
	auto json_path = instance_path / L"versions" / version.toStdWString() / (version + ".json").toStdWString();

	Json::JsonValue data = Json::JsonParcer::ParseFile(json_path);

	if (data.is_exist("inheritsFrom"))
	{
		data = libraries::utils::inheritJson(data, instance_path);
	}

	profile.setMainClass(data["mainClass"].to_string().c_str());

	QVector<GameProfile::ClasspathEntry> libraries = getLibraries(data, instance_path);
	if (libraries.isEmpty())
	{
		qWarning() << "Load libraries is failed";
		return false;
	}

	profile.setClasspathLibraries(libraries);
	return true;
}

void libraries::unpackLibraries(const GameProfile& profile)
{
	// unpack necessary libraries
	for (auto& lib : profile.getDownloads())
	{
		if (lib.mExtract)
		{
			std::string absoluteFilePath = std::filesystem::absolute(profile.getInstancePath() / lib.mLocalPath).string();

			QDir extractTo = std::filesystem::absolute(profile.getInstancePath() / "bin" / profile.id().toStdString());
			if (!extractTo.exists())
				extractTo.mkpath(extractTo.absolutePath());

			unzFile unz = unzOpen(absoluteFilePath.c_str());
			if (unz)
			{
				unz_global_info info;
				if (unzGetGlobalInfo(unz, &info) != UNZ_OK)
					continue;
				for (size_t i = 0; i < info.number_entry; ++i)
				{
					unz_file_info fileInfo;
					char cFileName[512];
					if (unzGetCurrentFileInfo(unz, &fileInfo, cFileName, sizeof(cFileName), nullptr, 0, nullptr,
						0) != UNZ_OK)
						break;

					QString fileName = cFileName;

					// meta-inf folder is not needed
					if (!fileName.startsWith("META-INF/"))
					{
						if (fileName.endsWith('/'))
						{
							// folder
							extractTo.mkpath(extractTo.absoluteFilePath(fileName));
						}
						else
						{
							// file
							if (unzOpenCurrentFile(unz) != UNZ_OK)
								break;


							QFile dstFile = extractTo.absoluteFilePath(fileName);
							auto containingDir = QFileInfo(dstFile).absoluteDir();
							if (!containingDir.exists())
								extractTo.mkpath(containingDir.absolutePath());

							dstFile.open(QIODevice::WriteOnly);

							char buf[0x1000]{};

							for (int read; (read = unzReadCurrentFile(unz, buf, sizeof(buf))) > 0;)
							{
								dstFile.write(buf, read);
							}

							dstFile.close();
							unzCloseCurrentFile(unz);
						}
					}


					if ((i + 1) < info.number_entry)
					{
						if (unzGoToNextFile(unz) != UNZ_OK)
							break;
					}
				}

				unzClose(unz);
			}
		}
	}
}

std::filesystem::path libraries::utils::getLibraryPath(const QString& lib_name, const std::filesystem::path& instance_path)
{
	/*
	Returns the path from a libname
	*/

	std::filesystem::path libpath = instance_path / L"libraries";

	std::vector<std::string> parts = Additionals::String::split(lib_name.toStdString(), ':');
	QString base_path = parts[0].c_str();
	QString libname = parts[1].c_str();
	QString version = parts[2].c_str();
	std::string fileend;

	for (auto& var : Additionals::String::split(base_path.toStdString(), '.'))
	{
		libpath = libpath / var;
	}
	if (version.contains('@'))
	{
		std::vector<std::string> splt = Additionals::String::split(version.toStdString(), '@', 2);
		version = splt[0].c_str();
		fileend = splt[1];
	}
	else
	{
		fileend = "jar";
	}
	// construct a filename with the remaining parts

	std::filesystem::path filename;

	//parts->CopyTo(parts_2, 3);
	/*int count = 0;
	for (auto& var : parts)
	{
		++count;
	}*/
	/*array<System::String^>^ parts_2 = gcnew array<System::String^>(count - 2);
	for (int i = 0; i < count - 2; i++)
	{
		parts_2[i] = parts[i + 2];
	}*/
	//filename = StrDogW({ const_cast<wchar_t*>(wch_libname), L"-", const_cast<wchar_t*>(wch_version) });
	for (auto& var : parts)
	{
		filename = libname.toStdString() + ("-" + var);
	}
	filename += ("." + fileend);

	libpath = libpath / libname.toStdString() / version.toStdString() / filename;
	return libpath;
}

Json::JsonValue libraries::utils::inheritJson(Json::JsonValue& original_data, const std::filesystem::path& path)
{
	/*
	Implement the inheritsFrom function
	See https://github.com/tomsik68/mclauncher-api/wiki/Version-Inheritance-&-forge
	*/

	Json::JsonValue inherit_version = original_data["inheritsFrom"];

	std::filesystem::path path_inh_json = path / "versions" / inherit_version.to_string() / (inherit_version.to_string() + ".json");
	Json::JsonParcer json_inherit;
	Json::JsonValue new_data = json_inherit.ParseFile(path_inh_json);

	//qDebug() << original_data["mainClass"].to_string() << std::endl;

	for (auto& var : original_data.get_object())
	{
		if (var.second.get_type() == Json::JsonTypes::Array &&
			new_data.is_exist(var.first) ? new_data[var.first].get_type() == Json::JsonTypes::Array : false)
		{
			new_data[var.first] = var.second + new_data[var.first];
		}
		else if (var.second.get_type() == Json::JsonTypes::Object &&
			new_data.is_exist(var.first) ? new_data[var.first].get_type() == Json::JsonTypes::Object : false)
		{
			for (auto& variable : var.second.get_object())
			{
				if (variable.second.get_type() == Json::JsonTypes::Array)
				{
					new_data[var.first][variable.first] = new_data[var.first][variable.first] + variable.second;
				}
			}
		}
		else
		{
			if (new_data.is_exist(var.first))
			{
				new_data[var.first] = var.second;
			}
			else
			{
				new_data.add_value(var.first, var.second);
			}
		}
	}

	//qDebug() << original_data["mainClass"].to_string() << std::endl;

	return new_data;
}


