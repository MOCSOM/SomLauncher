#ifndef LAUNCH_LAUNCHTASK_H_
#define LAUNCH_LAUNCHTASK_H_

#include <QProcess>

#include <memory>

#include "LogModel.h"
#include "../BaseInstance.h"
#include "../MessageLevel.h"
#include "../LoggedProcess.h"
#include "../Launch/LaunchStep.h"
#include "Task/Task.h"
#include "../QObjectPtr.h"

class LaunchTask : public Task
{
	Q_OBJECT

public:
	enum State
	{
		NotStarted,
		Running,
		Waiting,
		Failed,
		Aborted,
		Finished
	};

protected: /* data */
	InstancePtr m_instance;
	shared_qobject_ptr<LogModel> m_logModel;
	QList<shared_qobject_ptr<LaunchStep>> m_steps;
	QMap<QString, QString> m_censorFilter;
	int currentStep = -1;
	State state = State::NotStarted;
	qint64 m_pid = -1;

protected:
	explicit LaunchTask(InstancePtr instance);
	void init();

public: /* methods */
	virtual ~LaunchTask() = default;

	static shared_qobject_ptr<LaunchTask> create(InstancePtr inst);

	void appendStep(shared_qobject_ptr<LaunchStep> step);
	void prependStep(shared_qobject_ptr<LaunchStep> step);
	void setCensorFilter(QMap<QString, QString> filter);

	InstancePtr instance();

	void setPid(qint64 pid);

	qint64 pid() const;

	/**
	 * @brief prepare the process for launch (for multi-stage launch)
	 */
	virtual void executeTask() override;

	/**
	 * @brief launch the armed instance
	 */
	void proceed();

	/**
	 * @brief abort launch
	 */
	bool abort() override;

	bool canAbort() const override;

	shared_qobject_ptr<LogModel> getLogModel();

public:
	QString substituteVariables(const QString& cmd) const;
	QString censorPrivateInfo(QString in);

protected: /* methods */
	virtual void emitFailed(QString reason) override;
	virtual void emitSucceeded() override;

signals:
	/**
	 * @brief emitted when the launch preparations are done
	 */
	void readyForLaunch();

	void requestProgress(Task* task);

	void requestLogging();

public slots:
	void onLogLines(const QStringList& lines, MessageLevel::Enum defaultLevel = MessageLevel::Launcher);
	void onLogLine(QString line, MessageLevel::Enum defaultLevel = MessageLevel::Launcher);
	void onReadyForLaunch();
	void onStepFinished();
	void onProgressReportingRequested();

private: /*methods */
	void finalizeSteps(bool successful, const QString& error);
};

#endif // !LAUNCH_LAUNCHTASK_H_