#include "SomLauncherMainWindow.h"

SomLauncherMainWindow::SomLauncherMainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qInfo() << "ui setup completed" << std::endl;

	this->progressBar_ahtung_geometry = ui.progressBar_ahtung->geometry();

	qInfo() << "Setting mc standart path..." << std::endl;
	_settingMinecraftStandartPath();

	//Проверка и создание конфига
	qInfo() << "Checking config..." << std::endl;
	if (!isConfigExist())
	{
		createConfig();
		qInfo() << "Config created" << std::endl;
	}

	qInfo() << "Setting memory..." << std::endl;
	_settingMemory();

	qInfo() << "Parcing configs..." << std::endl;
	_parcingConfigs();

	qInfo() << "Configure options..." << std::endl;
	configureOptions();

	qInfo() << "Setting otions value from config..." << std::endl;
	setOptionsValuesFromConfig();

	qInfo() << "Setting ui changes..." << std::endl;
	_settingUiChanges();

	qInfo() << "Setting ui connections..." << std::endl;
	_settingConnections();

	qInfo() << "Setting cyrrentversion..." << std::endl;
	setCurrentVersionFromDatabase();

	/*qInfo() << "Checking verison..." << std::endl;
	if (isVersionOld())
	{
		qInfo() << "Start updater" << std::endl;
		emit this->updateSignal(getLatestVersionFromDatabase()[getLatestVersionFromDatabase().get_array().size() - 1]["file"].to_string());
	}*/

	this->recomended_memory = 3072;
	this->curret_memory = this->config_parce["user"]["memory"].to_int();

	qInfo() << "Create main window complete" << std::endl;
}

SomLauncherMainWindow::~SomLauncherMainWindow()
{
	this->database_connection->close();
}

void SomLauncherMainWindow::_settingMinecraftStandartPath()
{
	char* path_buffer = nullptr;
	size_t path_buffer_size = 0;
	_dupenv_s(&path_buffer, &path_buffer_size, "APPDATA");
	this->minecraft_core_dir_path = Join({ path_buffer == nullptr ? "" : path_buffer, ".SomSomSom" });
	this->config_path = "SOMCONFIG.json";
	this->template_config_path = "SOMCONFIG_template.json";
	this->servers_json = "SERVERS.json";
}

void SomLauncherMainWindow::_parcingConfigs()
{
	this->config_parce = this->global_parcer.ParseFile(this->config_path);
}

void SomLauncherMainWindow::_parcingServers()
{
	//setConnectionWithDatabase();
	this->servers_parce = getServersFromDatabase();
	//this->database_connection->close();
}

void SomLauncherMainWindow::_parcingServers(sql::Connection* connect)
{
	this->servers_parce = getServersFromDatabase(connect);
}

void SomLauncherMainWindow::_settingUiChanges()
{

	ui.stackedWidget_bottommenu->setCurrentIndex(0);

	this->top_frame = new TopSlideFrameWidget(this);
	this->top_frame->setGeometry(QRect(30, -90, 741, 131));
	this->top_frame->raise();

	this->top_frame_animation = new QPropertyAnimation(this->top_frame, "geometry", this);

	QFile styleFile(this->style_sheet.c_str());
	styleFile.open(QFile::ReadOnly);
	// Apply the loaded stylesheet
	QString style(styleFile.readAll());
	this->setStyleSheet(style);

	QIcon icon("resources\\som.ico");
	this->setWindowIcon(icon);

	QPixmap pixmap("resources\\som.png");
	ui.label_logo->setPixmap(pixmap);

	QPixmap background = QPixmap(this->background.c_str());

	/*QGraphicsBlurEffect* blur = new QGraphicsBlurEffect;
	blur->setBlurRadius(8);

	background.fromImage(applyEffectToImage(background.toImage(), blur));*/
	ui.scrollArea_servers->setStyleSheet("background-color: transparent;");

	ui.labeltest->setPixmap(background);
	//ui.centralWidget->setStyleSheet("background: linear-gradient(135deg, rgb(194, 183, 119), rgb(255, 143, 31));");

	this->top_frame->setMainButtonsTextAlightButtom();
	this->top_frame->changeLabelsCurrencyCountAndAccountName();

	this->server_changer_button_text = ui.pushButton_changeserver->text().toStdString();

	//_settingServersWidgets();

	ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());

	NewsViewWidget* news_view = new NewsViewWidget();
	ui.gridLayout_page_news->addWidget(news_view);

	_settingServerType();

	ui.progressBar_ahtung->setHidden(true);
	ui.label_download_status_change->setHidden(true);
	ui.label_download_speed->setHidden(true);
	ui.label_download_time->setHidden(true);
}

