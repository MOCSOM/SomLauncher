#pragma once

#include <QWidget>
#include "ui_ServerWidget.h"
#include <qbuttongroup.h>

#include "../Json/Json.h"

class ServerWidget : public QWidget
{
	//Q_OBJECT

public:
	ServerWidget(QButtonGroup* group, Json::JsonValue* server_data, QWidget *parent = nullptr);
	~ServerWidget();

//private slots:
//	void refreshLables();

private:
	Ui::ServerWidgetClass ui;
};
