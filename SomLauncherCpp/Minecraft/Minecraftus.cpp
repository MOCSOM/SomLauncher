#include "Minecraftus.h"

std::string MinecraftCpp::option::MinecraftOptions::get(const std::string& param, const std::string& writ)
{
	//16 полей
	/*wchar_t* username;
	wchar_t* uuid;
	wchar_t* token;
	wchar_t* executablePath;
	wchar_t* jvmArguments;
	wchar_t* launcherName;
	wchar_t* launcherVersion;
	wchar_t* gameDirectory;
	bool	 demo;
	bool	 customResolution;
	wchar_t* resolutionWidth;
	wchar_t* resolutionHeight;
	wchar_t* server;
	wchar_t* port;
	wchar_t* nativesDirectory;
	bool	 enableLoggingConfig;*/

	std::string field = "";

	if (param == "username")
		field = this->username;
	else if (param == "uuid")
		field = this->uuid;
	else if (param == "token")
		field = this->token;
	else if (param == "executablePath")
		field = this->executablePath;
	else if (param == "jvmArguments")
		field = this->jvmArguments;
	else if (param == "launcherName")
		field = this->launcherName;
	else if (param == "launcherVersion")
		field = this->launcherVersion;
	else if (param == "gameDirectory")
		field = this->gameDirectory;
	else if (param == "resolutionWidth")
		field = this->resolutionWidth;
	else if (param == "resolutionHeight")
		field = this->resolutionHeight;
	else if (param == "server")
		field = this->server;
	else if (param == "port")
		field = this->port;
	else if (param == "nativesDirectory")
		field = this->nativesDirectory;
	else
		return this->NULLES;

	if (writ == "")
	{
		return field;
	}
	else if (field == "")
	{
		return writ;
	}
	else
	{
		return field;
	}
}

bool MinecraftCpp::option::MinecraftOptions::get(const std::string& param, bool writ)
{
	bool field = false;

	if (param == "demo")
		field = this->demo;
	else if (param == "customResolution")
		field = this->customResolution;
	else if (param == "enableLoggingConfig")
		field = this->enableLoggingConfig;
	else
		return false;

	if (!writ)
		return field;

	if (field)
		return field;

	field = writ;
	return field;
}

