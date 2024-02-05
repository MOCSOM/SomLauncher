#include "Crypto.h"

QString crypto::sha1(QFile& file)
{
	QCryptographicHash hash(QCryptographicHash::Sha1);
	file.open(QFile::ReadOnly);
	hash.addData(&file);
	file.close();

	return hash.result().toHex();
}

QString crypto::sha1(const QByteArray& data)
{
	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(data);

	return hash.result().toHex();
}

QString crypto::md5(const QString& from)
{
	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(from.toLatin1());

	return hash.result().toHex();
}