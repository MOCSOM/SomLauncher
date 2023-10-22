#include "ServerChangerForm.h"

ServerChanger::ServerChanger(QWidget* parent, std::string config_path)
	: QDialog(parent), config_path(config_path)
{
	ui.setupUi(this);

	connect(ui.listWidget_changeserver, &QListWidget::itemClicked, this, &ServerChanger::itemChangedlistWidget);

	connect(ui.pushButton_apply, &QPushButton::released, this, &ServerChanger::onClickedpushButton_apply);
	connect(ui.pushButton_denide, &QPushButton::released, this, &ServerChanger::onClickedpushButton_denied);

	ui.listWidget_changeserver->clear();
	Json::JsonParcer json_serv;
	Json::JsonValue json_parce = json_serv.ParseFile("SERVERS.json");
	Json::JsonValue parce_config = json_serv.ParseFile(this->config_path);

	for (int i = 0; i < json_parce["servers"].get_count(); ++i)
	{
		this->item = new QListWidgetItem(json_parce["servers"][i]["name"].to_string().c_str(), ui.listWidget_changeserver);
		this->item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		this->item->setCheckState(Qt::Unchecked);
	}

	if (ui.listWidget_changeserver->item(parce_config["user"]["server"].to_int())->text() == "")
	{
		ui.pushButton_apply->setEnabled(false);
	}
	else
	{
		ui.pushButton_apply->setEnabled(true);
	}

	ui.listWidget_changeserver->item(parce_config["user"]["server"].to_int())->setCheckState(Qt::Checked);
}

ServerChanger::~ServerChanger()
{
	delete item;
}

void ServerChanger::onClickedpushButton_apply()
{
	Json::JsonParcer json_config;
	Json::JsonValue config_parce = json_config.ParseFile(this->config_path);
	config_parce["user"]["server"] = this->index;

	std::cout << "Server is: " << config_parce["user"]["server"].to_string() << std::endl;

	config_parce.save_json_to_file(this->config_path, 4);

	std::cout << "Server saved" << std::endl;

	this->close();

	emit accepted();
}

void ServerChanger::onClickedpushButton_denied()
{
	this->close();
}

void ServerChanger::itemChangedlistWidget(QListWidgetItem* item)
{
	int count = ui.listWidget_changeserver->count();
	int count_selected_items = 0;

	/* Превращение в radio bottom */
	for (int i = 0; i < count; ++i)
	{
		if (ui.listWidget_changeserver->item(i) != item)
		{
			ui.listWidget_changeserver->item(i)->setCheckState(Qt::Unchecked);
		}
		else
		{
			this->index = i;
		}
		if (ui.listWidget_changeserver->item(i)->checkState() == Qt::Checked)
		{
			++count_selected_items;
		}
	}

	if (count_selected_items != 0)
	{
		std::cout << ui.listWidget_changeserver->item(this->index)->text().toStdString() << std::endl;
		server = ui.listWidget_changeserver->item(this->index)->text().toStdString();
		ui.pushButton_apply->setEnabled(true);
	}
	else
	{
		server = "";
		ui.pushButton_apply->setEnabled(false);
	}
}