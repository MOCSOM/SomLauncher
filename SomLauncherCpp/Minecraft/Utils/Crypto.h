#ifndef UTILS_CRYPTO_H_
#define UTILS_CRYPTO_H_

#include <QString>
#include <QFile>
#include <QCryptographicHash>

namespace crypto
{
	QString sha1(QFile& file);
	QString sha1(const QByteArray& data);

	QString md5(const QString& from);
};

#endif // !UTILS_CRYPTO_H_