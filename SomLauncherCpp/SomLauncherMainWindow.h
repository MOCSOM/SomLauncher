#ifndef MAINWINDOW_H_     // equivalently, #if !defined HEADER_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
//#include <iostream>
//#include <string>
//
//#include "DownloadClasses.h"
//#include "CallbackDict.h"
////#include "ChangeServerForm.h"
//#include "Additionals.h"

#include "ui_SomLauncherMainWindow.h"

class SomLauncherMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /*std::string minecraft_core_dir_path = Additionals::Convectors::ConvertWcharPtrToString(JoinA({ getenv("APPDATA"), ".SomSomSom" }));
    std::string config_path = Additionals::Convectors::ConvertWcharPtrToString(JoinA({ "\\", minecraft_core_dir_path.c_str(), "SOMCONFIG.json"}));
    std::string launcher_name = "SomLauncher";
    std::string launcher_version = "2.0";
    std::string username = nullptr;
    std::string servers_json = Additionals::Convectors::ConvertWcharPtrToString(JoinA({ "\\", minecraft_core_dir_path.c_str(), "SERVERS.json" }));*/

public:
    SomLauncherMainWindow(QWidget *parent = nullptr);
    ~SomLauncherMainWindow();

    /*void start_minecraft_params();
    void install_run_minecraft(
        std::string version,
        std::string loader_mame,
        std::string loader_version,
        std::string java,
        std::string mcdir,
        MinecraftCpp::option::MinecraftOptions options);

    bool IsConfigExist();
    void CreateConfig();*/

private:
    Ui::SomLauncherMainWindowClass ui;
};

#endif /*MAINWINDOW_H_*/