#include "Task.h"

Task::Task(QObject* parent)
	: QObject(parent)
{
}

bool Task::isRunning() const
{
	return this->m_state == State::Running;
}

bool Task::isFinished() const
{
	return this->m_state != State::Running && this->m_state != State::Inactive;
}

bool Task::wasSuccessful() const
{
	return this->m_state == State::Succeeded;
}

QString Task::failReason() const
{
	return this->m_failReason;
}

QStringList Task::warnings() const
{
	return this->m_Warnings;
}

bool Task::canAbort() const
{
	return false;
}

const QString& Task::getStatus() const
{
	return this->m_status;
}

const qint64& Task::getProgress() const
{
	return this->m_progress;
}

const qint64& Task::getTotalProgress() const
{
	return this->m_progressTotal;
}

void Task::logWarning(const QString& line)
{
	qWarning() << line;
	this->m_Warnings.append(line);
}

QString Task::describe()
{
	QString outStr;
	QTextStream out(&outStr);
	out << metaObject()->className() << QChar('(');
	auto name = objectName();
	if (name.isEmpty())
	{
		out << QString("0x%1").arg((quintptr)this, 0, 16);
	}
	else
	{
		out << name;
	}
	out << QChar(')');
	out.flush();
	return outStr;
}

void Task::start()
{
	switch (this->m_state)
	{
	case State::Inactive:
	{
		qDebug() << "Task" << describe() << "starting for the first time";
		break;
	}
	case State::AbortedByUser:
	{
		qDebug() << "Task" << describe() << "restarting for after being aborted by user";
		break;
	}
	case State::Failed:
	{
		qDebug() << "Task" << describe() << "restarting for after failing at first";
		break;
	}
	case State::Succeeded:
	{
		qDebug() << "Task" << describe() << "restarting for after succeeding at first";
		break;
	}
	case State::Running:
	{
		qWarning() << "The launcher tried to start task" << describe() << "while it was already running!";
		return;
	}
	}
	// NOTE: only fall thorugh to here in end states
	this->m_state = State::Running;
	emit started();
	executeTask();
}

bool Task::abort()
{
	return false;
}

void Task::emitSucceeded()
{
	// Don't succeed twice.
	if (!isRunning())
	{
		qCritical() << "Task" << describe() << "succeeded while not running!!!!";
		return;
	}
	this->m_state = State::Succeeded;
	qDebug() << "Task" << describe() << "succeeded";
	emit succeeded();
	emit finished();
}

void Task::emitAborted()
{
	// Don't abort twice.
	if (!isRunning())
	{
		qCritical() << "Task" << describe() << "aborted while not running!!!!";
		return;
	}
	this->m_state = State::AbortedByUser;
	this->m_failReason = "Aborted.";
	qDebug() << "Task" << describe() << "aborted.";
	emit failed(this->m_failReason);
	emit finished();
}

void Task::emitFailed(QString reason)
{
	// Don't fail twice.
	if (!isRunning())
	{
		qCritical() << "Task" << describe() << "failed while not running!!!!: " << reason;
		return;
	}
	this->m_state = State::Failed;
	this->m_failReason = reason;
	qCritical() << "Task" << describe() << "failed: " << reason;
	emit failed(reason);
	emit finished();
}

void Task::setStatus(const QString& new_status)
{
	if (this->m_status != new_status)
	{
		this->m_status = new_status;
		emit status(this->m_status);
	}
}

void Task::setProgress(qint64 current, qint64 total)
{
	this->m_progress = current;
	this->m_progressTotal = total;
	emit progress(this->m_progress, this->m_progressTotal);
}
