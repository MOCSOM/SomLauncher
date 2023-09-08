#ifndef SERVERCHANGERFORM_H_
#define SERVERCHANGERFORM_H_

#include <QtWidgets/qdialog.h>

#include <string>

#include "../../SomJsonLib/SomJson.h"

#include "ui_ServerChangerForm.h"

class ServerChanger : public QDialog
{
	Q_OBJECT

private:
	std::string server = "";
	std::string config_path;
	int index = -1;

	QListWidgetItem* item;

public:
	ServerChanger(QWidget* parent = nullptr, std::string config_path = "");
	~ServerChanger();

private slots:
	void itemChangedlistWidget(QListWidgetItem* item);
	void onClickedpushButton_apply();
	void onClickedpushButton_denied();

private:
	Ui::ServerChanger ui;
};

#endif /*SERVERCHANGERFORM_H_*/