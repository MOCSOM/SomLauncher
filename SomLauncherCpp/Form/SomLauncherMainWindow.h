#ifndef MAINWINDOW_H_     // equivalently, #if !defined HEADER_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <string>

#include "DownloadClasses.h"
#include "CallbackDict.h"
//#include "ChangeServerForm.h"
#include "Additionals.h"
#include "Json.h"
#include "Minecraftus.h"

#include "ui_SomLauncherMainWindow.h"

#include "ClickableLabel.h"

class SomLauncherMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::string minecraft_core_dir_path = Additionals::Convectors::ConvertWStringToString(JoinA({ getenv("APPDATA"), ".SomSomSom" }));
    std::string config_path = Additionals::Convectors::ConvertWStringToString(JoinA({ /*"\\",*/ minecraft_core_dir_path.c_str(), "SOMCONFIG.json"}));
    std::string launcher_name = "SomLauncher";
    std::string launcher_version = "2.0";
    std::string username = "";
    std::string servers_json = Additionals::Convectors::ConvertWStringToString(JoinA({ /*"\\",*/ minecraft_core_dir_path.c_str(), "SERVERS.json" }));

    bool expect_table_menu = false;

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

    void onClickpushButton_startgame();

    void mouseEnterframe_topslidemenu();


private:
    Ui::SomLauncherMainWindowClass ui;
};

#endif /*MAINWINDOW_H_*/