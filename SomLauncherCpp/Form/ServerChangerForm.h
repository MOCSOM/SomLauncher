#ifndef SERVERCHANGERFORM_H_
#define SERVERCHANGERFORM_H_

#include <QtWidgets/qdialog.h>

#include "ui_ServerChangerForm.h"

class ServerChanger : public QDialog
{
	Q_OBJECT

public:
	ServerChanger(QWidget* parent = nullptr);
	~ServerChanger();

private:
	Ui::ServerChanger ui;
};

#endif /*SERVERCHANGERFORM_H_*/