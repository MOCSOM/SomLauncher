#ifndef SERVERCHANGERFORM_H_
#define SERVERCHANGERFORM_H_

#include <QtWidgets/qdialog.h>
#include <QDebug>

#include <string>
#include <memory>
#include <fstream>

#include <nlohmann/json.hpp>

#include "ui_ServerChangerForm.h"

#include "../Moc/Logger/MocIOStream.h"

class ServerChanger : public QDialog
{
	Q_OBJECT

private:
	std::string server = "";
	std::filesystem::path config_path = "";
	nlohmann::json json_parce;
	int index = -1;

	QListWidgetItem* item = nullptr;

public:
	explicit ServerChanger(QWidget* parent = nullptr, const std::filesystem::path& config_path = "", nlohmann::json server_parce = nlohmann::json());
	~ServerChanger();

private slots:
	void itemChangedlistWidget(QListWidgetItem* item);
	void onClickedpushButton_apply();
	void onClickedpushButton_denied();

private:
	Ui::ServerChanger ui;
};

#endif /*SERVERCHANGERFORM_H_*/