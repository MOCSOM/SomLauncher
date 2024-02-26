#include "Minecraftus.h"

std::string MinecraftCpp::option::MinecraftOptions::get(const std::string& param, const std::string& writ) const
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
		field = this->executablePath.u8string();
	else if (param == "jvmArguments")
		field = this->jvmArguments;
	else if (param == "launcherName")
		field = this->launcherName;
	else if (param == "launcherVersion")
		field = this->launcherVersion;
	else if (param == "gameDirectory")
		field = this->gameDirectory.u8string();
	else if (param == "resolutionWidth")
		field = this->resolutionWidth;
	else if (param == "resolutionHeight")
		field = this->resolutionHeight;
	else if (param == "server")
		field = this->server;
	else if (param == "port")
		field = this->port;
	else if (param == "nativesDirectory")
		field = this->nativesDirectory.u8string();
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

bool MinecraftCpp::option::MinecraftOptions::get(const std::string& param, bool writ) const
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

bool MinecraftCpp::install_minecraft_version(const std::string& versionid, const std::filesystem::path& minecraft_directory, std::shared_ptr<CallbackNull> callback)
{
	/*
	Install a Minecraft Version. Fore more Information take a look at the documentation"
	*/
	std::filesystem::path full_dir = minecraft_directory / "versions" / versionid / (versionid + ".json");

	std::filesystem::path download_dir = minecraft_directory / "downloads";

	if (!std::filesystem::exists(download_dir))
	{
		bool out_mkdir = std::filesystem::create_directories(download_dir);
		qInfo() << "java dir is maked with status: " << out_mkdir << std::endl;
	}

	if (std::filesystem::exists(full_dir))
	{
		if (!std::filesystem::is_directory(full_dir))
		{
			qInfo() << "doversion install" << std::endl;
			do_version_install(versionid, minecraft_directory, callback);
			qInfo() << "version is installed" << std::endl;
			return true;
		}
	}

	auto version_manifest_file = DownloadFile("https://launchermeta.mojang.com/mc/game/version_manifest.json",
		download_dir, callback);

	std::ifstream ifstr(version_manifest_file);
	nlohmann::json version_list = nlohmann::json::parse(ifstr);
	ifstr.close();


	if (version_list == nullptr)
	{
		qFatal() << "error in version list";
	}

	for (auto& var : version_list["versions"])
	{
		qInfo() << "doversion install" << std::endl;
		if (var["id"].template get<std::string>() == versionid)
		{
			qInfo() << "doversion install" << std::endl;
			do_version_install(versionid, minecraft_directory, callback, var["url"].template get<std::string>());
			qInfo() << "version is installed" << std::endl;
			return true;
		}
	}

	for (auto& var : version_list["versions"].items())
	{
		qInfo() << "doversion install obj" << std::endl;
		if (var.value()["id"].template get<std::string>() == versionid)
		{
			qInfo() << "doversion install" << std::endl;
			do_version_install(versionid, minecraft_directory, callback, var.value()["url"].template get<std::string>());
			qInfo() << "version is installed" << std::endl;
			return true;
		}
	}

	qWarning() << "minecraft not installed";
	return false;
}

bool MinecraftCpp::do_version_install(const std::string& versionid, const std::filesystem::path& path,
	std::shared_ptr<CallbackNull> callback, const std::string& url)
{
	/*
	Install the given version
	*/
	std::filesystem::path path_ver_json = path / "versions" / versionid / (versionid + ".json");

	// Download and read versions.json
	qInfo() << "Download and read versions.json..." << std::endl;
	if (url != "")
	{
		DownloadFile(url, path_ver_json, callback);
	}
	std::ifstream ifstr(path_ver_json);
	nlohmann::json versiondata = nlohmann::json::parse(ifstr);
	ifstr.close();

	// For forge
	qInfo() << "Download For forge..." << std::endl;
	if (versiondata.contains("inheritsFrom"))
	{
		qInfo() << "install_minecraft_version For forge..." << std::endl;
		install_minecraft_version(versiondata["inheritsFrom"].template get<std::string>(), path, callback);
		versiondata = inherit_json(versiondata, path);
	}
	install_libraries(versiondata, path, callback);
	install_assets(versiondata, path, callback);

	//Download logging config
	qInfo() << "Download logging config..." << std::endl;
	std::filesystem::path logger_file = "";
	if (versiondata.contains("logging"))
	{
		if (versiondata["logging"].size() != 0)
		{
			callback->setTotalDownloadSize(versiondata["logging"]["client"]["file"]["size"].template get<int>());
			logger_file = path / "assets" / "log_configs" / versiondata["logging"]["client"]["file"]["id"].template get<std::string>();
			DownloadFile(versiondata["logging"]["client"]["file"]["url"].template get<std::string>(), logger_file, callback); //to with sha
		}
	}

	//Download minecraft.jar
	qInfo() << "Download minecraft.jar..." << std::endl;
	if (versiondata.contains("downloads"))
	{
		callback->setTotalDownloadSize(versiondata["downloads"]["client"]["size"].template get<int>());
		DownloadFile(versiondata["downloads"]["client"]["url"].template get<std::string>(), path / "versions" / versiondata["id"].template get<std::string>() / (versiondata["id"].template get<std::string>() + ".jar"), callback, versiondata["downloads"]["client"]["sha1"].template get<std::string>());
	}

	//Need to copy jar for old forge versions
	qInfo() << "Need to copy jar for old forge versions..." << std::endl;
	if (std::filesystem::is_directory(path / "versions" / versiondata["id"].template get<std::string>() / (versiondata["id"].template get<std::string>() + ".jar")) && versiondata.contains("inheritsFrom"))
	{
		std::filesystem::copy
		(
			path / "versions" / versiondata["id"].template get<std::string>() / (versiondata["id"].template get<std::string>() + ".jar"),
			path / "versions" / versiondata["inheritsFrom"].template get<std::string>() / (versiondata["inheritsFrom"].template get<std::string>() + ".jar")
		);
	}

	//Install java runtime if needed
	/*qInfo() << "Install java runtime if needed..." << std::endl;
	if (versiondata.is_exist("javaVersion"))
	{
		install_jvm_runtime(versiondata["javaVersion"]["component"].to_string(), path, callback);
	}*/

	return true;
}

nlohmann::json MinecraftCpp::inherit_json(nlohmann::json original_data, const std::filesystem::path& path)
{
	/*
	Implement the inheritsFrom function
	See https://github.com/tomsik68/mclauncher-api/wiki/Version-Inheritance-&-forge
	*/

	nlohmann::json inherit_version = original_data["inheritsFrom"];

	std::filesystem::path path_inh_json = path / "versions" / inherit_version.template get<std::string>() / (inherit_version.template get<std::string>() + ".json");

	//SJson::JsonValue new_data = SJson::JsonParcer::ParseFile(path_inh_json);

	nlohmann::json new_data;
	std::ifstream ifs;
	ifs.open(path_inh_json);
	ifs >> new_data;
	ifs.close();

	std::cout << original_data["libraries"].size() << std::endl;
	std::cout << new_data["libraries"].size() << std::endl;

	for (auto& var : original_data.items())
	{
		if (var.value().type() == nlohmann::json_abi_v3_11_3::detail::value_t::array &&
			new_data[var.key()].type() == nlohmann::json_abi_v3_11_3::detail::value_t::array)
		{
			//std::cout << new_data[var.key()] << std::endl;
			for (auto& elem : var.value())
			{
				new_data[var.key()].push_back(elem);
			}
		}
		else if (var.value().type() == nlohmann::json_abi_v3_11_3::detail::value_t::object &&
			new_data[var.key()].type() == nlohmann::json_abi_v3_11_3::detail::value_t::object)
		{
			for (auto& variable : var.value().items())
			{
				if (variable.value().type() == nlohmann::json_abi_v3_11_3::detail::value_t::array)
				{
					for (auto& elem : variable.value())
					{
						new_data[var.key()][variable.key()].push_back(elem);
					}
					//new_data[var.key()][variable.key()] += variable;
				}
			}
		}
		else
		{
			if (new_data.contains(var.key()))
			{
				new_data.erase(var.key());
			}
			new_data[var.key()] = var.value();
		}
	}

	std::cout << new_data["libraries"].size() << std::endl;

	return new_data;
}

SJson::JsonValue MinecraftCpp::get_version_list()
{
	/*
	Returns all versions that Mojang offers to download
	*/
	qInfo() << "getting version list" << std::endl;
	SJson::JsonParcer parcer;

	SJson::JsonValue vlist = parcer.ParseUrl("https://launchermeta.mojang.com/mc/game/version_manifest.json");
	SJson::JsonValue returnlist = SJson::JsonValue(std::vector<SJson::JsonValue>());

	int count = -1;
	for (auto& i : vlist["versions"].get_array())
	{
		++count;
		SJson::JsonValue object = SJson::JsonValue(std::unordered_map<std::string, SJson::JsonValue>());

		object.add_value(std::make_pair("id", i["id"]));
		object.add_value(std::make_pair("type", i["type"]));

		std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(_parseDateTime(i["releaseTime"].to_string()).time_since_epoch());

		object.add_value(std::make_pair("releaseTime", SJson::JsonValue(seconds.count())));

		returnlist.add_value(object);
	}
	return returnlist;
}