bool MinecraftCpp::option::MinecraftOptions::is_exist(const std::string& param)
{
	if (param == "username" ||
		param == "uuid" ||
		param == "token" ||
		param == "executablePath" ||
		param == "jvmArguments" ||
		param == "launcherName" ||
		param == "launcherVersion" ||
		param == "gameDirectory" ||
		param == "resolutionWidth" ||
		param == "resolutionHeight" ||
		param == "server" ||
		param == "port" ||
		param == "nativesDirectory" ||
		param == "demo" ||
		param == "customResolution" ||
		param == "enableLoggingConfig")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MinecraftCpp::install_minecraft_version(const std::string& versionid, const std::string& minecraft_directory, CallbackNull* callback)
{
	/*
	Install a Minecraft Version. Fore more Information take a look at the documentation"
	*/
	Json::JsonParcer json_manifest;

	std::string full_dir = Join({ minecraft_directory , "versions" , versionid, (versionid + ".json") });

	std::string download_dir = Join({ minecraft_directory, "downloads" });

	if (!std::filesystem::exists(download_dir)) {
		bool out_mkdir = std::filesystem::create_directories(download_dir);
		std::cout << "java dir is maked with status: " << out_mkdir << std::endl;
	}

	if (std::filesystem::exists(full_dir))
	{
		if (!std::filesystem::is_directory(full_dir))
		{
			do_version_install(versionid, minecraft_directory, callback);
			return true;
		}
	}

	std::string version_manifest_file = DownloadFile("https://launchermeta.mojang.com/mc/game/version_manifest.json",
		download_dir, callback);

	Json::JsonValue version_list = json_manifest.ParseFile(version_manifest_file.c_str());

	for (auto& var : version_list["versions"].get_array())
	{
		if (var["id"].to_string() == versionid)
		{
			do_version_install(versionid, minecraft_directory, callback, var["url"].to_string());
			return true;
		}
	}
	return false;
}

bool MinecraftCpp::do_version_install(const std::string& versionid, const std::string& path,
	CallbackNull* callback, const std::string& url)
{
	/*
	Install the given version
	*/

	Json::JsonParcer json_verid;
	std::string path_ver_json = Join({ path, "versions", versionid, (versionid + ".json") });

	// Download and read versions.json
	if (url != "")
	{
		DownloadFile(url, path_ver_json, callback);
	}
	Json::JsonValue versiondata = json_verid.ParseFile(path_ver_json);

	// For forge
	if (versiondata.is_exist("inheritsFrom"))
	{
		install_minecraft_version(versiondata["inheritsFrom"].to_string(), path, callback);
		versiondata = inherit_json(versiondata, path);
	}
	install_libraries(versiondata, path, callback);
	install_assets(versiondata, path, callback);

	//Download logging config
	std::string logger_file = "";
	if (versiondata.is_exist("logging"))
	{
		if (versiondata["logging"].get_count() != 0)
		{
			logger_file = Join({ path, "assets", "log_configs", versiondata["logging"]["client"]["file"]["id"].to_string() });
			DownloadFile(versiondata["logging"]["client"]["file"]["url"].to_string(), logger_file, callback); //to with sha
		}
	}

	//Download minecraft.jar
	if (versiondata.is_exist("downloads"))
	{
		DownloadFile(versiondata["downloads"]["client"]["url"].to_string(), Join({ path, "versions", versiondata["id"].to_string(), (versiondata["id"].to_string() + ".jar") }), callback);
	}

	//Need to copy jar for old forge versions
	if (std::filesystem::is_directory(Join({ path, "versions", versiondata["id"].to_string(), (versiondata["id"].to_string() + ".jar") })) && versiondata.is_exist("inheritsFrom"))
	{
		std::filesystem::copy
		(
			std::string
			(
				Join
				({
					path,
					"versions",
					versiondata["id"].to_string(),
					(
						versiondata["id"].to_string()
						+
						".jar"
					)
					})
			),
			std::string
			(
				Join
				({
					path,
					"versions",
					versiondata["inheritsFrom"].to_string(),
					(
						versiondata["inheritsFrom"].to_string()
						+
						".jar"
					)
					})
			)
		);
	}

	//Install java runtime if needed
	if (versiondata.is_exist("javaVersion"))
	{
		install_jvm_runtime(versiondata["javaVersion"]["component"].to_string(), path, callback);
	}

	return true;
}

Json::JsonValue MinecraftCpp::inherit_json(Json::JsonValue original_data, const std::string& path)
{
	/*
	Implement the inheritsFrom function
	See https://github.com/tomsik68/mclauncher-api/wiki/Version-Inheritance-&-forge
	*/

	Json::JsonValue inherit_version = original_data["inheritsFrom"];

	std::string path_inh_json = Join({ path, "versions", inherit_version.to_string(), (inherit_version.to_string() + ".json") });
	Json::JsonParcer json_inherit;
	Json::JsonValue new_data = json_inherit.ParseFile(path_inh_json);

	qInfo() << original_data["mainClass"].to_string() << std::endl;

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

	qInfo() << new_data["mainClass"].to_string() << std::endl;

	return new_data;
}

Json::JsonValue MinecraftCpp::get_version_list()
{
	/*
	Returns all versions that Mojang offers to download
	*/
	Json::JsonParcer parcer;
	Json::JsonValue vlist = parcer.ParseUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json");
	Json::JsonValue returnlist = Json::JsonValue(std::vector<Json::JsonValue>());

	int count = -1;
	for (auto& i : vlist["versions"].get_array())
	{
		++count;
		Json::JsonValue object = Json::JsonValue(std::unordered_map<std::string, Json::JsonValue>());

		object.add_value(std::make_pair("id", i["id"]));
		object.add_value(std::make_pair("type", i["type"]));

		std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(_parseDateTime(i["releaseTime"].to_string()).time_since_epoch());

		object.add_value(std::make_pair("releaseTime", Json::JsonValue(seconds.count())));

		returnlist.add_value(object);
	}
	return returnlist;
}

std::vector<std::string> MinecraftCpp::get_minecraft_command__(const std::string& version, const std::string& minecraft_directory,
	MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Returns a command for launching Minecraft.For more information take a look at the documentation.
	*/
	if (!std::filesystem::exists(Join({ minecraft_directory, "versions", version, (version + ".json") })) ||
		!std::filesystem::is_directory(Join({ minecraft_directory, "versions", version })))
	{
		qFatal() << "Version Not Found" << version;
		return {};
	}

	Json::JsonParcer json_parcer;
	Json::JsonValue orig_data = json_parcer.ParseFile(Join({ minecraft_directory, "versions", version, (version + ".json") }));
	Json::JsonValue data;

	if (orig_data.is_exist("inheritsFrom"))
	{
		data = MinecraftCpp::inherit_json(orig_data, minecraft_directory); //FIXME: Баг: библиотеки(лист) не приравниваются, в функции всё норм
	}
	qInfo() << data.to_string() << std::endl;
	options.nativesDirectory = options.get("nativesDirectory", Join({ minecraft_directory, "versions", data["id"].to_string(), "natives" }));
	//options.nativesDirectory = JoinW({ minecraft_directory, L"versions", data["id"]->to_stringW(), L"natives" });
	options.classpath = MinecraftCpp::get_libraries(data, minecraft_directory);

	std::vector<std::string> command;

	// Add Java executable
	if (options.executablePath != "")
	{
		command.push_back(options.executablePath);
	}
	else if (data.is_exist("javaVersion"))
	{
		std::string java_path = MinecraftCpp::get_executable_path(data["javaVersion"]["component"].to_string(), minecraft_directory);
		if (java_path == "")
		{
			command.push_back("java");
		}
		else
		{
			command.push_back(java_path);
		}
	}
	else
	{
		command.push_back(options.get("defaultExecutablePath", std::string("java")));
	}

	if (options.jvmArguments != "")
	{
		command.push_back(options.jvmArguments);
	}

	qInfo() << data.to_string() << std::endl;
	// Newer Versions have jvmArguments in version.json
	if (data.is_exist("arguments") ? data["arguments"].get_type() == Json::JsonTypes::Object : false)
	{
		if (data["arguments"].is_exist("jvm"))
		{
			command.push_back(MinecraftCpp::get_arguments(data["arguments"]["jvm"], data, minecraft_directory, options));
		}
		else
		{
			command.push_back("-Djava.library.path=" + options.nativesDirectory);
			command.push_back("-cp");
			command.push_back(options.classpath);
		}
	}
	else
	{
		command.push_back("-Djava.library.path=" + options.nativesDirectory);
		command.push_back("-cp");
		command.push_back(options.classpath);
	}

	if (options.get("enableLoggingConfig", false))
	{
		if (data.is_exist("logging"))
		{
			if (data["logging"].to_int() != 0)
			{
				std::string logger_file = Join({ minecraft_directory, "assets", "log_configs", data["logging"]["client"]["file"]["id"].to_string() });
				std::string data_replacer = data["logging"]["client"]["argument"].to_string();
				Additionals::String::replace(data_replacer, "${path}", logger_file);
				command.push_back(data_replacer);
			}
		}
	}

	command.push_back(data["mainClass"].to_string());

	if (data.is_exist("minecraftArguments"))
	{
		// For older versions
		command.push_back(MinecraftCpp::get_arguments_string(data, minecraft_directory, options));
	}
	else
	{
		command.push_back(MinecraftCpp::get_arguments(data["arguments"]["game"], data, minecraft_directory, options));
	}

	if (options.server != "")
	{
		command.push_back("--server");
		command.push_back(options.server);

		if (options.port != "")
		{
			command.push_back("--port");
			command.push_back(options.port);
		}
	}

	return command;
}

std::string MinecraftCpp::get_libraries(Json::JsonValue data, const std::string& path)
{
	/*
	Returns the argument with all libs that come after -cp
	*/
	std::string classpath_seperator = MinecraftCpp::get_classpath_separator();
	std::string libstr = "";
	std::string native = "";
	MinecraftCpp::option::MinecraftOptions empty;

	for (auto& elem : data["libraries"].get_array())
	{
		if (elem.is_exist("rules") && !(MinecraftCpp::parse_rule_list(elem, "rules", empty)))
		{
			continue;
		}

		libstr += MinecraftCpp::get_library_path(elem["name"].to_string(), path) + classpath_seperator;
		native = MinecraftCpp::get_natives(elem);

		if (native != "")
		{
			if (elem.is_exist("downloads"))
			{
				libstr += Join({ path, "libraries", elem["downloads"]["classifiers"][native]["path"].to_string() }) + classpath_seperator;
			}
			else
			{
				libstr += MinecraftCpp::get_library_path((elem["name"].to_string() + ("-" + native)), path) + classpath_seperator;
			}
		}
	}

	if (data.is_exist("jar"))
	{
		libstr = libstr + Join({ path, "versions", data["jar"].to_string(), (data["jar"].to_string() + ".jar") });
	}
	else
	{
		libstr = libstr + Join({ path, "versions", data["id"].to_string(), (data["id"].to_string() + ".jar") });
	}

	return libstr;
}

std::chrono::system_clock::time_point MinecraftCpp::_parseDateTime(const std::string& isoDateTime)
{
	std::tm t = {};
	std::istringstream stream(isoDateTime);

	// Парсим дату и время из строки в формате ISO 8601
	stream >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");

	// Преобразуем структуру std::tm в std::chrono::system_clock::time_point
	return std::chrono::system_clock::from_time_t(std::mktime(&t));
}

bool MinecraftCpp::start_minecraft(const std::string& java_path, const std::string& args)
{
	std::string path;

	path = java_path + " ";
	path = path + args;

	std::unique_ptr<wchar_t[]> buffer = Additionals::Convectors::ConvertStringToWcharUniqPtr(args);
	LPWSTR szPath = buffer.get();
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));
	if (CreateProcessW(NULL, szPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		// программа запущена, ждем её завершения

		DWORD dwWait = WaitForSingleObject(pi.hProcess, INFINITE);
		if (dwWait == WAIT_OBJECT_0)
		{
			qInfo() << "Programm has been closed" << std::endl;
			// программа благополучно завершилась
		}
		else if (dwWait == WAIT_ABANDONED)
		{
			qInfo() << "Programm has been adadonde" << std::endl;
			// программа была насильно "прибита"
		}
		//  else ну и может быть другие варианты ожидания

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	//return system(path.c_str());
	return 0;
}

std::string MinecraftCpp::get_classpath_separator()
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

bool MinecraftCpp::parse_rule_list(Json::JsonValue data, const std::string& rule_string, MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Parse a list of rules
	*/

	if (!data.is_exist(rule_string))
	{
		return true;
	}
	for (Json::SomJson var : data[rule_string].get_array())
	{
		if (!MinecraftCpp::parse_single_rule(var, options))
		{
			return false;
		}
	}
	return true;
}

bool MinecraftCpp::parse_single_rule(Json::JsonValue rule, MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Parse a single rule from the versions.json
	*/
	bool returnvalue = false;
	if (rule["action"].to_string() == "allow")
	{
		returnvalue = false;
	}
	else if (rule["action"].to_string() == "disallow")
	{
		returnvalue = true;
	}
	if (rule.is_exist("os"))
	{
		for (auto& var : rule["os"].get_object())
		{
			if (var.first == "name")
			{
				if (var.second.to_string() == "windows" && OS != "Windows")
				{
					return returnvalue;
				}
				else if (var.second.to_string() == "osx" && OS != "Darwin")
				{
					return returnvalue;
				}
				else if (var.second.to_string() == "linux" && OS != "Linux")
				{
					return returnvalue;
				}
			}
			else if (var.first == "arch")
			{
				if (var.second.to_string() == "x86" && ARCH != "x86")
				{
					return returnvalue;
				}
			}
			else if (var.first == "version")
			{
				if (var.second.to_string() != OS)
				{
					return returnvalue;
				}
			}
		}
	}
	if (rule.is_exist("features"))
	{
		for (auto& var : rule["features"].get_object())
		{
			if (var.first == "has_custom_resolution" && !options.get("customResolution", false))
			{
				return returnvalue;
			}
			else if (var.first == "is_demo_user" && !options.get("demo", false))
			{
				return returnvalue;
			}
		}
	}
	return !returnvalue;
}

std::string MinecraftCpp::get_library_path(const std::string& name, const std::string& path)
{
	/*
	Returns the path from a libname
	*/

	std::string libpath = Join({ path, "libraries" });

	std::vector<std::string> parts = Additionals::String::split(name, ':');
	std::string base_path = parts[0];
	std::string libname = parts[1];
	std::string version = parts[2];
	std::string fileend;

	for (auto& var : Additionals::String::split(base_path, '.'))
	{
		libpath = Join({ libpath, var.c_str() });
	}
	if (version.find('@') == 0)
	{
		std::vector<std::string> splt = Additionals::String::split(version, '@', 2);
		version = splt[0];
		fileend = splt[1];
	}
	else
	{
		fileend = "jar";
	}
	// construct a filename with the remaining parts

	std::string filename = "";

	//parts->CopyTo(parts_2, 3);
	int count = 0;
	for (auto& var : parts)
	{
		++count;
	}
	/*array<System::String^>^ parts_2 = gcnew array<System::String^>(count - 2);
	for (int i = 0; i < count - 2; i++)
	{
		parts_2[i] = parts[i + 2];
	}*/
	//filename = StrDogW({ const_cast<wchar_t*>(wch_libname), L"-", const_cast<wchar_t*>(wch_version) });
	for (auto& var : parts)
	{
		filename = libname + ("-" + var);
	}
	filename = filename + ("." + fileend);

	libpath = Join({ libpath, libname, version, filename });
	return libpath;
}

std::string MinecraftCpp::get_natives(Json::JsonValue data)
{
	/*
	Returns the native part from the json data
	*/
	std::string arch_type;
	if (ARCH == "x86")
	{
		arch_type = "32";
	}
	else
	{
		arch_type = "64";
	}

	if (data.is_exist("natives"))
	{
		if (OS == "windows")
		{
			if (data["natives"].is_exist("windows"))
			{
				std::string replace_string = data["natives"]["windows"].to_string();
				Additionals::String::replace(replace_string, "${arch}", arch_type);
				return replace_string;
			}
			else
			{
				return "";
			}
		}
		else if (OS == "mac")
		{
			if (data["natives"].is_exist("osx"))
			{
				std::string replace_string = data["natives"]["osx"].to_string();
				Additionals::String::replace(replace_string, "${arch}", arch_type);
				return replace_string;
			}
			else
			{
				return "";
			}
		}
		else
		{
			if (data["natives"].is_exist("linux"))
			{
				std::string replace_string = data["natives"]["linux"].to_string();
				Additionals::String::replace(replace_string, "${arch}", arch_type);
				return replace_string;
			}
			else
			{
				return "";
			}
		}
	}
	else
	{
		return "";
	}
}

std::string MinecraftCpp::_get_jvm_platform_string()
{
	/*
	Get the name that is used the identify the platform
	*/
	if (OS == "windows")
	{
		if (ARCH == "x86")
		{
			return "windows-x86";
		}
		else
		{
			return "windows-x64";
		}
	}
	else if (OS == "linux")
	{
		if (ARCH == "x86")
		{
			return "linux-i386";
		}
		else
		{
			return "linux";
		}
	}
	else if (OS == "mac")
	{
		return "mac-os";
	}
	return "";
}

std::string MinecraftCpp::replace_arguments(std::string argstr, Json::JsonValue versionData,
	const std::string& path, MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Replace all 20 placeholder in arguments with the needed value
	*/

	/*if (Additionals::String::replace(argstr, "${natives_directory}", options.nativesDirectory))
		return argstr;
	if (Additionals::String::replace(argstr, "${launcher_name}", options.get("launcherName", std::string("null"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${launcher_version}", options.get("launcherVersion", std::string("null"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${classpath}", options.classpath))
		return argstr;
	if (Additionals::String::replace(argstr, "${auth_player_name}", options.get("username", std::string("{username}"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${version_name}", versionData["id"].to_string()))
		return argstr;
	if (Additionals::String::replace(argstr, "${game_directory}", options.get("gameDirectory", path)))
		return argstr;
	if (Additionals::String::replace(argstr, "${assets_root}", Join({ path, "assets" })))
		return argstr;
	if (Additionals::String::replace(argstr, "${assets_index_name}", versionData["assets"] != nullptr ? versionData["assets"].to_string() : versionData["id"].to_string()))
		return argstr;
	if (Additionals::String::replace(argstr, "${auth_uuid}", options.get("uuid", std::string("{uuid}"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${auth_access_token}", options.get("token", std::string("{token}"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${user_type}", "mojang"))
		return argstr;
	if (Additionals::String::replace(argstr, "${version_type}", versionData["type"].to_string()))
		return argstr;
	if (Additionals::String::replace(argstr, "${user_properties}", "{}"))
		return argstr;
	if (Additionals::String::replace(argstr, "${resolution_width}", options.get("resolutionWidth", std::string("854"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${resolution_height}", options.get("resolutionHeight", std::string("480"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${game_assets}", Join({ path, "assets", "virtual", "legacy" })))
		return argstr;
	if (Additionals::String::replace(argstr, "${auth_session}", options.get("token", std::string("{token}"))))
		return argstr;
	if (Additionals::String::replace(argstr, "${library_directory}", Join({ path, "libraries" })))
		return argstr;
	if (Additionals::String::replace(argstr, "${classpath_separator}", MinecraftCpp::get_classpath_separator()))
		return argstr;

	return std::string();*/

	Additionals::String::replace(argstr, "${natives_directory}", options.nativesDirectory);
	Additionals::String::replace(argstr, "${launcher_name}", options.get("launcherName", std::string("null")));
	Additionals::String::replace(argstr, "${launcher_version}", options.get("launcherVersion", std::string("null")));
	Additionals::String::replace(argstr, "${classpath}", options.classpath);
	Additionals::String::replace(argstr, "${auth_player_name}", options.get("username", std::string("{username}")));
	Additionals::String::replace(argstr, "${version_name}", versionData["id"].to_string());
	Additionals::String::replace(argstr, "${game_directory}", options.get("gameDirectory", path));
	Additionals::String::replace(argstr, "${assets_root}", Join({ path, "assets" }));
	Additionals::String::replace(argstr, "${assets_index_name}", versionData["assets"] != nullptr ? versionData["assets"].to_string() : versionData["id"].to_string());
	Additionals::String::replace(argstr, "${auth_uuid}", options.get("uuid", std::string("{uuid}")));
	Additionals::String::replace(argstr, "${auth_access_token}", options.get("token", std::string("{token}")));
	Additionals::String::replace(argstr, "${user_type}", "mojang");
	Additionals::String::replace(argstr, "${version_type}", versionData["type"].to_string());
	Additionals::String::replace(argstr, "${user_properties}", "{}");
	Additionals::String::replace(argstr, "${resolution_width}", options.get("resolutionWidth", std::string("854")));
	Additionals::String::replace(argstr, "${resolution_height}", options.get("resolutionHeight", std::string("480")));
	Additionals::String::replace(argstr, "${game_assets}", Join({ path, "assets", "virtual", "legacy" }));
	Additionals::String::replace(argstr, "${auth_session}", options.get("token", std::string("{token}")));
	Additionals::String::replace(argstr, "${library_directory}", Join({ path, "libraries" }));
	Additionals::String::replace(argstr, "${classpath_separator}", MinecraftCpp::get_classpath_separator());
	Additionals::String::replace(argstr, "${quickPlayPath}", options.get("quickPlayPath", std::string("quickPlayPath")));
	Additionals::String::replace(argstr, "${quickPlaySingleplayer}", options.get("quickPlaySingleplayer", std::string("quickPlaySingleplayer")));
	Additionals::String::replace(argstr, "${quickPlayMultiplayer}", options.get("quickPlayMultiplayer", std::string("quickPlayMultiplayer")));
	Additionals::String::replace(argstr, "${quickPlayRealms}", options.get("quickPlayRealms", std::string("quickPlayRealms")));

	return argstr;
}

std::string MinecraftCpp::get_executable_path(const std::string& jvm_version, const std::string& minecraft_directory)
{
	/*
	Returns the path to the executable. Returns None if none is found.
	*/
	std::string java_path = Join({ minecraft_directory, "runtime", jvm_version, _get_jvm_platform_string(), jvm_version, "bin", "java" });
	if (std::filesystem::exists(java_path))
	{
		if (!std::filesystem::is_directory(java_path))
		{
			return java_path;
		}
		else if (!std::filesystem::is_directory(java_path + ".exe"))
		{
			return java_path + ".exe";
		}
	}

	std::string java_w_path = java_path;
	Additionals::String::replace(java_w_path, Join({ "bin", "java" }), Join({ "jre.bundle", "Contents", "Home", "bin", "java" }));

	if (std::filesystem::exists(java_w_path))
	{
		if (!std::filesystem::is_directory(java_w_path))
		{
			return java_w_path;
		}
		else
		{
			return "";
		}
	}
	return "";
}

bool MinecraftCpp::install_libraries(Json::JsonValue data, const std::string& path, CallbackNull* callback)
{
	/*
	Install all libraries
	*/

	callback->OnProgress(NULL, NULL, NULL, L"Download Libraries");
	callback->OnProgress(NULL, NULL, NULL, std::to_wstring(data["libraries"].get_count() - 1).c_str());

	int count = -1;
	for (auto& var : data["libraries"].get_array())
	{
		++count;

		MinecraftCpp::option::MinecraftOptions empty;

		// Check, if the rules allow this lib for the current system
		if (!MinecraftCpp::parse_rule_list(var, "rules", empty))
		{
			continue;
		}

		// Turn the name into a path
		std::string currentPath = Join({ path, "libraries" });
		std::string downloadUrl = "";

		if (var.is_exist("url"))
		{
			if (Additionals::String::EndsWith(var["url"].to_string(), "/"))
			{
				std::string download_string = Additionals::String::rtrim_copy(var["url"].to_string(), '/');
				downloadUrl = download_string;
			}
			else
			{
				downloadUrl = var["url"].to_string();
			}
		}
		else
		{
			downloadUrl = "https://libraries.minecraft.net";
		}

		std::string libPath;
		std::string name;
		std::string version;

		if (var["name"] != nullptr)
		{
			libPath = Additionals::String::split(var["name"].to_string(), ':')[0];
			name = Additionals::String::split(var["name"].to_string(), ':')[1];
			version = Additionals::String::split(var["name"].to_string(), ':')[2];
		}
		else
		{
			continue;
		}

		for (auto& libPart : Additionals::String::split(libPath, '.'))
		{
			currentPath = Join({ currentPath, libPart });
			downloadUrl = downloadUrl + "/" + libPart;
		}

		std::string fileend;
		if (Additionals::String::split(version, '@')[0] != version)
		{
			auto splt = Additionals::String::split(version, '@');
			version = splt[0];
			fileend = splt[1];
		}
		else
		{
			fileend = "jar";
		}

		std::string jarFilename = name + "-" + version + "." + fileend;
		downloadUrl = downloadUrl + "/" + name + "/" + version;
		currentPath = Join({ currentPath, name, version });
		std::string native = get_natives(var);

		//Check if there is a native file
		std::string jarFilenameNative = "";
		if (native != "")
		{
			jarFilenameNative = name + "-" + version + "-" + native + ".jar";
		}
		jarFilename = name + "-" + version + "." + fileend;
		downloadUrl = downloadUrl + "/" + jarFilename;

		//Try to download the lib
		DownloadFile(downloadUrl, Join({ currentPath, jarFilename }), callback);

		if (!var.is_exist("downloads"))
		{
			if (var.is_exist("extract"))
			{
				extract_natives_file(Join({ currentPath, jarFilenameNative }), Join({ path, "versions", data["id"].to_string(), "natives" }), var["extract"]);
			}
			continue;
		}
		if (var["downloads"].is_exist("artifact"))
		{
			DownloadFile(var["downloads"]["artifact"]["url"].to_string(), Join({ path, "libraries", var["downloads"]["artifact"]["path"].to_string() }), callback);
		}
		if (native != "")
		{
			DownloadFile(var["downloads"]["classifiers"][native]["url"].to_string(), Join({ currentPath, jarFilenameNative }), callback);
			if (var["extract"] != nullptr)
			{
				extract_natives_file(Join({ currentPath, jarFilenameNative }), Join({ path, "versions", data["id"].to_string(), "natives" }), var["extract"]);
			}
		}
		callback->OnProgress(count, NULL, NULL, NULL);
	}
	return true;
}

bool MinecraftCpp::extract_natives_file(const std::string& filename, const std::string& extract_path, Json::JsonValue extract_data)
{
	/*
	Unpack natives
	*/
	bool ret = std::filesystem::create_directories(extract_path);

	if (!std::filesystem::exists(filename))
	{
		return false;
	}

	QZipReader zArchive(filename.c_str());

	foreach(QZipReader::FileInfo var, zArchive.fileInfoList())
	{
		for (auto& var2 : extract_data["exclude"].get_array())
		{
			if (Additionals::Path::getFileNameFromPath(var.filePath.toStdString())._Starts_with(var2.to_string()))
			{
				continue;
			}
		}
		int count = 0;
		for (auto& var : Additionals::String::split(var.filePath.toStdString(), '.'))
		{
			++count;
		}
		if (count == 1)
		{
			continue;
		}
		if (!std::filesystem::exists(extract_path + "\\" + var.filePath.toStdString()))
		{
			Additionals::archives::decompressFile(zArchive, var, extract_path + "\\" + var.filePath.toStdString());
		}
	}
	return true;
}

bool MinecraftCpp::install_assets(Json::JsonValue data, const std::string& path, CallbackNull* callback)
{
	/*
	Install all assets
	*/
	// Old versions dosen't have this
	if (!data.is_exist("assetIndex"))
	{
		return false;
	}
	callback->OnProgress(NULL, NULL, NULL, L"Download Assets");

	// Download all assets
	Json::JsonParcer jsonParcer;
	DownloadFile(
		data["assetIndex"]["url"].to_string(),
		Join({ path, "assets", "indexes", (data["assets"].to_string() + ".json") }),
		callback,
		data["assetIndex"]["sha1"].to_string()
	);
	Json::JsonValue assets_data = jsonParcer.ParseFile(Join({ path, "assets", "indexes", (data["assets"].to_string() + ".json") }));

	// The assets has a hash. e.g. c4dbabc820f04ba685694c63359429b22e3a62b5
	// With this hash, it can be download from https://resources.download.minecraft.net/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
	// And saved at assets/objects/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
	//return true;
	callback->OnProgress(NULL, assets_data["objects"].get_count() - 1, NULL, NULL);

	int count = 0;
	for (auto& var : assets_data["objects"].get_object())
	{
		DDIC::Download::Files::download_file
		(
			(
				"https://resources.download.minecraft.net/" +
				var.second["hash"].to_string().substr(0, 2) +
				"/" +
				var.second["hash"].to_string()
				),
			(
				path + '\\' + "assets" + '\\' + "objects" + '\\' +
				var.second["hash"].to_string().substr(0, 2) + '\\' +
				var.second["hash"].to_string()
				),
			callback,
			var.second["hash"].to_string()
		);

		++count;
		callback->OnProgress(count, NULL, NULL, NULL);
	}
	callback->OnProgress(NULL, NULL, 6, NULL);
	return true;
}

bool MinecraftCpp::install_jvm_runtime(const std::string& jvm_version, const std::string& minecraft_directory, CallbackNull* callback)
{
	/*
	Installs the given jvm runtime. callback is the same dict as in the install module.
	*/
	std::string _JVM_MANIFEST_URL = "https://launchermeta.mojang.com/v1/products/java-runtime/2ec0cc96c44e5a76b9c8b7c39df7210883d12871/all.json";

	Json::JsonParcer jsonParcer;
	std::string platform_string = _get_jvm_platform_string();
	std::string download_path = DDIC::Download::Files::download_file(_JVM_MANIFEST_URL);
	Json::JsonValue manifest_data = jsonParcer.ParseFile(download_path.c_str());

	// Check if the jvm version exists
	if (!manifest_data[platform_string].is_exist(jvm_version))
	{
		std::cout << "Version Not Found" << jvm_version << std::endl;

		return false;
	}

	// Check if there is a platform manifest
	if (manifest_data[platform_string][jvm_version].get_count() == 0)
	{
		return false;
	}

	Json::JsonValue platform_manifest = jsonParcer.ParseFile(DownloadFile(manifest_data[platform_string][jvm_version][0]["manifest"]["url"].to_string()).c_str());
	std::string base_path = Join({ minecraft_directory, "runtime", jvm_version, platform_string, jvm_version });

	// Download all files of the runtime
	//callback.get("setMax", empty)(len(platform_manifest["files"]) - 1)
	callback->OnProgress(NULL, platform_manifest["files"].get_count() - 1, NULL, NULL);
	int count = 0;
	std::vector<std::filesystem::path> file_list;
	for (auto& var : platform_manifest["files"].get_object())
	{
		std::filesystem::path current_path = Join({ base_path, var.first });

		if (var.second["type"].to_string() == "file")
		{
			// Prefer downloading the compresses file
			if (var.second["downloads"].is_exist("lzma"))
			{
				DownloadFile(var.second["downloads"]["lzma"]["url"].to_string(), current_path.u8string(), callback, var.second["downloads"]["raw"]["sha1"].to_string(), true);
			}
			else
			{
				DownloadFile(var.second["downloads"]["raw"]["url"].to_string(), current_path.u8string(), callback, var.second["downloads"]["raw"]["sha1"].to_string());
			}

			// Make files executable on unix systems
			if (var.second["executable"] != nullptr)
			{
				if (std::filesystem::exists(current_path) && OS == "linux")
				{
					std::string command = "chmod ";
					command += "+x ";
					command += current_path.u8string();
					system(command.c_str());
				}
			}

			file_list.push_back(var.first);
		}
		else if (var.second["type"].to_string() == "directory")
		{
			int outp = std::filesystem::create_directories(current_path);
		}
		else if (var.second["type"].to_string() == "link")
		{
			check_path_inside_minecraft_directory(minecraft_directory, Join({ base_path, var.second["target"].to_string() }));

			if (!std::filesystem::is_directory(current_path.parent_path()))
			{
				int outp = std::filesystem::create_directories(current_path);
			}

			try
			{
				std::filesystem::create_symlink(var.second["target"].to_string(), current_path);
			}
			catch (const std::exception& exc)
			{
			}
		}
		callback->OnProgress(count, NULL, NULL, NULL);
		++count;
	}
	callback->OnProgress(NULL, NULL, 6, NULL);

	// Create the.version file
	std::string path = Join({ minecraft_directory, "runtime", jvm_version, platform_string, ".version" });
	manifest_data[platform_string][jvm_version][0]["version"]["name"].save_json_to_file(path, 4);

	// Writes the .sha1 file
	// It has the structure {path} /#// {sha1} {creation time in nanoseconds}
	std::string sha1_path = Join({ minecraft_directory, "runtime", jvm_version, platform_string, std::string("jvm_version") + ".sha1" });
	check_path_inside_minecraft_directory(minecraft_directory, sha1_path);
	//with open(sha1_path, "w", encoding = "utf-8") as f :
	std::ofstream file = std::ofstream(sha1_path);
	for (auto& current_file : file_list)
	{
		std::filesystem::path current_path = Join({ base_path, current_file.u8string() });
		std::filesystem::file_time_type _ctime = std::filesystem::last_write_time(current_path);
		std::string sha1 = get_sha1_hash(current_path);

		auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(_ctime -
			std::filesystem::file_time_type::clock::now()
			+ std::chrono::system_clock::now());

		std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
		std::tm* gmt = std::gmtime(&tt);
		std::stringstream buffer;
		buffer << std::put_time(gmt, "%A, %d %B %Y %H:%M");
		std::string formattedFileTime = buffer.str();

		file << current_file << " /#// " << sha1 << " " << formattedFileTime << "\n";
	}
	file.close();

	return true;
}

void MinecraftCpp::check_path_inside_minecraft_directory(const std::string& minecraft_directory, const std::string& path)
{
	if (!std::filesystem::absolute(path).u8string()._Starts_with(std::filesystem::absolute(minecraft_directory).u8string()))
		throw FileOutsideMinecraftDirectoryException(std::filesystem::absolute(path), std::filesystem::absolute(minecraft_directory));
}

std::string MinecraftCpp::get_sha1_hash(const std::filesystem::path& path)
{
	return SHA1::from_file(path.u8string());
}

std::string MinecraftCpp::get_arguments(
	Json::JsonValue& data,
	Json::JsonValue versionData,
	const std::string& path,
	MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Returns all arguments from the version.json
	*/

	std::string arglist = "";
	if (data.get_type() == Json::JsonTypes::Array)
	{
		for (auto& var : data.get_array())
		{
			if (var.get_type() == Json::JsonTypes::String)
			{
				arglist += MinecraftCpp::replace_arguments(var.to_string(), versionData, path, options);
				arglist += " ";
			}
			else
			{
				// Rules might has 2 different names in different versions.json
				if (var.is_exist("compatibilityRules") && !parse_rule_list(var, "compatibilityRules", options))
				{
					continue;
				}
				if (var.is_exist("rules") && !parse_rule_list(var, "rules", options))
				{
					continue;
				}

				// var could be the argument
				if (var["value"].get_type() == Json::JsonTypes::String)
				{
					qInfo() << "data " << data.to_string() << std::endl;
					qInfo() << "var " << var.to_string() << std::endl;
					std::string replace = MinecraftCpp::replace_arguments(var["value"].to_string(), versionData, path, options);
					arglist += replace;
					arglist += " ";
				}
				else
				{
					for (auto& v : var["value"].get_object())
					{
						std::string val = replace_arguments(v.second.to_string(), versionData, path, options);
						arglist += val;
						arglist += " ";
					}
				}
			}
		}
	}
	else
	{
		for (auto& var : data.get_array())
		{
			if (var.get_type() == Json::JsonTypes::String)
			{
				arglist += MinecraftCpp::replace_arguments(var.to_string(), versionData, path, options);
			}
			else
			{
				// Rules might has 2 different names in different versions.json
				if (var.is_exist("compatibilityRules") && !parse_rule_list(var, "compatibilityRules", options))
				{
					continue;
				}
				if (var.is_exist("rules") && !parse_rule_list(var, "rules", options))
				{
					continue;
				}

				// var could be the argument
				if (var["value"].get_type() == Json::JsonTypes::String)
				{
					qInfo() << "data " << data.to_string() << std::endl;
					qInfo() << "var " << var.to_string() << std::endl;
					std::string replace = MinecraftCpp::replace_arguments(var["value"].to_string(), versionData, path, options);
					arglist += replace;
					arglist += " ";
				}
				else
				{
					for (auto& v : var["value"].get_object())
					{
						std::string val = replace_arguments(v.second.to_string(), versionData, path, options);
						arglist += val;
						arglist += " ";
					}
				}
			}
		}
	}
	return arglist;
}

std::string MinecraftCpp::get_arguments_string(Json::JsonValue versionData, const std::string& path,
	MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Turns the argument string from the version.json into a list
	*/
	std::string arglist = "";

	for (auto& var : Additionals::String::split(versionData["minecraftArguments"].to_string(), ' '))
	{
		var = replace_arguments(var, versionData, path, options);
		arglist += var + " ";
	}
	// Custom resolution is not in the list
	if (options.get("customResolution", false))
	{
		arglist += "--width";
		arglist += " ";
		arglist += options.get("resolutionWidth", "854");
		arglist += " ";
		arglist += "--height";
		arglist += " ";
		arglist += options.get("resolutionHeight", "480");
		arglist += " ";
	}
	if (options.get("demo", false))
	{
		arglist += "--demo";
		arglist += " ";
	}

	return arglist;
}

bool MinecraftCpp::forge::install_forge_version(const std::string& versionid, const std::string& path, CallbackNull* callback, const std::string& java)
{
	/*
	Installs a forge version. Fore more information look at the documentation.
	*/

	int random_num = 1 + (rand() % 100000);

	std::string FORGE_DOWNLOAD_URL = "https://files.minecraftforge.net/maven/net/minecraftforge/forge/" + versionid + "/forge-" + versionid + "-installer.jar";
	std::string temp_file_path = Additionals::TempFile::get_tempdir_SYSTEM() + ("forge-installer-" + std::to_string(random_num) + ".tmp");
	if (DownloadFile(FORGE_DOWNLOAD_URL, temp_file_path, callback) == "")
	{
		std::cout << "Version Not Found" << versionid << std::endl;
		return false;
	}

	QZipReader zArchive(temp_file_path.c_str());

	// Read the install_profile.json
	Json::JsonParcer json_parcer;
	Json::JsonValue version_data = nullptr;

	foreach(QZipReader::FileInfo var, zArchive.fileInfoList())
	{
		if (var.filePath == "install_profile.json")
		{
			std::string json_str = zArchive.fileData(var.filePath).toStdString();

			version_data = json_parcer.ParseJson(json_str);

			break;
		}
	}

	std::string forge_version_id = version_data["version"].to_string();

	// Make sure, the base version is installed
	install_minecraft_version(version_data["minecraft"].to_string(), path, callback);

	// Install all needed libs from install_profile.json
	install_libraries(version_data, path, callback);

	// Extract the version.json
	std::string version_json_path = Join({ path, "versions", forge_version_id, (forge_version_id + ".json") });
	extract_file(zArchive, "version.json", version_json_path);

	// Extract forge libs from the installer
	std::string forge_lib_path = Join({ path, "libraries", "net", "minecraftforge", "forge", versionid });
	extract_file(zArchive, ("maven/net/minecraftforge/forge/" + versionid + "/forge-" + versionid + ".jar"), (forge_lib_path + "\\" + ("forge-" + versionid + ".jar")));
	extract_file(zArchive, ("maven/net/minecraftforge/forge/" + versionid + "/forge-" + versionid + "-universal.jar"), Join({ forge_lib_path, ("forge-" + versionid + "-universal.jar") }));
	extract_file(zArchive, (versionid + "/forge-" + versionid + "-universal.jar"), Join({ forge_lib_path, ("forge-" + versionid + ".jar") }));

	// Extract the client.lzma
	std::string lzma_path = Additionals::TempFile::get_tempdir_SYSTEM() + ("lzma-" + std::to_string(random_num) + ".tmp");

	extract_file(zArchive, "data/client.lzma", lzma_path);

	// Install the rest with the vanilla function
	install_minecraft_version(forge_version_id, path, callback);

	// Run the processors
	forge_processors(version_data, path, lzma_path, temp_file_path, callback, java);

	// Delete the temporary files
	//std::filesystem::permissions(temp_file_path, std::filesystem::perms::all);
	DeleteFileA(temp_file_path.c_str());
	if (std::filesystem::exists(lzma_path) && !std::filesystem::is_directory(lzma_path))
	{
		std::filesystem::permissions(lzma_path, std::filesystem::perms::all);
		std::filesystem::remove(lzma_path);
	}

	zArchive.close();
	return true;
}

bool MinecraftCpp::forge::extract_file(const QZipReader& handler, const std::string& zip_path, const std::string& extract_path)
{
	/*
	Extract a file from a zip handler into the given path
	*/
	std::filesystem::path p = extract_path;
	std::filesystem::path dir = p.parent_path();
	DWORD attrib = GetFileAttributesW(dir.wstring().c_str());
	if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		if (!CreateDirectoryW(dir.wstring().c_str(), NULL))
		{
			// Обработка ошибки создания директории
			int error = GetLastError();
		}
	}

	QVector<QZipReader::FileInfo> allFiles = handler.fileInfoList();

	for (auto& var : allFiles)
	{
		if (var.filePath.toStdString() == zip_path)
		{
			Additionals::archives::decompressFile(handler, var, p.string());
			break;
		}
	}

	return true;
}

