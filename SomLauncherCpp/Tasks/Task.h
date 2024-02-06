#ifndef TASKS_TASK_H_
#define TASKS_TASK_H_

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "../QObjects/QObjectPtr.h"

class Task : public QObject
{
	Q_OBJECT

public:
	using Ptr = shared_qobject_ptr<Task>;

	enum class State
	{
		Inactive,
		Running,
		Succeeded,
		Failed,
		AbortedByUser
	};

public:
	explicit Task(QObject* parent = nullptr);
	virtual ~Task() = default;

	bool isRunning() const;
	bool isFinished() const;
	bool wasSuccessful() const;

	/*!
	 * Returns the string that was passed to emitFailed as the error message when the task failed.
	 * If the task hasn't failed, returns an empty string.
	 */
	QString failReason() const;

	virtual QStringList warnings() const;

	virtual bool canAbort() const { return false; }

	QString getStatus()
	{
		return m_status;
	}

	qint64 getProgress() const
	{
		return m_progress;
	}

	qint64 getTotalProgress() const
	{
		return m_progressTotal;
	}

protected:
	void logWarning(const QString& line);

private:
	QString describe();

signals:
	void started();
signals:
	void progress(qint64 current, qint64 total);
signals:
	void finished();
signals:
	void succeeded();
signals:
	void failed(QString reason);
signals:
	void status(QString status);

public slots:
	virtual void start();
	virtual bool abort() { return false; };

protected:
	virtual void executeTask() = 0;

protected slots:
	virtual void emitSucceeded();
	virtual void emitAborted();
	virtual void emitFailed(QString reason);

public slots:
	void setStatus(const QString& status);
public slots:
	void setProgress(qint64 current, qint64 total);

private:
	State m_state = State::Inactive;
	QStringList m_Warnings;
	QString m_failReason = "";
	QString m_status;
	int m_progress = 0;
	int m_progressTotal = 100;
};

#endif // !TASKS_TASK_H_
