#include "BaseProfiler.h"

BaseProfiler::BaseProfiler(SettingsObjectPtr settings, InstancePtr instance, QObject* parent)
    : BaseExternalTool(settings, instance, parent)
{
}

void BaseProfiler::beginProfiling(std::shared_ptr<LaunchTask> process)
{
    beginProfilingImpl(process);
}

void BaseProfiler::abortProfiling()
{
    abortProfilingImpl();
}

void BaseProfiler::abortProfilingImpl()
{
    if (!this->m_profilerProcess)
    {
        return;
    }
    this->m_profilerProcess->terminate();
    this->m_profilerProcess->deleteLater();
    this->m_profilerProcess = 0;
    emit abortLaunch(tr("Profiler aborted"));
}

BaseProfiler* BaseProfilerFactory::createProfiler(InstancePtr instance, QObject* parent)
{
    return qobject_cast<BaseProfiler*>(createTool(instance, parent));
}