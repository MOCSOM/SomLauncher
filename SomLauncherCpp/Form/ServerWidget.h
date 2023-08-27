#ifndef SERVERWIDGET_H_
#define SERVERWIDGET_H_

#include <QWidget>
#include "ui_ServerWidget.h"
#include <qbuttongroup.h>

#include "../Json/Json.h"

class ServerWidget : public QWidget
{
	Q_OBJECT

public:
	ServerWidget(QButtonGroup* group, Json::JsonValue* server_data, QWidget *parent = nullptr);
	~ServerWidget();

	void setStatusServer(bool value);

private slots:
	void pushButtonSelectClicked();
private slots:
	void radioButtonChecked(bool checked);

private:
	Ui::ServerWidgetClass ui;
};

#endif /*SERVERWIDGET_H_*/