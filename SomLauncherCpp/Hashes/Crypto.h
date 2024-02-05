#ifndef HASHES_CRYPTO_H_
#define HASHES_CRYPTO_H_

#include <QString>
#include <QFile>
#include <QCryptographicHash>
#include <QFileDialog>

namespace crypto
{
	QString sha1(QFile& file);
	QString sha1(const QByteArray& data);

	QString md5(const QString& from);
};

#endif // !HASHES_CRYPTO_H_
