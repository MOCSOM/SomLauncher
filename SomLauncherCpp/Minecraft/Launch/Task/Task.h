#ifndef TASK_TASK_H_
#define TASK_TASK_H_

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "memory"

class Task : public QObject
{
	Q_OBJECT

public:
	using Ptr = std::shared_ptr<Task>;

	enum class State
	{
		Inactive,
		Running,
		Succeeded,
		Failed,
		AbortedByUser
	};

private:
	State m_state = State::Inactive;
	QStringList m_Warnings;
	QString m_failReason = "";
	QString m_status = "";
	int m_progress = 0;
	int m_progressTotal = 100;

public:
	explicit Task(QObject* parent = 0);
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
	virtual bool canAbort() const;

	const QString& getStatus() const;
	const qint64& getProgress() const;
	const qint64& getTotalProgress() const;

protected:
	void logWarning(const QString& line);

private:
	QString describe();

signals:
	void started();
	void progress(qint64 current, qint64 total);
	void finished();
	void succeeded();
	void failed(QString reason);
	void status(QString status);

public slots:
	virtual void start();
	virtual bool abort();

protected:
	virtual void executeTask() = 0;

protected slots:
	virtual void emitSucceeded();
	virtual void emitAborted();
	virtual void emitFailed(QString reason);

public slots:
	void setStatus(const QString& status);
	void setProgress(qint64 current, qint64 total);
};

#endif // !TASK_TASK_H_