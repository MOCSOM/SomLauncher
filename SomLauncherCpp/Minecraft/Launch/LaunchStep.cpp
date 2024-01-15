#include "LaunchStep.h"

LaunchStep::LaunchStep(LaunchTask* parent)
    :Task(nullptr), m_parent(parent)
{
    bind(parent);
}

void LaunchStep::bind(LaunchTask* parent)
{
    this->m_parent = parent;
    connect(this, &LaunchStep::readyForLaunch, parent, &LaunchTask::onReadyForLaunch);
    connect(this, &LaunchStep::logLine, parent, &LaunchTask::onLogLine);
    connect(this, &LaunchStep::logLines, parent, &LaunchTask::onLogLines);
    connect(this, &LaunchStep::finished, parent, &LaunchTask::onStepFinished);
    connect(this, &LaunchStep::progressReportingRequest, parent, &LaunchTask::onProgressReportingRequested);
}

void LaunchStep::proceed()
{
}

void LaunchStep::finalize()
{
}
