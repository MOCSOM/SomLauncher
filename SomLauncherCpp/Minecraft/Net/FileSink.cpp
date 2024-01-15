#include "FileSink.h"


Net::FileSink::FileSink(QString filename)
    :m_filename(filename)
{
}

JobStatus Net::FileSink::init(QNetworkRequest& request)
{
    auto result = initCache(request);
    if (result != Job_InProgress)
    {
        return result;
    }
    // create a new save file and open it for writing
    if (!std::filesystem::exists(this->m_filename.toStdWString()))
    {
        qCritical() << "Could not create folder for " + this->m_filename;
        return Job_Failed;
    }
    this->wroteAnyData = false;
    this->m_output_file.reset(new QSaveFile(this->m_filename));
    if (!this->m_output_file->open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not open " + this->m_filename + " for writing";
        return Job_Failed;
    }

    if (initAllValidators(request))
        return Job_InProgress;
    return Job_Failed;
}

JobStatus Net::FileSink::write(QByteArray& data)
{
    return Job_InProgress;
}

JobStatus Net::FileSink::abort()
{
    this->m_output_file->cancelWriting();
    failAllValidators();
    return Job_Failed;
}

JobStatus Net::FileSink::finalize(QNetworkReply& reply)
{
    bool gotFile = false;
    QVariant statusCodeV = reply.attribute(QNetworkRequest::HttpStatusCodeAttribute);
    bool validStatus = false;
    int statusCode = statusCodeV.toInt(&validStatus);
    if (validStatus)
    {
        // this leaves out 304 Not Modified
        gotFile = statusCode == 200 || statusCode == 203;
    }
    // if we wrote any data to the save file, we try to commit the data to the real file.
    // if it actually got a proper file, we write it even if it was empty
    if (gotFile || this->wroteAnyData)
    {
        // ask validators for data consistency
        // we only do this for actual downloads, not 'your data is still the same' cache hits
        if (!finalizeAllValidators(reply))
            return Job_Failed;
        // nothing went wrong...
        if (!this->m_output_file->commit())
        {
            qCritical() << "Failed to commit changes to " << this->m_filename;
            this->m_output_file->cancelWriting();
            return Job_Failed;
        }
    }
    // then get rid of the save file
    this->m_output_file.reset();

    return finalizeCache(reply);
}

bool Net::FileSink::hasLocalData()
{
    QFileInfo info(this->m_filename);
    return info.exists() && info.size() != 0;
}

JobStatus Net::FileSink::initCache(QNetworkRequest&)
{
    return Job_InProgress;
}

JobStatus Net::FileSink::finalizeCache(QNetworkReply& reply)
{
    return Job_Finished;
}