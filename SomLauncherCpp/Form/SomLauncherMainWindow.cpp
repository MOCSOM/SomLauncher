#include "SomLauncherMainWindow.h"

SomLauncherMainWindow::SomLauncherMainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QMovie* movie = new QMovie(this);
	movie->setFileName(this->background_gif.c_str());
	movie->start();

	ui.labeltest->setMovie(movie);

	MEMORYSTATUSEX statex{};
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	this->max_memory = statex.ullTotalPhys / MEM_DIV - 512;

	this->servers_parce = this->global_parcer.ParseFile(this->servers_json);
	this->config_parce = this->global_parcer.ParseFile(this->config_path);

	configureOptions();

	this->default_options = this->options;

	setOptionsValuesFromConfig();

	this->dialog = std::make_unique<SettingsDialog>(std::make_shared<Json::JsonObject>(), this->options, this); //TODO: Сделать отправку данных о акке

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

	QObject::connect(this->dialog.get(), &SettingsDialog::acceptButtonClicked, this, &SomLauncherMainWindow::saveSettings);
	QObject::connect(this->dialog.get(), &SettingsDialog::setToDefaultButtonClicked,
		this, [=]() -> void
		{
			this->dialog->setToDefault(default_options, recomended_memory);
		});

	ui.pushButton_game->setStyleSheet("text-align:bottom;");
	ui.pushButton_servers->setStyleSheet("text-align:bottom;");
	ui.pushButton_news->setStyleSheet("text-align:bottom;");
	ui.pushButton_aboutus->setStyleSheet("text-align:bottom;");

	this->server_buttom_text = ui.pushButton_changeserver->text().toStdString();
	ui.pushButton_changeserver->setText((this->server_buttom_text +
		(*(*(*this->servers_parce)["servers"])[(*(*this->config_parce)["user"])["server"]->to_int()])["name"]->to_string() +
		")").c_str());

	ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());

	//ui.scrollAreaWidgetContents->setAttribute(Qt::WA_TranslucentBackground);
	ui.scrollArea_servers->setStyleSheet("background-color: transparent;");

	this->server_radio_button_group = std::make_unique<QButtonGroup>();

	for (int i = 0; i < (*this->servers_parce)["servers"]->get_count(); ++i)
	{
		ServerWidget* widget = new ServerWidget(this->server_radio_button_group.get(), (*(*this->servers_parce)["servers"])[i]);

		this->widget_list.append(widget);

		if ((*(*this->config_parce)["user"])["server"]->get_type() != Json::JsonTypes::Null && (*(*this->config_parce)["user"])["server"]->to_int() == i)
		{
			widget->setStatusServer(true);
		}
	}

	int index = 0;
	for (int i = 0; i < ((*this->servers_parce)["servers"]->get_count() - 1) / 2 + 1; ++i)
	{
		for (int j = 0; j < ((*this->servers_parce)["servers"]->get_count() - 1) / 2 + 1; ++j)
		{
			ui.gridLayout_scrollArea_servers->addWidget(this->widget_list[index], i, j);

			++index;
		}
	}

	QObject::connect(this->server_radio_button_group.get(), &QButtonGroup::buttonToggled,
		this, &SomLauncherMainWindow::groupButtonsClicked);

	//Проверка и создание конфига
	if (!isConfigExist())
	{
		createConfig();
		std::cout << "Config created" << std::endl;
	}

	this->recomended_memory = 3072;
	this->curret_memory = (*(*this->config_parce)["user"])["memory"]->to_int();
}

SomLauncherMainWindow::~SomLauncherMainWindow()
{
	//delete this->dialog;
}

void SomLauncherMainWindow::onClickedpushButton_game()
{
	std::cout << "pushButton_game clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(0);
}

void SomLauncherMainWindow::onClickedpushButton_servers()
{
	std::cout << "pushButton_servers clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(1);
}

void SomLauncherMainWindow::onClickedpushButton_news()
{
	std::cout << "pushButton_news clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(2);
}

void SomLauncherMainWindow::onClickedpushButton_aboutus()
{
	std::cout << "pushButton_aboutus clicked" << std::endl;

	ui.stackedWidget_bottommenu->setCurrentIndex(3);
}

void SomLauncherMainWindow::onClickedpushButton_changeserver()
{
	std::cout << "pushButton_changeserver clicked" << std::endl;

	ServerChanger dialog(this, this->config_path);

	QObject::connect(&dialog, &ServerChanger::accepted,
		this, [=]() -> void
		{
			this->config_parce = this->global_parcer.ParseFile(this->config_path);
			ui.pushButton_changeserver->setText((this->server_buttom_text +
				(*(*(*this->servers_parce)["servers"])[(*(*this->config_parce)["user"])["server"]->to_int()])["name"]->to_string() +
				")").c_str());
			this->widget_list[(*(*this->config_parce)["user"])["server"]->to_int()]->setStatusServer(true);
		});

	dialog.exec(); //modal dialog
}

