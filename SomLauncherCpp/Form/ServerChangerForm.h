#ifndef SERVERCHANGERFORM_H_
#define SERVERCHANGERFORM_H_

#include <QtWidgets/qdialog.h>

#include <string>
#include <memory>

#include "../../MocJsonLib/SomJson.h"

#include "ui_ServerChangerForm.h"

class ServerChanger : public QDialog
{
	Q_OBJECT

private:
	std::string server = "";
	std::string config_path = "";
	Json::JsonValue json_parce;
	int index = -1;

	QListWidgetItem* item = nullptr;

public:
	explicit ServerChanger(QWidget* parent = nullptr, std::string config_path = "", Json::JsonValue server_parce = Json::JsonValue());
	~ServerChanger();

private slots:
	void itemChangedlistWidget(QListWidgetItem* item);
	void onClickedpushButton_apply();
	void onClickedpushButton_denied();

private:
	Ui::ServerChanger ui;
};

#endif /*SERVERCHANGERFORM_H_*/