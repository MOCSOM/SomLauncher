#include "SomLauncherMainWindow.h"

SomLauncherMainWindow::SomLauncherMainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qInfo() << "ui setup completed" << std::endl;

	this->progressBar_ahtung_geometry = ui.progressBar_ahtung->geometry();

	qInfo() << "Setting mc standart path..." << std::endl;
	_settingMinecraftStandartPath();

	qInfo() << "Parcing configs..." << std::endl;
	_parcingConfigs();

	qInfo() << "Setting memory..." << std::endl;
	_settingMemory();

	qInfo() << "Configure options..." << std::endl;
	configureOptions();

	qInfo() << "Setting otions value from config..." << std::endl;
	setOptionsValuesFromConfig();

	qInfo() << "Setting ui changes..." << std::endl;
	_settingUiChanges();

	qInfo() << "Setting ui connections..." << std::endl;
	_settingConnections();

	qInfo() << "Setting cyrrentversion..." << std::endl;
	setCurrentVersionFromSite();

	/*qInfo() << "Checking version..." << std::endl;
	if (isVersionOld())
	{
		qInfo() << "Start updater" << std::endl;
		emit this->updateSignal(getLatestVersionFromSite()[getLatestVersionFromSite().get_array().size() - 1]["file"].to_string());
	}*/

	this->recomended_memory = 3072;
	this->curret_memory = this->config.json()["user"]["memory"].template get<int>();

	qInfo() << "Create main window complete" << std::endl;
}

SomLauncherMainWindow::~SomLauncherMainWindow()
{
}

void SomLauncherMainWindow::_settingMinecraftStandartPath()
{
	char* path_buffer = nullptr;
	size_t path_buffer_size = 0;
	_dupenv_s(&path_buffer, &path_buffer_size, "APPDATA");
	this->minecraft_core_dir_path = Join({ path_buffer == nullptr ? "" : path_buffer, ".SomSomSom" });
	this->config_path = "SOMCONFIG.json";
	this->servers_json = "SERVERS.json";
}

void SomLauncherMainWindow::_parcingConfigs()
{
	qDebug() << this->config_path << std::endl;

	this->config = Config(this->config_path);
}

void SomLauncherMainWindow::_parcingServers()
{
	//setConnectionWithDatabase();
	this->servers_parce = getServersFromServer();
	//this->database_connection->close();
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

	ui.label_background->setPixmap(background);
	//ui.centralWidget->setStyleSheet("background: linear-gradient(135deg, rgb(194, 183, 119), rgb(255, 143, 31));");

	this->top_frame->setMainButtonsTextAlightButtom();
	this->top_frame->swapLabelsCurrencyCountAndAccountName();

	this->server_changer_button_text = ui.pushButton_changeserver->text().toStdString();

	//_settingServersWidgets();

	ui.label_minecraft_directory->setText(QString::fromStdWString(this->minecraft_core_dir_path.wstring()));

	NewsViewWidget* news_view = new NewsViewWidget();
	ui.gridLayout_page_news->addWidget(news_view);

	ui.progressBar_ahtung->setHidden(true);
	ui.label_download_status_change->setHidden(true);
	ui.label_download_speed->setHidden(true);
	ui.label_download_time->setHidden(true);
}

