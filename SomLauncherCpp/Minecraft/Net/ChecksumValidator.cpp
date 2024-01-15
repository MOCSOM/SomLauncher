#include "ChecksumValidator.h"

Net::ChecksumValidator::ChecksumValidator(QCryptographicHash::Algorithm algorithm, QByteArray expected)
    :m_checksum(algorithm), m_expected(expected)
{
}

bool Net::ChecksumValidator::init(QNetworkRequest&)
{
    this->m_checksum.reset();
    return true;
}

bool Net::ChecksumValidator::write(QByteArray& data)
{
    this->m_checksum.addData(data);
    return true;
}

bool Net::ChecksumValidator::abort()
{
    return true;
}

bool Net::ChecksumValidator::validate(QNetworkReply&)
{
    if (this->m_expected.size() && this->m_expected != hash())
    {
        qWarning() << "Checksum mismatch, download is bad.";
        return false;
    }
    return true;
}

QByteArray Net::ChecksumValidator::hash()
{
    return this->m_checksum.result();
}

void Net::ChecksumValidator::setExpected(QByteArray expected)
{
    this->m_expected = expected;
}