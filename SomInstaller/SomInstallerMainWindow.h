#ifndef SOMINSTALLERMAINWINDOW_H_
#define SOMINSTALLERMAINWINDOW_H_

#include <qobject.h>
#include <qwidget.h>
#include <qmainwindow.h>

#include "ui_SomInstallerMainWindow.h"

class SomInstallerMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SomInstallerMainWindow(QWidget* parent = nullptr);
	~SomInstallerMainWindow();
private:
	Ui::SomInstallerMainWindow ui;
};

#endif /*SOMINSTALLERMAINWINDOW_H_*/