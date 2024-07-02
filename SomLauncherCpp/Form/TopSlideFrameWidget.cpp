#include "TopSlideFrameWidget.h"

TopSlideFrameWidget::TopSlideFrameWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

TopSlideFrameWidget::~TopSlideFrameWidget()
{}

HoveredFrame* TopSlideFrameWidget::getFrame() const
{
	return ui.frame_topslidemenu;
}

QLabel* TopSlideFrameWidget::getLabelProfile() const
{
	return ui.label_account_name;
}

QPushButton* TopSlideFrameWidget::getPushButtonSettings() const
{
	return ui.pushButton_settings;
}

QPushButton* TopSlideFrameWidget::getPushButtonAboutUs() const
{
	return ui.pushButton_aboutus;
}

QPushButton* TopSlideFrameWidget::getPushButtonNews() const
{
	return ui.pushButton_news;
}

QPushButton* TopSlideFrameWidget::getPushButtonServers() const
{
	return ui.pushButton_servers;
}

QPushButton* TopSlideFrameWidget::getPushButtonGame() const
{
	return ui.pushButton_game;
}

QLabel* TopSlideFrameWidget::getAccountIcon() const
{
	return ui.label_avatar_image;
}

QLabel* TopSlideFrameWidget::getCurrencyLabel() const
{
	return ui.label_currency_count;
}

QLabel* TopSlideFrameWidget::getCurrencyIconLabel() const
{
	return ui.label_currency_icon;
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

void TopSlideFrameWidget::swapLabelsCurrencyCountAndAccountName()
{
	QGridLayout* layout = qobject_cast<QGridLayout*>(ui.gridLayout);

	int index_name = layout->indexOf(ui.label_account_name);
	int index_count = layout->indexOf(ui.label_currency_count);
	int index_icon = layout->indexOf(ui.label_currency_icon);
	int index_spacer = layout->indexOf(ui.horizontalSpacerCurrency);

	int row_name, column_name, row_span_name, column_span_name;
	int row_count, column_count, row_span_count, column_span_count;
	int row_icon, column_icon, row_span_icon, column_span_icon;
	int row_spacer, column_spacer, row_span_spacer, column_span_spacer;

	layout->getItemPosition(index_name, &row_name, &column_name, &row_span_name, &column_span_name);
	layout->getItemPosition(index_count, &row_count, &column_count, &row_span_count, &column_span_count);
	layout->getItemPosition(index_icon, &row_icon, &column_icon, &row_span_icon, &column_span_icon);
	layout->getItemPosition(index_spacer, &row_spacer, &column_spacer, &row_span_spacer, &column_span_spacer);

	layout->takeAt(index_name);
	layout->takeAt(index_count);
	layout->takeAt(index_icon);
	layout->takeAt(index_spacer);

	layout->addWidget(ui.label_currency_count, row_name, 1, row_span_name, 1);
	layout->addWidget(ui.label_currency_icon, row_name, 0, row_span_name, 1);
	layout->addItem(ui.horizontalSpacerCurrency, row_name, 3, row_span_name, 1);
	layout->addWidget(ui.label_account_name, row_icon, column_icon, row_span_icon, 4);
}
