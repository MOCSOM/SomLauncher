#include "LaunchTask.h"

LaunchTask::LaunchTask(InstancePtr instance)
	: m_instance(instance)
{
}

void LaunchTask::init()
{
	this->m_instance->setRunning(true);
}

shared_qobject_ptr<LaunchTask> LaunchTask::create(InstancePtr inst)
{
	shared_qobject_ptr<LaunchTask> proc = make_shared_qobject<LaunchTask>(inst);
	proc->init();
	return proc;
}

void LaunchTask::appendStep(shared_qobject_ptr<LaunchStep> step)
{
	this->m_steps.append(step);
}

void LaunchTask::prependStep(shared_qobject_ptr<LaunchStep> step)
{
	this->m_steps.prepend(step);
}

void LaunchTask::setCensorFilter(QMap<QString, QString> filter)
{
	this->m_censorFilter = filter;
}

InstancePtr LaunchTask::instance()
{
	return this->m_instance;
}

void LaunchTask::setPid(qint64 pid)
{
	this->m_pid = pid;
}

qint64 LaunchTask::pid() const
{
	return this->m_pid;
}

void LaunchTask::executeTask()
{
	this->m_instance->setCrashed(false);
	if (!this->m_steps.size())
	{
		this->state = LaunchTask::Finished;
		emitSucceeded();
	}
	this->state = LaunchTask::Running;
	onStepFinished();
}

void LaunchTask::proceed()
{
	if (this->state != LaunchTask::Waiting)
	{
		return;
	}
	this->m_steps[this->currentStep]->proceed();
}

bool LaunchTask::abort()
{
	switch (this->state)
	{
	case LaunchTask::Aborted:
	case LaunchTask::Failed:
	case LaunchTask::Finished:
		return true;
	case LaunchTask::NotStarted:
	{
		this->state = LaunchTask::Aborted;
		emitFailed("Aborted");
		return true;
	}
	case LaunchTask::Running:
	case LaunchTask::Waiting:
	{
		auto& step = this->m_steps[this->currentStep];
		if (!step->canAbort())
		{
			return false;
		}
		if (step->abort())
		{
			this->state = LaunchTask::Aborted;
			return true;
		}
	}
	default:
		break;
	}
	return false;
}

bool LaunchTask::canAbort() const
{
	switch (this->state)
	{
	case LaunchTask::Aborted:
	case LaunchTask::Failed:
	case LaunchTask::Finished:
		return false;
	case LaunchTask::NotStarted:
		return true;
	case LaunchTask::Running:
	case LaunchTask::Waiting:
	{
		auto& step = this->m_steps[this->currentStep];
		return step->canAbort();
	}
	}
	return false;
}

shared_qobject_ptr<LogModel> LaunchTask::getLogModel()
{
	if (!this->m_logModel)
	{
		this->m_logModel.reset(make_shared_qobject<LogModel>());
		this->m_logModel->setMaxLines(this->m_instance->getConsoleMaxLines());
		this->m_logModel->setStopOnOverflow(this->m_instance->shouldStopOnConsoleOverflow());
		// FIXME: should this really be here?
		this->m_logModel->setOverflowMessage(tr("Stopped watching the game log because the log length surpassed %1 lines.\n"
			"You may have to fix your mods because the game is still logging to files and"
			" likely wasting harddrive space at an alarming rate!").arg(m_logModel->getMaxLines()));
	}
	return this->m_logModel;
}

QString LaunchTask::substituteVariables(const QString& cmd) const
{
	QString out = cmd;
	auto variables = this->m_instance->getVariables();
	for (auto it = variables.begin(); it != variables.end(); ++it)
	{
		out.replace("$" + it.key(), it.value());
	}
	auto env = QProcessEnvironment::systemEnvironment();
	for (auto& var : env.keys())
	{
		out.replace("$" + var, env.value(var));
	}
	return out;
}

QString LaunchTask::censorPrivateInfo(QString in)
{
	auto iter = this->m_censorFilter.begin();
	while (iter != this->m_censorFilter.end())
	{
		in.replace(iter.key(), iter.value());
		++iter;
	}
	return in;
}

void LaunchTask::emitFailed(QString reason)
{
	this->m_instance->setRunning(false);
	this->m_instance->setCrashed(true);
	Task::emitFailed(reason);
}

void LaunchTask::emitSucceeded()
{
	this->m_instance->setRunning(false);
	Task::emitSucceeded();
}

void LaunchTask::onLogLines(const QStringList& lines, MessageLevel::Enum defaultLevel)
{
	for (auto& line : lines)
	{
		onLogLine(line, defaultLevel);
	}
}

void LaunchTask::onLogLine(QString line, MessageLevel::Enum level)
{
	// if the launcher part set a log level, use it
	auto innerLevel = MessageLevel::fromLine(line);
	if (innerLevel != MessageLevel::Unknown)
	{
		level = innerLevel;
	}

	// If the level is still undetermined, guess level
	if (level == MessageLevel::StdErr || level == MessageLevel::StdOut || level == MessageLevel::Unknown)
	{
		level = this->m_instance->guessLevel(line, level);
	}

	// censor private user info
	line = censorPrivateInfo(line);

	auto& model = *getLogModel();
	model.append(level, line);
}

void LaunchTask::onReadyForLaunch()
{
	this->state = LaunchTask::Waiting;
	emit readyForLaunch();
}

void LaunchTask::onStepFinished()
{
	// initial -> just start the first step
	if (this->currentStep == -1)
	{
		++this->currentStep;
		this->m_steps[this->currentStep]->start();
		return;
	}

	auto& step = this->m_steps[this->currentStep];
	if (step->wasSuccessful())
	{
		// end?
		if (this->currentStep == this->m_steps.size() - 1)
		{
			finalizeSteps(true, QString());
		}
		else
		{
			++this->currentStep;
			step = this->m_steps[this->currentStep];
			step->start();
		}
	}
	else
	{
		finalizeSteps(false, step->failReason());
	}
}

void LaunchTask::onProgressReportingRequested()
{
	this->state = LaunchTask::Waiting;
	emit requestProgress(this->m_steps[this->currentStep].get());
}

void LaunchTask::finalizeSteps(bool successful, const QString& error)
{
	for (auto step = currentStep; step >= 0; step--)
	{
		this->m_steps[step]->finalize();
	}
	if (successful)
	{
		emitSucceeded();
	}
	else
	{
		emitFailed(error);
	}
}
