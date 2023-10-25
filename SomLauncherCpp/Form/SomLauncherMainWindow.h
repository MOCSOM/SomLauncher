#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <qpropertyanimation.h>
#include <qbuttongroup.h>
#include <qsharedpointer.h>
#include <qshareddata.h>
#include <qthread.h>
#include <qjsondocument.h>
#include <qurl.h>
#include <qnetworkrequest.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
//#include <qgraphicsview.h>

#include <iostream>
#include <string>
#include <windows.h>
#include <thread>

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../../SomAdditionalsLib/Additionals.h"
#include "../../MocJsonLib/SomJson.h"
#include "../Minecraft/Minecraftus.h"
#include "../Moc/Logger/MocIOStream.h"
#include "../Servers/ServerTypes.h"
#include "../Exceptions/TerminateProgrammException.h"

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
	std::string minecraft_core_dir_path = "";
	std::string config_path = "";
	std::string template_config_path = "";
	std::string servers_json = "";
	std::string launcher_name = "SomLauncher";
	std::string launcher_version = "2.0";
	std::string username = "Debug";
	bool is_install_mods = true;

	std::string server_changer_button_text = "";

	std::string background_gif = "minecraft2.gif";
	std::string mocsom_site_url = "https://mocsom.site/";

	MinecraftCpp::option::MinecraftOptions options;
	MinecraftCpp::option::MinecraftOptions default_options = options;
	std::unique_ptr<SettingsDialog> settings_dialog;

	Json::JsonValue config_parce;
	Json::JsonValue servers_parce;

	Json::JsonParcer global_parcer;

	int max_memory = 1024;
	int recomended_memory = 1024;
	int uses_memory = 1024;
	int curret_memory = recomended_memory;

	QList<QSharedPointer<ServerWidget>> widget_list;

	std::unique_ptr<QButtonGroup> server_radio_button_group;

	FunctionThread* download_thread = nullptr;

	QRect progressBar_ahtung_geometry;

public:
	explicit SomLauncherMainWindow(QWidget* parent = nullptr);
	~SomLauncherMainWindow() = default;

	void _settingMinecraftStandartPath();
	void _parcingConfigs();
	void _settingUiChanges();
	void _settingCurrentServerName();
	void _settingConnections();
	void _settingMemory();
	void _settingModsCount();
	void _settingServerType();

	void start_minecraft_params();
	std::string install_minecraft(
		std::string version,
		std::string loader_mame,
		std::string loader_version,
		std::string java,
		std::string mcdir,
		MinecraftCpp::option::MinecraftOptions& options);

	bool isConfigExist();
	void createConfig();
	void configureOptions();
	void checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison = "");
	void setOptionsValuesFromConfig();
	size_t getMinecraftModsCount();
	ServerTypes getServerType();
	std::string getCurrentServerName();
	void _settingServerNameInChangeServerButton();
	std::string getLatestVersionFromGithub();
	std::string getCurrentVersionFromConfig();
	void setCurrentVersionFromGithub();
	bool isVersionOld();

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

	void updateProgressBar(int value);

	void pageChangedSlidedWidget(int value);

signals:
	void updateSignal();

private:
	Ui::SomLauncherMainWindowClass ui;
};

#endif /*MAINWINDOW_H_*/