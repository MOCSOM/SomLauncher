#ifndef NET_BYTEARRAY_SINK_H_
#define NET_BYTEARRAY_SINK_H_

#include "Sink.h"

namespace Net 
{
    /*
     * Sink object for downloads that uses an external QByteArray it doesn't own as a target.
     */
    class ByteArraySink : public Sink
    {
    private:
        QByteArray* m_output;

    public:
        ByteArraySink(QByteArray* output);
        virtual ~ByteArraySink() = default;

    public:
        JobStatus init(QNetworkRequest& request) override;
        JobStatus write(QByteArray& data) override;
        JobStatus abort() override;
        JobStatus finalize(QNetworkReply& reply) override;
        bool hasLocalData() override;
    };
}

#endif // !NET_BYTEARRAY_SINK_H_