std::vector<std::string> MinecraftCpp::generateCommandLine(const std::filesystem::path& nativeFolder,
	MinecraftCpp::option::LaunchOptions& options)
{
	return std::vector<std::string>();

	//CommandBuilder res;
	//Version version;

	//switch (options.processPriority)
	//{
	//case option::ProcessPriority::HIGH:
	//	if (OS == "windows")
	//	{
	//		// res.add("cmd", "/C", "start", "unused title", "/B", "/high");
	//	}
	//	else if (OS == "linux" || OS == "mac")
	//	{
	//		res.add({ "nice", "-n", "-5" });
	//	}
	//	break;
	//case option::ProcessPriority::ABOVE_NORMAL:
	//	if (OS == "windows")
	//	{
	//		// res.add("cmd", "/C", "start", "unused title", "/B", "/abovenormal");
	//	}
	//	else if (OS == "linux" || OS == "mac")
	//	{
	//		res.add({ "nice", "-n", "-1" });
	//	}
	//	break;
	//case option::ProcessPriority::NORMAL:
	//	// do nothing
	//	break;
	//case option::ProcessPriority::BELOW_NORMAL:
	//	if (OS == "windows")
	//	{
	//		// res.add("cmd", "/C", "start", "unused title", "/B", "/belownormal");
	//	}
	//	else if (OS == "linux" || OS == "mac")
	//	{
	//		res.add({ "nice", "-n", "1" });
	//	}
	//	break;
	//case option::ProcessPriority::LOW:
	//	if (OS == "windows")
	//	{
	//		// res.add("cmd", "/C", "start", "unused title", "/B", "/low");
	//	}
	//	else if (OS == "linux" || OS == "mac")
	//	{
	//		res.add({ "nice", "-n", "5" });
	//	}
	//	break;
	//}

	//// Executable
	//if (!options.wrapper.empty())
	//	res.addAllWithoutParsing(StringUtils::tokenize(options.wrapper));

	//res.add({ options.java });

	//res.addAllWithoutParsing({ options.noGeneratedJVMArgs, "" });

	////TODO: proxy
	///*Proxy proxy = options.getProxy();
	//if (proxy && options.getProxyUser().empty() && options.getProxyPass().empty())
	//{
	//	auto address = std::any_cast<InetSocketAddress>(proxy.address());
	//	if (address) {
	//		std::string host = address->getHostString();
	//		int port = address->getPort();
	//		if (proxy.type() == Proxy::Type::HTTP)
	//		{
	//			res.addDefault("-Dhttp.proxyHost=", host);
	//			res.addDefault("-Dhttp.proxyPort=", std::to_string(port));
	//			res.addDefault("-Dhttps.proxyHost=", host);
	//			res.addDefault("-Dhttps.proxyPort=", std::to_string(port));
	//		}
	//		else if (proxy.type() == Proxy::Type::SOCKS)
	//		{
	//			res.addDefault("-DsocksProxyHost=", host);
	//			res.addDefault("-DsocksProxyPort=", std::to_string(port));
	//		}
	//	}
	//}*/

	///*if (options.getMaxMemory() > 0)
	//	res.addDefault("-Xmx", std::to_string(options.getMaxMemory()) + "m");

	//if (options.getMinMemory() > 0 && (options.getMaxMemory() <= 0 || options.getMinMemory() <= options.getMaxMemory()))
	//	res.addDefault("-Xms", std::to_string(options.getMinMemory()) + "m");*/

	//if (options.metaspace > 0)
	//{
	//	if (options.java < "8")
	//		res.addDefault("-XX:PermSize=", std::to_string(options.metaspace) + "m");
	//	else
	//		res.addDefault("-XX:MetaspaceSize=", std::to_string(options.metaspace) + "m");
	//}

	//res.addAllDefaultWithoutParsing(options.javaArguments);

	//std::string encoding = OS;
	//std::string fileEncoding = res.addDefault("-Dfile.encoding=", encoding);
	//if (fileEncoding != "-Dfile.encoding=COMPAT")
	//{
	//	try
	//	{
	//		encoding = fileEncoding.substr(strlen("-Dfile.encoding="));
	//	}
	//	catch (const std::exception& ex)
	//	{
	//		qWarning() << "Bad file encoding" << ex.what();
	//	}
	//}
	//res.addDefault("-Dsun.stdout.encoding=", encoding);
	//res.addDefault("-Dsun.stderr.encoding=", encoding);

	//// Fix RCE vulnerability of log4j2
	//res.addDefault("-Djava.rmi.server.useCodebaseOnly=", "true");
	//res.addDefault("-Dcom.sun.jndi.rmi.object.trustURLCodebase=", "false");
	//res.addDefault("-Dcom.sun.jndi.cosnaming.object.trustURLCodebase=", "false");

	////std::string formatMsgNoLookups = res.addDefault("-Dlog4j2.formatMsgNoLookups=", "true");
	///*if (formatMsgNoLookups != "-Dlog4j2.formatMsgNoLookups=false" && isUsingLog4j()) {
	//	res.addDefault("-Dlog4j.configurationFile=", getLog4jConfigurationFile().getAbsolutePath());
	//}*/

	//// Default JVM Args
	//if (!options.noGeneratedJVMArgs) {
	//	//appendJvmArgs(res);

	//	res.addDefault("-Dminecraft.client.jar=", options.gameDir.u8string() + "\\" + "versions" + "\\" + options.versionName);

	//	/*if (OS == "mac") {
	//		res.addDefault("-Xdock:name=", "Minecraft " + version.getId());
	//		auto minecraftIcns = repository.getAssetObject(version.getId(), version.getAssetIndex().getId(), "icons/minecraft.icns");
	//		if (minecraftIcns) {
	//			res.addDefault("-Xdock:icon=", minecraftIcns->toAbsolutePath().toString());
	//		}
	//	}*/

	//	if (OS != "windows")
	//		res.addDefault("-Duser.home=", options.gameDir.parent_path().u8string());

	//	// Using G1GC with its settings by default
	//	if (options.java >= "8" &&
	//		!res.noneMatch([](const std::string& arg) { return arg == "-XX:-UseG1GC" || (arg._Starts_with("-XX:+Use") && Additionals::String::EndsWith(arg, "GC")); })) {
	//		res.addUnstableDefault("UnlockExperimentalVMOptions", true);
	//		res.addUnstableDefault("UseG1GC", true);
	//		res.addUnstableDefault("G1NewSizePercent", "20");
	//		res.addUnstableDefault("G1ReservePercent", "20");
	//		res.addUnstableDefault("MaxGCPauseMillis", "50");
	//		res.addUnstableDefault("G1HeapRegionSize", "32m");
	//	}

	//	res.addUnstableDefault("UseAdaptiveSizePolicy", false);
	//	res.addUnstableDefault("OmitStackTraceInFastThrow", false);
	//	res.addUnstableDefault("DontCompileHugeMethods", false);

	//	// As 32-bit JVM allocate 320KB for stack by default rather than 64-bit version allocating 1MB,
	//	// causing Minecraft 1.13 crashed accounting for java.lang.StackOverflowError.
	//	/*if (options.getJava().getBits() == Bits::BIT_32) {
	//		res.addDefault("-Xss", "1m");
	//	}*/

	//	if (options.java == "16")
	//		res.addDefault("--illegal-access=", "permit");

	//	res.addDefault("-Dfml.ignoreInvalidMinecraftCertificates=", "true");
	//	res.addDefault("-Dfml.ignorePatchDiscrepancies=", "true");
	//}

	//std::string minecraft_directory = options.gameDir.u8string();
	//std::string minecraft_version = options.versionName;

	//SJson::JsonValue data = SJson::JsonParcer::ParseFile(Join({ minecraft_directory, "versions", minecraft_version, (minecraft_version + ".json") }));

	//if (data.is_exist("inheritsFrom"))
	//{
	//	data = MinecraftCpp::inherit_json(data, minecraft_directory);
	//}
	//std::string classpath = MinecraftCpp::get_libraries(data, minecraft_directory);;

	//std::filesystem::path jar = Join({ minecraft_directory, "versions", minecraft_version, (minecraft_version + ".jar") });
	//if (!std::filesystem::exists(jar) || !std::filesystem::is_regular_file(jar))
	//	throw std::runtime_error("Minecraft jar does not exist");
	//classpath += jar.u8string();

	//// Provided Minecraft arguments
	//std::filesystem::path gameAssets = Join({ minecraft_directory, "assets", "indexes" });

	//std::map<std::string, std::string> configuration = version.getConfigurations(options.auth_info, options, minecraft_directory, version);
	//configuration["${classpath}"] = Join({ classpath, get_classpath_separator() });
	//configuration["${game_assets}"] = gameAssets.string();
	//configuration["${assets_root}"] = gameAssets.string();

	//// lwjgl assumes path to native libraries encoded by ASCII.
	//// Here is a workaround for this issue: https://github.com/huanghongxun/HMCL/issues/1141.
	//std::string nativeFolderPath = nativeFolder.string();
	//std::filesystem::path tempNativeFolder;
	//if ((OS == "linux" || OS == "mac") &&
	//	!StringUtils::isASCII(nativeFolderPath))
	//{
	//	tempNativeFolder = std::filesystem::path("/tmp/natives-" + std::to_string(options.auth_info.getUUID().Data1));
	//	nativeFolderPath = tempNativeFolder.string() + "\\" + nativeFolderPath;
	//}
	//configuration["${natives_directory}"] = nativeFolderPath;

	//res.addAll(Arguments::parseArguments(version.arguments.getJvm(), configuration));

	//Arguments argumentsFromAuthInfo = nullptr /*options.auth_info.getLaunchArguments(options)*/;
	//if (!argumentsFromAuthInfo.getGame().empty() && !argumentsFromAuthInfo.getJvm().empty())
	//	res.addAll(Arguments::parseArguments(argumentsFromAuthInfo.getJvm(), configuration));

	//for (const std::string& javaAgent : options.javaAgents)
	//{
	//	res.add({ "-javaagent:" + javaAgent });
	//}

	//res.add({ version.mainClass });

	//res.addAll(Arguments::parseStringArguments(options.gameArguments, configuration));

	//std::map<std::string, bool> features;
	//features["has_custom_resolution"] = options.height != 0 && options.width != 0;

	//res.addAll(Arguments::parseArguments(version.arguments.getGame(), configuration, features));
	//if (!options.gameArguments.empty())
	//{
	//	std::map<std::string, bool> mad = { std::make_pair("has_custom_resolution", true) };
	//	std::vector<std::shared_ptr<Argument>> game;
	//	game.push_back(std::make_shared<RuledArgument>
	//		(std::vector<CompatibilityRule> {
	//		CompatibilityRule(CompatibilityRule::Action::ALLOW, nullptr, &mad)
	//	},
	//			std::vector<std::string>{"--width", "${resolution_width}", "--height", "${resolution_height}"}
	//	));
	//	res.addAll(Arguments::parseArguments(game, configuration, features));
	//}
	//if (!argumentsFromAuthInfo.getGame().empty() && !argumentsFromAuthInfo.getJvm().empty())
	//	res.addAll(Arguments::parseArguments(argumentsFromAuthInfo.getGame(), configuration, features));

	///*if (!options.serverIp.empty())
	//{
	//	std::vector<std::string> args = Additionals::String::split(options.serverIp, ':');
	//	if (version.compareTo(Version("1.20")) < 0)
	//	{
	//		res.add("--server");
	//		res.add(args[0]);
	//		res.add("--port");
	//		res.add(args.size() > 1 ? args[1] : "25565");
	//	}
	//	else
	//	{
	//		res.add("--quickPlayMultiplayer");
	//		res.add(args[0] + ":" + (args.size() > 1 ? args[1] : "25565"));
	//	}
	//}*/

	//if (options.fullscreen)
	//	res.add({ "--fullscreen" });

	////TODO: Proxy
	///*if (options.getProxy() && options.getProxy().type() == Proxy::Type::SOCKS) {
	//	auto address = std::any_cast<InetSocketAddress>(options.getProxy().address());
	//	if (address) {
	//		res.add("--proxyHost");
	//		res.add(address->getHostString());
	//		res.add("--proxyPort");
	//		res.add(std::to_string(address->getPort()));
	//		if (!options.getProxyUser().empty() && !options.getProxyPass().empty()) {
	//			res.add("--proxyUser");
	//			res.add(options.getProxyUser());
	//			res.add("--proxyPass");
	//			res.add(options.getProxyPass());
	//		}
	//	}
	//}*/

	//res.addAllWithoutParsing(Arguments::parseStringArguments(options.gameArguments, configuration));

	///*res.removeIf(
	//	[=](const std::string& it)
	//	{
	//		return std::pair("-Xincgc", ()->options.getJava().getParsedVersion() >= JavaVersion.JAVA_9);
	//	}
	//);*/

	//return res.asList();
}

