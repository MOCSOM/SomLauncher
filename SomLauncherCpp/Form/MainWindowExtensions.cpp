#include "SomLauncherMainWindow.h"

void SomLauncherMainWindow::setConnectionWithDatabase()
{
	try
	{
		this->database_connection = sqlbase::mysql::sqlconnector::connect(
			"79.174.93.203", "sombd", "somuser", "Vblyfqn_jqk23");
	}
	catch (sql::SQLException& exc)
	{
		qWarning() << "exception " << exc.what() << " trying again";
		if (connection_tries != 0)
		{
			--connection_tries;
			setConnectionWithDatabase();
		}
	}
}

Json::JsonValue SomLauncherMainWindow::getServersFromDatabase()
{
	sql::ResultSet* res = nullptr;
	QString querry =
		R"(
SELECT
	JSON_OBJECT('servers',
	JSON_ARRAYAGG(JSON_OBJECT('server_id',server_id, 'name',server_name, 'server_img',server_img, 'description',server_description, 'server_ip',server_ip, 'java',java_versions, 'version',minecraft_version, 'core',loader_core, 'loaderVersion',minimal_loader_version, 'server_type',server_type, 'server_slug',server_slug, 'modpack_id_id',modpack_id_id)))
FROM servers_server)";

	try
	{
		res = sqlbase::mysql::sqlconnector::sendQuerry(this->database_connection, querry.toStdString());
	}
	catch (sql::SQLException& eSQL)
	{
		qFatal() << "Failed with exception: " << eSQL.what();
	}
	Json::JsonValue returned;

	while (res->next())
	{
		//std::cout << res->getString(1) << std::endl;
		returned = Json::JsonParcer::ParseJson(res->getString(1));
	}
	return returned;
}

Json::JsonValue SomLauncherMainWindow::getServersFromDatabase(sql::Connection* connect)
{
	sql::ResultSet* res = nullptr;
	QString querry =
		"SELECT JSON_OBJECTAGG('servers',JSON_ARRAY(JSON_OBJECT('server_id',server_id, 'name',server_name, 'server_img',server_img, 'description',server_description, 'server_ip',server_ip, 'java',java_versions, 'version',minecraft_version, 'core',loader_core, 'loaderVersion',minimal_loader_version, 'server_type',server_type, 'server_slug',server_slug, 'modpack_id_id',modpack_id_id))) FROM servers_server";
	try
	{
		res = sqlbase::mysql::sqlconnector::sendQuerry(connect, querry.toStdString());
	}
	catch (sql::SQLException& eSQL)
	{
		qFatal() << "Failed with exception: " << eSQL.what();
	}
	Json::JsonValue returned;

	while (res->next())
	{
		//std::cout << res->getString(1) << std::endl;
		returned = Json::JsonParcer::ParseJson(res->getString(1));
	}
	return returned;
}

