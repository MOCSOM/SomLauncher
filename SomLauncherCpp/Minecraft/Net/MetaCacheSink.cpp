#include "MetaCacheSink.h"

Net::MetaCacheSink::MetaCacheSink(MetaEntryPtr entry, ChecksumValidator* md5sum)
    :Net::FileSink(entry->getFullPath()), m_entry(entry), m_md5Node(md5sum)
{
    addValidator(md5sum);
}

bool Net::MetaCacheSink::hasLocalData()
{
    QFileInfo info(this->m_filename);
    return info.exists() && info.size() != 0;
}

JobStatus Net::MetaCacheSink::initCache(QNetworkRequest& request)
{
    if (!this->m_entry->isStale())
    {
        return Job_Finished;
    }
    // check if file exists, if it does, use its information for the request
    QFile current(this->m_filename);
    if (current.exists() && current.size() != 0)
    {
        if (this->m_entry->getRemoteChangedTimestamp().size())
        {
            request.setRawHeader(QString("If-Modified-Since").toLatin1(), this->m_entry->getRemoteChangedTimestamp().toLatin1());
        }
        if (this->m_entry->getETag().size())
        {
            request.setRawHeader(QString("If-None-Match").toLatin1(), this->m_entry->getETag().toLatin1());
        }
    }
    return Job_InProgress;
}

JobStatus Net::MetaCacheSink::finalizeCache(QNetworkReply& reply)
{
    QFileInfo output_file_info(this->m_filename);
    if (this->wroteAnyData)
    {
        this->m_entry->setMD5Sum(this->m_md5Node->hash().toHex().constData());
    }
    this->m_entry->setETag(reply.rawHeader("ETag").constData());
    if (reply.hasRawHeader("Last-Modified"))
    {
        this->m_entry->setRemoteChangedTimestamp(reply.rawHeader("Last-Modified").constData());
    }
    this->m_entry->setLocalChangedTimestamp(output_file_info.lastModified().toUTC().toMSecsSinceEpoch());
    this->m_entry->setStale(false);
    APPLICATION->metacache()->updateEntry(this->m_entry);
    return Job_Finished;
}

