#include "SomLauncherMainWindow.h"

SomLauncherMainWindow::SomLauncherMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	connect(ui.pushButton_game, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_game);
	connect(ui.pushButton_servers, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_servers);
	connect(ui.pushButton_news, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_news);
	connect(ui.pushButton_aboutus, &QPushButton::released, this, &SomLauncherMainWindow::onClickedpushButton_aboutus);

	connect(ui.pushButton_startgame, &QPushButton::released, this, &SomLauncherMainWindow::onClickpushButton_startgame);

	connect(ui.label_4, &ClickableLabel::clicked, this, &SomLauncherMainWindow::mouseEnterframe_topslidemenu);

	//Проверка и создание конфига
	if (!SomLauncherMainWindow::IsConfigExist())
	{
		SomLauncherMainWindow::CreateConfig();
		std::cout << "Config created" << std::endl;
	}
}

SomLauncherMainWindow::~SomLauncherMainWindow()
{
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

void SomLauncherMainWindow::onClickpushButton_startgame()
{
	start_minecraft_params();
}

void SomLauncherMainWindow::mouseEnterframe_topslidemenu()
{
	std::cout << "frame_topslidemenu mouse enter" << std::endl;

	int i = 0;
	while (!this->expect_table_menu && ui.frame_topslidemenu->geometry() != QRect(30, 0, 741, 131))
	{
		this->expect_table_menu = true;

		++i;
		ui.frame_topslidemenu->setGeometry(QRect(30, (i / 18) - 90, 741, 131));

		this->expect_table_menu = false;
	}
}
