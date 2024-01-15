#ifndef MINECRAFT_BASEINSTANCE_H_
#define MINECRAFT_BASEINSTANCE_H_

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QProcess>
#include <QSet>

#include <cassert>
#include <filesystem>

#include "Launch/Task/Task.h"

#include "Settings/SettingsObject.h"

#include "Auth/MinecraftAccount.h"
#include "BaseVersionList.h"
#include "MessageLevel.h"
#include "Pathmatcher/IPathMatcher.h"
#include "Settings/INIFile.h"

#include "Net/Mode.h"

#include "Launch/QuickPlayTarget.h"

#include "Settings/INISettingsObject.h"
#include "Settings/OverrideSetting.h"
#include "Settings/Setting.h"

#include "BuildConfig/BuildConfig.h"
#include "Commandline.h"

class Task;
class LaunchTask;
class BaseInstance;

// pointer for lazy people
typedef std::shared_ptr<BaseInstance> InstancePtr;

/*!
 * \brief Base class for instances.
 * This class implements many functions that are common between instances and
 * provides a standard interface for all instances.
 *
 * To create a new instance type, create a new class inheriting from this class
 * and implement the pure virtual functions.
 */
class BaseInstance : public QObject, public std::enable_shared_from_this<BaseInstance>
{
	Q_OBJECT

public: /* types */
	enum class Status
	{
		Present,
		Gone // either nuked or invalidated
	};

protected: /* data */
	QString m_rootDir;
	SettingsObjectPtr m_settings;
	// InstanceFlags m_flags;
	bool m_isRunning = false;
	std::shared_ptr<LaunchTask> m_launchProcess;
	QDateTime m_timeStarted;

private: /* data */
	Status m_status = Status::Present;
	bool m_crashed = false;
	bool m_hasUpdate = false;
	bool m_hasBrokenVersion = false;

protected:
	/// no-touchy!
	BaseInstance(SettingsObjectPtr globalSettings, SettingsObjectPtr settings, const QString& rootDir);

public:
	/// virtual destructor to make sure the destruction is COMPLETE
	virtual ~BaseInstance() = default;

	virtual void saveNow() = 0;

	/***
	 * the instance has been invalidated - it is no longer tracked by the launcher for some reason,
	 * but it has not necessarily been deleted.
	 *
	 * Happens when the instance folder changes to some other location, or the instance is removed by external means.
	 */
	void invalidate();

	/// The instance's ID. The ID SHALL be determined by LAUNCHER internally. The ID IS guaranteed to
	/// be unique.
	virtual QString id() const;

	void setRunning(bool running);
	bool isRunning() const;
	int64_t totalTimePlayed() const;
	int64_t lastTimePlayed() const;
	void resetTimePlayed() const;

	/// get the type of this instance
	QString instanceType() const;

	/// Path to the instance's root directory.
	QString instanceRoot() const;

	/// Path to the instance's game root directory.
	virtual QString gameRoot() const;

	/// Path to the instance's mods directory.
	virtual QString modsRoot() const = 0;

	QString name() const;
	void setName(QString val);

	/// Value used for instance window titles
	QString windowTitle() const;

	QString instanceTitle() const;

	QString iconKey() const;
	void setIconKey(QString val);

	QString notes() const;
	void setNotes(QString val);

	QString getPreLaunchCommand() const;
	QString getPostExitCommand() const;
	QString getWrapperCommand() const;

	bool isManagedPack() const;
	QString getManagedPackType() const;
	QString getManagedPackID() const;
	QString getManagedPackName() const;
	QString getManagedPackVersionID() const;
	QString getManagedPackVersionName() const;
	void setManagedPack(const QString& type, const QString& id, const QString& name, const QString& versionId, const QString& version) const;

	/// guess log level from a line of game log
	virtual MessageLevel::Enum guessLevel(const QString& line, MessageLevel::Enum level);

	virtual QStringList extraArguments() const;

	/// Traits. Normally inside the version, depends on instance implementation.
	virtual QSet<QString> traits() const = 0;

	/**
	 * Gets the time that the instance was last launched.
	 * Stored in milliseconds since epoch.
	 */
	qint64 lastLaunch() const;
	/// Sets the last launched time to 'val' milliseconds since epoch
	void setLastLaunch(qint64 val = QDateTime::currentMSecsSinceEpoch());

	/*!
	 * \brief Gets this instance's settings object.
	 * This settings object stores instance-specific settings.
	 * \return A pointer to this instance's settings object.
	 */
	virtual SettingsObjectPtr settings() const;

	/// returns a valid update task
	virtual Task::Ptr createUpdateTask(Net::Mode mode) = 0;

	/// returns a valid launcher (task container)
	virtual std::shared_ptr<LaunchTask> createLaunchTask(
		AuthSessionPtr account, QuickPlayTargetPtr quickPlayTarget) = 0;

	/// returns the current launch task (if any)
	std::shared_ptr<LaunchTask> getLaunchTask();

	/*!
	 * Create envrironment variables for running the instance
	 */
	virtual QProcessEnvironment createEnvironment() = 0;

	/*!
	 * Returns a matcher that can maps relative paths within the instance to whether they are 'log files'
	 */
	virtual IPathMatcher::Ptr getLogFileMatcher() = 0;

	/*!
	 * Returns the root folder to use for looking up log files
	 */
	virtual QString getLogFileRoot() = 0;

	virtual QString getStatusbarDescription() = 0;

	/// FIXME: this really should be elsewhere...
	virtual QString instanceConfigFolder() const = 0;

	/// get variables this instance exports
	virtual QMap<QString, QString> getVariables() const = 0;

	virtual QString typeName() const = 0;

	bool hasVersionBroken() const;
	void setVersionBroken(bool value);

	bool hasUpdateAvailable() const;
	void setUpdateAvailable(bool value);
	bool hasCrashed() const;
	void setCrashed(bool value);

	virtual bool canLaunch() const;
	virtual bool canEdit() const = 0;
	virtual bool canExport() const = 0;

	bool reloadSettings();

	/**
	 * 'print' a verbose description of the instance into a QStringList
	 */
	virtual QStringList verboseDescription(AuthSessionPtr session, QuickPlayTargetPtr quickPlayTarget) = 0;

	Status currentStatus() const;

	int getConsoleMaxLines() const;
	bool shouldStopOnConsoleOverflow() const;

protected:
	void changeStatus(Status newStatus);

signals:
	/*!
	 * \brief Signal emitted when properties relevant to the instance view change
	 */
	void propertiesChanged(BaseInstance* inst);

	void launchTaskChanged(std::shared_ptr<LaunchTask>);

	void runningStatusChanged(bool running);

	void statusChanged(Status from, Status to);

protected slots:
	void iconUpdated(QString key);

};

Q_DECLARE_METATYPE(std::shared_ptr<BaseInstance>)
//Q_DECLARE_METATYPE(BaseInstance::InstanceFlag)
//Q_DECLARE_OPERATORS_FOR_FLAGS(BaseInstance::InstanceFlags)

#endif // !MINECRAFT_BASEINSTANCE_H_