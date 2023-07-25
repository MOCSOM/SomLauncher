#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SomLauncherMainWindow.h"

class SomLauncherMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SomLauncherMainWindow(QWidget *parent = nullptr);
    ~SomLauncherMainWindow();

private:
    Ui::SomLauncherMainWindowClass ui;
};
