#include "ImageEditing.h"

QImage applyEffectToImage(QImage src, QGraphicsEffect* effect, int extent)
{
	if (src.isNull()) return QImage();   //No need to do anything else!
	if (!effect) return src;             //No need to do anything else!
	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	item.setPixmap(QPixmap::fromImage(src));
	item.setGraphicsEffect(effect);
	scene.addItem(&item);
	QImage res(src.size() + QSize(extent * 2, extent * 2), QImage::Format_ARGB32);
	res.fill(Qt::transparent);
	QPainter ptr(&res);
	scene.render(&ptr, QRectF(), QRectF(-extent, -extent, src.width() + extent * 2, src.height() + extent * 2));
	return res;
}