std::string MinecraftCpp::forge::get_data_library_path(const std::string& libname, const std::string& path)
{
	/*
	Turns the libname into a path
	*/
	std::string _libname = libname;

	for (size_t i = 0; _libname[i] != '\0'; i++)
	{
		if (i == 0)
		{
			continue;
		}
		if (_libname[i + 1] == '\0')
		{
			continue;
		}
		_libname[i - 1] = _libname[i];
	}

	std::string libpath = Join({ path, "libraries" });
	std::string base_path = Additionals::String::split(_libname, ':')[0];
	std::string libname_str = Additionals::String::split(_libname, ':')[1];
	std::string version = Additionals::String::split(_libname, ':')[2];
	std::string extra = Additionals::String::split(_libname, ':')[3];
	std::string fileend;

	for (auto& var : Additionals::String::split(base_path, '.'))
	{
		libpath = Join({ libpath, var });

		if (Additionals::String::split(extra, '@')[0] == extra)
		{
			fileend = "jar";
		}
		else
		{
			extra = Additionals::String::split(extra, '@')[0];
			fileend = Additionals::String::split(extra, '@')[1];
		}
	}

	libpath = Join({ libpath, _libname, version, (_libname + "-" + version + "-" + extra + "." + fileend) });
	return libpath;
}

