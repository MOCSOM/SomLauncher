#ifndef SERVERWIDGET_H_
#define SERVERWIDGET_H_

#include <QWidget>
#include "ui_ServerWidget.h"
#include <qbuttongroup.h>

#include <nlohmann/json.hpp>

#include "../Moc/Logger/MocIOStream.h"
#include "../Json/SomJson.h"
#include "../Web/Minecraft/Status/MinecraftStatus.h"

class ServerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ServerWidget(QButtonGroup* group, nlohmann::json server_data, QWidget* parent = nullptr);
	~ServerWidget();

	void setStatusServer(bool value);

	void setServerDataFromApi();

signals:
	void toggled();

private slots:
	void pushButtonSelectClicked();
private slots:
	void radioButtonChecked(bool checked);

private:
	Ui::ServerWidgetClass ui;

	nlohmann::json server_data;
};

#endif /*SERVERWIDGET_H_*/