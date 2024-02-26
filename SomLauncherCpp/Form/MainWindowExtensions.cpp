#include "SomLauncherMainWindow.h"

nlohmann::json SomLauncherMainWindow::getServersFromServer()
{
	nlohmann::json result;
	try
	{
		std::stringstream response;
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		request.setOpt(curlpp::options::Verbose(true));
		request.setOpt(curlpp::options::Url("https://mocsom.site/api/servers/?format=json"));
		request.setOpt(curlpp::options::WriteStream(&response));

		request.perform();
		long http_code = curlpp::infos::ResponseCode::get(request);


		if (http_code != 200)
		{
			qWarning() << "code not 200" << std::endl;
		}

		result = nlohmann::json::parse(response.str());
	}
	catch (curlpp::LogicError& e)
	{
		qWarning() << e.what() << std::endl;
	}
	catch (curlpp::RuntimeError& e)
	{
		qWarning() << e.what() << std::endl;
	}

	return result;
}

void SomLauncherMainWindow::start_minecraft_params()
{
	qInfo() << "Config loaded" << std::endl;
	qInfo() << this->config_parce["user"]["name"].template get<std::string>() << std::endl;
	qInfo() << this->config_parce["user"]["memory"].template get<int>() << std::endl;
	if (this->config_parce["user"]["mcdir"].is_array())
	{
		std::filesystem::path pat = "";
		for (auto& symbol : this->config_parce["user"]["mcdir"])
		{
			pat += static_cast<wchar_t>(symbol.template get<int>());
		}
		qInfo() << pat << std::endl;
	}
	else
	{
		qInfo() << this->config_parce["user"]["mcdir"].template get<std::filesystem::path>() << std::endl;
	}
	qInfo() << this->config_parce["user"]["isInstallMods"].template get<bool>() << std::endl;
	qInfo() << this->config_parce["user"]["server"].template get<int>() << std::endl;

	qInfo() << "Configurate options..." << std::endl;
	this->configureOptions();
	this->setUuidFromAccount();

	switch (this->config_parce["user"]["server"].template get<int>())
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
	std::string java = std::to_string(this->servers_parce[index]["java_versions"].template get<int>());
	std::string core = this->servers_parce[index]["loader_core"].template get<std::string>();
	std::string version = this->servers_parce[index]["minecraft_version"].template get<std::string>();
	std::string name = this->servers_parce[index]["server_slug"].template get<std::string>();
	std::string ip_port = this->servers_parce[index]["server_ip"].template get<std::string>();
	std::string modpack_id = this->servers_parce[index]["modpack_id"].template get<std::string>();

	name.erase(Additionals::String::remove_if(name.begin(), name.end(), isspace));

	std::filesystem::path instance_path = this->minecraft_core_dir_path / name;

	std::shared_ptr<QCallback> callback = std::make_shared<QCallback>();
	callback->setQProgressBar(ui.progressBar_ahtung);
	callback->setQLabelProggress(ui.label_download_status_change);
	callback->setQLabelProggress(ui.label_download_status_change);
	callback->setQLabelDownloadSpeed(ui.label_download_speed);
	callback->setQLabelDownloadTime(ui.label_download_time);

	qInfo() << "starting installing minecraft..." << std::endl;

	std::string launch_version = install_minecraft(
		instance_path,
		version,
		core,
		this->servers_parce[index]["minimal_loader_version"].template get<std::string>(),
		java,
		this->options,
		callback
	);

	nlohmann::json modpack_info = getModpackInfoFromServer(modpack_id);
	installMods(instance_path / "mods", modpack_info, callback);

	serversdat::createServersDat(instance_path / "servers.dat", name, ip_port);

	options.gameDirectory = instance_path.wstring();

	std::vector<std::variant<std::string, std::filesystem::path, std::wstring>> command = MinecraftCpp::get_minecraft_command__(launch_version, instance_path, options);
	//qInfo() << command;

	//MinecraftCpp::option::LaunchOptions _options;
	//_options.gameDir = options.gameDirectory;
	//_options.javaArguments = { options.jvmArguments };
	//_options.java = options.executablePath;
	//_options.maxMemory = this->max_memory;
	//_options.minMemory = 1024;
	//_options.versionName = version;

	//std::vector<std::string> command = MinecraftCpp::generateCommandLine(instance_path.u8string(), _options);
	setUiToDownload(false);
	hide();

	auto work_dir = std::filesystem::current_path();
	std::filesystem::current_path(instance_path);
	client::startProcess(command);
	std::filesystem::current_path(work_dir);

	setWindowState(windowState()/* & ~Qt::WindowMinimized)*/ | Qt::WindowActive);
	show();
}

