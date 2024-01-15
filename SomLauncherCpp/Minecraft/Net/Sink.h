#ifndef NET_SLINK_H_
#define NET_SLINK_H_

#include "NetAction.h"

#include "Validator.h"

namespace Net 
{
    class Sink
    {
    protected: /* data */
        std::vector<std::shared_ptr<Validator>> validators;

    public: /* con/des */
        Sink() = default;
        virtual ~Sink() = default;

    public: /* methods */
        virtual JobStatus init(QNetworkRequest& request) = 0;
        virtual JobStatus write(QByteArray& data) = 0;
        virtual JobStatus abort() = 0;
        virtual JobStatus finalize(QNetworkReply& reply) = 0;
        virtual bool hasLocalData() = 0;

        void addValidator(Validator* validator);

    protected: /* methods */
        bool finalizeAllValidators(QNetworkReply& reply);
        bool failAllValidators();
        bool initAllValidators(QNetworkRequest& request);
        bool writeAllValidators(QByteArray& data);
    };
}

#endif // !NET_SLINK_H_