#include "HoveredFrame.h"

HoveredFrame::HoveredFrame(QWidget* parent, Qt::WindowFlags f)
    : QFrame(parent) {
    setAttribute(Qt::WA_Hover);
}

HoveredFrame::~HoveredFrame() {}

void HoveredFrame::enterEvent(QEvent* e)
{
    qDebug() << Q_FUNC_INFO << e->type();
}

void HoveredFrame::leaveEvent(QEvent* e)
{
    //qDebug() << Q_FUNC_INFO << e->type();
}


bool HoveredFrame::event(QEvent* e)
{
    
    switch (e->type())
    {
    case QEvent::HoverEnter:
        emit Enter();
        //hoverEnter(reinterpret_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverLeave:
        emit Leave();
        //hoverLeave(reinterpret_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverMove:
        //hoverMove(reinterpret_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void HoveredFrame::hoverEnter(QHoverEvent* event)
{
    qDebug() << Q_FUNC_INFO << event;
}

void HoveredFrame::hoverLeave(QHoverEvent* event)
{
    qDebug() << Q_FUNC_INFO << event;
}

void HoveredFrame::hoverMove(QHoverEvent* event)
{
    qDebug() << Q_FUNC_INFO << event;
}

