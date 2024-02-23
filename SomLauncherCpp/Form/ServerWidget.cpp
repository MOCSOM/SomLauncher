#include "ServerWidget.h"

ServerWidget::ServerWidget(QButtonGroup* group, SJson::JsonValue server_data, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	group->addButton(ui.radioButton_selecterserver);

	ui.label_servername->setText(server_data["name"].to_string().c_str());
	ui.radioButton_selecterserver->setObjectName(server_data["name"].to_string());

	ui.textBrowser_serverdescription->setText(server_data["description"].to_string().c_str());

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