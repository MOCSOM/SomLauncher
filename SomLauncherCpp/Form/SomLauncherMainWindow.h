﻿#ifndef MAINWINDOW_H_
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
#include <QDesktopServices>
//#include <qgraphicsview.h>

#include <QSimpleUpdater.h>

#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <charconv>

#include <nlohmann/json.hpp>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../Additionals/Additionals.h"
#include "../Json/SomJson.h"
#include "../Minecraft/Minecraftus.h"
#include "../Moc/Logger/MocIOStream.h"
#include "../Servers/ServerTypes.h"
#include "../Exceptions/TerminateProgrammException.h"
//#include "../Minecraft/CommandBuilder.h"
#include "../Client/StartProcess.h"
#include "../Minecraft/Mods.h"
#include "../Minecraft/Servers/ServerDatConfiguration.h"
#include "../Callbacks/QCallback.h"
#include "../Web/Utils/WebUtils.h"
#include "../Client/Config/Config.h"

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
	std::filesystem::path minecraft_core_dir_path = "";
	std::filesystem::path config_path = "";
	std::string servers_json = "";
	std::string launcher_name = "SomLauncher";
	std::string launcher_version = "2.0";
	std::wstring username = L"Debug";
	bool is_install_mods = true;

	std::string server_changer_button_text = "";

	std::string background = "resources\\background_normal2.png";
	std::string mocsom_site_url = "https://mocsom.site/";
	std::string mocsom_site_api = "api/";
	std::string mocsom_api_launcher = "launcher/";
	std::string style_sheet = "resources\\StyleSheets\\Wstartpage_modyfied.qss";

	MinecraftCpp::option::MinecraftOptions options;
	MinecraftCpp::option::MinecraftOptions default_options = options;
	std::unique_ptr<SettingsDialog> settings_dialog;

	Config config;

	nlohmann::json servers_parce;
	nlohmann::json account_data;

	QSimpleUpdater* updater;

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

	short int connection_tries = 5;

public:
	explicit SomLauncherMainWindow(QWidget* parent = nullptr);
	~SomLauncherMainWindow();

	void _settingMinecraftStandartPath();
	void _parcingConfigs();
	void _parcingServers();
	void _settingUiChanges();
	void _settingServersWidgets();
	void _settingCurrentServerName();
	void _settingConnections();
	void _settingMemory();
	void _settingModsCount();
	void _settingServerType();
	void _settingAccountDataInUi();

	void settingUserProfileImage();

	void checkUpdates();

	void disableServer();

	void setUiToDownload(bool status);

	nlohmann::json getServersFromServer();

	void setupInstallMinecraft(const size_t& index);
	std::string install_minecraft(
		const std::filesystem::path& install_path,
		std::string version,
		std::string loader_mame,
		std::string loader_version,
		std::string java,
		MinecraftCpp::option::MinecraftOptions& options,
		std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>()) const;

	nlohmann::json getModpackInfoFromServer(const std::string& modpack_id);
	void installMods(const std::filesystem::path& install_path, const nlohmann::json& modpack_info,
		const std::string& modpack_old_version,
		std::shared_ptr<CallbackNull> callback = std::make_shared<CallbackNull>()) const;

	void createSettingsForm();
	bool isConfigExist() const;
	void createConfig() const;
	void configureOptions();
	void checkJava(MinecraftCpp::option::MinecraftOptions& options, std::string java_verison = "", CallbackNull* callback = new CallbackNull) const;
	void setOptionsValuesFromConfig();
	size_t getMinecraftModsCount();
	std::string getServerType();
	std::string getCurrentServerName();
	const std::filesystem::path getConfigPath();
	void _settingServerNameInChangeServerButton();
	std::string getLatestVersionFromGithub();
	nlohmann::json getLatestVersionFromSite();
	std::string getCurrentVersionFromConfig();
	void setCurrentVersionFromGithub();
	void setCurrentVersionFromSite();
	bool isVersionOld();
	void setAccountData(const nlohmann::json& data);
	void setUuidFromAccount();
	std::unique_ptr<SettingsDialog>& getSettingsDialog();

	const std::string& getStyleSheetPath();
	
	void disableElementsInDevelopment();

private slots:
	void start_minecraft_params();

	void onClickedpushButton_game();
	void onClickedpushButton_servers();
	void onClickedpushButton_news();
	void onClickedpushButton_aboutus();
	void onClickedpushButton_changeserver();
	void onClickedpushLable_profile();
	void onClickedpushButton_settings();
	void onClickedPushButton_check_update();
	void onClickedPushButtonSendBugReport();

	void onClickpushButton_startgame();


	void mouseEnterframe_topslidemenu();
	void mouseLeaveframe_topslidemenu();

	void groupButtonsClicked(QAbstractButton* id, bool status);

	void saveSettings();

	void setNewVersionInConfig(const QString& url);

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