std::string MinecraftCpp::forge::get_jar_mainclass(const std::string& path)
{
	/*
	Returns the mainclass of a given jar
	*/
	//Additionals::archives::Archive zArchive(path);

	// Parse the MANIFEST.MF
	/*for (auto& var : zArchive.entries)
	{
	}*/
	std::cout << "get_jar_mainclass is not done blyat" << std::endl;

	return "";
}

bool MinecraftCpp::forge::forge_processors(
	Json::JsonValue data,
	const std::string& minecraft_directory,
	const std::string& lzma_path,
	const std::string& installer_path,
	CallbackNull* callback,
	const std::string& java = nullptr)
{
	/*
	Run the processors of the install_profile.json
	*/
	int random_num = 1 + (rand() % 100000);
	std::string path = minecraft_directory;

	Json::JsonValue argument_vars = Json::JsonValue(std::unordered_map<std::string, Json::JsonValue>());
	Json::JsonValue value_ = Json::JsonValue(Join({ path, "versions", data["minecraft"].to_string(), (data["minecraft"].to_string() + ".jar") }));
	argument_vars.add_value("{MINECRAFT_JAR}", value_);

	for (auto& var : data["data"].get_object())
	{
		if (var.second["client"].to_string()._Starts_with("[") && Additionals::String::EndsWith(var.second["client"].to_string(), "]"))
		{
			argument_vars["{" + var.first + "}"] = get_data_library_path(var.second["client"].to_string(), path);
		}
		else
		{
			argument_vars["{" + var.first + "}"] = var.second["client"];
		}
	}
	std::string root_path = Additionals::TempFile::get_tempdir_SYSTEM() + "forge-root-" + std::to_string(random_num);

	argument_vars.replace_value("{INSTALLER}", installer_path);
	argument_vars.replace_value("{BINPATCH}", lzma_path);
	argument_vars.replace_value("{ROOT}", root_path);
	argument_vars.replace_value("{SIDE}", "client");

	std::string classpath_seperator = "";
	if (OS == "windows")
	{
		classpath_seperator = ";";
	}
	else
	{
		classpath_seperator = ":";
	}

	//callback.get("setMax", empty)(len(data["processors"]))
	//callback->OnProgress(NULL, (*data)["processors"]->to_int(), NULL, NULL);

	int count = -1;
	for (auto& var : data["processors"].get_array())
	{
		++count;

		if (!(var["sides"].is_exist("client")) || !(var["sides"] == var ? true : false))
		{
			// Skip server side only processors
			continue;
		}
		callback->OnProgress(NULL, NULL, NULL, (L"Running processor " + var["jar"].to_stringW()).c_str());

		// Get the classpath
		std::string classpath = "";
		for (auto& var2 : var["classpath"].get_array())
		{
			classpath = classpath + get_library_path(var2.to_string(), path) + classpath_seperator;
		}

		classpath = classpath + get_library_path(var["jar"].to_string(), path);
		std::string mainclass = get_jar_mainclass(get_library_path(var["jar"].to_string(), path));
		std::vector<std::string> command;
		command[0] = java == "" ? "java" : java + "-cp", classpath, mainclass;

		std::string variable = "";
		for (auto& var2 : var["args"].get_array())
		{
			variable = argument_vars[var2.to_string()] == nullptr ? var2.to_string() : argument_vars[var2.to_string()].to_string();
			if (variable._Starts_with("[") && Additionals::String::EndsWith(variable, "]"))
			{
				command.push_back(get_library_path(variable, path));
			}
			else
			{
				command.push_back(variable);
			}
		}

		for (auto& var2 : argument_vars.get_object())
		{
			for (size_t i = 0; i < command.size(); i++)
			{
				std::replace(command.begin(), command.end(), var2.first, var2.second.to_string());
				//command[i] = command[i].insert(libPart.first, libPart.second->to_string());
			}
		}

		std::string commant_strw = "";
		for (size_t i = 0; i < command.size(); i++)
		{
			commant_strw = commant_strw + command[i];
		}

		int out = system(commant_strw.c_str());

		callback->OnProgress(count, NULL, NULL, NULL);
	}
	if (std::filesystem::exists(root_path))
	{
		std::filesystem::remove(root_path);
	}

	return true;
}

