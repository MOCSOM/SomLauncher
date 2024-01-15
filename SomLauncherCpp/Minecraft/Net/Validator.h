#ifndef NET_VALIDATOR_H_
#define NET_VALIDATOR_H_

#include "NetAction.h"

namespace Net 
{
    class Validator
    {
    public: /* con/des */
        Validator() = default;
        virtual ~Validator() = default;

    public: /* methods */
        virtual bool init(QNetworkRequest& request) = 0;
        virtual bool write(QByteArray& data) = 0;
        virtual bool abort() = 0;
        virtual bool validate(QNetworkReply& reply) = 0;
    };
}

#endif // !NET_VALIDATOR_H_
