#include "Download.h"

Net::Download::Download()
{
    this->m_status = Job_NotStarted;
}

Net::Download::Ptr Net::Download::makeCached(QUrl url, MetaEntryPtr entry, Options options)
{
    std::shared_ptr<Download> dl = std::make_shared<Download>();
    dl->m_url = url;
    dl->m_options = options;
    auto md5Node = std::make_shared<ChecksumValidator>(QCryptographicHash::Md5);
    auto cachedNode = std::make_shared<MetaCacheSink>(entry, md5Node.get());
    dl->m_sink.reset(cachedNode.get());
    dl->m_target_path = entry->getFullPath();
    return dl;
}

Net::Download::Ptr Net::Download::makeByteArray(QUrl url, QByteArray* output, Options options)
{
    std::shared_ptr<Download> dl = std::make_shared<Download>();
    dl->m_url = url;
    dl->m_options = options;
    dl->m_sink.reset(std::make_shared<ByteArraySink>(output).get());
    return dl;
}

Net::Download::Ptr Net::Download::makeFile(QUrl url, QString path, Options options)
{
    std::shared_ptr<Download> dl = std::make_shared<Download>();
    dl->m_url = url;
    dl->m_options = options;
    dl->m_sink.reset(std::make_shared<FileSink>(path).get());
    return dl;
}

QString Net::Download::getTargetFilepath()
{
    return this->m_target_path;
}

void Net::Download::addValidator(Validator* v)
{
    this->m_sink->addValidator(v);
}

bool Net::Download::abort()
{
    if (this->m_reply)
    {
        this->m_reply->abort();
    }
    else
    {
        this->m_status = Job_Aborted;
    }
    return true;
}

bool Net::Download::canAbort()
{
    return true;
}

bool Net::Download::handleRedirect()
{
    QUrl redirect = this->m_reply->header(QNetworkRequest::LocationHeader).toUrl();
    if (!redirect.isValid())
    {
        if (!this->m_reply->hasRawHeader("Location"))
        {
            // no redirect -> it's fine to continue
            return false;
        }
        // there is a Location header, but it's not correct. we need to apply some workarounds...
        QByteArray redirectBA = this->m_reply->rawHeader("Location");
        if (redirectBA.size() == 0)
        {
            // empty, yet present redirect header? WTF?
            return false;
        }
        QString redirectStr = QString::fromUtf8(redirectBA);

        if (redirectStr.startsWith("//"))
        {
            /*
             * IF the URL begins with //, we need to insert the URL scheme.
             * See: https://bugreports.qt.io/browse/QTBUG-41061
             * See: http://tools.ietf.org/html/rfc3986#section-4.2
             */
            redirectStr = this->m_reply->url().scheme() + ":" + redirectStr;
        }
        else if (redirectStr.startsWith("/"))
        {
            /*
             * IF the URL begins with /, we need to process it as a relative URL
             */
            auto url = this->m_reply->url();
            url.setPath(redirectStr, QUrl::TolerantMode);
            redirectStr = url.toString();
        }

        /*
         * Next, make sure the URL is parsed in tolerant mode. Qt doesn't parse the location header in tolerant mode, which causes issues.
         * FIXME: report Qt bug for this
         */
        redirect = QUrl(redirectStr, QUrl::TolerantMode);
        if (!redirect.isValid())
        {
            qWarning() << "Failed to parse redirect URL:" << redirectStr;
            downloadError(QNetworkReply::ProtocolFailure);
            return false;
        }
        qDebug() << "Fixed location header:" << redirect;
    }
    else
    {
        qDebug() << "Location header:" << redirect;
    }

    this->m_url = QUrl(redirect.toString());
    qDebug() << "Following redirect to " << m_url.toString();
    start(this->m_network);
    return true;
}

void Net::Download::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    this->m_total_progress = bytesTotal;
    this->m_progress = bytesReceived;
    emit netActionProgress(this->m_index_within_job, bytesReceived, bytesTotal);
}

void Net::Download::downloadError(QNetworkReply::NetworkError error)
{
    if (error == QNetworkReply::OperationCanceledError)
    {
        qCritical() << "Aborted " << m_url.toString();
        this->m_status = Job_Aborted;
    }
    else
    {
        if (this->m_options & Option::AcceptLocalFiles)
        {
            if (this->m_sink->hasLocalData())
            {
                this->m_status = Job_Failed_Proceed;
                return;
            }
        }
        // error happened during download.
        qCritical() << "Failed " << this->m_url.toString() << " with reason " << error;
        this->m_status = Job_Failed;
    }
}