int MinecraftCpp::fabric::install_fabric_version(const std::string& minecraft_version, const std::string& minecraft_directory, const std::string& loader_version, CallbackNull* callback, const std::string& java)
{
	/*
	Install a fabric version
	*/

	std::string loader = loader_version;

	// Check if the given version exists
	if (!_is_version_valid(minecraft_version, minecraft_directory))
	{
		qFatal() << "Version Not Found " << minecraft_version;
		return -1;
	}
	// Check if the given Minecraft version supported
	if (!_is_minecraft_version_supported(minecraft_version))
	{
		qFatal() << "Unsupported Version " << minecraft_version;
		return -1;
	}
	// Get latest loader version if not given
	if (loader == "")
	{
		loader = get_latest_loader_version();
	}
	// Make sure the Minecraft version is installed
	install_minecraft_version(minecraft_version, minecraft_directory, callback = callback);
	// Get installer version
	std::string installer_version = get_latest_installer_version();
	std::string installer_download_url = "https://maven.fabricmc.net/net/fabricmc/fabric-installer/" + installer_version + "\\fabric-installer-" + installer_version + ".jar";
	// Generate a temporary path for downloading the installer
	int random_num = 100 + (rand() % 10000);
	std::string installer_path = std::filesystem::temp_directory_path().string() + "fabric-installer-" + std::to_string(random_num) + ".tmp";
	// Download the installer
	DownloadFile(installer_download_url, installer_path, callback = callback);
	// Run the installer see https ://fabricmc.net/wiki/install#cli_installation
	callback->OnProgress(NULL, NULL, NULL, L"Running fabric installer");
	std::vector<std::string> command;

	command.push_back(java == "" ? "java" : java);
	command.push_back("-jar");
	command.push_back(installer_path);
	command.push_back("client");
	command.push_back("-dir");
	command.push_back(minecraft_directory);
	command.push_back("-mcversion");
	command.push_back(minecraft_version);
	command.push_back("-loader");
	command.push_back(loader_version);
	command.push_back("-launcher win32");
	command.push_back("-noprofile");
	command.push_back("-snapshot");

	std::string command_string;
	for (const auto& arg : command)
	{
		command_string += arg + " ";
	}

	//int result = std::system(command_string.c_str());

	MinecraftCpp::start_minecraft("", command_string);

	/*if (result != 0)
	{
		qFatal() << "External Program Error " << command_string;
		return -1;
	}*/

	// Удаляем файл с помощью std::remove()
	if (std::remove(installer_path.c_str()) != 0)
	{
		qFatal() << "Error to delete installer file";
	}
	else
	{
		qInfo() << "Installer file sucsesful delete" << std::endl;
	}

	// Install all libs of fabric
	std::string fabric_minecraft_version = "fabric-loader-" + loader_version + "-" + minecraft_version;
	install_minecraft_version(fabric_minecraft_version, minecraft_directory, callback = callback);

	return 0;
}

