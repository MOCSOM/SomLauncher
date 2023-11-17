#include "TopSlideFrameWidget.h"

TopSlideFrameWidget::TopSlideFrameWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

TopSlideFrameWidget::~TopSlideFrameWidget()
{}

HoveredFrame* TopSlideFrameWidget::getFrame()
{
	return ui.frame_topslidemenu;
}

QLabel* TopSlideFrameWidget::getLabelProfile()
{
	return ui.label_account_name;
}

QPushButton* TopSlideFrameWidget::getPushButtonSettings()
{
	return ui.pushButton_settings;
}

QPushButton* TopSlideFrameWidget::getPushButtonAboutUs()
{
	return ui.pushButton_aboutus;
}

QPushButton* TopSlideFrameWidget::getPushButtonNews()
{
	return ui.pushButton_news;
}

QPushButton* TopSlideFrameWidget::getPushButtonServers()
{
	return ui.pushButton_servers;
}

QPushButton* TopSlideFrameWidget::getPushButtonGame()
{
	return ui.pushButton_game;
}

void TopSlideFrameWidget::setMainButtonsTextAlightButtom()
{
	ui.pushButton_game->setStyleSheet("text-align:bottom;");
	ui.pushButton_servers->setStyleSheet("text-align:bottom;");
	ui.pushButton_news->setStyleSheet("text-align:bottom;");
	ui.pushButton_aboutus->setStyleSheet("text-align:bottom;");
}

void TopSlideFrameWidget::setMainButtonsTextAlightCenter()
{
	ui.pushButton_game->setStyleSheet("text-align:center;");
	ui.pushButton_servers->setStyleSheet("text-align:center;");
	ui.pushButton_news->setStyleSheet("text-align:center;");
	ui.pushButton_aboutus->setStyleSheet("text-align:center;");
}

void TopSlideFrameWidget::changeLabelsCurrencyCountAndAccountName()
{
	const QRect& account_label_place = ui.label_account_name->geometry();
	const QRect& currency_count_label_place = ui.label_currency_count->geometry();

	QRect temp = account_label_place;
	ui.label_account_name->setGeometry(currency_count_label_place);
	ui.label_currency_count->setGeometry(temp);
}
