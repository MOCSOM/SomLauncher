#ifndef TOPSLIDEFRAMEWIDGET_H_
#define TOPSLIDEFRAMEWIDGET_H_

#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>

#include "../QObjects/HoveredFrame.h"
#include "../QObjects/ClickableLabel.h"

#include "ui_TopSlideFrameWidget.h"

class TopSlideFrameWidget : public QWidget
{
	Q_OBJECT

public:
	TopSlideFrameWidget(QWidget* parent = nullptr);
	~TopSlideFrameWidget();

	HoveredFrame* getFrame();
	QLabel* getLabelProfile();
	QPushButton* getPushButtonSettings();
	QPushButton* getPushButtonAboutUs();
	QPushButton* getPushButtonNews();
	QPushButton* getPushButtonServers();
	QPushButton* getPushButtonGame();

	void setMainButtonsTextAlightButtom();
	void setMainButtonsTextAlightCenter();

	void changeLabelsCurrencyCountAndAccountName();

private:
	Ui::TopSlideFrameWidget ui;
};

#endif /*!TOPSLIDEFRAMEWIDGET_H_*/