bool MinecraftCpp::fabric::_is_version_valid(const std::string& version, const std::string& minecraft_directory)
{
	/*
	Checks if the given version exists
	*/
	if (std::filesystem::is_directory(Join({ minecraft_directory, "versions", version })))
	{
		return true;
	}
	Json::JsonValue arr = get_version_list();
	for (auto& i : arr.get_array())
	{
		if (i["id"].to_string() == version)
		{
			return true;
		}
	}
	return false;
}

bool MinecraftCpp::fabric::_is_minecraft_version_supported(const std::string& version)
{
	/*
	Checks if a Minecraft version supported by fabric
	*/
	Json::JsonValue minecraft_versions = get_all_minecraft_versions();
	for (auto& i : minecraft_versions.get_array())
	{
		if (i["version"].to_string() == version)
		{
			return true;
		}
	}
	return false;
}

Json::JsonValue MinecraftCpp::fabric::get_all_minecraft_versions()
{
	/*
	Returns all available Minecraft Versions for fabric
	*/
	std::string FABRIC_MINECARFT_VERSIONS_URL = "https://meta.fabricmc.net/v2/versions/game";
	Json::JsonParcer parcer;
	return parcer.ParseUrl(FABRIC_MINECARFT_VERSIONS_URL);
}

std::string MinecraftCpp::fabric::get_latest_loader_version()
{
	/*
	Get the latest loader version
	*/
	Json::JsonValue loader_versions = get_all_loader_versions();
	return loader_versions[0]["version"].to_string();
}

