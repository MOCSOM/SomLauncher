#include "ServerChangerForm.h"

ServerChanger::ServerChanger(QWidget* parent, const std::filesystem::path& config_path, nlohmann::json server_parce)
	: QDialog(parent), config_path(config_path)
{
	ui.setupUi(this);

	connect(ui.listWidget_changeserver, &QListWidget::itemClicked, this, &ServerChanger::itemChangedlistWidget);

	connect(ui.pushButton_apply, &QPushButton::released, this, &ServerChanger::onClickedpushButton_apply);
	connect(ui.pushButton_denide, &QPushButton::released, this, &ServerChanger::onClickedpushButton_denied);

	ui.listWidget_changeserver->clear();

	nlohmann::json json_parce = server_parce;

	std::ifstream istr(this->config_path);
	nlohmann::json parce_config = nlohmann::json::parse(istr);
	istr.close();

	for (int i = 0; i < json_parce.size(); ++i)
	{
		this->item = new QListWidgetItem(json_parce[i]["server_name"].template get<std::string>().c_str(), ui.listWidget_changeserver);
		this->item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		this->item->setCheckState(Qt::Unchecked);
	}

	if (ui.listWidget_changeserver->item(parce_config["user"]["server"].template get<int>())->text() == "")
	{
		ui.pushButton_apply->setEnabled(false);
	}
	else
	{
		ui.pushButton_apply->setEnabled(true);
	}

	ui.listWidget_changeserver->item(parce_config["user"]["server"].template get<int>())->setCheckState(Qt::Checked);
}

ServerChanger::~ServerChanger()
{
	delete item;
}

void ServerChanger::onClickedpushButton_apply()
{
	std::ifstream istr(this->config_path);
	nlohmann::json config_parce = nlohmann::json::parse(istr);
	istr.close();

	config_parce["user"]["server"] = this->index;

	std::cout << "Server is: " << config_parce["user"]["server"].template get<int>() << std::endl;

	std::ofstream o(this->config_path);
	o << config_parce.dump(4) << std::endl;
	o.close();

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