void Net::Download::sslErrors(const QList<QSslError>& errors) const
{
    int i = 1;
    for (auto& error : errors)
    {
        qCritical() << "Download" << this->m_url.toString() << "SSL Error #" << i << " : " << error.errorString();
        auto cert = error.certificate();
        qCritical() << "Certificate in question:\n" << cert.toText();
        i++;
    }
}

void Net::Download::downloadFinished()
{
    // handle HTTP redirection first
    if (handleRedirect())
    {
        qDebug() << "Download redirected:" << this->m_url.toString();
        return;
    }

    // if the download failed before this point ...
    if (this->m_status == Job_Failed_Proceed)
    {
        qDebug() << "Download failed but we are allowed to proceed:" << this->m_url.toString();
        this->m_sink->abort();
        this->m_reply.reset();
        emit succeeded(this->m_index_within_job);
        return;
    }
    else if (this->m_status == Job_Failed)
    {
        qDebug() << "Download failed in previous step:" << this->m_url.toString();
        this->m_sink->abort();
        this->m_reply.reset();
        emit failed(this->m_index_within_job);
        return;
    }
    else if (this->m_status == Job_Aborted)
    {
        qDebug() << "Download aborted in previous step:" << m_url.toString();
        this->m_sink->abort();
        this->m_reply.reset();
        emit aborted(this->m_index_within_job);
        return;
    }

    // make sure we got all the remaining data, if any
    auto data = this->m_reply->readAll();
    if (data.size())
    {
        qDebug() << "Writing extra" << data.size() << "bytes to" << this->m_target_path;
        this->m_status = this->m_sink->write(data);
    }

    // otherwise, finalize the whole graph
    this->m_status = this->m_sink->finalize(*this->m_reply.get());
    if (this->m_status != Job_Finished)
    {
        qDebug() << "Download failed to finalize:" << m_url.toString();
        this->m_sink->abort();
        this->m_reply.reset();
        emit failed(this->m_index_within_job);
        return;
    }
    this->m_reply.reset();
    qDebug() << "Download succeeded:" << m_url.toString();
    emit succeeded(this->m_index_within_job);
}

void Net::Download::downloadReadyRead()
{
    if (this->m_status == Job_InProgress)
    {
        auto data = this->m_reply->readAll();
        this->m_status = this->m_sink->write(data);
        if (this->m_status == Job_Failed)
        {
            qCritical() << "Failed to process response chunk for " << this->m_target_path;
        }
        // qDebug() << "Download" << m_url.toString() << "gained" << data.size() << "bytes";
    }
    else
    {
        qCritical() << "Cannot write to " << this->m_target_path << ", illegal status" << this->m_status;
    }
}

void Net::Download::startImpl()
{
    if (this->m_status == Job_Aborted)
    {
        qWarning() << "Attempt to start an aborted Download:" << this->m_url.toString();
        emit aborted(this->m_index_within_job);
        return;
    }
    QNetworkRequest request(this->m_url);
    this->m_status = this->m_sink->init(request);
    switch (this->m_status)
    {
    case Job_Finished:
        emit succeeded(this->m_index_within_job);
        qDebug() << "Download cache hit " << this->m_url.toString();
        return;
    case Job_InProgress:
        qDebug() << "Downloading " << this->m_url.toString();
        break;
    case Job_Failed_Proceed: // this is meaningless in this context. We do need a sink.
    case Job_NotStarted:
    case Job_Failed:
        emit failed(this->m_index_within_job);
        return;
    case Job_Aborted:
        return;
    }

    request.setHeader(QNetworkRequest::UserAgentHeader, BuildConfig.USER_AGENT);

    QNetworkReply* rep = this->m_network->get(request);

    this->m_reply.reset(rep);
    connect(rep, SIGNAL(downloadProgress(qint64, qint64)), SLOT(downloadProgress(qint64, qint64)));
    connect(rep, SIGNAL(finished()), SLOT(downloadFinished()));
    connect(rep, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(downloadError(QNetworkReply::NetworkError)));
    connect(rep, &QNetworkReply::sslErrors, this, &Download::sslErrors);
    connect(rep, &QNetworkReply::readyRead, this, &Download::downloadReadyRead);
}


