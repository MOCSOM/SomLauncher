#include "SomLauncherMainWindow.h"

SomLauncherMainWindow::SomLauncherMainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Logger << "ui setup completed" << std::endl;

	this->progressBar_ahtung_geometry = ui.progressBar_ahtung->geometry();

	_settingMinecraftStandartPath();

	//Проверка и создание конфига
	if (!isConfigExist())
	{
		createConfig();
		Logger << "Config created" << std::endl;
	}

	_settingMemory();

	_parcingConfigs();

	configureOptions();

	setOptionsValuesFromConfig();

	this->settings_dialog = std::make_unique<SettingsDialog>(Json::JsonValue(), this->options, this); //TODO: Сделать отправку данных о акке

	_settingConnections();

	_settingUiChanges();

	QObject::connect(this->server_radio_button_group.get(), &QButtonGroup::buttonToggled,
		this, &SomLauncherMainWindow::groupButtonsClicked);

	setCurrentVersionFromGithub();

	if (isVersionOld())
	{
	}

	this->recomended_memory = 3072;
	this->curret_memory = this->config_parce["user"]["memory"].to_int();
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
	this->servers_parce = this->global_parcer.ParseFile(this->servers_json);
	this->config_parce = this->global_parcer.ParseFile(this->config_path);
}

void SomLauncherMainWindow::_settingUiChanges()
{
	QPixmap background = QPixmap(this->background_gif.c_str());
	ui.labeltest->setPixmap(background);

	ui.pushButton_game->setStyleSheet("text-align:bottom;");
	ui.pushButton_servers->setStyleSheet("text-align:bottom;");
	ui.pushButton_news->setStyleSheet("text-align:bottom;");
	ui.pushButton_aboutus->setStyleSheet("text-align:bottom;");

	this->server_changer_button_text = ui.pushButton_changeserver->text().toStdString();
	ui.pushButton_changeserver->setText((this->server_changer_button_text +
		this->servers_parce["servers"][this->config_parce["user"]["server"].to_int()]["name"].to_string() +
		")").c_str());

	ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());

	//ui.scrollAreaWidgetContents->setAttribute(Qt::WA_TranslucentBackground);
	ui.scrollArea_servers->setStyleSheet("background-color: transparent;");

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
		for (int j = 0; j < (this->servers_parce["servers"].get_count() - 1) / 2 + 1; ++j)
		{
			ui.gridLayout_scrollArea_servers->addWidget(this->widget_list[index].get(), i, j);

			++index;
		}
	}

	_settingCurrentServerName();

	_settingModsCount();

	_settingServerType();

	ui.progressBar_ahtung->setHidden(true);
	ui.label_download_status_change->setHidden(true);
}

void SomLauncherMainWindow::_settingCurrentServerName()
{
	ui.label_server_name->setText(getCurrentServerName().c_str());
}

