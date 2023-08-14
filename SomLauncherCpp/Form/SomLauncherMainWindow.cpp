#include "SomLauncherMainWindow.h"

SomLauncherMainWindow::SomLauncherMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	this->dialog = new SettingsDialog(new Json::JsonObject(), this->options, this);


	recomended_memory = 3072;

	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	max_memory = statex.ullTotalPhys / MEM_DIV - 512;


	configureOptions();


	Json::JsonParcer json_config;
	this->servers_parce = json_config.ParseFile(this->servers_json);
	this->config_parce = json_config.ParseFile(this->config_path);


	QObject::connect(ui.pushButton_game, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_game);
	QObject::connect(ui.pushButton_servers, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_servers);
	QObject::connect(ui.pushButton_news, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_news);
	QObject::connect(ui.pushButton_aboutus, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_aboutus);
	QObject::connect(ui.pushButton_changeserver, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_changeserver);
	QObject::connect(ui.pushButton_settings, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_settings);

	QObject::connect(ui.pushButton_startgame, &QPushButton::released, this, &SomLauncherMainWindow::onClickpushButton_startgame);

	QObject::connect(ui.label_profile, &ClickableLabel::clicked, this, &SomLauncherMainWindow::onClickedpushLable_profile);

	QObject::connect(ui.frame_topslidemenu, &HoveredFrame::Enter, this, &SomLauncherMainWindow::mouseEnterframe_topslidemenu);
	QObject::connect(ui.frame_topslidemenu, &HoveredFrame::Leave , this, &SomLauncherMainWindow::mouseLeaveframe_topslidemenu);


	ui.pushButton_game->setStyleSheet("text-align:bottom;");
	ui.pushButton_servers->setStyleSheet("text-align:bottom;");
	ui.pushButton_news->setStyleSheet("text-align:bottom;");
	ui.pushButton_aboutus->setStyleSheet("text-align:bottom;");


	this->server_radio_button_group = new QButtonGroup();

	QList<ServerWidget*> widget_list;

	for (int i = 0; i < (*this->servers_parce)["servers"]->get_count(); ++i)
	{
		ServerWidget* widget = new ServerWidget(this->server_radio_button_group, (*(*this->servers_parce)["servers"])[i]);

		widget_list.append(widget);
	}

	int index = 0;
	for (int i = 0; i < ((*this->servers_parce)["servers"]->get_count() - 1) / 2 + 1; i++)
	{
		for (int j = 0; j < ((*this->servers_parce)["servers"]->get_count() - 1) / 2 + 1; j++)
		{
			ui.gridLayout_scrollArea_servers->addWidget(widget_list[index], i, j);

			++index;
		}
	}


	//Проверка и создание конфига
	if (!SomLauncherMainWindow::IsConfigExist())
	{
		SomLauncherMainWindow::CreateConfig();
		std::cout << "Config created" << std::endl;
	}
}

SomLauncherMainWindow::~SomLauncherMainWindow()
{
	delete this->dialog;
	delete this->servers_parce;
	delete this->config_parce;
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
	dialog.exec(); //modal dialog
}

void SomLauncherMainWindow::onClickedpushLable_profile()
{
	std::cout << "pushLable_profile clicked" << std::endl;
}

void SomLauncherMainWindow::onClickedpushButton_settings()
{
	std::cout << "pushButton_settings clicked" << std::endl;

	

	dialog->setMemoryData(1024, max_memory, recomended_memory);
	
	dialog->setStandartJavaPath(this->options.executablePath);
	dialog->setStandartMinecraftPath(this->minecraft_core_dir_path);

	dialog->exec();
}

void SomLauncherMainWindow::onClickpushButton_startgame()
{
	std::cout << "pushButton_startgame clicked" << std::endl;

	start_minecraft_params();
}

void SomLauncherMainWindow::mouseEnterframe_topslidemenu()
{
	std::cout << "frame_topslidemenu mouse enter" << std::endl;

	if (!this->expect_table_menu == true && ui.frame_topslidemenu->geometry() != QRect(30, 0, 741, 131))
	{
		this->expect_table_menu = true;

		QPropertyAnimation* animation = new QPropertyAnimation(ui.frame_topslidemenu, "geometry");
		animation->setDuration(100);
		animation->setStartValue(ui.frame_topslidemenu->geometry());
		animation->setEndValue(QRect(30, 0, 741, 131));
		animation->start();

		this->expect_table_menu = false;
	}

	ui.pushButton_game->setStyleSheet("text-align:center;");
	ui.pushButton_servers->setStyleSheet("text-align:center;");
	ui.pushButton_news->setStyleSheet("text-align:center;");
	ui.pushButton_aboutus->setStyleSheet("text-align:center;");
}

void SomLauncherMainWindow::mouseLeaveframe_topslidemenu()
{
	std::cout << "frame_topslidemenu mouse leave" << std::endl;

	if (!this->expect_table_menu == true && ui.frame_topslidemenu->geometry() != QRect(30, -90, 741, 131))
	{
		this->expect_table_menu = true;

		QPropertyAnimation* animation = new QPropertyAnimation(ui.frame_topslidemenu, "geometry");
		animation->setDuration(100);
		animation->setStartValue(ui.frame_topslidemenu->geometry());
		animation->setEndValue(QRect(30, -90, 741, 131));
		animation->start();

		this->expect_table_menu = false;
	}

	//animation->finished();
	ui.pushButton_game->setStyleSheet("text-align:bottom;");
	ui.pushButton_servers->setStyleSheet("text-align:bottom;");
	ui.pushButton_news->setStyleSheet("text-align:bottom;");
	ui.pushButton_aboutus->setStyleSheet("text-align:bottom;");
}