void SomLauncherMainWindow::_settingServersWidgets()
{
	try
	{
		if (this->servers_parce["servers"].get_array().size() > this->config_parce["user"]["server"].to_int())
		{
			ui.pushButton_changeserver->setText((this->server_changer_button_text +
				this->servers_parce["servers"][this->config_parce["user"]["server"].to_int()]["name"].to_string() +
				")").c_str());

			this->server_radio_button_group = std::make_unique<QButtonGroup>();

			for (int i = 0; i < this->servers_parce["servers"].get_count(); ++i)
			{
				QSharedPointer<ServerWidget> widget = QSharedPointer<ServerWidget>::create(this->server_radio_button_group.get(), this->servers_parce["servers"][i]);

				this->widget_list.append(widget);

				if (this->config_parce["user"]["server"].get_type() != Json::JsonTypes::Null && this->config_parce["user"]["server"].to_int() == i)
				{
					widget->setStatusServer(true);
				}
			}

			int index = 0;
			for (int i = 0; i < (this->servers_parce["servers"].get_count() - 1) / 2 + 1; ++i)
			{
				for (int j = 0; j < (this->servers_parce["servers"].get_count()) / 2 + 1; ++j)
				{
					ui.gridLayout_scrollArea_servers->addWidget(this->widget_list[index].get(), i, j);

					++index;
				}
			}

			QObject::connect(this->server_radio_button_group.get(), &QButtonGroup::buttonToggled,
				this, &SomLauncherMainWindow::groupButtonsClicked);
		}
		else
		{
			ui.pushButton_changeserver->setText((this->server_changer_button_text + ")").c_str());
		}
	}
	catch (const std::exception& exc)
	{
		qWarning() << exc.what();
	}
}

void SomLauncherMainWindow::_settingCurrentServerName()
{
	ui.label_server_name->setText(getCurrentServerName().c_str());
}

void SomLauncherMainWindow::_settingConnections()
{
	QObject::connect(this->top_frame->getPushButtonGame(), &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_game);
	QObject::connect(this->top_frame->getPushButtonServers(), &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_servers);
	QObject::connect(this->top_frame->getPushButtonNews(), &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_news);
	QObject::connect(this->top_frame->getPushButtonAboutUs(), &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_aboutus);
	QObject::connect(ui.pushButton_changeserver, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_changeserver);
	QObject::connect(this->top_frame->getPushButtonSettings(), &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_settings);

	QObject::connect(ui.pushButton_startgame, &QPushButton::released, this, &SomLauncherMainWindow::onClickpushButton_startgame);

	//QObject::connect(this->top_frame->getLabelProfile(), &ClickableLabel::clicked, this, &SomLauncherMainWindow::onClickedpushLable_profile);

	QObject::connect(this->top_frame->getFrame(), &HoveredFrame::Enter, this, &SomLauncherMainWindow::mouseEnterframe_topslidemenu);
	QObject::connect(this->top_frame->getFrame(), &HoveredFrame::Leave, this, &SomLauncherMainWindow::mouseLeaveframe_topslidemenu);

	QObject::connect(ui.stackedWidget_bottommenu, &QStackedWidget::currentChanged, this, &SomLauncherMainWindow::pageChangedSlidedWidget);

	QObject::connect(ui.pushButton_checkupdates, &QPushButton::released, this, &SomLauncherMainWindow::onClickedPushButton_check_update);
}

void SomLauncherMainWindow::_settingMemory()
{
	MEMORYSTATUSEX statex{};
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	this->max_memory = statex.ullTotalPhys / MEM_DIV - 512;
}

void SomLauncherMainWindow::_settingModsCount()
{
	size_t count = getMinecraftModsCount();
	ui.label_mods_count_change->setText(std::to_string(count).c_str());
}

void SomLauncherMainWindow::_settingServerType()
{
	ServerTypes type = getServerType();
	ui.label_client_type->setText(ServerTypesToString(type).c_str());
}

void SomLauncherMainWindow::_settingAccountDataInUi()
{
	for (auto& elem : account_data.get_array())
	{
		if (elem.is_exist("username"))
		{
			this->top_frame->getLabelProfile()->setText(elem["username"].to_string().c_str());
		}
	}
}

void SomLauncherMainWindow::onClickedpushButton_game()
{
	qInfo() << "pushButton_game clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(0);
}

void SomLauncherMainWindow::onClickedpushButton_servers()
{
	qInfo() << "pushButton_servers clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(1);
}

void SomLauncherMainWindow::onClickedpushButton_news()
{
	qInfo() << "pushButton_news clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(2);
}

void SomLauncherMainWindow::onClickedpushButton_aboutus()
{
	qInfo() << "pushButton_aboutus clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(3);
}