std::vector<std::variant<std::string, std::filesystem::path, std::wstring>> MinecraftCpp::get_minecraft_command__(const std::string& version, const std::filesystem::path& minecraft_directory,
	MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Returns a command for launching Minecraft.For more information take a look at the documentation.
	*/
	if (!std::filesystem::exists(minecraft_directory / "versions" / version / (version + ".json")) ||
		!std::filesystem::is_directory(minecraft_directory / "versions" / version))
	{
		qFatal() << "Version Not Found" << version;
		return {};
	}

	//SJson::JsonValue data = SJson::JsonParcer::ParseFile(Join({ minecraft_directory, "versions", version, (version + ".json") }));
	nlohmann::json data;
	std::ifstream ifs;
	ifs.open(minecraft_directory / "versions" / version / (version + ".json"));
	ifs >> data;
	ifs.close();

	if (data.contains("inheritsFrom"))
	{
		data = MinecraftCpp::inherit_json(data, minecraft_directory);
	}
	qInfo() << data.dump() << std::endl;
	if (options.nativesDirectory.empty())
	{
		options.nativesDirectory = minecraft_directory / "versions" / data["id"].template get<std::string>() / "natives";
	}
	else
	{
		options.nativesDirectory = "nativesDirectory";
	}
	//options.nativesDirectory = options.get("nativesDirectory", minecraft_directory / "versions" / data["id"].template get<std::string>() / "natives");

	options.classpath = MinecraftCpp::get_libraries(data, minecraft_directory);

	std::vector<std::variant<std::string, std::filesystem::path, std::wstring>> command;

	// Add Java executable
	if (options.executablePath != "")
	{
		command.push_back(options.executablePath.wstring());
	}
	else if (data.contains("javaVersion"))
	{
		std::filesystem::path java_path = MinecraftCpp::get_executable_path(data["javaVersion"]["component"].template get<std::string>(), minecraft_directory);
		if (java_path == "")
		{
			command.push_back(std::string("java"));
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

	qInfo() << data.dump() << std::endl;
	// Newer Versions have jvmArguments in version.json
	if (data["arguments"].type() == nlohmann::json_abi_v3_11_3::detail::value_t::object)
	{
		if (data["arguments"].contains("jvm"))
		{
			auto argus = MinecraftCpp::get_arguments(data["arguments"]["jvm"], data, minecraft_directory, options);
			command.insert(command.end(), argus.begin(), argus.end());
		}
		else
		{
			command.push_back(L"-Djava.library.path=" + options.nativesDirectory.wstring());
			command.push_back(std::string("-cp"));
			command.push_back(options.classpath);
		}
	}
	else
	{
		command.push_back(L"-Djava.library.path=" + options.nativesDirectory.wstring());
		command.push_back(std::string("-cp"));
		command.push_back(options.classpath);
	}

	if (options.get("enableLoggingConfig", false))
	{
		if (data.contains("logging"))
		{
			if (data["logging"].template get<int>() != 0)
			{
				std::filesystem::path logger_file = minecraft_directory / "assets" / "log_configs" / data["logging"]["client"]["file"]["id"].template get<std::string>();
				std::string data_replacer = data["logging"]["client"]["argument"].template get<std::string>();
				Additionals::String::replace(data_replacer, std::string("${path}"), logger_file.wstring());
				command.push_back(data_replacer);
			}
		}
	}

	command.push_back(data["mainClass"].template get<std::string>());

	if (data.contains("minecraftArguments"))
	{
		// For older versions
		command.push_back(MinecraftCpp::get_arguments_string(data, minecraft_directory, options));
	}
	else
	{
		auto args = MinecraftCpp::get_arguments(data["arguments"]["game"], data, minecraft_directory, options);
		command.insert(command.end(), args.begin(), args.end());
	}

	if (options.server != "")
	{
		command.push_back(std::string("--server"));
		command.push_back(options.server);

		if (options.port != "")
		{
			command.push_back(std::string("--port"));
			command.push_back(options.port);
		}
	}

	return command;
}

std::wstring MinecraftCpp::get_libraries(nlohmann::json data, const std::filesystem::path& path)
{
	/*
	Returns the argument with all libs that come after -cp
	*/
	std::wstring classpath_seperator;
	if (OS == "windows")
	{
		classpath_seperator = L";";
	}
	else
	{
		classpath_seperator = L":";
	}
	std::wstring libstr = L"";
	std::string native = "";
	MinecraftCpp::option::MinecraftOptions empty;

	std::cout << data["libraries"].size() << std::endl;

	for (auto& elem : data["libraries"])
	{
		if (elem.type() != nlohmann::json_abi_v3_11_3::detail::value_t::object)
		{
			continue;
		}
		if (elem.contains("rules") && !(MinecraftCpp::parse_rule_list(elem, "rules", empty)))
		{
			continue;
		}

		libstr += MinecraftCpp::getLibraryPath(Additionals::Convectors::ConvertStringToWString(elem["name"].template get<std::string>()), path).wstring() + classpath_seperator;
		native = MinecraftCpp::get_natives(elem);

		if (native != "")
		{
			if (elem.contains("downloads"))
			{
				libstr += (path / "libraries" / elem["downloads"]["classifiers"][native]["path"].template get<std::string>()).wstring() + classpath_seperator;
			}
			else
			{
				libstr += MinecraftCpp::get_library_path((elem["name"].template get<std::string>() + ("-" + native)), path).wstring() + classpath_seperator;
			}
		}
	}

	if (data.contains("jar"))
	{
		libstr += (path / "versions" / data["jar"].template get<std::string>() / (data["jar"].template get<std::string>() + ".jar")).wstring();
	}
	else
	{
		libstr += (path / "versions" / data["id"].template get<std::string>() / (data["id"].template get<std::string>() + ".jar")).wstring();
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

std::wstring MinecraftCpp::getWClasspathSeparator()
{
	if (OS == "windows")
	{
		return L";";
	}
	else
	{
		return L":";
	}
}

bool MinecraftCpp::parse_rule_list(nlohmann::json data, const std::string& rule_string, MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Parse a list of rules
	*/

	if (!data.contains(rule_string))
	{
		return true;
	}
	for (auto& var : data[rule_string])
	{
		if (var.type() != nlohmann::json::value_t::object)
		{
			continue;
		}
		if (!MinecraftCpp::parse_single_rule(var, options))
		{
			return false;
		}
	}
	return true;
}

bool MinecraftCpp::parse_single_rule(nlohmann::json rule, MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Parse a single rule from the versions.json
	*/
	bool returnvalue = false;
	if (rule["action"].template get<std::string>() == "allow")
	{
		returnvalue = false;
	}
	else if (rule["action"].template get<std::string>() == "disallow")
	{
		returnvalue = true;
	}
	if (rule.contains("os"))
	{
		for (auto& var : rule["os"].items())
		{
			if (var.key() == "name")
			{
				if (var.value().template get<std::string>() == "windows" && OS != "Windows")
				{
					return returnvalue;
				}
				else if (var.value().template get<std::string>() == "osx" && OS != "Darwin")
				{
					return returnvalue;
				}
				else if (var.value().template get<std::string>() == "linux" && OS != "Linux")
				{
					return returnvalue;
				}
			}
			else if (var.key() == "arch")
			{
				if (var.value().template get<std::string>() == "x86" && ARCH != "x86")
				{
					return returnvalue;
				}
			}
			else if (var.key() == "version")
			{
				if (var.value().template get<std::string>() != OS)
				{
					return returnvalue;
				}
			}
		}
	}
	if (rule.contains("features"))
	{
		for (auto& var : rule["features"].items())
		{
			if (var.key() == "has_custom_resolution" && !options.get("customResolution", false))
			{
				return returnvalue;
			}
			else if (var.key() == "is_demo_user" && !options.get("demo", false))
			{
				return returnvalue;
			}
		}
	}
	return !returnvalue;
}

std::filesystem::path MinecraftCpp::get_library_path(const std::string& name, const std::filesystem::path& path)
{
	/*
	Returns the path from a libname
	*/

	std::filesystem::path libpath = path / "libraries";

	std::vector<std::string> parts = Additionals::String::split(name, ':');
	std::string& base_path = parts[0];
	std::string& libname = parts[1];
	std::string& version = parts[2];
	std::string fileend;

	for (auto& var : Additionals::String::split(base_path, '.'))
	{
		libpath /= var.c_str();
	}
	if (version.find('@') != std::string::npos && version[version.find('@')] == '@')
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

	std::string filename = libname + "-" + version;

	/*for (auto& var : parts)
	{
		filename = libname + ("-" + var);
	}
	filename = filename + ("." + fileend);*/

	for (size_t i = 3; i < parts.size(); ++i)
	{
		filename += "-" + parts[i];
	}
	filename += "." + fileend;

	libpath = libpath / libname / version / filename;
	return libpath;
}

std::filesystem::path MinecraftCpp::getLibraryPath(const std::wstring& name, const std::filesystem::path& path)
{
	/*
	Returns the path from a libname
	*/

	std::filesystem::path libpath = path / "libraries";

	std::vector<std::wstring> parts = Additionals::String::split(name, ':');
	std::wstring& base_path = parts[0];
	std::wstring& libname = parts[1];
	std::wstring& version = parts[2];
	std::wstring fileend;

	for (auto& var : Additionals::String::split(base_path, '.'))
	{
		libpath /= var.c_str();
	}
	if (version.find('@') != std::wstring::npos && version[version.find('@')] == '@')
	{
		std::vector<std::wstring> splt = Additionals::String::split(version, '@', 2);
		version = splt[0];
		fileend = splt[1];
	}
	else
	{
		fileend = L"jar";
	}
	// construct a filename with the remaining parts

	std::wstring filename = libname + L"-" + version;

	for (size_t i = 3; i < parts.size(); ++i)
	{
		filename += L"-" + parts[i];
	}
	filename += L"." + fileend;

	libpath = libpath / libname / version / filename;
	return libpath;
}

std::string MinecraftCpp::get_natives(nlohmann::json data)
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

	if (data.type() != nlohmann::json_abi_v3_11_3::detail::value_t::object && data.contains("natives"))
	{
		if (OS == "windows")
		{
			if (data.type() != nlohmann::json_abi_v3_11_3::detail::value_t::object && data["natives"].contains("windows"))
			{
				std::string replace_string = data["natives"]["windows"].template get<std::string>();
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
			if (data.type() != nlohmann::json_abi_v3_11_3::detail::value_t::object && data["natives"].contains("osx"))
			{
				std::string replace_string = data["natives"]["osx"].template get<std::string>();
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
			if (data.type() != nlohmann::json_abi_v3_11_3::detail::value_t::object && data["natives"].contains("linux"))
			{
				std::string replace_string = data["natives"]["linux"].template get<std::string>();
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

std::string MinecraftCpp::replace_arguments(std::string argstr, nlohmann::json versionData,
	const std::filesystem::path& path, MinecraftCpp::option::MinecraftOptions options)
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

	Additionals::String::replace(argstr, std::string("${natives_directory}"), options.nativesDirectory.wstring());
	Additionals::String::replace(argstr, std::string("${launcher_name}"), options.get("launcherName", std::string("null")));
	Additionals::String::replace(argstr, std::string("${launcher_version}"), options.get("launcherVersion", std::string("null")));
	Additionals::String::replace(argstr, std::string("${classpath}"), options.classpath);
	Additionals::String::replace(argstr, std::string("${auth_player_name}"), options.get("username", std::string("{username}")));
	Additionals::String::replace(argstr, std::string("${version_name}"), versionData["id"].template get<std::string>());
	Additionals::String::replace(argstr, std::string("${game_directory}"), !options.gameDirectory.empty() ? options.gameDirectory.wstring() : path.wstring());
	Additionals::String::replace(argstr, std::string("${assets_root}"), path / "assets");
	Additionals::String::replace(argstr, std::string("${assets_index_name}"), !versionData["assets"].empty() ? versionData["assets"].template get<std::string>() : versionData["id"].template get<std::string>());
	Additionals::String::replace(argstr, std::string("${auth_uuid}"), options.get("uuid", std::string("{uuid}")));
	Additionals::String::replace(argstr, std::string("${auth_access_token}"), options.get("token", std::string("{token}")));
	Additionals::String::replace(argstr, std::string("${user_type}"), std::string("mojang"));
	Additionals::String::replace(argstr, std::string("${version_type}"), versionData["type"].template get<std::string>());
	Additionals::String::replace(argstr, std::string("${user_properties}"), std::string("{}"));
	Additionals::String::replace(argstr, std::string("${resolution_width}"), options.get("resolutionWidth", std::string("854")));
	Additionals::String::replace(argstr, std::string("${resolution_height}"), options.get("resolutionHeight", std::string("480")));
	Additionals::String::replace(argstr, std::string("${game_assets}"), path / "assets" / "virtual" / "legacy");
	Additionals::String::replace(argstr, std::string("${auth_session}"), options.get("token", std::string("{token}")));
	Additionals::String::replace(argstr, std::string("${library_directory}"), path / "libraries");
	Additionals::String::replace(argstr, std::string("${classpath_separator}"), MinecraftCpp::get_classpath_separator());
	Additionals::String::replace(argstr, std::string("${quickPlayPath}"), options.get("quickPlayPath", std::string("quickPlayPath")));
	Additionals::String::replace(argstr, std::string("${quickPlaySingleplayer}"), options.get("quickPlaySingleplayer", std::string("quickPlaySingleplayer")));
	Additionals::String::replace(argstr, std::string("${quickPlayMultiplayer}"), options.get("quickPlayMultiplayer", std::string("quickPlayMultiplayer")));
	Additionals::String::replace(argstr, std::string("${quickPlayRealms}"), options.get("quickPlayRealms", std::string("quickPlayRealms")));

	return argstr;
}

std::wstring MinecraftCpp::replace_arguments(std::wstring argstr, nlohmann::json versionData, const std::filesystem::path& path, MinecraftCpp::option::MinecraftOptions options)
{
	Additionals::String::replace(argstr, std::wstring(L"${natives_directory}"), options.nativesDirectory.wstring());
	Additionals::String::replace(argstr, std::wstring(L"${launcher_name}"), options.get("launcherName", std::string("null")));
	Additionals::String::replace(argstr, std::string("${launcher_version}"), options.get("launcherVersion", std::string("null")));
	Additionals::String::replace(argstr, std::string("${classpath}"), options.classpath);
	Additionals::String::replace(argstr, std::string("${auth_player_name}"), options.get("username", std::string("{username}")));
	Additionals::String::replace(argstr, std::string("${version_name}"), versionData["id"].template get<std::string>());
	Additionals::String::replace(argstr, std::string("${game_directory}"), !options.gameDirectory.empty() ? options.gameDirectory.wstring() : path.wstring());
	Additionals::String::replace(argstr, std::string("${assets_root}"), path / "assets");
	Additionals::String::replace(argstr, std::string("${assets_index_name}"), !versionData["assets"].empty() ? versionData["assets"].template get<std::string>() : versionData["id"].template get<std::string>());
	Additionals::String::replace(argstr, std::string("${auth_uuid}"), options.get("uuid", std::string("{uuid}")));
	Additionals::String::replace(argstr, std::string("${auth_access_token}"), options.get("token", std::string("{token}")));
	Additionals::String::replace(argstr, std::string("${user_type}"), "mojang");
	Additionals::String::replace(argstr, std::string("${version_type}"), versionData["type"].template get<std::string>());
	Additionals::String::replace(argstr, std::string("${user_properties}"), "{}");
	Additionals::String::replace(argstr, std::string("${resolution_width}"), options.get("resolutionWidth", std::string("854")));
	Additionals::String::replace(argstr, std::string("${resolution_height}"), options.get("resolutionHeight", std::string("480")));
	Additionals::String::replace(argstr, std::wstring(L"${game_assets}"), path / "assets" / "virtual" / "legacy");
	Additionals::String::replace(argstr, std::string("${auth_session}"), options.get("token", std::string("{token}")));
	Additionals::String::replace(argstr, std::wstring(L"${library_directory}"), path / "libraries");
	Additionals::String::replace(argstr, std::string("${classpath_separator}"), MinecraftCpp::get_classpath_separator());
	Additionals::String::replace(argstr, std::string("${quickPlayPath}"), options.get("quickPlayPath", std::string("quickPlayPath")));
	Additionals::String::replace(argstr, std::string("${quickPlaySingleplayer}"), options.get("quickPlaySingleplayer", std::string("quickPlaySingleplayer")));
	Additionals::String::replace(argstr, std::string("${quickPlayMultiplayer}"), options.get("quickPlayMultiplayer", std::string("quickPlayMultiplayer")));
	Additionals::String::replace(argstr, std::string("${quickPlayRealms}"), options.get("quickPlayRealms", std::string("quickPlayRealms")));

	return argstr;
}

std::filesystem::path MinecraftCpp::get_executable_path(const std::string& jvm_version, const std::filesystem::path& minecraft_directory)
{
	/*
	Returns the path to the executable. Returns None if none is found.
	*/
	std::filesystem::path java_path = minecraft_directory / "runtime" / jvm_version / _get_jvm_platform_string() / jvm_version / "bin" / "java";
	if (std::filesystem::exists(java_path))
	{
		if (!std::filesystem::is_directory(java_path))
		{
			return java_path;
		}
		else if (!std::filesystem::is_directory(java_path.wstring() + L".exe"))
		{
			return java_path.wstring() + L".exe";
		}
	}

	std::filesystem::path java_w_path = java_path;
	java_w_path = std::regex_replace(java_w_path.wstring(), std::wregex((std::filesystem::path("bin") / "java").wstring()), (std::filesystem::path("jre.bundle") / "Contents" / "Home" / "bin" / "java").wstring());
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

bool MinecraftCpp::install_libraries(nlohmann::json& data, const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback)
{
	/*
	Install all libraries
	*/

	callback->OnProgress(NULL, NULL, NULL, L"Download Libraries");
	callback->OnProgress(NULL, NULL, NULL, std::to_wstring(data["libraries"].size() - 1).c_str());

	int count = -1;
	for (auto& var : data["libraries"])
	{
		++count;

		MinecraftCpp::option::MinecraftOptions empty;

		// Check, if the rules allow this lib for the current system
		/*if (!MinecraftCpp::parse_rule_list(var, "rules", empty))
		{
			continue;
		}*/

		if (var["downloads"].contains("artifact"))
		{
			callback->setTotalDownloadSize(var["downloads"]["artifact"]["size"].template get<int>());
			DownloadFile(var["downloads"]["artifact"]["url"].template get<std::string>(), path / "libraries" / var["downloads"]["artifact"]["path"].template get<std::string>(), callback, var["downloads"]["artifact"]["sha1"].template get<std::string>());
			continue;
		}

		// Turn the name into a path
		std::filesystem::path currentPath = path / "libraries";
		std::string downloadUrl = "";



		if (var.contains("url"))
		{
			if (Additionals::String::EndsWith(var["url"].template get<std::string>(), "/"))
			{
				std::string download_string = Additionals::String::rtrim_copy(var["url"].template get<std::string>(), '/');
				downloadUrl = download_string;
			}
			else
			{
				downloadUrl = var["url"].template get<std::string>();
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
			libPath = Additionals::String::split(var["name"].template get<std::string>(), ':')[0];
			name = Additionals::String::split(var["name"].template get<std::string>(), ':')[1];
			version = Additionals::String::split(var["name"].template get<std::string>(), ':')[2];
		}
		else
		{
			continue;
		}

		for (auto& libPart : Additionals::String::split(libPath, '.'))
		{
			currentPath /= libPart;
			downloadUrl += "/" + libPart;
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
		downloadUrl += "/" + name + "/" + version;
		currentPath /= name + "\\" + version;
		std::string native /*= get_natives(var)*/;

		//Check if there is a native file
		std::string jarFilenameNative = "";
		if (native != "")
		{
			jarFilenameNative = name + "-" + version + "-" + native + ".jar";
		}
		jarFilename = name + "-" + version + "." + fileend;
		downloadUrl += "/" + jarFilename;

		if (!std::filesystem::exists(currentPath / jarFilename))
		{
			//Try to download the lib
			DownloadFile(downloadUrl, currentPath / jarFilename, callback);
		}

		if (!var.contains("downloads"))
		{
			if (var.contains("extract"))
			{
				extract_natives_file(currentPath / jarFilenameNative, path / "versions" / data["id"].template get<std::string>() / "natives", var["extract"]);
			}
			continue;
		}
		if (native != "")
		{
			callback->setTotalDownloadSize(var["downloads"]["classifiers"][native]["size"].template get<int>());
			DownloadFile(var["downloads"]["classifiers"][native]["url"].template get<std::string>(), currentPath / jarFilenameNative, callback, var["downloads"]["artifact"]["sha1"].template get<std::string>());
			if (var["extract"] != nullptr)
			{
				extract_natives_file(currentPath / jarFilenameNative, path / "versions" / data["id"].template get<std::string>() / "natives", var["extract"]);
			}
		}
		callback->OnProgress(count, NULL, NULL, NULL);
	}
	return true;
}

bool MinecraftCpp::extract_natives_file(const std::filesystem::path& filename, const std::filesystem::path& extract_path, nlohmann::json& extract_data)
{
	/*
	Unpack natives
	*/
	bool ret = std::filesystem::create_directories(extract_path);

	if (!std::filesystem::exists(filename))
	{
		return false;
	}

	QZipReader zArchive(filename.u8string().c_str());

	foreach(QZipReader::FileInfo var, zArchive.fileInfoList())
	{
		for (auto& var2 : extract_data["exclude"])
		{
			if (Additionals::Path::getFileNameFromPath(var.filePath.toStdString())._Starts_with(var2.template get<std::string>()))
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
		if (!std::filesystem::exists(extract_path / var.filePath.toStdString()))
		{
			Additionals::archives::decompressFile(zArchive, var, extract_path / var.filePath.toStdString());
		}
	}
	return true;
}

bool MinecraftCpp::install_assets(nlohmann::json& data, const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback)
{
	/*
	Install all assets
	*/
	// Old versions dosen't have this
	if (!data.contains("assetIndex"))
	{
		return false;
	}
	callback->OnProgress(NULL, NULL, NULL, L"Download Assets");

	// Download all assets
	callback->setTotalDownloadSize(data["assetIndex"]["size"].template get<int>());
	DownloadFile(
		data["assetIndex"]["url"].template get<std::string>(),
		path / "assets" / "indexes" / (data["assets"].template get<std::string>() + ".json"),
		callback,
		data["assetIndex"]["sha1"].template get<std::string>()
	);
	std::ifstream ifstr(path / "assets" / "indexes" / (data["assets"].template get<std::string>() + ".json"));
	nlohmann::json assets_data = nlohmann::json::parse(ifstr);
	ifstr.close();

	// The assets has a hash. e.g. c4dbabc820f04ba685694c63359429b22e3a62b5
	// With this hash, it can be download from https://resources.download.minecraft.net/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
	// And saved at assets/objects/c4/c4dbabc820f04ba685694c63359429b22e3a62b5
	//return true;
	callback->OnProgress(NULL, assets_data["objects"].size() - 1, NULL, NULL);

	int count = 0;
	for (auto& var : assets_data["objects"].items())
	{
		callback->setTotalDownloadSize(var.value()["size"].template get<int>());
		DownloadFile
		(
			(
				"https://resources.download.minecraft.net/" +
				var.value()["hash"].template get<std::string>().substr(0, 2)
				+ "/" +
				var.value()["hash"].template get<std::string>()
				),
			(
				path / "assets" / "objects" /
				var.value()["hash"].template get<std::string>().substr(0, 2) /
				var.value()["hash"].template get<std::string>()
				),
			callback,
			var.value()["hash"].template get<std::string>()
		);

		++count;
		callback->OnProgress(count, NULL, NULL, NULL);
	}
	callback->OnProgress(NULL, NULL, 6, NULL);
	return true;
}

bool MinecraftCpp::install_jvm_runtime(const std::string& jvm_version, const std::string& minecraft_directory, std::shared_ptr<CallbackNull> callback)
{
	/*
	Installs the given jvm runtime. callback is the same dict as in the install module.
	*/
	std::string _JVM_MANIFEST_URL = "https://launchermeta.mojang.com/v1/products/java-runtime/2ec0cc96c44e5a76b9c8b7c39df7210883d12871/all.json";

	SJson::JsonParcer jsonParcer;
	std::string platform_string = _get_jvm_platform_string();
	auto download_path = DownloadFile(_JVM_MANIFEST_URL);
	SJson::JsonValue manifest_data = jsonParcer.ParseFile(download_path);

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

	callback->setTotalDownloadSize(manifest_data[platform_string][jvm_version][0]["manifest"]["size"].to_int());
	SJson::JsonValue platform_manifest = jsonParcer.ParseFile(DownloadFile(manifest_data[platform_string][jvm_version][0]["manifest"]["url"].to_string()));
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
				callback->setTotalDownloadSize(var.second["downloads"]["lzma"]["size"].to_int());
				//TODO: сделать lzma
				DownloadFile(var.second["downloads"]["lzma"]["url"].to_string(), current_path.u8string(), callback, var.second["downloads"]["raw"]["sha1"].to_string(), false);
			}
			else
			{
				callback->setTotalDownloadSize(var.second["downloads"]["raw"]["size"].to_int());
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
	return SHA1::from_file(path.wstring());
}

std::vector<std::wstring> MinecraftCpp::get_arguments(
	nlohmann::json& data,
	nlohmann::json versionData,
	const std::filesystem::path& path,
	MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Returns all arguments from the version.json
	*/

	std::vector<std::wstring> arglist;
	if (data.type() == nlohmann::json_abi_v3_11_3::detail::value_t::array)
	{
		for (auto& var : data)
		{
			if (var.type() == nlohmann::json_abi_v3_11_3::detail::value_t::string)
			{
				auto s = var.template get<std::filesystem::path>();
				std::wstring rep = MinecraftCpp::replace_arguments(s.wstring(), versionData, path, options);
				if (rep != s)
				{
					arglist.push_back(L"\"" + rep + L"\"");
				}
				else
				{
					arglist.push_back(rep);
				}
			}
			else
			{
				// Rules might has 2 different names in different versions.json
				if (var.type() != nlohmann::json::value_t::object)
				{
					continue;
				}
				if (var.contains("compatibilityRules") && !parse_rule_list(var, "compatibilityRules", options))
				{
					continue;
				}
				if (var.contains("rules") && !parse_rule_list(var, "rules", options))
				{
					continue;
				}

				// var could be the argument
				if (var["value"].type() == nlohmann::json_abi_v3_11_3::detail::value_t::string)
				{
					auto a = var.template get<std::filesystem::path>();
					std::wstring replace = MinecraftCpp::replace_arguments(a.wstring(), versionData, path, options);
					if (!replace.empty())
					{
						arglist.push_back(L"\"" + replace + L"\"");
					}
				}
				else
				{
					for (auto& v : var["value"])
					{
						std::wstring val;
						if (v["value"].type() == nlohmann::json_abi_v3_11_3::detail::value_t::array)
						{
							auto a = v["value"][0].template get<std::filesystem::path>();
							val = replace_arguments(a.wstring(), versionData, path, options);
						}
						else
						{
							auto a = v["value"].template get<std::filesystem::path>();
							val = replace_arguments(a.wstring(), versionData, path, options);
						}

						if (!val.empty())
						{
							arglist.push_back(L"\"" + val + L"\"");
						}
					}
				}
			}
		}
	}
	else
	{
		//for (auto& var : data.get_array())
		//{
		//	if (var.get_type() == SJson::JsonTypes::String)
		//	{
		//		arglist += MinecraftCpp::replace_arguments(var.to_string(), versionData, path, options);
		//	}
		//	else
		//	{
		//		// Rules might has 2 different names in different versions.json
		//		if (var.is_exist("compatibilityRules") && !parse_rule_list(var, "compatibilityRules", options))
		//		{
		//			continue;
		//		}
		//		if (var.is_exist("rules") && !parse_rule_list(var, "rules", options))
		//		{
		//			continue;
		//		}

		//		// var could be the argument
		//		if (var["value"].get_type() == SJson::JsonTypes::String)
		//		{
		//			qInfo() << "data " << data.to_string() << std::endl;
		//			qInfo() << "var " << var.to_string() << std::endl;
		//			std::string replace = MinecraftCpp::replace_arguments(var["value"].to_string(), versionData, path, options);
		//			arglist += replace;
		//			arglist += " ";
		//		}
		//		else
		//		{
		//			for (auto& v : var["value"].get_object())
		//			{
		//				std::string val = replace_arguments(v.second.to_string(), versionData, path, options);
		//				arglist += val;
		//				arglist += " ";
		//			}
		//		}
		//	}
		//}
	}
	return arglist;
}

std::string MinecraftCpp::get_arguments_string(nlohmann::json versionData, const std::filesystem::path& path,
	MinecraftCpp::option::MinecraftOptions options)
{
	/*
	Turns the argument string from the version.json into a list
	*/
	std::string arglist = "";

	for (auto& var : Additionals::String::split(versionData["minecraftArguments"].template get<std::string>(), ' '))
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

bool MinecraftCpp::forge::install_forge_version(const std::string& versionid, const std::filesystem::path& path, std::shared_ptr<CallbackNull> callback, const std::filesystem::path& java)
{
	/*
	Installs a forge version. Fore more information look at the documentation.
	*/

	int random_num = 1 + (rand() % 100000);

	std::string FORGE_DOWNLOAD_URL = "https://maven.minecraftforge.net/net/minecraftforge/forge/" + versionid + "/forge-" + versionid + "-installer.jar";
	std::string temp_file_path = Additionals::TempFile::get_tempdir_SYSTEM() + ("forge-installer-" + std::to_string(random_num) + ".tmp");
	if (DownloadFile(FORGE_DOWNLOAD_URL, temp_file_path, callback) == "")
	{
		std::cout << "Version Not Found" << versionid << std::endl;
		return false;
	}

	QZipReader zArchive(temp_file_path.c_str());

	// Read the install_profile.json
	nlohmann::json version_data = nullptr;

	foreach(QZipReader::FileInfo var, zArchive.fileInfoList())
	{
		if (var.filePath == "install_profile.json")
		{
			std::string json_str = zArchive.fileData(var.filePath).toStdString();

			version_data = nlohmann::json::parse(json_str);

			break;
		}
	}

	std::string forge_version_id = version_data.contains("version") ? version_data["version"].template get<std::string>() : version_data["install"]["version"].template get<std::string>();
	std::string minecraft_version = version_data.contains("minecraft") ? version_data["minecraft"].template get<std::string>() : version_data["install"]["minecraft"].template get<std::string>();

	// Make sure, the base version is installed
	install_minecraft_version(minecraft_version, path, callback);

	// Install all needed libs from install_profile.json
	if (version_data.contains("libraries"))
	{
		install_libraries(version_data, path, callback);
	}

	// Extract the version.json
	std::filesystem::path version_json_path = path / "versions" / forge_version_id / (forge_version_id + ".json");
	if (!extract_file(zArchive, "version.json", version_json_path))
		if (version_data.contains("versionInfo"))
		{
			std::ofstream o(version_json_path);
			o << version_data["versionInfo"].dump(4) << std::endl;
		}

	// Extract forge libs from the installer
	std::filesystem::path forge_lib_path = path / "libraries" / "net" / "minecraftforge" / "forge" / versionid;
	extract_file(zArchive, ("maven/net/minecraftforge/forge/" + versionid + "/forge-" + versionid + ".jar"), (forge_lib_path / ("forge-" + versionid + ".jar")));
	extract_file(zArchive, ("maven/net/minecraftforge/forge/" + versionid + "/forge-" + versionid + "-universal.jar"), forge_lib_path / ("forge-" + versionid + "-universal.jar"));
	extract_file(zArchive, ("forge-" + versionid + "-universal.jar"), forge_lib_path / ("forge-" + versionid + ".jar"));

	// Extract the client.lzma
	std::string lzma_path = Additionals::TempFile::get_tempdir_SYSTEM() + ("lzma-" + std::to_string(random_num) + ".tmp");

	extract_file(zArchive, "data/client.lzma", lzma_path);

	// Install the rest with the vanilla function
	install_minecraft_version(forge_version_id, path, callback);

	// Run the processors
	if (version_data.contains("processors"))
	{
		qInfo() << "Run the forge processors" << std::endl;
		forge_processors(version_data, path, lzma_path, temp_file_path, callback, java);
	}

	MinecraftCpp::natives::downloadNatives(path / "versions" / forge_version_id / "natives", callback);

	// Delete the temporary files
	qInfo() << "Delete the temporary files" << std::endl;
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

bool MinecraftCpp::forge::extract_file(const QZipReader& handler, const std::string& zip_path, const std::filesystem::path& extract_path)
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
	int count = 0;
	for (auto& var : allFiles)
	{
		if (var.filePath.toStdString() == zip_path)
		{
			Additionals::archives::decompressFile(handler, var, p.string());
			break;
		}
		++count;
	}

	if (count == 0)
	{
		return false;
	}

	return true;
}

std::filesystem::path MinecraftCpp::forge::get_data_library_path(const std::string& libname, const std::filesystem::path& path)
{
	/*
	Turns the libname into a path
	*/
	qInfo() << "Get data library path" << std::endl;
	std::string _libname = libname;

	_libname = _libname.substr(1, _libname.size() - 2);
	qDebug() << "libname:" << _libname << std::endl;

	qInfo() << "Get data library path split" << std::endl;
	std::filesystem::path libpath = path / "libraries";
	std::string base_path = Additionals::String::split(_libname, ':')[0];
	std::string version = Additionals::String::split(_libname, ':')[2];
	std::string extra = Additionals::String::split(_libname, ':')[3];
	_libname = Additionals::String::split(_libname, ':')[1];
	std::string fileend;
	qInfo() << "Get data library path split completed" << std::endl;

	for (auto& var : Additionals::String::split(base_path, '.'))
	{
		libpath /= var;
		qDebug() << libpath << std::endl;

		if (Additionals::String::split(extra, '@').size() <= 1)
		{
			qInfo() << "Get data library path split extrajar files" << extra << Additionals::String::split(extra, '@').size() << std::endl;

			if (extra == "mappings" || extra == "mappings-merged")
			{
				fileend = "txt";
			}
			else
			{
				fileend = "jar";
			}
		}
		else
		{
			qInfo() << "Get data library path split extra" << Additionals::String::split(extra, '@').size() << std::endl;

			auto splt = Additionals::String::split(extra, '@');

			qDebug() << splt << std::endl;

			extra = splt[0];
			fileend = splt[1];

			qDebug() << extra << fileend << std::endl;
		}
	}
	qInfo() << "Get data library path split extra completed" << std::endl;

	libpath = libpath / _libname / version / (_libname + "-" + version + "-" + extra + "." + fileend);

	qInfo() << "Get data library path completed" << libpath << std::endl;

	return libpath;
}

std::string MinecraftCpp::forge::get_jar_mainclass(const std::filesystem::path& path)
{
	/*
	Returns the mainclass of a given jar
	*/
	qInfo() << "Get jar mainclass" << std::endl;
	QZipReader zArchive(path.u8string().c_str());
	auto st = zArchive.status();
	//auto ss = zArchive.fileData("META-INF/MANIFEST.MF"); //TODO: impletments this line
	auto manifest_path = std::filesystem::path(Additionals::TempFile::get_tempdir_SYSTEM()) / "MANIFEST.MF";
	foreach(QZipReader::FileInfo var, zArchive.fileInfoList())
	{
		if (var.filePath == "META-INF/MANIFEST.MF")
		{
			//qDebug() << "decompress file" << std::endl;
			Additionals::archives::decompressFile(zArchive, var, manifest_path.u8string());
		}
	}

	QFile file(manifest_path);
	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning() << file.errorString() << std::endl;

		QMessageBox::information(0, "error", file.errorString());
	}

	QTextStream in(&file);
	QStringList lines;

	while (!in.atEnd())
	{
		lines += in.readLine();
	}

	file.close();

	std::string key, value;
	std::unordered_map<std::string, std::string> content;
	//qDebug() << "split lines" << std::endl;
	for (auto& line : lines)
	{
		//qDebug() << "split" << line << Additionals::String::split(line.toStdString(), ':') << Additionals::String::split(line.toStdString(), ':').size() << std::endl;
		if (!(Additionals::String::split(line.toStdString(), ':').size() <= 1))
		{
			key = Additionals::String::split(line.toStdString(), ':')[0];
			value = Additionals::String::split(line.toStdString(), ':')[1];

			//qDebug() << "added split to map" << key << value << std::endl;
			content.insert(std::make_pair(key, value.substr(1)));
		}
	}

	//qDebug() << "Get jar mainclass completed" << std::endl;
	return content["Main-Class"];
}

bool MinecraftCpp::forge::forge_processors(
	nlohmann::json& data,
	const std::filesystem::path& minecraft_directory,
	const std::filesystem::path& lzma_path,
	const std::filesystem::path& installer_path,
	std::shared_ptr<CallbackNull> callback,
	const std::filesystem::path& java)
{
	/*
	Run the processors of the install_profile.json
	*/
	int random_num = 1 + (rand() % 100000);
	std::filesystem::path path = minecraft_directory;

	nlohmann::json argument_vars = nlohmann::json(nlohmann::json::value_t::object);
	nlohmann::json value_ = nlohmann::json(path / "versions" / data["minecraft"].template get<std::string>() / (data["minecraft"].template get<std::string>() + ".jar"));

	argument_vars["{MINECRAFT_JAR}"] = value_;

	qDebug() << "Get client data" << std::endl;
	for (auto& var : data["data"].items())
	{
		qDebug() << "clinet data loop" << var.key() << std::endl;
		if (var.value()["client"].template get<std::string>()._Starts_with("[") && Additionals::String::EndsWith(var.value()["client"].template get<std::string>(), "]"))
		{
			qDebug() << "Getting library path in client data" << std::endl;
			auto lib = get_data_library_path(var.value()["client"].template get<std::string>(), path);
			qDebug() << "lib:" << lib << std::endl;
			argument_vars["{" + var.key() + "}"] = lib;
		}
		else
		{
			qDebug() << "Setting client data in client data" << std::endl;
			argument_vars["{" + var.key() + "}"] = var.value()["client"];
		}
	}
	//qDebug() << argument_vars.template get<std::string>() << std::endl;

	qDebug() << "Get root path" << std::endl;
	std::string root_path = Additionals::TempFile::get_tempdir_SYSTEM() + "forge-root-" + std::to_string(random_num);

	if (argument_vars.contains("{INSTALLER}"))
	{
		argument_vars.erase("{INSTALLER}");
	}
	argument_vars["{INSTALLER}"] = installer_path;
	if (argument_vars.contains("{BINPATCH}"))
	{
		argument_vars.erase("{BINPATCH}");
	}
	argument_vars["{BINPATCH}"] = lzma_path;
	if (argument_vars.contains("{ROOT}"))
	{
		argument_vars.erase("{ROOT}");
	}
	argument_vars["{ROOT}"] = root_path;
	if (argument_vars.contains("{SIDE}"))
	{
		argument_vars.erase("{SIDE}");
	}
	argument_vars["{SIDE}"] = "client";

	qDebug() << "Setting separator" << std::endl;
	std::wstring classpath_seperator = getWClasspathSeparator();

	//callback.get("setMax", empty)(len(data["processors"]))
	//callback->OnProgress(NULL, (*data)["processors"]->to_int(), NULL, NULL);

	int count = -1;
	for (auto& var : data["processors"])
	{
		++count;

		if (var["sides"] != nullptr)
		{
			if (var["sides"][0].template get<std::string>() != "client")
			{
				// Skip server side only processors
				//qDebug() << "Skip server side only processors" << std::endl;
				continue;
			}
		}


		//callback->OnProgress(NULL, NULL, NULL, (L"Running processor " + var["jar"].to_stringW()).c_str());
		//callback->setQLabelProggressValue(("Running processor " + var["jar"].to_string()).c_str());

		// Get the classpath
		qDebug() << "Get the classpath" << std::endl;
		std::wstring classpath = L"";
		for (auto& var2 : var["classpath"])
		{
			qDebug() << "Get the classpath path with separator" << std::endl;
			classpath = classpath + get_library_path(var2.template get<std::string>(), path).wstring() + classpath_seperator;
		}

		qDebug() << "Get the classpath path" << std::endl;
		classpath = classpath + get_library_path(var["jar"].template get<std::string>(), path).wstring();

		qDebug() << "Get the mainclass" << std::endl;
		std::filesystem::path classpath_paths = classpath;
		std::string mainclass = get_jar_mainclass(get_library_path(var["jar"].template get<std::string>(), path));
		std::vector<std::wstring> command;
		qDebug() << "Configure command" << std::endl;
		command.push_back(java.empty() ? L"java" : L"\"" + java.wstring() + L"\"");
		command.push_back(L"-cp");
		command.push_back(classpath_paths.wstring());
		command.push_back(Additionals::Convectors::ConvertStringToWString(mainclass));

		qDebug() << "cmd:" << classpath << mainclass << std::endl;

		qDebug() << "Get the args" << std::endl;
		std::wstring variable = L"";
		for (auto& var2 : var["args"])
		{

			variable = argument_vars[var2.template get<std::string>()] == nullptr ? var2.template get<std::filesystem::path>().wstring() : argument_vars[var2.template get<std::string>()].template get<std::filesystem::path>().wstring();

			if (variable._Starts_with(L"[") && Additionals::String::EndsWith(variable, L"]"))
			{
				qDebug() << variable << path << std::endl;
				command.push_back(getLibraryPath(variable.substr(1, variable.size() - 2), path).wstring());
			}
			else
			{
				command.push_back(variable);
			}
		}

		qDebug() << command << std::endl;
		/*std::wostringstream imploded;
		std::copy(command.begin(), command.end(),
			std::ostream_iterator<std::wstring, wchar_t, std::char_traits<wchar_t>>(imploded, L" "));*/

		std::wstring imploded;
		for (std::vector<std::wstring>::const_iterator ii = command.begin(); ii != command.end(); ++ii)
		{
			imploded += (*ii);
			if (ii + 1 != command.end())
			{
				imploded += L" ";
			}
		}
		std::unique_ptr<wchar_t[]> ch_array = std::make_unique<wchar_t[]>(imploded.size() + 1);
		wcsncpy(ch_array.get(), imploded.c_str(), imploded.size());

		UIThread::run(
			[&]()
			{
				int out = _wsystem(ch_array.get());

			});

		//int out = client::startProcess(command);

		//callback->OnProgress(count, NULL, NULL, NULL);
		//callback->setQProgressValue(count);
	}
	if (std::filesystem::exists(root_path))
	{
		std::filesystem::remove(root_path);
	}

	return true;
}

int MinecraftCpp::fabric::install_fabric_version(const std::string& minecraft_version, const std::filesystem::path& minecraft_directory,
	const std::string& loader_version, std::shared_ptr<CallbackNull> callback, const std::filesystem::path& java)
{
	/*
	Install a fabric version
	*/

	std::string loader = loader_version;
	std::string fabric_minecraft_version = "fabric-loader-" + loader_version + "-" + minecraft_version;
	std::filesystem::path fabric_version_dir = minecraft_directory / "versions" / fabric_minecraft_version;

	// Check if the given version exists
	//qInfo() << "Checking version valid..." << minecraft_version << " " << minecraft_directory << std::endl;
	//if (!_is_version_valid(minecraft_version, minecraft_directory))
	//{
	//	qInfo() << "Version Not Found" << minecraft_version << std::endl;
	//	qFatal() << "Version Not Found " << minecraft_version;
	//	return -1;
	//}
	//// Check if the given Minecraft version supported
	//qInfo() << "Checking version supported..." << minecraft_version << std::endl;
	//if (!_is_minecraft_version_supported(minecraft_version))
	//{
	//	qInfo() << "Unsupported Version" << minecraft_version << std::endl;
	//	qFatal() << "Unsupported Version " << minecraft_version;
	//	return -1;
	//}
	//// Get latest loader version if not given
	//if (loader == "")
	//{
	//	qInfo() << "Getting latest loader..." << std::endl;
	//	loader = get_latest_loader_version();
	//}

	qInfo() << "Installed minecraft..." << std::endl;
	// Make sure the Minecraft version is installed
	install_minecraft_version(minecraft_version, minecraft_directory, callback = callback);

	std::filesystem::create_directories(fabric_version_dir);

	// Get installer version
	std::string installer_version = get_latest_installer_version();

	std::string libraries_url = "https://meta.fabricmc.net/v2/versions/loader/"
		+ minecraft_version + "/" + loader_version + "/profile/json";

	nlohmann::json libraries_json;

	auto dwn_path = DownloadFile(libraries_url, std::filesystem::temp_directory_path());
	std::ifstream ifst(dwn_path);
	libraries_json = nlohmann::json::parse(ifst);
	ifst.close();

	//SJson::JsonValue libraries_json = SJson::JsonParcer::ParseUrl(libraries_url, fabric_version_dir + "\\" + fabric_minecraft_version + ".json");

	libraries_json = inherit_json(libraries_json, minecraft_directory);
	install_libraries(libraries_json, minecraft_directory, callback);
	MinecraftCpp::natives::downloadNatives(fabric_version_dir / "natives", callback);
	//install_minecraft_version(fabric_minecraft_version, minecraft_directory, callback = callback);

	//std::string installer_download_url = "https://maven.fabricmc.net/net/fabricmc/fabric-installer/" + installer_version + "\\fabric-installer-" + installer_version + ".jar";
	//// Generate a temporary path for downloading the installer
	//int random_num = 100 + (rand() % 10000);
	//std::string installer_path = std::filesystem::temp_directory_path().string() + "fabric-installer-" + std::to_string(random_num) + ".tmp";
	//// Download the installer
	//DownloadFile(installer_download_url, installer_path, callback = callback);
	//// Run the installer see https ://fabricmc.net/wiki/install#cli_installation
	//callback->OnProgress(NULL, NULL, NULL, L"Running fabric installer");
	//std::vector<std::string> command;

	//std::string java_w = java;
	//size_t pos = java_w.find("java.exe");

	//java_w.insert(pos + 4, "w");

	//command.push_back(java == "" ? "javaw" : java_w);
	//command.push_back("-jar");
	//command.push_back(installer_path);
	//command.push_back("client");
	//command.push_back("-dir");
	//command.push_back(minecraft_directory);
	//command.push_back("-mcversion");
	//command.push_back(minecraft_version);
	//command.push_back("-loader");
	//command.push_back(loader_version);
	//command.push_back("-launcher win32");
	//command.push_back("-noprofile");
	//command.push_back("-snapshot");

	//client::startProcess(command);

	/*if (result != 0)
	{
		qFatal() << "External Program Error " << command_string;
		return -1;
	}*/

	// Удаляем файл с помощью std::remove()
	/*if (std::remove(installer_path.c_str()) != 0)
	{
		qFatal() << "Error to delete installer file";
	}
	else
	{
		qInfo() << "Installer file sucsesful delete" << std::endl;
	}*/

	// Install all libs of fabric

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
	SJson::JsonValue arr = get_version_list();
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
	SJson::JsonValue minecraft_versions = get_all_minecraft_versions();
	for (auto& i : minecraft_versions.get_array())
	{
		if (i["version"].to_string() == version)
		{
			return true;
		}
	}
	return false;
}

SJson::JsonValue MinecraftCpp::fabric::get_all_minecraft_versions()
{
	/*
	Returns all available Minecraft Versions for fabric
	*/
	std::string FABRIC_MINECARFT_VERSIONS_URL = "https://meta.fabricmc.net/v2/versions/game";
	SJson::JsonParcer parcer;
	return parcer.ParseUrl(FABRIC_MINECARFT_VERSIONS_URL);
}

std::string MinecraftCpp::fabric::get_latest_loader_version()
{
	/*
	Get the latest loader version
	*/
	SJson::JsonValue loader_versions = get_all_loader_versions();
	return loader_versions[0]["version"].to_string();
}

SJson::JsonValue MinecraftCpp::fabric::get_all_loader_versions()
{
	/*
	Returns all loader versions
	*/
	std::string FABRIC_LOADER_VERSIONS_URL = "https://meta.fabricmc.net/v2/versions/loader";
	SJson::JsonParcer parcer;
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

SJson::JsonValue MinecraftCpp::fabric::parse_maven_metadata(const std::string& url)
{
	/*
	Parses a maven metadata file
	*/

	SJson::JsonValue data = SJson::JsonValue(std::unordered_map<std::string, SJson::JsonValue>());
	std::string text;

	std::string destenation_file = Additionals::TempFile::get_tempdir_SYSTEM();

	{
		std::string replace_url = url;
		replace_url = Additionals::String::split(url, '/')[Additionals::String::split(url, '/').size() - 1];
		destenation_file = destenation_file /*+ "\\"*/ + replace_url;
	}
	//std::shared_ptr<QCallback> callback = std::make_shared<QCallback>();
	auto path = DownloadFile(url, destenation_file/*, callback*/);

	if (path != "")
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
		data.add_value(std::make_pair("release", SJson::JsonValue(result)));
	}

	pattern = R"(<latest>(.*?)</latest>)";
	if (std::regex_search(text, mathc, pattern))
	{
		// matches[0] содержит всю найденную строку, matches[1] содержит текст между тегами
		std::string result = mathc[1];
		data.add_value(std::make_pair("latest", SJson::JsonValue(result)));
	}

	data.add_value(std::make_pair("versions", SJson::JsonValue(std::vector<SJson::JsonValue>())));

	pattern = R"(<version>(.*?)</version>)";
	while (std::regex_search(text, mathc, pattern))
	{
		// matches[0] содержит всю найденную строку, matches[1] содержит текст между тегами
		std::string result = mathc[1];
		data["versions"].add_value(SJson::JsonValue(result));

		text = mathc.suffix();
	}

	return data;
}