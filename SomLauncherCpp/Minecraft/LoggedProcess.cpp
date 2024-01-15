#include "LoggedProcess.h"

QStringList reprocess(const QByteArray& data, QString& leftover)
{
    QString str = leftover + QString::fromLocal8Bit(data);

    str.remove('\r');
    QStringList lines = str.split("\n");
    leftover = lines.takeLast();
    return lines;
}

LoggedProcess::LoggedProcess(QObject* parent)
    : QProcess(parent)
{
    // QProcess has a strange interface... let's map a lot of those into a few.
    connect(this, &QProcess::readyReadStandardOutput, this, &LoggedProcess::on_stdOut);
    connect(this, &QProcess::readyReadStandardError, this, &LoggedProcess::on_stdErr);
    connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(on_exit(int, QProcess::ExitStatus)));
    connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(on_error(QProcess::ProcessError)));
    connect(this, &QProcess::stateChanged, this, &LoggedProcess::on_stateChange);
}

LoggedProcess::~LoggedProcess()
{
    if (this->m_is_detachable)
    {
        setProcessState(QProcess::NotRunning);
    }
}

LoggedProcess::State LoggedProcess::state() const
{
    return this->m_state;
}

int LoggedProcess::exitCode() const
{
    return this->m_exit_code;
}

qint64 LoggedProcess::processId() const
{
#ifdef Q_OS_WIN
    //std::this_thread::get_id();
    return getpid() ? getpid() : 0;
#else
    return getpid();
#endif
}

void LoggedProcess::setDetachable(bool detachable)
{
    this->m_is_detachable = detachable;
}

void LoggedProcess::kill()
{
    this->m_is_aborting = true;
    QProcess::kill();
}

void LoggedProcess::on_stdErr()
{
    auto lines = reprocess(readAllStandardError(), this->m_err_leftover);
    emit log(lines, MessageLevel::StdErr);
}

void LoggedProcess::on_stdOut()
{
    auto lines = reprocess(readAllStandardOutput(), this->m_out_leftover);
    emit log(lines, MessageLevel::StdOut);
}

void LoggedProcess::on_exit(int exit_code, QProcess::ExitStatus status)
{
    // save the exit code
    this->m_exit_code = exit_code;

    // Flush console window
    if (!this->m_err_leftover.isEmpty())
    {
        emit log({ this->m_err_leftover }, MessageLevel::StdErr);
        this->m_err_leftover.clear();
    }
    if (!this->m_out_leftover.isEmpty())
    {
        emit log({ this->m_err_leftover }, MessageLevel::StdOut);
        this->m_out_leftover.clear();
    }

    // based on state, send signals
    if (!this->m_is_aborting)
    {
        if (status == QProcess::NormalExit)
        {
            //: Message displayed on instance exit
            emit log({ tr("Process exited with exit code %1 (0x%2).").arg(exit_code).arg(exit_code, 0, 16) }, MessageLevel::Launcher);
            changeState(LoggedProcess::Finished);
        }
        else
        {
            //: Message displayed on instance crashed
            if (exit_code == -1)
                emit log({ tr("Process crashed.") }, MessageLevel::Launcher);
            else
                emit log({ tr("Process crashed with exit code %1 (0x%2).").arg(exit_code).arg(exit_code, 0, 16) }, MessageLevel::Launcher);
            changeState(LoggedProcess::Crashed);
        }

        // Filter out some exit codes, which would only result in erroneous output
        // -1, 0, 1 and 255 are usually program generated and don't aid much in debugging
        if ((exit_code < -1 || exit_code > 1) && (exit_code != 255))
        {
            // Gross hack for preserving the **exact bit pattern**, we need to "cast" while ignoring the sign bit
            unsigned int u_exit_code = *((unsigned int*)&exit_code);

            std::string statusName;
            std::string statusDescription;
            bool hasNameOrDescription = Sys::lookupSystemStatusCode(u_exit_code, statusName, statusDescription);
            if (hasNameOrDescription)
            {
                emit log({ tr("Below is an analysis of the exit code. THIS MAY BE INCORRECT AND SHOULD BE TAKEN WITH A GRAIN OF SALT!") }, MessageLevel::Launcher);

                if (!statusName.empty())
                {
                    emit log({ tr("System exit code name: %1").arg(QString::fromStdString(statusName)) }, MessageLevel::Launcher);
                }

                if (!statusDescription.empty())
                {
                    emit log({ tr("System exit code description: %1").arg(QString::fromStdString(statusDescription)) }, MessageLevel::Launcher);
                }
            }
        }

        emit log({ tr("Please note that usually neither the exit code, nor its description are enough to diagnose issues!") }, MessageLevel::Launcher);
        emit log({ tr("Always upload the entire log and not just the exit code.") }, MessageLevel::Launcher);
    }
    else
    {
        //: Message displayed after the instance exits due to kill request
        emit log({ tr("Process was killed by user.") }, MessageLevel::Error);
        changeState(LoggedProcess::Aborted);
    }
}

void LoggedProcess::on_error(QProcess::ProcessError error)
{
    switch (error)
    {
    case QProcess::FailedToStart:
    {
        emit log({ tr("The process failed to start.") }, MessageLevel::Fatal);
        changeState(LoggedProcess::FailedToStart);
        break;
    }
    // we'll just ignore those... never needed them
    case QProcess::Crashed:
    case QProcess::ReadError:
    case QProcess::Timedout:
    case QProcess::UnknownError:
    case QProcess::WriteError:
        break;
    }
}

void LoggedProcess::on_stateChange(QProcess::ProcessState state)
{
    switch (state)
    {
    case QProcess::NotRunning:
        break; // let's not - there are too many that handle this already.
    case QProcess::Starting:
    {
        if (this->m_state != LoggedProcess::NotRunning)
        {
            qWarning() << "Wrong state change for process from state" << this->m_state << "to" << (int)LoggedProcess::Starting;
        }
        changeState(LoggedProcess::Starting);
        return;
    }
    case QProcess::Running:
    {
        if (this->m_state != LoggedProcess::Starting)
        {
            qWarning() << "Wrong state change for process from state" << this->m_state << "to" << (int)LoggedProcess::Running;
        }
        changeState(LoggedProcess::Running);
        return;
    }
    }
}

void LoggedProcess::changeState(LoggedProcess::State state)
{
    if (state == this->m_state)
        return;
    this->m_state = state;
    emit stateChanged(this->m_state);
}