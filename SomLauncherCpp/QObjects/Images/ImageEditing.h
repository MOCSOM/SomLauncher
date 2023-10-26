#ifndef IMAGEEDITING_H_
#define IMAGEEDITING_H_

#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <qgraphicseffect.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qgraphicsitem.h>

QImage applyEffectToImage(QImage src, QGraphicsEffect* effect, int extent = 0);

#endif /*!IMAGEEDITING_H_*/