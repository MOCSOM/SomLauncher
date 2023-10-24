#include "SomLauncherMainWindow.h"

void SomLauncherMainWindow::start_minecraft_params()
{
	qInfo() << "Config loaded" << std::endl;
	qInfo() << this->config_parce["user"]["name"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["memory"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["mcdir"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["isInstallMods"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["server"].to_string() << std::endl;

	std::string java = "";
	std::string core = "";
	std::string version = "";

	this->configureOptions();

	switch (this->config_parce["user"]["server"].to_int())
	{
	case 0:
	{
		java = this->servers_parce["servers"][0]["java"].to_string();
		core = this->servers_parce["servers"][0]["core"].to_string();
		version = this->servers_parce["servers"][0]["version"].to_string();
		std::string launch_version = install_minecraft(version, core, this->servers_parce["servers"][0]["loaderVersion"].to_string(), java, this->config_parce["user"]["mcdir"].to_string(), this->options);
		std::string command = MinecraftCpp::get_minecraft_command__(launch_version, this->minecraft_core_dir_path, options);
		qInfo() << command;

		this->close();

		std::filesystem::current_path(this->minecraft_core_dir_path);
		MinecraftCpp::start_minecraft("", command);

		break;
	}
	case 1:
	{
		java = this->servers_parce["servers"][1]["java"].to_string();
		core = this->servers_parce["servers"][1]["core"].to_string();
		version = this->servers_parce["servers"][1]["version"].to_string();
		std::string launch_version = install_minecraft(version, core, this->servers_parce["servers"][1]["loaderVersion"].to_string(), java, this->config_parce["user"]["mcdir"].to_string(), this->options);

		std::string command = MinecraftCpp::get_minecraft_command__(launch_version, this->minecraft_core_dir_path, options);
		qInfo() << command << std::endl;

		this->close();

		std::filesystem::current_path(this->minecraft_core_dir_path);
		MinecraftCpp::start_minecraft("", command);

		break;
	}
	case 2:
	{
		java = servers_parce["servers"][2]["java"].to_string();
		core = servers_parce["servers"][2]["core"].to_string();
		version = servers_parce["servers"][2]["version"].to_string();
		std::string launch_version = install_minecraft(version, core, this->servers_parce["servers"][2]["loaderVersion"].to_string(), java, this->config_parce["user"]["mcdir"].to_string(), this->options);

		std::string command = MinecraftCpp::get_minecraft_command__(launch_version, this->minecraft_core_dir_path, options);
		qInfo() << command << std::endl;

		this->close();

		std::filesystem::current_path(this->minecraft_core_dir_path);
		MinecraftCpp::start_minecraft("", command);

		break;
	}
	case 3:
	{
		java = this->servers_parce["servers"][3]["java"].to_string();
		core = this->servers_parce["servers"][3]["core"].to_string();
		version = this->servers_parce["servers"][3]["version"].to_string();

		std::string launch_version = install_minecraft(version, core, this->servers_parce["servers"][3]["loaderVersion"].to_string(), java, this->config_parce["user"]["mcdir"].to_string(), this->options);

		std::string command = MinecraftCpp::get_minecraft_command__(launch_version, this->minecraft_core_dir_path, options);
		qInfo() << command << std::endl;

		this->close();

		std::filesystem::current_path(this->minecraft_core_dir_path);
		MinecraftCpp::start_minecraft("", command);

		break;
	}
	default:
	{
		break;
	}
	}
}

std::string SomLauncherMainWindow::install_minecraft(
	std::string version,
	std::string loader_mame,
	std::string loader_version,
	std::string java,
	std::string mcdir,
	MinecraftCpp::option::MinecraftOptions options)
{
	checkJava(options, java);

	Json::JsonParcer parecer_modpack;
	Json::JsonValue data_modpack = parecer_modpack.ParseFile(this->minecraft_core_dir_path);

	/* minecraft_version = 1.12.2 + "-" + forge_version = 14.23.5.2860 */
	//wchar_t* launch_varsion = L"1.12.2-forge-14.23.5.2860";

	std::string launch_version;
	std::string install_version;

	std::shared_ptr<CallbackDict> callback = std::make_shared<CallbackDict>();
	callback->setQProgressBar(ui.progressBar_ahtung);
	callback->setQLabelProggress(ui.label_download_status_change);

	if (loader_mame == "forge" || loader_mame == "Forge")
	{
		launch_version = version + "-" + loader_mame + "-" + loader_version;
		install_version = version + "-" + loader_version;

		MinecraftCpp::forge::install_forge_version(
			install_version, this->minecraft_core_dir_path, callback.get(), options.executablePath);

		return launch_version;
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{
		launch_version = std::string("fabric") + "-" + "loader" + "-" + loader_version + "-" + version;

		MinecraftCpp::fabric::install_fabric_version(
			version, this->minecraft_core_dir_path, loader_version, callback.get(), options.executablePath);

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

void SomLauncherMainWindow::checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison)
{
	std::string java_dir = "";

	if (java_verison == "")
	{
		options.executablePath = DDIC::Download::Files::getInstalledJavaInDirectory(this->minecraft_core_dir_path) + "\\" + "bin" + "\\" + "java.exe";

		return;
	}

	if (!DDIC::Download::Java::check_system_verison_java(java_verison))
	{
		if (!DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path, java_verison))
		{
			java_dir = DDIC::Download::Java::install(java_verison, this->minecraft_core_dir_path);
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
				options.executablePath = var.first + "\\" + "bin" + "\\" + "java.exe";
			}
		}
	}
}

size_t SomLauncherMainWindow::getMinecraftModsCount()
{
	size_t count = 0;

	std::filesystem::directory_iterator directory(this->minecraft_core_dir_path + "\\" + "mods");
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