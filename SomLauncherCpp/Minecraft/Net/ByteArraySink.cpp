#include "ByteArraySink.h"

Net::ByteArraySink::ByteArraySink(QByteArray* output)
    :m_output(output)
{
}

JobStatus Net::ByteArraySink::init(QNetworkRequest& request)
{
    this->m_output->clear();
    if (initAllValidators(request))
        return Job_InProgress;
    return Job_Failed;
}

JobStatus Net::ByteArraySink::write(QByteArray& data)
{
    this->m_output->append(data);
    if (writeAllValidators(data))
        return Job_InProgress;
    return Job_Failed;
}

JobStatus Net::ByteArraySink::abort()
{
    this->m_output->clear();
    failAllValidators();
    return Job_Failed;
}

JobStatus Net::ByteArraySink::finalize(QNetworkReply& reply)
{
    if (finalizeAllValidators(reply))
        return Job_Finished;
    return Job_Failed;
}

bool Net::ByteArraySink::hasLocalData()
{
    return false;
}