std::string SomLauncherMainWindow::install_minecraft(
	const std::filesystem::path& install_path,
	std::string version,
	std::string loader_mame,
	std::string loader_version,
	std::string java,
	MinecraftCpp::option::MinecraftOptions& options,
	std::shared_ptr<CallbackNull> callback) const
{
	//SJson::JsonValue data_modpack = parecer_modpack.ParseFile(this->minecraft_core_dir_path);

	/* minecraft_version = 1.12.2 + "-" + forge_version = 14.23.5.2860 */
	//wchar_t* launch_varsion = L"1.12.2-forge-14.23.5.2860";

	std::string launch_version;
	std::string install_version;

	qInfo() << "Checking java..." << std::endl;
	checkJava(options, java, callback.get());

	qInfo() << "Starting download minecraft..." << std::endl;
	if (loader_mame == "forge" || loader_mame == "Forge")
	{
		launch_version = version + "-" + loader_mame + "-" + loader_version;
		install_version = version + "-" + loader_version;

		qInfo() << "Starting download forge..." << std::endl;
		MinecraftCpp::forge::install_forge_version(
			install_version, install_path, callback, options.executablePath);

		return launch_version;
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{
		launch_version = std::string("fabric") + "-" + "loader" + "-" + loader_version + "-" + version;

		qInfo() << "Starting download fabric..." << std::endl;
		MinecraftCpp::fabric::install_fabric_version(
			version, install_path, loader_version, callback, options.executablePath);

		std::filesystem::copy_file(Join({ install_path.u8string(), "versions", version, version + ".jar" }),
			Join({ install_path.u8string(), "versions", launch_version, launch_version + ".jar" }),
			std::filesystem::copy_options::overwrite_existing);

		return launch_version;
	}

	qWarning() << "Unknow loader";
	return std::string();
}

nlohmann::json SomLauncherMainWindow::getModpackInfoFromServer(const std::string& modpack_id)
{
	nlohmann::json modpacks;
	try
	{
		std::stringstream response;
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		request.setOpt(curlpp::options::Verbose(true));
		request.setOpt(curlpp::options::Url("https://mocsom.site/api/modpacks/" + modpack_id + "/?format=json"));
		request.setOpt(curlpp::options::WriteStream(&response));

		request.perform();
		long http_code = curlpp::infos::ResponseCode::get(request);

		modpacks = nlohmann::json::parse(response.str());

		if (http_code != 200)
		{
			qWarning() << "code not 200" << std::endl;
		}
	}
	catch (curlpp::LogicError& e)
	{
		qWarning() << e.what() << std::endl;
	}
	catch (curlpp::RuntimeError& e)
	{
		qWarning() << e.what() << std::endl;
	}
	return modpacks;
}

void SomLauncherMainWindow::installMods(const std::filesystem::path& install_path,
	const nlohmann::json& modpack_info,
	std::shared_ptr<CallbackNull> callback)
{
	std::filesystem::create_directories(install_path);
	for (auto& mod : modpack_info["mods"])
	{
		std::string url = mod["mod_link"].template get<std::string>();
		std::string sha1 = mod["sha1"].template get<std::string>();

		callback->setTotalDownloadSize(web::utils::getFileSizeFromUrl(url));

		std::filesystem::path downloaded_path = DownloadFile(url,
			install_path, callback, sha1);
	}
}

void SomLauncherMainWindow::createSettingsForm()
{
	this->settings_dialog = std::make_unique<SettingsDialog>(this->account_data, this->options, this);

	this->settings_dialog->setConfigPath(this->config_path);

	QObject::connect(this->settings_dialog.get(), &SettingsDialog::acceptButtonClicked, this, &SomLauncherMainWindow::saveSettings);
	QObject::connect(this->settings_dialog.get(), &SettingsDialog::setToDefaultButtonClicked,
		this, [=]() -> void
		{
			this->settings_dialog->setToDefault(default_options, recomended_memory);
		});
}

bool SomLauncherMainWindow::isConfigExist() const
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

void SomLauncherMainWindow::createConfig() const
{
	std::filesystem::copy(this->template_config_path, this->config_path, std::filesystem::copy_options::overwrite_existing);
}

void SomLauncherMainWindow::configureOptions()
{

	//char* appdata = nullptr;
	//size_t appdata_sz = 0;

	//_dupenv_s(&appdata, &appdata_sz, "APPDATA");
	//std::filesystem::temp_directory_path();

	//std::string path_wch_java = DDIC::Download::Files::_get_java_path(Join({ appdata == nullptr ? "" : appdata, ".SomSomSom" }))[0].first + "\\" + "bin" + "\\" + "java.exe";
	//qDebug() << this->config_parce.get_count() << std::endl;

	this->options.customResolution = false;
	this->options.gameDirectory = this->minecraft_core_dir_path;
	this->options.launcherName = this->launcher_name;
	this->options.launcherVersion = this->launcher_version;
	this->options.username = this->username;
	this->options.jvmArguments = "-Xms1024M -Xmx" + std::to_string(this->config_parce["user"]["memory"].template get<int>()) + "M";
	this->options.executablePath = "";
	this->options.uuid = "uuu";
	this->options.token = "uuu";

	checkJava(this->options);

	this->default_options = this->options;
}

void SomLauncherMainWindow::checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison, CallbackNull* callback) const
{
	qInfo() << "Checking java..." << std::endl;
	std::filesystem::path java_dir = "";

	if (java_verison == "")
	{
		qInfo() << "Getting installed java in directory..." << std::endl;
		std::filesystem::path java_path =
			DDIC::Download::Files::getInstalledJavaInDirectory(this->minecraft_core_dir_path);

		if (java_path == "")
		{
			qInfo() << "Getting standart installed java in directory..." << std::endl;
			options.executablePath = DDIC::Download::Files::getInstalledJavaInDirectory();
			return;
		}

		options.executablePath = java_path / "bin" / "java.exe";

		return;
	}

	if (!DDIC::Download::Java::check_system_verison_java(java_verison))
	{
		qInfo() << "Checking installed java..." << std::endl;
		if (!DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path, java_verison))
		{
			qInfo() << "Install java..." << std::endl;
			java_dir = DDIC::Download::Java::install(java_verison, this->minecraft_core_dir_path, callback);
			options.executablePath = java_dir / "bin" / "java.exe";
		}
		else
		{
			qInfo() << "Getting java..." << std::endl;
			for (auto& var : DDIC::Download::Files::_get_java_path(this->minecraft_core_dir_path))
			{
				if (var.second == java_verison)
				{
					options.executablePath = var.first / "bin" / "java.exe";
				}
			}
		}
	}
	else
	{
		//java_dir = DDIC::Download::Java::install(java_verison, this->minecraft_core_dir_path, callback);
		qInfo() << "Getting java in programm files..." << std::endl;
		char* program_files = nullptr;
		size_t program_files_sz = 0;
		_dupenv_s(&program_files, &program_files_sz, "ProgramFiles");

		for (auto& var : DDIC::Download::Files::_get_java_path(
			std::string(program_files == nullptr ? "" : program_files)
			+ '\\' + "java"))
		{
			if (var.second == java_verison)
			{
				options.executablePath = var.first / "bin" / "java.exe";
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
		directory = std::filesystem::directory_iterator(this->minecraft_core_dir_path / "mods");
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
	if (this->servers_parce.size() > this->config_parce["user"]["server"].template get<int>())
	{
		return this->servers_parce[this->config_parce["user"]["server"].template get<int>()]["server_name"].template get<std::string>();
	}
	else
	{
		return "";
	}
}

const std::filesystem::path SomLauncherMainWindow::getConfigPath()
{
	return std::filesystem::path(this->config_path);
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

nlohmann::json SomLauncherMainWindow::getLatestVersionFromDatabase()
{
	return nlohmann::json();
}

std::string SomLauncherMainWindow::getCurrentVersionFromConfig()
{
	return this->config_parce["launcher"]["verison"].template get<std::string>();
}

void SomLauncherMainWindow::setCurrentVersionFromGithub()
{
	if (getCurrentVersionFromConfig() == "")
	{
		this->config_parce["launcher"]["verison"] = getLatestVersionFromGithub();

		std::ofstream o(this->config_path);
		o << this->config_parce.dump(4) << std::endl;
		o.close();
	}
}

void SomLauncherMainWindow::setCurrentVersionFromDatabase()
{
	if (getCurrentVersionFromConfig().empty())
	{
		/*this->config_parce["launcher"]["verison"] = getLatestVersionFromDatabase()[getLatestVersionFromDatabase().size() - 1]["file"].template get<std::string>();
		std::ofstream o(this->config_path);
		o << this->config_parce.dump(4) << std::endl;
		o.close();*/
	}
}

bool SomLauncherMainWindow::isVersionOld()
{
	/*if (getCurrentVersionFromConfig() != getLatestVersionFromDatabase()[getLatestVersionFromDatabase().size()]["file"].template get<std::string>())
	{
		return true;
	}*/
	return false;
}

void SomLauncherMainWindow::setAccountData(const nlohmann::json& data)
{
	this->account_data = data;
}

void SomLauncherMainWindow::setUuidFromAccount()
{
	this->options.uuid = this->account_data["id"].template get<std::string>();
}

std::unique_ptr<SettingsDialog>& SomLauncherMainWindow::getSettingsDialog()
{
	return this->settings_dialog;
}

const std::string& SomLauncherMainWindow::getStyleSheetPath()
{
	return this->style_sheet;
}