void SomLauncherMainWindow::onClickedpushButton_changeserver()
{
	qInfo() << "pushButton_changeserver clicked" << std::endl;

	ServerChanger dialog(this, this->config_path, this->servers_parce);

	QObject::connect(&dialog, &ServerChanger::accepted,
		this, [=]() -> void
		{
			_settingServerNameInChangeServerButton();
			_settingCurrentServerName();
		});

	dialog.exec(); //modal server changer
}

void SomLauncherMainWindow::_settingServerNameInChangeServerButton()
{
	this->config_parce = this->global_parcer.ParseFile(this->config_path);
	ui.pushButton_changeserver->setText((this->server_changer_button_text +
		this->servers_parce["servers"][this->config_parce["user"]["server"].to_int()]["name"].to_string() +
		")").c_str());
	this->widget_list[this->config_parce["user"]["server"].to_int()]->setStatusServer(true);
}

void SomLauncherMainWindow::onClickedpushLable_profile()
{
	qInfo() << "pushLable_profile clicked" << std::endl;
}

void SomLauncherMainWindow::onClickedpushButton_settings()
{
	qInfo() << "pushButton_settings clicked" << std::endl;

	QObject::connect(this->settings_dialog.get(), &SettingsDialog::changedMinecraftPathSignal,
		[=](const std::filesystem::path& path) -> void
		{
			this->config_path = path.u8string();
			this->_parcingConfigs();
		}
	);

	this->settings_dialog->setMemoryData(1024, this->max_memory, this->recomended_memory);
	this->settings_dialog->setCurretMemory(this->curret_memory);

	this->settings_dialog->setStandartJavaPath(this->options.executablePath);
	this->settings_dialog->setStandartMinecraftPath(this->options.gameDirectory);

	this->settings_dialog->exec();
}

void SomLauncherMainWindow::onClickpushButton_startgame()
{
	qInfo() << "pushButton_startgame clicked" << std::endl;

	setUiToDownload(true);

	UIThread::run(
		[&]()
		{
			start_minecraft_params();
		}
	);

	/*std::function<void()> start_minecraft_thread_func =
		[this]() -> void
		{
			start_minecraft_params();
		};

	connect(ui.progressBar_ahtung, &QProgressBar::valueChanged, this, &SomLauncherMainWindow::updateProgressBar);
	connect(ui.label_download_status_change, &SignalLabel::textChanged, this, &SomLauncherMainWindow::updateProgressLabel);

	download_thread = new FunctionThread(start_minecraft_thread_func);

	download_thread->start();*/
}

void SomLauncherMainWindow::setUiToDownload(bool status)
{
	ui.progressBar_ahtung->setHidden(!status);
	ui.label_download_status_change->setHidden(!status);
	ui.label_download_speed->setHidden(!status);
	ui.label_download_time->setHidden(!status);

	ui.pushButton_startgame->setDisabled(status);
	this->top_frame->getPushButtonSettings()->setDisabled(status);
	ui.pushButton_checkupdates->setDisabled(status);
	ui.pushButton_changeserver->setDisabled(status);
	//ui.scrollArea_servers->setDisabled(status);
	ui.scrollAreaWidgetContents->setDisabled(status);
}

void SomLauncherMainWindow::mouseEnterframe_topslidemenu()
{
	qInfo() << "frame_topslidemenu mouse enter" << std::endl;

	if (this->top_frame->geometry() != QRect(30, 0, 741, 131))
	{
		this->top_frame_animation->setDuration(100);
		this->top_frame_animation->setStartValue(this->top_frame->geometry());
		this->top_frame_animation->setEndValue(QRect(30, 0, 741, 131));
		this->top_frame_animation->start();
	}

	this->top_frame->setMainButtonsTextAlightCenter();
	this->top_frame->changeLabelsCurrencyCountAndAccountName();
}

void SomLauncherMainWindow::mouseLeaveframe_topslidemenu()
{
	qInfo() << "frame_topslidemenu mouse leave" << std::endl;

	if (this->top_frame->geometry() != QRect(30, -90, 741, 131))
	{
		this->top_frame_animation->setDuration(100);
		this->top_frame_animation->setStartValue(this->top_frame->geometry());
		this->top_frame_animation->setEndValue(QRect(30, -90, 741, 131));
		this->top_frame_animation->start();
	}

	this->top_frame->setMainButtonsTextAlightButtom();
	this->top_frame->changeLabelsCurrencyCountAndAccountName();
}

