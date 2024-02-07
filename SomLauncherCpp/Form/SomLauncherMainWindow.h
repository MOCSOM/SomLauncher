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
//#include "../Minecraft/CommandBuilder.h"
#include "../Client/StartProcess.h"
#include "../Minecraft/Mods.h"
#include "../Databases/SQLBased.h"
#include "../Minecraft/Servers/ServerDatConfiguration.h"
#include "../Callbacks/QCallback.h"

#include "ui_SomLauncherMainWindow.h"

#include "../QObjects/ClickableLabel.h"
#include "../QObjects/HoveredFrame.h"
#include "../QObjects/Threads/FunThread.h"
#include "../QObjects/Images/ImageEditing.h"
#include "../QObjects/SignalLabel.h"

#include "ServerChangerForm.h"
#include "ServerWidget.h"
#include "SettingsDialog.h"
#include "TopSlideFrameWidget.h"
#include "NewsViewWidget.h"

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

	std::string background = "resources\\background_normal2.png";
	std::string mocsom_site_url = "https://mocsom.site/";
	std::string style_sheet = "resources\\StyleSheets\\Wstartpage_modyfied.qss";

	MinecraftCpp::option::MinecraftOptions options;
	MinecraftCpp::option::MinecraftOptions default_options = options;
	std::unique_ptr<SettingsDialog> settings_dialog;

	Json::JsonValue config_parce;
	Json::JsonValue servers_parce;
	Json::JsonValue account_data;

	Json::JsonParcer global_parcer;

	int max_memory = 1024;
	int recomended_memory = 1024;
	int uses_memory = 1024;
	int curret_memory = recomended_memory;

	TopSlideFrameWidget* top_frame = nullptr;
	QPropertyAnimation* top_frame_animation = nullptr;

	QList<QSharedPointer<ServerWidget>> widget_list;

	std::unique_ptr<QButtonGroup> server_radio_button_group;

	FunctionThread* download_thread = nullptr;

	QRect progressBar_ahtung_geometry;

	sql::Connection* database_connection = nullptr;
	short int connection_tries = 5;

public:
	explicit SomLauncherMainWindow(QWidget* parent = nullptr);
	~SomLauncherMainWindow();

	void _settingMinecraftStandartPath();
	void _parcingConfigs();
	void _parcingServers();
	void _parcingServers(sql::Connection* connect);
	void _settingUiChanges();
	void _settingServersWidgets();
	void _settingCurrentServerName();
	void _settingConnections();
	void _settingMemory();
	void _settingModsCount();
	void _settingServerType();
	void _settingAccountDataInUi();

	void setUiToDownload(bool status);

	void setConnectionWithDatabase();
	Json::JsonValue getServersFromDatabase();
	Json::JsonValue getServersFromDatabase(sql::Connection* connect);

	void start_minecraft_params();
	void setupInstallMinecraft(const size_t& index);
	std::string install_minecraft(
		const std::filesystem::path& install_path,
		std::string version,
		std::string loader_mame,
		std::string loader_version,
		std::string java,
		std::string mcdir,
		MinecraftCpp::option::MinecraftOptions& options,
		std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>()) const;

	void installMods(const std::filesystem::path& install_path, const std::string& modpack_name,
		const std::string& version,
		std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>());

	void createSettingsForm();
	bool isConfigExist();
	void createConfig();
	void configureOptions();
	void checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison = "", CallbackNull* callback = new CallbackNull) const;
	void setOptionsValuesFromConfig();
	size_t getMinecraftModsCount();
	ServerTypes getServerType();
	std::string getCurrentServerName();
	const std::filesystem::path getConfigPath();
	void _settingServerNameInChangeServerButton();
	std::string getLatestVersionFromGithub();
	Json::JsonValue getLatestVersionFromDatabase();
	std::string getCurrentVersionFromConfig();
	void setCurrentVersionFromGithub();
	void setCurrentVersionFromDatabase();
	bool isVersionOld();
	void setAccountData(const Json::JsonValue& data);
	void setUuidFromAccount();
	std::unique_ptr<SettingsDialog>& getSettingsDialog();

	const std::string& getStyleSheetPath();

private slots:
	void onClickedpushButton_game();
	void onClickedpushButton_servers();
	void onClickedpushButton_news();
	void onClickedpushButton_aboutus();
	void onClickedpushButton_changeserver();
	void onClickedpushLable_profile();
	void onClickedpushButton_settings();
	void onClickedPushButton_check_update();

	void onClickpushButton_startgame();


	void mouseEnterframe_topslidemenu();
	void mouseLeaveframe_topslidemenu();

	void groupButtonsClicked(QAbstractButton* id, bool status);

	void saveSettings();

	void updateProgressBar(int value);
	void updateProgressLabel(const QString& text);

	void pageChangedSlidedWidget(int value);

	void setReinstallMods(bool state);

signals:
	void updateSignal(const std::string& newl_laucher_url);

private:
	Ui::SomLauncherMainWindowClass ui;
};

#endif /*MAINWINDOW_H_*/