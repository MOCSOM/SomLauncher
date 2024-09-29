#include "ServerWidget.h"

ServerWidget::ServerWidget(QButtonGroup* group, nlohmann::json server_data, QWidget* parent)
	: QWidget(parent), server_data(server_data)
{
	ui.setupUi(this);

	group->addButton(ui.radioButton_selecterserver);

	ui.label_servername->setText(this->server_data["server_name"].template get<std::string>().c_str());
	ui.radioButton_selecterserver->setObjectName(this->server_data["server_name"].template get<std::string>());

	ui.textBrowser_serverdescription->setText(this->server_data["server_description"].template get<std::string>().c_str());

	addNewPage(this->server_data["server_name"].template get<std::string>());

	setServerDataFromApi();

	QObject::connect(ui.pushButton_selectserver, &QPushButton::clicked, this, &ServerWidget::pushButtonSelectClicked);
	QObject::connect(ui.radioButton_selecterserver, &QAbstractButton::toggled, this, &ServerWidget::radioButtonChecked);
}

ServerWidget::~ServerWidget()
{
}

void ServerWidget::addNewPage(const std::string& name)
{
	auto prev_tab = new QWidget(ui.tab_server);
	prev_tab;
	//ui.tabWidget_server->addTab(QWidget::createWindowContainer(this, ui.tab_server), name.c_str());
}

void ServerWidget::setStatusServer(bool value)
{
	ui.radioButton_selecterserver->setChecked(value);

	emit toggled();
}

void ServerWidget::setServerDataFromApi()
{
	this->status = web::minecraft::status::getMinecraftStatusServer(this->server_data["server_ip"].template get<std::string>());

	try
	{
		ui.label_playerscount->setText(std::to_string(this->status["players"]["online"].template get<int>()).c_str());
		ui.progressBar_capacityserver->setValue(this->status["players"]["online"].template get<int>());
		ui.progressBar_capacityserver->setMaximum(this->status["players"]["max"].template get<int>());
	}
	catch (const std::exception&)
	{
		ui.label_playerscount->setHidden(true);
		ui.progressBar_capacityserver->setHidden(true);
	}
	ui.label_onlinestatus->setText(this->status["online"].template get<bool>() ? tr("Online") : tr("Offline"));
}

bool ServerWidget::isToFriends()
{
	return (this->server_data["server_type"].template get<std::string>() == FRIENDS_SERVERS_TYPE) ||
		(this->server_data["server_type"].template get<std::string>() == CLOSE_SERVERS_TYPE);
}

const QString ServerWidget::getServerName()
{
	return this->server_data["server_name"].template get<std::string>().c_str();
}

const QString ServerWidget::getServerStatus()
{
	return this->status["online"].template get<bool>() ? tr("Online") : tr("Offline");
}

void ServerWidget::pushButtonSelectClicked()
{
	ui.radioButton_selecterserver->setChecked(true);
}

void ServerWidget::radioButtonChecked(bool checked)
{
	if (checked == true)
	{
		qInfo() << "radioButtonChecked true";
		QString style = R"(#widget_selecter {border-style: solid;
 border-width : 1.2px;
 border-color: red;})";
		ui.widget_selecter->setStyleSheet(style);
	}
	else
	{
		qInfo() << "radioButtonChecked false";
		QString style = R"(#widget_selecter {border-style: solid;
 border-width : 0px;
 border-color: red;})";
		ui.widget_selecter->setStyleSheet(style);
	}
}