void SomLauncherMainWindow::_settingConnections()
{
	QObject::connect(ui.pushButton_game, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_game);
	QObject::connect(ui.pushButton_servers, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_servers);
	QObject::connect(ui.pushButton_news, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_news);
	QObject::connect(ui.pushButton_aboutus, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_aboutus);
	QObject::connect(ui.pushButton_changeserver, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_changeserver);
	QObject::connect(ui.pushButton_settings, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_settings);

	QObject::connect(ui.pushButton_startgame, &QPushButton::released, this, &SomLauncherMainWindow::onClickpushButton_startgame);

	QObject::connect(ui.label_profile, &ClickableLabel::clicked, this, &SomLauncherMainWindow::onClickedpushLable_profile);

	QObject::connect(ui.frame_topslidemenu, &HoveredFrame::Enter, this, &SomLauncherMainWindow::mouseEnterframe_topslidemenu);
	QObject::connect(ui.frame_topslidemenu, &HoveredFrame::Leave, this, &SomLauncherMainWindow::mouseLeaveframe_topslidemenu);

	QObject::connect(this->settings_dialog.get(), &SettingsDialog::acceptButtonClicked, this, &SomLauncherMainWindow::saveSettings);
	QObject::connect(this->settings_dialog.get(), &SettingsDialog::setToDefaultButtonClicked,
		this, [=]() -> void
		{
			this->settings_dialog->setToDefault(default_options, recomended_memory);
		});

	QObject::connect(ui.stackedWidget_bottommenu, &QStackedWidget::currentChanged, this, &SomLauncherMainWindow::pageChangedSlidedWidget);
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

void SomLauncherMainWindow::onClickedpushButton_game()
{
	Logger << "pushButton_game clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(0);
}

void SomLauncherMainWindow::onClickedpushButton_servers()
{
	Logger << "pushButton_servers clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(1);
}

void SomLauncherMainWindow::onClickedpushButton_news()
{
	Logger << "pushButton_news clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(2);
}

void SomLauncherMainWindow::onClickedpushButton_aboutus()
{
	Logger << "pushButton_aboutus clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(3);
}

void SomLauncherMainWindow::onClickedpushButton_changeserver()
{
	Logger << "pushButton_changeserver clicked" << std::endl;

	ServerChanger dialog(this, this->config_path);

	QObject::connect(&dialog, &ServerChanger::accepted,
		this, [=]() -> void
		{
			_settingServerNameInChangeServerButton();
			_settingCurrentServerName();
		});

	dialog.exec(); //modal settings_dialog
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
	Logger << "pushLable_profile clicked" << std::endl;
}

void SomLauncherMainWindow::onClickedpushButton_settings()
{
	Logger << "pushButton_settings clicked" << std::endl;

	this->settings_dialog->setMemoryData(1024, this->max_memory, this->recomended_memory);
	this->settings_dialog->setCurretMemory(this->curret_memory);

	this->settings_dialog->setStandartJavaPath(this->options.executablePath);
	this->settings_dialog->setStandartMinecraftPath(this->options.gameDirectory);

	this->settings_dialog->exec();
}

void SomLauncherMainWindow::onClickpushButton_startgame()
{
	Logger << "pushButton_startgame clicked" << std::endl;

	ui.progressBar_ahtung->setHidden(false);
	ui.label_download_status_change->setHidden(false);

	ui.pushButton_startgame->setDisabled(true);
	ui.pushButton_settings->setDisabled(true);

	std::function<void()> myFunction =
		[this]()
		{
			start_minecraft_params();
		};

	connect(ui.progressBar_ahtung, &QProgressBar::valueChanged, this, &SomLauncherMainWindow::updateProgressBar);
	download_thread = new FunctionThread(myFunction);
	download_thread->start();
}

void SomLauncherMainWindow::mouseEnterframe_topslidemenu()
{
	Logger << "frame_topslidemenu mouse enter" << std::endl;

	if (ui.frame_topslidemenu->geometry() != QRect(30, 0, 741, 131))
	{
		QPropertyAnimation* animation = new QPropertyAnimation(ui.frame_topslidemenu, "geometry");
		animation->setDuration(100);
		animation->setStartValue(ui.frame_topslidemenu->geometry());
		animation->setEndValue(QRect(30, 0, 741, 131));
		animation->start();
	}

	ui.pushButton_game->setStyleSheet("text-align:center;");
	ui.pushButton_servers->setStyleSheet("text-align:center;");
	ui.pushButton_news->setStyleSheet("text-align:center;");
	ui.pushButton_aboutus->setStyleSheet("text-align:center;");
}

void SomLauncherMainWindow::mouseLeaveframe_topslidemenu()
{
	Logger << "frame_topslidemenu mouse leave" << std::endl;

	if (ui.frame_topslidemenu->geometry() != QRect(30, -90, 741, 131))
	{
		QPropertyAnimation* animation = new QPropertyAnimation(ui.frame_topslidemenu, "geometry");
		animation->setDuration(100);
		animation->setStartValue(ui.frame_topslidemenu->geometry());
		animation->setEndValue(QRect(30, -90, 741, 131));
		animation->start();
	}

	//animation->finished();
	ui.pushButton_game->setStyleSheet("text-align:bottom;");
	ui.pushButton_servers->setStyleSheet("text-align:bottom;");
	ui.pushButton_news->setStyleSheet("text-align:bottom;");
	ui.pushButton_aboutus->setStyleSheet("text-align:bottom;");
}

void SomLauncherMainWindow::groupButtonsClicked(QAbstractButton* id, bool status)
{
	Logger << "groupButtons Clicked id: " << id->objectName().toStdString() << " " << status << std::endl;

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

		Logger << "Server is: " << this->config_parce["user"]["server"].to_string() << std::endl;

		config_parce.save_json_to_file(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		Logger << "Server saved" << std::endl;

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
		config_parce["user"]["isInstallMods"] = this->is_install_mods;
	}

	this->curret_memory = memory_value;

	config_parce["user"]["memory"] = memory_value;

	Logger << "Memory is: " << this->config_parce["user"]["memory"].to_string() << std::endl;

	this->config_parce.save_json_to_file(this->config_path, 4);

	Logger << "Memory saved" << std::endl;

	std::string minecraft_path = this->settings_dialog->getMinecraftPath();

	if (minecraft_path != "")
	{
		this->minecraft_core_dir_path = minecraft_path;

		this->config_parce["user"]["mcdir"] = this->minecraft_core_dir_path;

		Logger << "Mcdir is: " << this->config_parce["user"]["mcdir"].to_string() << std::endl;

		this->config_parce.save_json_to_file(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		Logger << "Mcdir saved" << std::endl;

		ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());
	}
	else
	{
		this->minecraft_core_dir_path = this->default_options.gameDirectory;

		this->config_parce["user"]["mcdir"] = "";

		Logger << "Mcdir is: " << this->config_parce["user"]["mcdir"].to_string() << std::endl;

		this->config_parce.save_json_to_file(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		Logger << "Mcdir saved" << std::endl;

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