void SomLauncherMainWindow::groupButtonsClicked(QAbstractButton* id, bool status)
{
	qInfo() << "groupButtons Clicked id: " << id->objectName().toStdString() << " " << status << std::endl;

	if (status == true)
	{
		int index = 0;
		int i = -1;
		for (auto& var : this->servers_parce["servers"].get_array())
		{
			++i;
			if (var["name"].to_string() == id->objectName().toStdString())
			{
				index = i;
			}
		}

		this->config_parce["user"]["server"] = index;

		qInfo() << "Server is: " << this->config_parce["user"]["server"].to_string() << std::endl;

		config_parce.save_json_to_file(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		qInfo() << "Server saved" << std::endl;

		_settingServerNameInChangeServerButton();
		_settingCurrentServerName();
	}
}

void SomLauncherMainWindow::saveSettings()
{
	int memory_value = this->settings_dialog->getMemoryValue();

	if (this->settings_dialog->getReintsallModsState() == true)
	{
		this->is_install_mods = true;
		this->config_parce["user"]["isInstallMods"] = this->is_install_mods;
		qInfo() << "isInstallMods is: " << this->config_parce["user"]["isInstallMods"].to_string() << std::endl;
	}
	qInfo() << "isInstallMods is: " << this->config_parce["user"]["isInstallMods"].to_string() << std::endl;

	this->curret_memory = memory_value;

	config_parce["user"]["memory"] = memory_value;

	qInfo() << "Memory is: " << this->config_parce["user"]["memory"].to_string() << std::endl;

	this->config_parce.save_json_to_file(this->config_path, 4);

	qInfo() << "Memory saved" << std::endl;

	std::string minecraft_path = this->settings_dialog->getMinecraftPath();

	if (minecraft_path != "")
	{
		this->minecraft_core_dir_path = minecraft_path;

		this->config_parce["user"]["mcdir"] = this->minecraft_core_dir_path;

		qInfo() << "Mcdir is: " << this->config_parce["user"]["mcdir"].to_string() << std::endl;

		this->config_parce.save_json_to_file(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		qInfo() << "Mcdir saved" << std::endl;

		ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());
	}
	else
	{
		this->minecraft_core_dir_path = this->default_options.gameDirectory;

		this->config_parce["user"]["mcdir"] = "";

		qInfo() << "Mcdir is: " << this->config_parce["user"]["mcdir"].to_string() << std::endl;

		this->config_parce.save_json_to_file(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		qInfo() << "Mcdir saved" << std::endl;

		ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());
	}
}

void SomLauncherMainWindow::updateProgressBar(int value)
{
	ui.progressBar_ahtung->setValue(value);
}

void SomLauncherMainWindow::pageChangedSlidedWidget(int value)
{
	if (value != 0 && !ui.progressBar_ahtung->isHidden())
	{
		ui.gridLayout_page_game->removeWidget(ui.progressBar_ahtung);
		ui.progressBar_ahtung->setParent(ui.centralWidget);
		ui.progressBar_ahtung->setGeometry(ui.label_minecraft_directory->geometry());
		ui.progressBar_ahtung->show();
	}
	else if (!ui.progressBar_ahtung->isHidden())
	{
		ui.gridLayout_page_game->addWidget(ui.progressBar_ahtung, 2, 0, 1, 1);
		ui.progressBar_ahtung->setGeometry(this->progressBar_ahtung_geometry);
	}
}

void SomLauncherMainWindow::onClickedPushButton_check_update()
{
	qInfo() << "onClickedPushButton_check_update" << std::endl;
	if (isVersionOld())
	{
		qInfo() << "Start updater" << std::endl;
		this->config_parce["launcher"]["verison"] = getLatestVersionFromDatabase()[getLatestVersionFromDatabase().get_array().size() - 1]["version"].to_string();
		this->config_parce.save_json_to_file(this->config_path, 4);
		emit this->updateSignal(getLatestVersionFromDatabase()[getLatestVersionFromDatabase().get_array().size() - 1]["file"].to_string());
	}
}

void SomLauncherMainWindow::setReinstallMods(bool state)
{
	qInfo() << "setReinstallMods " << state << std::endl;
	this->config_parce["user"]["isInstallMods"] = state;
}

void SomLauncherMainWindow::updateProgressLabel(const QString& text)
{
	ui.label_download_status_change->setText(text);
}

void SomLauncherMainWindow::setOptionsValuesFromConfig()
{
	if (this->config_parce["user"]["mcdir"].to_string() != "")
	{
		this->minecraft_core_dir_path = this->config_parce["user"]["mcdir"].to_string();
	}

	this->username = this->config_parce["user"]["name"].to_string();
	this->options.resolutionWidth = this->config_parce["user"]["wight"].to_int();
	this->options.resolutionHeight = this->config_parce["user"]["hight"].to_int();
	this->curret_memory = this->config_parce["user"]["memory"].to_int();

	this->options.gameDirectory = this->minecraft_core_dir_path;
	this->options.username = this->username;

	this->is_install_mods = this->config_parce["user"]["isInstallMods"].get_bool();
}