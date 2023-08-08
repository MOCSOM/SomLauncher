#ifndef MAINWINDOW_H_     // equivalently, #if !defined HEADER_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <qpropertyanimation.h>
#include <qbuttongroup.h>

#include <iostream>
#include <string>

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../Additionals/Additionals.h"
#include "../Json/Json.h"
#include "../Minecraft/Minecraftus.h"

#include "ui_SomLauncherMainWindow.h"

#include "../QObjects/ClickableLabel.h"
#include "../QObjects/HoveredFrame.h"
#include "ServerChangerForm.h"
#include "ServerWidget.h"

class SomLauncherMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::string minecraft_core_dir_path = Join({ getenv("APPDATA"), ".SomSomSom" });
    std::string config_path = Join({ /*"\\",*/ minecraft_core_dir_path, "SOMCONFIG.json"});
    std::string launcher_name = "SomLauncher";
    std::string launcher_version = "2.0";
    std::string username = "Debug";
    std::string servers_json = Join({ /*"\\",*/ minecraft_core_dir_path, "SERVERS.json" });

    bool expect_table_menu = false;

    Json::JsonValue* config_parce;
    Json::JsonValue* servers_parce;

public:
    SomLauncherMainWindow(QWidget *parent = nullptr);
    ~SomLauncherMainWindow();

    void start_minecraft_params();
    void install_run_minecraft(
        std::string version,
        std::string loader_mame,
        std::string loader_version,
        std::string java,
        std::string mcdir,
        MinecraftCpp::option::MinecraftOptions options);

    bool IsConfigExist();
    void CreateConfig();

private slots:
    void onClickedpushButton_game();
    void onClickedpushButton_servers();
    void onClickedpushButton_news();
    void onClickedpushButton_aboutus();
    void onClickedpushButton_changeserver();
    void onClickedpushLable_profile();

    void onClickpushButton_startgame();

    void mouseEnterframe_topslidemenu();
    void mouseLeaveframe_topslidemenu();


private:
    Ui::SomLauncherMainWindowClass ui;

    QButtonGroup* server_radio_button_group;
};

#endif /*MAINWINDOW_H_*/