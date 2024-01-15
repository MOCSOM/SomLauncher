#include "NetAction.h"

NetAction::NetAction()
	: QObject(nullptr) 
{
}

bool NetAction::isRunning() const
{
    return this->m_status == Job_InProgress;
}

bool NetAction::isFinished() const
{
    return this->m_status >= Job_Finished;
}

bool NetAction::wasSuccessful() const
{
    return this->m_status == Job_Finished || this->m_status == Job_Failed_Proceed;
}

qint64 NetAction::totalProgress() const
{
    return this->m_total_progress;
}

qint64 NetAction::currentProgress() const
{
    return this->m_progress;
}

bool NetAction::abort()
{
    return false;
}

bool NetAction::canAbort()
{
    return false;
}

QUrl NetAction::url() const
{
    return this->m_url;
}

void NetAction::start(std::shared_ptr<QNetworkAccessManager> network)
{
    this->m_network = network;
    startImpl();
}