void SomLauncherMainWindow::start_minecraft_params()
{
	qInfo() << "Config loaded" << std::endl;
	qInfo() << this->config_parce["user"]["name"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["memory"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["mcdir"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["isInstallMods"].to_string() << std::endl;
	qInfo() << this->config_parce["user"]["server"].to_string() << std::endl;

	qInfo() << "Configurate options..." << std::endl;
	this->configureOptions();
	this->setUuidFromAccount();

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
	std::string name = this->servers_parce["servers"][index]["server_slug"].to_string();
	std::string ip_port = this->servers_parce["servers"][index]["server_ip"].to_string();
	std::string modpack_id = this->servers_parce["servers"][index]["modpack_id_id"].to_string();

	name.erase(Additionals::String::remove_if(name.begin(), name.end(), isspace));

	std::filesystem::path instance_path = this->minecraft_core_dir_path + "\\" + name;

	std::shared_ptr<CallbackDict> callback = std::make_shared<CallbackDict>();
	callback->setQProgressBar(ui.progressBar_ahtung);
	callback->setQLabelProggress(ui.label_download_status_change);

	qInfo() << "starting installing minecraft..." << std::endl;

	std::string launch_version = install_minecraft(
		instance_path,
		version,
		core,
		this->servers_parce["servers"][index]["loaderVersion"].to_string(),
		java,
		this->config_parce["user"]["mcdir"].to_string(),
		this->options,
		callback
	);

	installMods(instance_path / "mods", name, "0", callback);

	serversdat::createServersDat(instance_path / "servers.dat", name, ip_port);

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
	client::startProcess(command);
}

std::string SomLauncherMainWindow::install_minecraft(
	const std::filesystem::path& install_path,
	std::string version,
	std::string loader_mame,
	std::string loader_version,
	std::string java,
	std::string mcdir,
	MinecraftCpp::option::MinecraftOptions& options,
	std::shared_ptr<CallbackNull> callback) const
{
	//Json::JsonValue data_modpack = parecer_modpack.ParseFile(this->minecraft_core_dir_path);

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
			install_version, install_path.u8string(), callback.get(), options.executablePath);

		return launch_version;
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{
		launch_version = std::string("fabric") + "-" + "loader" + "-" + loader_version + "-" + version;

		qInfo() << "Starting download fabric..." << std::endl;
		MinecraftCpp::fabric::install_fabric_version(
			version, install_path.u8string(), loader_version, callback.get(), options.executablePath);

		std::filesystem::copy_file(Join({ install_path.u8string(), "versions", version, version + ".jar" }),
			Join({ install_path.u8string(), "versions", launch_version, launch_version + ".jar" }),
			std::filesystem::copy_options::overwrite_existing);

		return launch_version;
	}

	qWarning() << "Unknow loader";
	return std::string();
}

void SomLauncherMainWindow::installMods(const std::filesystem::path& install_path,
	const std::string& modpack_name, const std::string& version,
	std::shared_ptr<CallbackNull> callback)
{
	std::string querry = R"(SELECT mods_mod.mod_link FROM servers_server
INNER JOIN mods_modpack_mods ON servers_server.modpack_id_id = mods_modpack_mods.modpack_id
INNER JOIN mods_mod ON mods_modpack_mods.mod_id = mods_mod.mod_id
WHERE servers_server.server_slug LIKE )" + std::string("'%") + modpack_name + "%'";
	sql::ResultSet* result = nullptr;
	try
	{
		sql::ResultSet* result = sqlbase::mysql::sqlconnector::sendQuerry(this->database_connection, querry);

		while (result->next())
		{
			std::filesystem::create_directories(install_path);
			std::string downloaded_path = DownloadFile(result->getString(1),
				install_path.u8string(), callback.get());
		}
	}
	catch (const sql::SQLException& exc)
	{
		qWarning() << exc.what() << " " << exc.getErrorCode() << " " << exc.getSQLState();
	}

	//MinecraftCpp::modpacks::download::database::installModPack(, install_path, callback);
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

void SomLauncherMainWindow::checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison, CallbackNull* callback) const
{
	std::string java_dir = "";

	if (java_verison == "")
	{
		qInfo() << "Getting installed java in directory..." << std::endl;
		std::string java_path =
			DDIC::Download::Files::getInstalledJavaInDirectory(this->minecraft_core_dir_path);

		if (java_path == "")
		{
			qInfo() << "Getting standart installed java in directory..." << std::endl;
			options.executablePath = DDIC::Download::Files::getInstalledJavaInDirectory();
			return;
		}

		options.executablePath = java_path + "\\" + "bin" + "\\" + "java.exe";

		return;
	}

	if (!DDIC::Download::Java::check_system_verison_java(java_verison))
	{
		qInfo() << "Checking installed java..." << std::endl;
		if (!DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path, java_verison))
		{
			qInfo() << "Install java..." << std::endl;
			java_dir = DDIC::Download::Java::install(java_verison, this->minecraft_core_dir_path, callback);
			options.executablePath = java_dir + "\\" + "bin" + "\\" + "java.exe";
		}
		else
		{
			qInfo() << "Getting java..." << std::endl;
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
	if (this->servers_parce["servers"].get_array().size() > this->config_parce["user"]["server"].to_int())
	{
		return this->servers_parce["servers"][this->config_parce["user"]["server"].to_int()]["name"].to_string();
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

const std::filesystem::path SomLauncherMainWindow::getMCCorePath()
{
	return std::filesystem::path(this->minecraft_core_dir_path);
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

Json::JsonValue SomLauncherMainWindow::getLatestVersionFromDatabase()
{
	setConnectionWithDatabase();
	sql::ResultSet* res = nullptr;
	QString querry =
		R"(
SELECT
	JSON_ARRAYAGG(JSON_OBJECT('file',file, 'version',version))
FROM launcher_download_launcher)";

	try
	{
		res = sqlbase::mysql::sqlconnector::sendQuerry(this->database_connection, querry.toStdString());
	}
	catch (sql::SQLException& eSQL)
	{
		qFatal() << "Failed with exception: " << eSQL.what();
	}
	Json::JsonValue returned;

	while (res->next())
	{
		//std::cout << res->getString(1) << std::endl;
		returned = Json::JsonParcer::ParseJson(res->getString(1));
	}
	return returned;
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

void SomLauncherMainWindow::setCurrentVersionFromDatabase()
{
	if (getCurrentVersionFromConfig().empty())
	{
		this->config_parce["launcher"]["verison"] = getLatestVersionFromDatabase()[getLatestVersionFromDatabase().get_array().size() - 1]["file"].to_string();
		this->config_parce.save_json_to_file(this->config_path, 4);
	}
}

bool SomLauncherMainWindow::isVersionOld()
{
	/*if (getCurrentVersionFromConfig() != getLatestVersionFromGithub())
	{
		return true;
	}*/
	if (getCurrentVersionFromConfig() != getLatestVersionFromDatabase()[getLatestVersionFromDatabase().get_array().size() - 1]["file"].to_string())
	{
		return true;
	}
	return false;
}

void SomLauncherMainWindow::setAccountData(const Json::JsonValue& data)
{
	this->account_data = data;
}

void SomLauncherMainWindow::setUuidFromAccount()
{
	for (auto& elem : this->account_data.get_array())
	{
		if (elem.is_exist("id"))
		{
			this->options.uuid = elem["id"].to_string();
		}
	}
}

std::unique_ptr<SettingsDialog>& SomLauncherMainWindow::getSettingsDialog()
{
	return this->settings_dialog;
}

void SomLauncherMainWindow::installPackage(const QUrl& url)
{
	auto reply = mNetwork.get(QNetworkRequest(url));

	QObject::connect(reply, &QNetworkReply::finished,
		[&, reply]()
		{
			reply->deleteLater();
			auto buffer = reply->readAll();
			auto hash = crypto::sha1(buffer);
			QJsonObject manifest = QJsonDocument::fromJson(buffer).object();

			auto performDownload =
				[&, manifest, hash]()
				{
					QThreadPool::globalInstance()->start(
						[&, manifest, hash]()
						{
							QDir installDir = this->getMCCorePath() / "downloads" / hash.toStdString();
							if (!installDir.exists())
							{
								installDir.mkpath(installDir.absolutePath());
							}
							// compose the download list
							QList<DownloadEntry> downloads;
							for (auto& key : manifest["files"].toObject().keys())
							{
								auto file = manifest["files"].toObject()[key].toObject();
								// necessary directories will be created automatically
								if (file["type"].toString() == "file")
								{
									auto raw = file["downloads"].toObject()["raw"].toObject();
									downloads << DownloadEntry{ installDir.absoluteFilePath(key).toStdString(), raw["url"].toString(),
										quint64(raw["size"].toInt()), false, raw["sha1"].toString() };
								}
							}
							DownloadHelper d(this);
							//d.addDownloadList(downloads, true);
							d.performDownload();
							//UIThread::run([&]()
							//	{
							//		ui.play->setEnabled(true); // play will work only if ui.play is enabled
							//		play(false);
							//	});
						});
				};


			// check for the license file
			if (manifest["files"].toObject()["LICENSE"].isObject())
			{
				auto url =
					manifest["files"].toObject()["LICENSE"].toObject()["downloads"].toObject()["raw"].toObject()["url"].toString();
				auto licenseReply = mNetwork.get(QNetworkRequest(url));
				QObject::connect(licenseReply, &QNetworkReply::finished,
					[&, performDownload, licenseReply]()
					{
						licenseReply->deleteLater();

						//LicenseForm f(QString::fromUtf8(licenseReply->readAll()), this);
						//if (f.exec())
						//{
						//	performDownload();
						//}
						//else
						//{
						//	//setDownloadMode(false);
						//}
					});
			}
			else
			{
				performDownload();
			}
		});
}

QProcess* SomLauncherMainWindow::createProcess()
{
	if (mProcesses.empty())
	{
		//emit closeConsoleWindows();
	}
	auto p = new QProcess(this);
	mProcesses << p;
	hide();
	/*if (getSettings()->value("hide_launcher").toBool())
	{
		hide();
	}
	else {
		updatePlayButton();
	}
	if (getSettings()->value("show_console").toBool())
	{
		auto console = new ConsoleWindow(p);
		connect(this, &HackersMCLauncher::closeConsoleWindows, console, &ConsoleWindow::onClose);
	}*/
	return p;
}

void SomLauncherMainWindow::removeProcess(QProcess* p, int status, QProcess::ExitStatus e)
{
	mProcesses.removeAll(p);
	p->deleteLater();
	if (isHidden())
	{
		show();
	}
	/*else
	{
		updatePlayButton();
	}
	if (mProcesses.isEmpty())
	{
		if (getSettings()->value("close_launcher").toBool())
		{
			close();
		}
	}*/
}

void SomLauncherMainWindow::startMinecraft(const GameProfile& profile)
{
	auto args = commandline::generateCommand(profile);

	UIThread::run([&, args, profile]()
		{
			//auto p = createProcess();
			//connect(p, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
			//	[&, p](int status, QProcess::ExitStatus e)
			//	{
			//		removeProcess(p, status, e);
			//	});
			//connect(p, &QProcess::readyReadStandardOutput, this, [p]()
			//	{
			//		printf("%s", p->readAllStandardOutput().data());
			//		printf("%s", p->readAllStandardError().data());
			//	});
			//connect(p, &QProcess::errorOccurred, this, [&, p](QProcess::ProcessError e)
			//	{
			//		if (e == 0)
			//			switch (QMessageBox::question(this, tr("Could not start Java"), tr(
			//				"It seems like you have no proper Java installation."
			//				" Minecraft requires Java to launch.\n\nLauncher can download and install Java for you."),
			//				tr("Download and install Java for me"), tr("I'll install by myself")))
			//			{
			//			case 0: // install
			//				//downloadJava();
			//				break;
			//			case 1: // install by user
			//				QMessageBox::information(this, tr("Java installation"),
			//					tr("Don't forget to restart the launcher."), tr("Got it"));
			//				break;
			//			}
			//		removeProcess(p, 0, QProcess::ExitStatus::NormalExit);
			//	});
			//p->setWorkingDirectory(profile.getInstancePath().string().c_str());

			//// set default java command.
			//p->setProgram("java");

			// try to find java in packages dir
			QString executable = "java";
			if (profile.getjavaPath() == executable.toStdString())
			{
				QDir packageDir = std::filesystem::absolute(profile.getMinecraftCorePath() / "packages");
				for (auto& e : packageDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
				{
					executable = packageDir.absoluteFilePath(e + "/bin/java.exe");
					if (QFileInfo(executable).isFile())
					{
						//p->setProgram(executable);
						break;
					}
				}
			}
			else
			{
				executable = profile.getjavaPath().string().c_str();
			}
			//p->setArguments(args);

			//qInfo() << p->program() << std::endl;
			//qInfo() << p->arguments().join(' ') << std::endl;

			//p->start();

			hide();

			client::startProcess((executable + " " + args.join(' ')).toStdString());

			setWindowFlags(windowFlags() /*| Qt::Window*/ | Qt::WindowSystemMenuHint);
			show();
		});
}
