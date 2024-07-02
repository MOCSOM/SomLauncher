#ifndef IMAGING_H_
#define IMAGING_H_

#include <QPixmap>

#include <memory>
#include <exception>
#include <stdexcept>

std::shared_ptr<QPixmap> loadQPixmapFromBase64(QByteArray text);

#endif // !IMAGING_H_