void SomLauncherMainWindow::onClickedpushLable_profile()
{
	std::cout << "pushLable_profile clicked" << std::endl;
}

void SomLauncherMainWindow::onClickedpushButton_settings()
{
	std::cout << "pushButton_settings clicked" << std::endl;

	this->dialog->setMemoryData(1024, this->max_memory, this->recomended_memory);
	this->dialog->setCurretMemory(this->curret_memory);

	this->dialog->setStandartJavaPath(this->options.executablePath);
	this->dialog->setStandartMinecraftPath(this->options.gameDirectory);

	this->dialog->exec();
}

void SomLauncherMainWindow::onClickpushButton_startgame()
{
	std::cout << "pushButton_startgame clicked" << std::endl;

	start_minecraft_params();
}

void SomLauncherMainWindow::mouseEnterframe_topslidemenu()
{
	std::cout << "frame_topslidemenu mouse enter" << std::endl;

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
	std::cout << "frame_topslidemenu mouse leave" << std::endl;

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
	std::cout << "groupButtons Clicked id: " << id->objectName().toStdString() << " " << status << std::endl;

	if (status == true)
	{
		int index = 0;
		int i = -1;
		for (auto& var : (*this->servers_parce)["servers"]->get_value_list())
		{
			++i;
			if ((*var)["name"]->to_string() == id->objectName().toStdString())
			{
				index = i;
			}
		}

		(*(*this->config_parce)["user"])["server"]->operator=(index);

		std::cout << "Server is: " << (*(*config_parce)["user"])["server"]->to_string() << std::endl;

		config_parce->SaveJsonToFile(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		std::cout << "Server saved" << std::endl;
	}
}

void SomLauncherMainWindow::saveSettings()
{
	int memory_value = this->dialog->getMemoryValue();

	if (this->dialog->getReintsallModsState() == true)
	{
		this->isInstallMods = true;
		(*(*config_parce)["user"])["isInstallMods"]->operator=(this->isInstallMods);
	}

	this->curret_memory = memory_value;

	(*(*config_parce)["user"])["memory"]->operator=(memory_value);

	std::cout << "Memory is: " << (*(*config_parce)["user"])["memory"]->to_string() << std::endl;

	config_parce->SaveJsonToFile(this->config_path, 4);

	std::cout << "Memory saved" << std::endl;

	std::string minecraft_path = this->dialog->getMinecraftPath();

	if (minecraft_path != "")
	{
		this->minecraft_core_dir_path = minecraft_path;

		(*(*config_parce)["user"])["mcdir"]->operator=(this->minecraft_core_dir_path);

		std::cout << "Mcdir is: " << (*(*config_parce)["user"])["mcdir"]->to_string() << std::endl;

		config_parce->SaveJsonToFile(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		std::cout << "Mcdir saved" << std::endl;

		ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());
	}
	else
	{
		this->minecraft_core_dir_path = this->default_options.gameDirectory;

		(*(*config_parce)["user"])["mcdir"]->operator=("");

		std::cout << "Mcdir is: " << (*(*config_parce)["user"])["mcdir"]->to_string() << std::endl;

		config_parce->SaveJsonToFile(this->config_path, 4);

		this->config_parce = this->global_parcer.ParseFile(this->config_path);

		std::cout << "Mcdir saved" << std::endl;

		ui.label_minecraft_directory->setText(this->minecraft_core_dir_path.c_str());
	}
}

void SomLauncherMainWindow::setOptionsValuesFromConfig()
{
	if ((*(*this->config_parce)["user"])["mcdir"]->to_string() != "")
	{
		this->minecraft_core_dir_path = (*(*this->config_parce)["user"])["mcdir"]->to_string();
	}

	this->username = (*(*this->config_parce)["user"])["name"]->to_string();
	this->options.resolutionWidth = (*(*this->config_parce)["user"])["wight"]->to_int();
	this->options.resolutionHeight = (*(*this->config_parce)["user"])["hight"]->to_int();
	this->curret_memory = (*(*this->config_parce)["user"])["memory"]->to_int();

	this->options.gameDirectory = this->minecraft_core_dir_path;
	this->options.username = this->username;

	this->isInstallMods = (*(*config_parce)["user"])["isInstallMods"]->toBool();
}