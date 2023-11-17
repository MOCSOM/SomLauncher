#ifndef NEWSVIEWWIDGET_H_
#define NEWSVIEWWIDGET_H_

#include <qwidget.h>

#include "SingleNewsItemWidget.h"

#include "ui_NewsViewWidget.h"

class NewsViewWidget : public QWidget
{
	Q_OBJECT

public:
	NewsViewWidget(QWidget* parent = nullptr);
	~NewsViewWidget();

private:
	Ui::NewsViewWidgetClass ui;
};

#endif // !NEWSVIEWWIDGET_H_