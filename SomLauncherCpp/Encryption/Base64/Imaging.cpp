#include "Imaging.h"

std::shared_ptr<QPixmap> loadQPixmapFromBase64(QByteArray text)
{
	std::shared_ptr<QPixmap> image = std::make_shared<QPixmap>();
	if (!image->loadFromData(QByteArray::fromBase64(text)))
	{
		throw std::invalid_argument("Argument must be base64 without starting base64 text");
	}
	return image;
}
