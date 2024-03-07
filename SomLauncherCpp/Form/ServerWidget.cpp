#include "ServerWidget.h"

ServerWidget::ServerWidget(QButtonGroup* group, nlohmann::json server_data, QWidget* parent)
	: QWidget(parent), server_data(server_data)
{
	ui.setupUi(this);

	group->addButton(ui.radioButton_selecterserver);

	ui.label_servername->setText(this->server_data["server_name"].template get<std::string>().c_str());
	ui.radioButton_selecterserver->setObjectName(this->server_data["server_name"].template get<std::string>());

	ui.textBrowser_serverdescription->setText(this->server_data["server_description"].template get<std::string>().c_str());

	setServerDataFromApi();

	QObject::connect(ui.pushButton_selectserver, &QPushButton::clicked, this, &ServerWidget::pushButtonSelectClicked);
	QObject::connect(ui.radioButton_selecterserver, &QAbstractButton::toggled, this, &ServerWidget::radioButtonChecked);
}

ServerWidget::~ServerWidget()
{
}

void ServerWidget::setStatusServer(bool value)
{
	ui.radioButton_selecterserver->setChecked(value);

	emit toggled();
}

void ServerWidget::setServerDataFromApi()
{
	nlohmann::json status = web::minecraft::status::getMinecraftStatusServer(this->server_data["server_ip"].template get<std::string>());

	try
	{
		ui.label_playerscount->setText(std::to_string(status["players"]["online"].template get<int>()).c_str());
		ui.progressBar_capacityserver->setValue(status["players"]["online"].template get<int>());
		ui.progressBar_capacityserver->setMaximum(status["players"]["max"].template get<int>());
	}
	catch (const std::exception&)
	{
		ui.label_playerscount->setHidden(true);
		ui.progressBar_capacityserver->setHidden(true);
	}
	ui.label_onlinestatus->setText(status["online"].template get<bool>() ? tr("Online") : tr("Offline"));
}

bool ServerWidget::isToFriends()
{
	return (this->server_data["server_type"].template get<std::string>() == FRIENDS_SERVERS_TYPE) ||
		(this->server_data["server_type"].template get<std::string>() == CLOSE_SERVERS_TYPE);
}

void ServerWidget::pushButtonSelectClicked()
{
	ui.radioButton_selecterserver->setChecked(true);
}

void ServerWidget::radioButtonChecked(bool checked)
{
	if (checked == true)
	{
		qInfo() << "radioButtonChecked true" << std::endl;
		QString style = R"(#widget_selecter {border-style: solid;
 border-width : 1.2px;
 border-color: red;})";
		ui.widget_selecter->setStyleSheet(style);
	}
	else
	{
		qInfo() << "radioButtonChecked false" << std::endl;
		QString style = R"(#widget_selecter {border-style: solid;
 border-width : 0px;
 border-color: red;})";
		ui.widget_selecter->setStyleSheet(style);
	}
}