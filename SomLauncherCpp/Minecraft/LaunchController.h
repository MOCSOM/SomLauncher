#ifndef MINECRAFT_LAUNCHCONTROLLER_H_
#define MINECRAFT_LAUNCHCONTROLLER_H_

#include <QObject>
#include <QLineEdit>
#include <QInputDialog>
#include <QStringList>
#include <QHostInfo>
#include <QList>
#include <QHostAddress>
#include <QPushButton>

#include "Ui/Dialogs/CustomMessageBox.h"
#include "Ui/Dialogs/ProgressDialog.h"

#include "BaseInstance.h"
#include "Tools/BaseProfiler.h"
#include "Launch/QuickPlayTarget.h"
#include "Auth/MinecraftAccount.h"
#include "BuildConfig/BuildConfig.h"
#include "JavaCommon.h"
#include "Launch/Task/Task.h"
#include "Auth/AccountTask.h"
#include "Launch/LaunchTask.h"
#include "Launch/Steps/TextPrint.h"

class LaunchController : public Task
{
	Q_OBJECT

private:
	BaseProfilerFactory* m_profiler = nullptr;
	bool m_online = true;
	QString m_offlineName;
	InstancePtr m_instance;
	QWidget* m_parentWidget = nullptr;
	InstanceWindow* m_console = nullptr;
	MinecraftAccountPtr m_accountToUse = nullptr;
	AuthSessionPtr m_session;
	std::shared_ptr<LaunchTask> m_launcher;
	QuickPlayTargetPtr m_quickPlayTarget;

public:
	LaunchController(QObject* parent = nullptr);
	virtual ~LaunchController() = default;

	void executeTask() override;

	void setInstance(InstancePtr instance);

	InstancePtr instance();

	void setOnline(bool online);

	void setOfflineName(const QString& offlineName);

	void setProfiler(BaseProfilerFactory* profiler);

	void setParentWidget(QWidget* widget);

	void setQuickPlayTarget(QuickPlayTargetPtr quickPlayTarget);

	void setAccountToUse(MinecraftAccountPtr accountToUse);

	QString id();

	bool abort() override;

private:
	void login();
	void launchInstance();
	void decideAccount();

private slots:
	void readyForLaunch();

	void onSucceeded();
	void onFailed(QString reason);
	void onProgressRequested(Task* task);
};

#endif // !MINECRAFT_LAUNCHCONTROLLER_H_