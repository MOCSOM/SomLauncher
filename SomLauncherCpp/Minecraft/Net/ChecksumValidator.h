#ifndef NET_CHECKSUMVALIDATOR_H_
#define NET_CHECKSUMVALIDATOR_H_

#include <QCryptographicHash>
#include <QFile>

#include <memory>

#include "Validator.h"

namespace Net 
{
    class ChecksumValidator : public Validator
    {
    private: /* data */
        QCryptographicHash m_checksum;
        QByteArray m_expected;

    public: /* con/des */
        ChecksumValidator(QCryptographicHash::Algorithm algorithm, QByteArray expected = QByteArray());
        virtual ~ChecksumValidator() = default;

    public: /* methods */
        bool init(QNetworkRequest&) override;
        bool write(QByteArray& data) override;
        bool abort() override;
        bool validate(QNetworkReply&) override;
        QByteArray hash();
        void setExpected(QByteArray expected);
    };
}

#endif // !NET_CHECKSUMVALIDATOR_H_
