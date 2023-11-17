#ifndef SINGLENEWSITEMWIDGET_H_
#define SINGLENEWSITEMWIDGET_H_

#include <qwidget.h>

#include "ui_SingleNewsItemWidget.h"

class SingleNewsItemWidget : public QWidget
{
	Q_OBJECT

public:
	SingleNewsItemWidget(QWidget* parent = nullptr);
	~SingleNewsItemWidget();

private:
	Ui::SingleNewsItemWidgetClass ui;
};

#endif // !SINGLENEWSITEMWIDGET_H_