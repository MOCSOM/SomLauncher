#include "AuthFlow.h"

AuthFlow::AuthFlow(AccountData* data, QObject* parent)
	: AccountTask(data, parent)
{
}

Katabasis::Validity AuthFlow::validity()
{
    return this->m_data->validity_;
}

QString AuthFlow::getStateMessage() const
{
    switch (this->m_taskState)
    {
    case AccountTaskState::STATE_WORKING: 
    {
        if (this->m_currentStep)
        {
            return this->m_currentStep->describe();
        }
        else 
        {
            return tr("Working...");
        }
    }
    default: 
    {
        return AccountTask::getStateMessage();
    }
    }
}

void AuthFlow::executeTask()
{
    if (this->m_currentStep)
    {
        return;
    }
    changeState(AccountTaskState::STATE_WORKING, tr("Initializing"));
    nextStep();
}

void AuthFlow::stepFinished(AccountTaskState resultingState, QString message)
{
    if (changeState(resultingState, message)) 
    {
        nextStep();
    }
}

void AuthFlow::succeed()
{
    this->m_data->validity_ = Katabasis::Validity::Certain;
    changeState(
        AccountTaskState::STATE_SUCCEEDED,
        tr("Finished all authentication steps")
    );
}

void AuthFlow::nextStep()
{
    if (this->m_steps.size() == 0)
    {
        // we got to the end without an incident... assume this is all.
        this->m_currentStep.reset();
        succeed();
        return;
    }
    this->m_currentStep = this->m_steps.front();
    qDebug() << "AuthFlow:" << this->m_currentStep->describe();
    this->m_steps.pop_front();
    connect(this->m_currentStep.get(), &AuthStep::finished, this, &AuthFlow::stepFinished);
    connect(this->m_currentStep.get(), &AuthStep::showVerificationUriAndCode, this, &AuthFlow::showVerificationUriAndCode);
    connect(this->m_currentStep.get(), &AuthStep::hideVerificationUriAndCode, this, &AuthFlow::hideVerificationUriAndCode);

    this->m_currentStep->perform();
}
