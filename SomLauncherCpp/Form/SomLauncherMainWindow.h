#ifndef MAINWINDOW_H_     // equivalently, #if !defined HEADER_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <qpropertyanimation.h>
#include <qbuttongroup.h>

#include <iostream>
#include <string>
#include <windows.h>

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../../SomAdditionalsLib/Additionals.h"
#include "../../SomJsonLib/SomJson.h"
#include "../Minecraft/Minecraftus.h"

#include "ui_SomLauncherMainWindow.h"

#include "../QObjects/ClickableLabel.h"
#include "../QObjects/HoveredFrame.h"
#include "../QObjects/Threads/FunThread.h"

#include "ServerChangerForm.h"
#include "ServerWidget.h"
#include "SettingsDialog.h"

// Use to convert bytes to MB
constexpr int MEM_DIV = 1024 * 1024;

class SomLauncherMainWindow : public QMainWindow
{
	Q_OBJECT

private:
	std::string minecraft_core_dir_path = Join({ getenv("APPDATA"), ".SomSomSom" });
	std::string config_path = Join({ minecraft_core_dir_path, "SOMCONFIG.json" });
	std::string launcher_name = "SomLauncher";
	std::string launcher_version = "2.0";
	std::string username = "Debug";
	std::string servers_json = Join({ minecraft_core_dir_path, "SERVERS.json" });

	std::string server_buttom_text = "";

	MinecraftCpp::option::MinecraftOptions options;
	MinecraftCpp::option::MinecraftOptions default_options = options;
	std::unique_ptr<SettingsDialog> dialog;

	Json::JsonValue config_parce;
	Json::JsonValue servers_parce;

	Json::JsonParcer global_parcer;

	int max_memory = 1024;
	int recomended_memory = 1024;
	int uses_memory = 1024;
	int curret_memory = recomended_memory;

	QList<ServerWidget*> widget_list;

public:
	SomLauncherMainWindow(QWidget* parent = nullptr);
	~SomLauncherMainWindow();

	void start_minecraft_params();
	std::string install_minecraft(
		std::string version,
		std::string loader_mame,
		std::string loader_version,
		std::string java,
		std::string mcdir,
		MinecraftCpp::option::MinecraftOptions options);

	bool isConfigExist();
	void createConfig();
	void configureOptions();
	void checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison = "");
	void setOptionsValuesFromConfig();
	//void setStatusServer();

	//void setStandartServer();

private slots:
	void onClickedpushButton_game();
	void onClickedpushButton_servers();
	void onClickedpushButton_news();
	void onClickedpushButton_aboutus();
	void onClickedpushButton_changeserver();
	void onClickedpushLable_profile();
	void onClickedpushButton_settings();

	void onClickpushButton_startgame();

	void mouseEnterframe_topslidemenu();
	void mouseLeaveframe_topslidemenu();

	void groupButtonsClicked(QAbstractButton* id, bool status);

	void saveSettings();


private:
	Ui::SomLauncherMainWindowClass ui;

	std::unique_ptr<QButtonGroup> server_radio_button_group;
};

#endif /*MAINWINDOW_H_*/