#include "AccountTask.h"

AccountTask::AccountTask(AccountData* data, QObject* parent)
    : Task(parent), m_data(data)
{
    changeState(AccountTaskState::STATE_CREATED);
}

AccountTaskState AccountTask::taskState() const
{
    return this->m_taskState;
}

QString AccountTask::getStateMessage() const
{
    switch (this->m_taskState)
    {
    case AccountTaskState::STATE_CREATED:
        return "Waiting...";
    case AccountTaskState::STATE_WORKING:
        return tr("Sending request to auth servers...");
    case AccountTaskState::STATE_SUCCEEDED:
        return tr("Authentication task succeeded.");
    case AccountTaskState::STATE_OFFLINE:
        return tr("Failed to contact the authentication server.");
    case AccountTaskState::STATE_FAILED_SOFT:
        return tr("Encountered an error during authentication.");
    case AccountTaskState::STATE_FAILED_MUST_MIGRATE:
        return tr("Failed to authenticate. The account must be migrated to a Microsoft account to be usable.");
    case AccountTaskState::STATE_FAILED_HARD:
        return tr("Failed to authenticate. The session has expired.");
    case AccountTaskState::STATE_FAILED_GONE:
        return tr("Failed to authenticate. The account no longer exists.");
    default:
        return tr("...");
    }
}

bool AccountTask::changeState(AccountTaskState newState, QString reason)
{
    this->m_taskState = newState;
    setStatus(getStateMessage());
    switch (newState) 
    {
    case AccountTaskState::STATE_CREATED: 
    {
        this->m_data->error_string.clear();
        return true;
    }
    case AccountTaskState::STATE_WORKING: 
    {
        this->m_data->account_state = AccountState::Working;
        return true;
    }
    case AccountTaskState::STATE_SUCCEEDED: 
    {
        this->m_data->account_state = AccountState::Online;
        emitSucceeded();
        return false;
    }
    case AccountTaskState::STATE_OFFLINE: 
    {
        this->m_data->error_string = reason;
        this->m_data->account_state = AccountState::Offline;
        emitFailed(reason);
        return false;
    }
    case AccountTaskState::STATE_FAILED_SOFT: 
    {
        this->m_data->error_string = reason;
        this->m_data->account_state = AccountState::Errored;
        emitFailed(reason);
        return false;
    }
    case AccountTaskState::STATE_FAILED_MUST_MIGRATE: 
    {
        this->m_data->error_string = reason;
        this->m_data->account_state = AccountState::MustMigrate;
        emitFailed(reason);
        return false;
    }
    case AccountTaskState::STATE_FAILED_HARD: 
    {
        this->m_data->error_string = reason;
        this->m_data->account_state = AccountState::Expired;
        emitFailed(reason);
        return false;
    }
    case AccountTaskState::STATE_FAILED_GONE: 
    {
        this->m_data->error_string = reason;
        this->m_data->account_state = AccountState::Gone;
        emitFailed(reason);
        return false;
    }
    default: 
    {
        QString error = tr("Unknown account task state: %1").arg(int(newState));
        this->m_data->account_state = AccountState::Errored;
        emitFailed(error);
        return false;
    }
    }
}
