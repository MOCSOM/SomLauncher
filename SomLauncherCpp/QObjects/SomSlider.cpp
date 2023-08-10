#include "SomSlider.h"

SomSlider::SomSlider(QWidget* parent)
	: QSlider(parent)
{
}

SomSlider::~SomSlider()
{
}

void SomSlider::mousePressEvent(QMouseEvent* event)
{
    int tickInterval = this->tickInterval();
    int newValue = this->minimum() + ((event->x() * (this->maximum() - this->minimum())) / this->width());

    if (tickInterval > 0) 
    {
        newValue = this->minimum() + ((newValue - this->minimum()) / tickInterval) * tickInterval;
    }

    this->setValue(newValue);
    event->accept();
}

void SomSlider::mouseMoveEvent(QMouseEvent* event)
{
    int tickInterval = this->tickInterval();
    int newValue = this->minimum() + ((event->x() * (this->maximum() - this->minimum())) / this->width());

    if (tickInterval > 0)
    {
        newValue = this->minimum() + ((newValue - this->minimum()) / tickInterval) * tickInterval;
    }

    this->setValue(newValue);
    event->accept();
}

void SomSlider::paintEvent(QPaintEvent* event)
{
    QSlider::paintEvent(event);
    QPainter painter(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QRect grooveRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    int val = this->pivotal_value - minimum();
    int totalRange = maximum() - minimum();
    int sliderWidth = width();

    // Calculate positions for red and green segments
    int grooveLeft = grooveRect.left();
    int grooveRight = grooveRect.right();
    int midPosition = ((val * sliderWidth) / totalRange) + handleRect.width() / 2;
    int redSegmentRight = midPosition;
    int greenSegmentLeft = midPosition;

    // Draw red part
    QRect redRect(grooveLeft, grooveRect.height(), redSegmentRight - grooveLeft, grooveRect.height());
    QColor redColor = Qt::red;
    redColor.setAlphaF(0.2);
    painter.fillRect(redRect, redColor);

    // Draw green part
    QRect greenRect(greenSegmentLeft, grooveRect.height(), grooveRight - greenSegmentLeft, grooveRect.height());
    QColor greenColor = Qt::green;
    greenColor.setAlphaF(0.2);
    painter.fillRect(greenRect, greenColor);
}

void SomSlider::setPivotalValue(int new_value)
{
    this->pivotal_value = new_value;
}