void SomLauncherMainWindow::_settingServersWidgets()
{
	try
	{
		if (this->servers_parce.size() > this->config.json()["user"]["server"].template get<int>())
		{
			ui.pushButton_changeserver->setText((this->server_changer_button_text +
				this->servers_parce[this->config.json()["user"]["server"].template get<int>()]["server_name"].template get<std::string>() +
				")").c_str());

			this->server_radio_button_group = std::make_unique<QButtonGroup>();

			for (int i = 0; i < this->servers_parce.size(); ++i)
			{
				QSharedPointer<ServerWidget> widget = QSharedPointer<ServerWidget>::create(this->server_radio_button_group.get(), this->servers_parce[i]);

				this->widget_list.append(widget);

				if (this->config.json()["user"]["server"].type() != nlohmann::json::value_t::null && this->config.json()["user"]["server"].template get<int>() == i)
				{
					widget->setStatusServer(true);
				}
			}


			int index = 0;
			for (int i = 0; i < (this->servers_parce.size() - 1) / 2 + 1; ++i)
			{
				for (int j = 0; (j < (this->servers_parce.size()) / 2 + 1) && (index < this->servers_parce.size()); ++j)
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
		QMessageBox::warning(this, "Warning", exc.what());
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

	QObject::connect(ui.pushButton_reportbug, &QPushButton::released, this, &SomLauncherMainWindow::onClickedPushButtonSendBugReport);

	QObject::connect(ui.pushButtonRefreshServers, &QPushButton::released, this, &SomLauncherMainWindow::refreshServers);
	QObject::connect(this, &SomLauncherMainWindow::serverConnectSignal, this, &SomLauncherMainWindow::handleServerResult);
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
	std::string type = getServerType();
	ui.label_client_type->setText(type.c_str());
}

void SomLauncherMainWindow::_settingAccountDataInUi()
{
	this->top_frame->getLabelProfile()->setText(this->account_data["username"].template get<std::string>().c_str());
	this->top_frame->getCurrencyLabel()->setText(QString::number(this->account_data["somus"].template get<int>()));
	_settingProfileImage();
}

void SomLauncherMainWindow::_settingFastServerChangerForm()
{
	fast_server_changer_form = std::make_unique<ServerChanger>(this, this->config_path, this->servers_parce);
}

void SomLauncherMainWindow::_settingProfileImage()
{
	std::shared_ptr<QPixmap> image;
	try
	{
		image = loadQPixmapFromBase64(this->account_data["avatar"].template get<std::string>().c_str());
	}
	catch (const std::exception&)
	{
		image = loadQPixmapFromBase64("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");
	}
	this->top_frame->getAccountIcon()->setPixmap(*image.get());
	this->top_frame->getAccountIcon()->setScaledContents(true);
}

void SomLauncherMainWindow::_settingServerStatus()
{
	ui.label_server_status->setText(this->widget_list[this->config.json()["user"]["server"].template get<int>()]->getServerStatus());
}

void SomLauncherMainWindow::disablePlayButtonIfNeeded()
{
	bool is_friend = this->account_data["is_friend"].template get<bool>();
	if (is_friend)
	{
		return;
	}

	bool is_disable_button = true;
	for (auto& elem : this->widget_list)
	{
		if (elem->isToFriends() && elem->getServerName() == QString::fromStdString(getCurrentServerName()))
		{
			is_disable_button = true;
			continue;
		}
		else if (!elem->isToFriends() && elem->getServerName() == QString::fromStdString(getCurrentServerName()))
		{
			is_disable_button = false;
			continue;
		}
	}

	if (is_disable_button)
	{
		ui.pushButton_startgame->setDisabled(true);
	}
	else
	{
		ui.pushButton_startgame->setDisabled(false);
	}
}

void SomLauncherMainWindow::settingUserProfileImage()
{
	std::string user_icon_string = this->account_data["avatar"].template get<std::string>();
	QPixmap user_icon;
	user_icon.loadFromData(QByteArray::fromBase64(user_icon_string.c_str()), "PNG");
	this->top_frame->getAccountIcon()->setPixmap(user_icon);
}

void SomLauncherMainWindow::disableServer()
{
	bool is_friend = this->account_data["is_friend"].template get<bool>();

	if (is_friend)
	{
		return;
	}

	for (auto& elem : this->widget_list)
	{
		if (elem->isToFriends())
		{
			fast_server_changer_form->disabeServerItem(elem->getServerName());
			elem->setDisabled(true);
		}
	}

	//ui.pushButton_changeserver->setDisabled(true);
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


	QObject::connect(fast_server_changer_form.get(), &ServerChanger::accepted,
		this, [=]() -> void
		{
			_settingServerNameInChangeServerButton();
			_settingCurrentServerName();
			this->widget_list[this->config.json()["user"]["server"].template get<int>()]->setStatusServer(true);
		});

	fast_server_changer_form->exec(); //modal server changer
}

void SomLauncherMainWindow::_settingServerNameInChangeServerButton()
{
	this->config.reopenConfig();

	ui.pushButton_changeserver->setText((this->server_changer_button_text +
		this->servers_parce[this->config.json()["user"]["server"].template get<int>()]["server_name"].template get<std::string>() +
		")").c_str());
	//this->widget_list[this->config_parce["user"]["server"].to_int()]->setStatusServer(true);
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
			this->config.json()["user"]["mcdir"] = path;
			//this->config_path = path / "SOMCONFIG.json";
			////Проверка и создание конфига
			//qInfo() << "Checking config..." << std::endl;
			//if (!isConfigExist())
			//{
			//	createConfig();
			//	qInfo() << "Config created" << std::endl;
			//}
			//this->_parcingConfigs();
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
	QThread* thread = new QThread;

	connect(thread, &QThread::started, this, &SomLauncherMainWindow::start_minecraft_params);
	connect(thread, &QThread::finished, thread, &QThread::deleteLater);

	thread->start();

	/*UIThread::run(
		[&]()
		{
			start_minecraft_params();
		}
	);*/

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
	qDebug() << "frame_topslidemenu mouse enter" << std::endl;

	if (this->top_frame->geometry() != QRect(30, 0, 741, 131))
	{
		this->top_frame_animation->setDuration(100);
		this->top_frame_animation->setStartValue(this->top_frame->geometry());
		this->top_frame_animation->setEndValue(QRect(30, 0, 741, 131));
		this->top_frame_animation->start();
	}

	this->top_frame->setMainButtonsTextAlightCenter();
	this->top_frame->swapLabelsCurrencyCountAndAccountName();
}

void SomLauncherMainWindow::mouseLeaveframe_topslidemenu()
{
	qDebug() << "frame_topslidemenu mouse leave" << std::endl;

	if (this->top_frame->geometry() != QRect(30, -90, 741, 131))
	{
		this->top_frame_animation->setDuration(100);
		this->top_frame_animation->setStartValue(this->top_frame->geometry());
		this->top_frame_animation->setEndValue(QRect(30, -90, 741, 131));
		this->top_frame_animation->start();
	}

	this->top_frame->setMainButtonsTextAlightButtom();
	this->top_frame->swapLabelsCurrencyCountAndAccountName();
}

void SomLauncherMainWindow::groupButtonsClicked(QAbstractButton* id, bool status)
{
	qInfo() << "groupButtons Clicked id: " << id->objectName() << " " << status << std::endl;

	if (status == true)
	{
		int index = 0;
		int i = -1;
		for (auto& var : this->servers_parce)
		{
			++i;
			if (var["server_name"].template get<std::string>() == id->objectName().toStdString())
			{
				index = i;
			}
		}

		this->config.json()["user"]["server"] = index;

		qInfo() << "Server is: " << this->config.json()["user"]["server"].template get<int>() << std::endl;

		this->config.saveJsonToFile();
		this->config.reopenConfig();

		qInfo() << "Server saved" << std::endl;

		_settingServerNameInChangeServerButton();
		_settingCurrentServerName();
		_settingModsCount();
		_settingServerType();
		disablePlayButtonIfNeeded();
		_settingServerStatus();
	}
}

void SomLauncherMainWindow::saveSettings()
{
	int memory_value = this->settings_dialog->getMemoryValue();

	if (this->settings_dialog->getReintsallModsState() == true)
	{
		this->is_install_mods = true;
		this->config.json()["user"]["isInstallMods"] = this->is_install_mods;
		//qInfo() << "isInstallMods is: " << this->config_parce["user"]["isInstallMods"].template get<std::string>() << std::endl;
	}
	//qInfo() << "isInstallMods is: " << this->config_parce["user"]["isInstallMods"].template get<std::string>() << std::endl;

	this->curret_memory = memory_value;

	this->config.json()["user"]["memory"] = memory_value;

	//qInfo() << "Memory is: " << this->config_parce["user"]["memory"].template get<std::string>() << std::endl;

	/*auto a = decodeUtf8(config_parce["user"]["mcdir"].template get<std::string>());
	auto b = encodeUtf8(a);*/


	/*this->config_parce["user"]["mcdir"] = this->settings_dialog->getMinecraftPath();

	std::ofstream o(this->config_path);
	o << this->config_parce.dump(4, ' ', true, nlohmann::json::error_handler_t::replace) << std::endl;
	o.close();*/

	qInfo() << "Memory saved" << std::endl;

	std::filesystem::path minecraft_path = this->settings_dialog->getMinecraftPath();

	if (minecraft_path != "")
	{
		this->minecraft_core_dir_path = minecraft_path;
		this->config.json()["user"]["mcdir"] = this->minecraft_core_dir_path.wstring();
	}
	else
	{
		this->minecraft_core_dir_path = this->default_options.gameDirectory;
		this->config.json()["user"]["mcdir"] = "";
	}

	this->config.saveJsonToFile();
	this->config.reopenConfig();

	if (this->config.json()["user"]["mcdir"].is_array())
	{
		this->minecraft_core_dir_path = "";
		for (auto& symbol : this->config.json()["user"]["mcdir"])
		{
			this->minecraft_core_dir_path += static_cast<wchar_t>(symbol.template get<int>());
		}
	}
	else
	{
		if (this->config.json()["user"]["mcdir"].template get<std::filesystem::path>() != "")
		{
			this->minecraft_core_dir_path = this->config.json()["user"]["mcdir"].template get<std::filesystem::path>();
		}
		else
		{
			this->minecraft_core_dir_path = this->default_options.gameDirectory;
			this->config.json()["user"]["mcdir"] = "";
		}
	}

	qInfo() << "Mcdir saved" << std::endl;

	ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.u8string().c_str());
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
	/*if (isVersionOld())
	{
		qInfo() << "Start updater" << std::endl;
		this->config.json()["launcher"]["version"] = getLatestVersionFromSite()[getLatestVersionFromSite().size() - 1]["version"].template get<std::string>();

		this->config.saveJsonToFile();

		emit this->updateSignal(getLatestVersionFromSite()[getLatestVersionFromSite().size() - 1]["file"].template get<std::string>());
	}*/

	checkUpdates();
}

void SomLauncherMainWindow::onClickedPushButtonSendBugReport()
{
	QDesktopServices::openUrl(QUrl("https://mocsom.site/bug_report/"));
}

void SomLauncherMainWindow::setReinstallMods(bool state)
{
	qInfo() << "setReinstallMods " << state << std::endl;
	this->config.json()["user"]["isInstallMods"] = state;
}

void SomLauncherMainWindow::updateProgressLabel(const QString& text)
{
	ui.label_download_status_change->setText(text);
}

void SomLauncherMainWindow::setOptionsValuesFromConfig()
{
	if (this->config.json()["user"]["mcdir"].is_array())
	{
		this->minecraft_core_dir_path = "";
		for (auto& symbol : this->config.json()["user"]["mcdir"])
		{
			this->minecraft_core_dir_path += static_cast<wchar_t>(symbol.template get<int>());
		}
	}
	else
	{
		if (this->config.json()["user"]["mcdir"].template get<std::string>() != "")
		{
			this->minecraft_core_dir_path = this->config.json()["user"]["mcdir"].template get<std::string>();
		}
	}

	if (this->config.json()["user"]["name"].is_array())
	{
		this->username = this->config.json()["user"]["name"].template get<std::wstring>();
	}
	else
	{
		this->username = Additionals::Convectors::ConvertStringToWString(this->config.json()["user"]["name"].template get<std::string>());
	}

	this->options.resolutionWidth = this->config.json()["user"]["wight"].template get<int>();
	this->options.resolutionHeight = this->config.json()["user"]["hight"].template get<int>();
	this->curret_memory = this->config.json()["user"]["memory"].template get<int>();

	this->options.gameDirectory = this->minecraft_core_dir_path;
	this->options.username = this->username;

	this->is_install_mods = this->config.json()["user"]["isInstallMods"].template get<bool>();
}