#include "JavaCheckerJob.h"

JavaCheckerJob::JavaCheckerJob(QString job_name)
	: Task(), m_job_name(job_name) 
{
}

bool JavaCheckerJob::addJavaCheckerAction(JavaCheckerPtr base)
{
    this->javacheckers.append(base);
    // if this is already running, the action needs to be started right away!
    if (isRunning())
    {
        setProgress(this->num_finished, this->javacheckers.size());
        connect(base.get(), &JavaChecker::checkFinished, this, &JavaCheckerJob::partFinished);
        base->performCheck();
    }
    return true;
}

QList<JavaCheckResult> JavaCheckerJob::getResults()
{
    return javaresults;
}

void JavaCheckerJob::partFinished(JavaCheckResult result)
{
    ++this->num_finished;
    qDebug() << this->m_job_name.toLocal8Bit() << "progress:" << this->num_finished << "/"
        << this->javacheckers.size();
    setProgress(this->num_finished, this->javacheckers.size());

    this->javaresults.replace(result.id, result);

    if (this->num_finished == this->javacheckers.size())
    {
        emitSucceeded();
    }
}

void JavaCheckerJob::executeTask()
{
    qDebug() << this->m_job_name.toLocal8Bit() << " started.";
    for (auto& iter : this->javacheckers)
    {
        this->javaresults.append(JavaCheckResult());
        connect(iter.get(), SIGNAL(checkFinished(JavaCheckResult)), SLOT(partFinished(JavaCheckResult)));
        iter->performCheck();
    }
}