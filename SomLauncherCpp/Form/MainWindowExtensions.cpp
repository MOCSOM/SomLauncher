#include "SomLauncherMainWindow.h"

void SomLauncherMainWindow::start_minecraft_params()
{
	qInfo() << "Config loaded" << std::endl;
	qInfo() << this->config_parce["user"]["name"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["memory"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["mcdir"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["isInstallMods"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["server"].to_string() << std::endl;

	this->configureOptions();

	switch (this->config_parce["user"]["server"].to_int())
	{
	case 0:
	{
		setupInstallMinecraft(0);

		break;
	}
	case 1:
	{
		setupInstallMinecraft(1);

		break;
	}
	case 2:
	{
		setupInstallMinecraft(2);

		break;
	}
	case 3:
	{
		setupInstallMinecraft(3);

		break;
	}
	default:
	{
		break;
	}
	}
}

void SomLauncherMainWindow::setupInstallMinecraft(const size_t& index)
{
	std::string java = this->servers_parce["servers"][index]["java"].to_string();
	std::string core = this->servers_parce["servers"][index]["core"].to_string();
	std::string version = this->servers_parce["servers"][index]["version"].to_string();
	std::string name = this->servers_parce["servers"][index]["name"].to_string();

	name.erase(Additionals::String::remove_if(name.begin(), name.end(), isspace));

	std::filesystem::path instance_path = this->minecraft_core_dir_path + "\\" + name;

	std::string launch_version = install_minecraft(
		instance_path,
		version,
		core,
		this->servers_parce["servers"][index]["loaderVersion"].to_string(),
		java,
		this->config_parce["user"]["mcdir"].to_string(),
		this->options);

	options.gameDirectory = instance_path.u8string();
	std::vector<std::string> command = MinecraftCpp::get_minecraft_command__(launch_version, instance_path.u8string(), options);
	qInfo() << command;

	//MinecraftCpp::option::LaunchOptions _options;
	//_options.gameDir = options.gameDirectory;
	//_options.javaArguments = { options.jvmArguments };
	//_options.java = options.executablePath;
	//_options.maxMemory = this->max_memory;
	//_options.minMemory = 1024;
	//_options.versionName = version;

	//std::vector<std::string> command = MinecraftCpp::generateCommandLine(instance_path.u8string(), _options);

	this->close();

	std::filesystem::current_path(instance_path);
	MinecraftCpp::start_minecraft(command);
}

std::string SomLauncherMainWindow::install_minecraft(
	const std::filesystem::path& install_path,
	std::string version,
	std::string loader_mame,
	std::string loader_version,
	std::string java,
	std::string mcdir,
	MinecraftCpp::option::MinecraftOptions& options)
{
	//Json::JsonValue data_modpack = parecer_modpack.ParseFile(this->minecraft_core_dir_path);

	/* minecraft_version = 1.12.2 + "-" + forge_version = 14.23.5.2860 */
	//wchar_t* launch_varsion = L"1.12.2-forge-14.23.5.2860";

	std::string launch_version;
	std::string install_version;

	std::shared_ptr<CallbackDict> callback = std::make_shared<CallbackDict>();
	callback->setQProgressBar(ui.progressBar_ahtung);
	callback->setQLabelProggress(ui.label_download_status_change);

	checkJava(options, java, callback.get());

	if (loader_mame == "forge" || loader_mame == "Forge")
	{
		launch_version = version + "-" + loader_mame + "-" + loader_version;
		install_version = version + "-" + loader_version;

		MinecraftCpp::forge::install_forge_version(
			install_version, install_path.u8string(), callback.get(), options.executablePath);

		return launch_version;
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{
		launch_version = std::string("fabric") + "-" + "loader" + "-" + loader_version + "-" + version;

		MinecraftCpp::fabric::install_fabric_version(
			version, install_path.u8string(), loader_version, callback.get(), options.executablePath);

		std::filesystem::copy_file(Join({ install_path.u8string(), "versions", version, version + ".jar" }),
			Join({ install_path.u8string(), "versions", launch_version, launch_version + ".jar" }),
			std::filesystem::copy_options::overwrite_existing);

		return launch_version;
	}
	return std::string();
}

bool SomLauncherMainWindow::isConfigExist()
{
	if (std::filesystem::exists(this->config_path))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SomLauncherMainWindow::createConfig()
{
	std::filesystem::copy(this->template_config_path, this->config_path, std::filesystem::copy_options::overwrite_existing);
}

void SomLauncherMainWindow::configureOptions()
{
	char* appdata = nullptr;
	size_t appdata_sz = 0;

	_dupenv_s(&appdata, &appdata_sz, "APPDATA");

	//std::string path_wch_java = DDIC::Download::Files::_get_java_path(Join({ appdata == nullptr ? "" : appdata, ".SomSomSom" }))[0].first + "\\" + "bin" + "\\" + "java.exe";

	this->options.customResolution = false;
	this->options.gameDirectory = this->minecraft_core_dir_path;
	this->options.launcherName = this->launcher_name;
	this->options.launcherVersion = this->launcher_version;
	this->options.username = this->username;
	this->options.jvmArguments = "-Xms1024M -Xmx" + this->config_parce["user"]["memory"].to_string() + "M";
	this->options.executablePath = "";
	this->options.uuid = "uuu";
	this->options.token = "uuu";

	checkJava(this->options);

	this->default_options = this->options;
}

void SomLauncherMainWindow::checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison, CallbackNull* callback)
{
	std::string java_dir = "";

	if (java_verison == "")
	{
		std::string java_path = DDIC::Download::Files::getInstalledJavaInDirectory(this->minecraft_core_dir_path);

		if (java_path == "")
		{
			options.executablePath = DDIC::Download::Files::getInstalledJavaInDirectory();
			return;
		}

		options.executablePath = java_path + "\\" + "bin" + "\\" + "java.exe";

		return;
	}

	if (!DDIC::Download::Java::check_system_verison_java(java_verison))
	{
		if (!DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path, java_verison))
		{
			java_dir = DDIC::Download::Java::install(java_verison, this->minecraft_core_dir_path, callback);
			options.executablePath = java_dir + "\\" + "bin" + "\\" + "java.exe";
		}
		else
		{
			for (auto& var : DDIC::Download::Files::_get_java_path(this->minecraft_core_dir_path))
			{
				if (var.second == java_verison)
				{
					options.executablePath = var.first + "\\" + "bin" + "\\" + "java.exe";
				}
			}
		}
	}
	else
	{
		char* program_files = nullptr;
		size_t program_files_sz = 0;
		_dupenv_s(&program_files, &program_files_sz, "ProgramFiles");

		for (auto& var : DDIC::Download::Files::_get_java_path(
			std::string(program_files == nullptr ? "" : program_files)
			+ '\\' + "java"))
		{
			if (var.second == java_verison)
			{
				options.executablePath = "\"" + var.first + "\\" + "bin" + "\\" + "java.exe" + "\"";
			}
		}
	}
}

size_t SomLauncherMainWindow::getMinecraftModsCount()
{
	size_t count = 0;
	std::filesystem::directory_iterator directory;

	try
	{
		directory = std::filesystem::directory_iterator(this->minecraft_core_dir_path + "\\" + "mods");
	}
	catch (const std::exception&)
	{
		return count;
	}

	for (std::filesystem::directory_entry elem : directory)
	{
		if (elem.is_regular_file())
		{
			if (elem.path().extension().u8string() == ".jar" || elem.path().extension().u8string() == ".disabled")
				++count;
		}
	}

	return count;
}

ServerTypes SomLauncherMainWindow::getServerType()
{
	return ServerTypes::LIVE;
}

std::string SomLauncherMainWindow::getCurrentServerName()
{
	return this->servers_parce["servers"][this->config_parce["user"]["server"].to_int()]["name"].to_string();
}

std::string SomLauncherMainWindow::getLatestVersionFromGithub()
{
	QUrl url("https://api.github.com/repos/MOCSOM/SomLauncher/tags");
	qInfo() << url.toString().toStdString() << std::endl;
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	QNetworkAccessManager nam;
	QNetworkReply* reply = nam.get(request);

	bool timeout = false;

	while (!timeout)
	{
		qApp->processEvents();
		if (reply->isFinished()) break;
	}

	if (reply->isFinished())
	{
		QByteArray response_data = reply->readAll();
		QJsonDocument json = QJsonDocument::fromJson(response_data);
		return json[json.array().size() - 1]["name"].toString().toStdString();
	}
	else
	{
		return QString("Timeout").toStdString();
	}
}

std::string SomLauncherMainWindow::getCurrentVersionFromConfig()
{
	return this->config_parce["launcher"]["verison"].to_string();
}

void SomLauncherMainWindow::setCurrentVersionFromGithub()
{
	if (getCurrentVersionFromConfig() == "")
	{
		this->config_parce["launcher"]["verison"] = getLatestVersionFromGithub();
		this->config_parce.save_json_to_file(this->config_path, 4);
	}
}

bool SomLauncherMainWindow::isVersionOld()
{
	if (getCurrentVersionFromConfig() != getLatestVersionFromGithub())
	{
		return true;
	}
	return false;
}