Json::JsonValue MinecraftCpp::fabric::get_all_loader_versions()
{
	/*
	Returns all loader versions
	*/
	std::string FABRIC_LOADER_VERSIONS_URL = "https://meta.fabricmc.net/v2/versions/loader";
	Json::JsonParcer parcer;
	return parcer.ParseUrl(FABRIC_LOADER_VERSIONS_URL);
}

std::string MinecraftCpp::fabric::get_latest_installer_version()
{
	/*
	Returns the latest installer version
	*/
	std::string FABRIC_INSTALLER_MAVEN_URL = "https://maven.fabricmc.net/net/fabricmc/fabric-installer/maven-metadata.xml";
	return parse_maven_metadata(FABRIC_INSTALLER_MAVEN_URL)["latest"].to_string();
}

Json::JsonValue MinecraftCpp::fabric::parse_maven_metadata(const std::string& url)
{
	/*
	Parses a maven metadata file
	*/

	Json::JsonValue data = Json::JsonValue(std::unordered_map<std::string, Json::JsonValue>());
	std::string text;

	std::string destenation_file = Additionals::TempFile::get_tempdir_SYSTEM();

	{
		std::string replace_url = url;
		replace_url = Additionals::String::split(url, '/')[Additionals::String::split(url, '/').size() - 1];
		destenation_file = destenation_file /*+ "\\"*/ + replace_url;
	}

	HRESULT resurl = URLDownloadToFileA(NULL, url.c_str(), destenation_file.c_str(), NULL, NULL);

	if (resurl == S_OK)
	{
		if (!std::filesystem::exists(destenation_file))
		{
			std::cout << "Unable to open file: " << destenation_file << std::endl;
			return nullptr;
		}

		std::fstream file(destenation_file, std::ios::in);

		if (!file.is_open())
		{
			std::cout << "failed to open " << destenation_file << std::endl;
			return nullptr;
		}
		else
		{
			std::string json_str;

			std::string line;

			while (std::getline(file, line))
			{
				json_str += line + '\n';
			}

			file.close();

			text = json_str;
		}
		DeleteFileA(destenation_file.c_str());
	}
	else
	{
		std::cerr << "Dont download file in json" << std::endl;
		text = "";
	}

	std::smatch mathc;

	// The structure of the metadata file is simple.So you don't need a XML parser. It can be parsed using RegEx.
	std::regex pattern(R"(<release>(.*?)</release>)");
	if (std::regex_search(text, mathc, pattern))
	{
		// matches[0] содержит всю найденную строку, matches[1] содержит текст между тегами
		std::string result = mathc[1];
		data.add_value(std::make_pair("release", Json::JsonValue(result)));
	}

	pattern = R"(<latest>(.*?)</latest>)";
	if (std::regex_search(text, mathc, pattern))
	{
		// matches[0] содержит всю найденную строку, matches[1] содержит текст между тегами
		std::string result = mathc[1];
		data.add_value(std::make_pair("latest", Json::JsonValue(result)));
	}

	data.add_value(std::make_pair("versions", Json::JsonValue(std::vector<Json::JsonValue>())));

	pattern = R"(<version>(.*?)</version>)";
	while (std::regex_search(text, mathc, pattern))
	{
		// matches[0] содержит всю найденную строку, matches[1] содержит текст между тегами
		std::string result = mathc[1];
		data["versions"].add_value(Json::JsonValue(result));

		text = mathc.suffix();
	}

	return data;
}