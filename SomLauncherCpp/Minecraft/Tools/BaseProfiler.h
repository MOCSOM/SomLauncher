#ifndef TOOLS_BASEPROFILER_H_
#define TOOLS_BASEPROFILER_H_

#include <memory>

#include "BaseExternalTool.h"

class BaseInstance;
class SettingsObject;
class LaunchTask;
class QProcess;

class BaseProfiler : public BaseExternalTool
{
    Q_OBJECT

protected:
    QProcess* m_profilerProcess;

public:
    explicit BaseProfiler(SettingsObjectPtr settings, InstancePtr instance, QObject* parent = 0);
    ~BaseProfiler() = default;

public slots:
    void beginProfiling(std::shared_ptr<LaunchTask> process);
    void abortProfiling();

protected:
    virtual void beginProfilingImpl(std::shared_ptr<LaunchTask> process) = 0;
    virtual void abortProfilingImpl();

signals:
    void readyToLaunch(const QString& message);
signals:
    void abortLaunch(const QString& message);
};

class BaseProfilerFactory : public BaseExternalToolFactory
{
public:
    virtual BaseProfiler* createProfiler(InstancePtr instance, QObject* parent = 0);
};

#endif // !TOOLS_BASEPROFILER_H_