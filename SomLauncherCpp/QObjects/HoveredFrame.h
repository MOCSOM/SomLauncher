#ifndef HOVEREDFRAME_H_     // equivalently, #if !defined HEADER_H_
#define HOVEREDFRAME_H_

//#include <qframe.h>
#include <QtWidgets/qframe.h>


class HoveredFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HoveredFrame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~HoveredFrame();
};

#endif /*HOVEREDFRAME_H_*/