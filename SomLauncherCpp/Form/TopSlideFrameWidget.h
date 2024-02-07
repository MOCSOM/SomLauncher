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

	HoveredFrame* getFrame() const;
	QLabel* getLabelProfile() const;
	QPushButton* getPushButtonSettings() const;
	QPushButton* getPushButtonAboutUs() const;
	QPushButton* getPushButtonNews() const;
	QPushButton* getPushButtonServers() const;
	QPushButton* getPushButtonGame() const;

	void setMainButtonsTextAlightButtom();
	void setMainButtonsTextAlightCenter();

	void changeLabelsCurrencyCountAndAccountName();

private:
	Ui::TopSlideFrameWidget ui;
};

#endif /*!TOPSLIDEFRAMEWIDGET_H_*/