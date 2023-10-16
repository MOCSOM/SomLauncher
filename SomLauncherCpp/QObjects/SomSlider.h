#ifndef SOMSLIDER_H_
#define SOMSLIDER_H_

#include <qslider.h>
#include <QtWidgets>

class SomSlider : public QSlider
{
private:
	int pivotal_value = 0;

public:
	explicit SomSlider(QWidget* parent = nullptr);
	~SomSlider();

	void setPivotalValue(int new_value);

signals:

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
};

#endif /*SOMSLIDER_H_*/