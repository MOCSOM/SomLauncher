#include "ServerWidget.h"

ServerWidget::ServerWidget(QButtonGroup* group, Json::JsonValue* server_data, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	group->addButton(ui.radioButton_selecterserver);

	ui.label_servername->setText((*server_data)["name"]->to_string().c_str());

	ui.textBrowser_serverdescription->setText((*server_data)["description"]->to_string().c_str());
}

ServerWidget::~ServerWidget()
{}
