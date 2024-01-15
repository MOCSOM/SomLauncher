#ifndef LAUNCH_LAUNCHSTEP_H_
#define LAUNCH_LAUNCHSTEP_H_

#include <QStringList>

#include "Task/Task.h"
#include "../MessageLevel.h"
#include "LaunchTask.h"

class LaunchStep : public Task
{
    Q_OBJECT

protected: /* data */
    LaunchTask* m_parent;

public: /* methods */
    explicit LaunchStep(LaunchTask* parent);
    virtual ~LaunchStep() = default;

private: /* methods */
    void bind(LaunchTask* parent);

signals:
    void logLines(QStringList lines, MessageLevel::Enum level);
signals:
    void logLine(QString line, MessageLevel::Enum level);
signals:
    void readyForLaunch();
signals:
    void progressReportingRequest();

public slots:
    virtual void proceed();
    // called in the opposite order than the Task launch(), used to clean up or otherwise undo things after the launch ends
    virtual void finalize();
};

#endif // !LAUNCH_LAUNCHSTEP_H_