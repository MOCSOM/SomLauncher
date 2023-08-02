#ifndef HOVEREDFRAME_H_     // equivalently, #if !defined HEADER_H_
#define HOVEREDFRAME_H_

//#include <qframe.h>
#include <QtWidgets/qframe.h>
#include <QEvent>


class HoveredFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HoveredFrame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~HoveredFrame();

protected:
    void leaveEvent(QEvent* e);
    void enterEvent(QEvent* e);
    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    void hoverMove(QHoverEvent* event);
    bool event(QEvent* e);

Q_SIGNALS:
    void Enter();
    void Leave();

};

#endif /*HOVEREDFRAME_H_*/