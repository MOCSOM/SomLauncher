#include "BaseInstance.h"

BaseInstance::BaseInstance(SettingsObjectPtr globalSettings, SettingsObjectPtr settings, const QString& rootDir)
    : QObject()
{
    this->m_settings = settings;
    this->m_rootDir = rootDir;

    this->m_settings->registerSetting("name", "Unnamed Instance");
    this->m_settings->registerSetting("iconKey", "default");
    this->m_settings->registerSetting("notes", "");
    this->m_settings->registerSetting("lastLaunchTime", 0);
    this->m_settings->registerSetting("totalTimePlayed", 0);
    this->m_settings->registerSetting("lastTimePlayed", 0);

    // Custom Commands
    auto commandSetting = this->m_settings->registerSetting({ "OverrideCommands","OverrideLaunchCmd" }, false);
    this->m_settings->registerOverride(globalSettings->getSetting("PreLaunchCommand"), commandSetting);
    this->m_settings->registerOverride(globalSettings->getSetting("WrapperCommand"), commandSetting);
    this->m_settings->registerOverride(globalSettings->getSetting("PostExitCommand"), commandSetting);

    // Console
    auto consoleSetting = this->m_settings->registerSetting("OverrideConsole", false);
    this->m_settings->registerOverride(globalSettings->getSetting("ShowConsole"), consoleSetting);
    this->m_settings->registerOverride(globalSettings->getSetting("AutoCloseConsole"), consoleSetting);
    this->m_settings->registerOverride(globalSettings->getSetting("ShowConsoleOnError"), consoleSetting);
    this->m_settings->registerOverride(globalSettings->getSetting("LogPrePostOutput"), consoleSetting);

    this->m_settings->registerPassthrough(globalSettings->getSetting("ConsoleMaxLines"), nullptr);
    this->m_settings->registerPassthrough(globalSettings->getSetting("ConsoleOverflowStop"), nullptr);

    // Managed Packs
    this->m_settings->registerSetting("ManagedPack", false);
    this->m_settings->registerSetting("ManagedPackType", "");
    this->m_settings->registerSetting("ManagedPackID", "");
    this->m_settings->registerSetting("ManagedPackName", "");
    this->m_settings->registerSetting("ManagedPackVersionID", "");
    this->m_settings->registerSetting("ManagedPackVersionName", "");
}

void BaseInstance::invalidate()
{
    changeStatus(Status::Gone);
    qDebug() << "Instance" << id() << "has been invalidated.";
}

QString BaseInstance::id() const
{
    return QFileInfo(instanceRoot()).fileName();
}

void BaseInstance::setRunning(bool running)
{
    if (running == this->m_isRunning)
        return;

    this->m_isRunning = running;

    if (!this->m_settings->get("RecordGameTime").toBool())
    {
        emit runningStatusChanged(running);
        return;
    }

    if (running)
    {
        this->m_timeStarted = QDateTime::currentDateTime();
    }
    else
    {
        QDateTime timeEnded = QDateTime::currentDateTime();

        qint64 current = settings()->get("totalTimePlayed").toLongLong();
        settings()->set("totalTimePlayed", current + this->m_timeStarted.secsTo(timeEnded));
        settings()->set("lastTimePlayed", this->m_timeStarted.secsTo(timeEnded));

        emit propertiesChanged(this);
    }

    emit runningStatusChanged(running);
}

bool BaseInstance::isRunning() const
{
    return this->m_isRunning;
}

int64_t BaseInstance::totalTimePlayed() const
{
    qint64 current = settings()->get("totalTimePlayed").toLongLong();
    if (this->m_isRunning)
    {
        QDateTime timeNow = QDateTime::currentDateTime();
        return current + this->m_timeStarted.secsTo(timeNow);
    }
    return current;
}

int64_t BaseInstance::lastTimePlayed() const
{
    if (this->m_isRunning)
    {
        QDateTime timeNow = QDateTime::currentDateTime();
        return this->m_timeStarted.secsTo(timeNow);
    }
    return settings()->get("lastTimePlayed").toLongLong();
}

void BaseInstance::resetTimePlayed() const
{
    settings()->reset("totalTimePlayed");
    settings()->reset("lastTimePlayed");
}

QString BaseInstance::instanceType() const
{
    return this->m_settings->get("InstanceType").toString();
}

QString BaseInstance::instanceRoot() const
{
    return this->m_rootDir;
}

QString BaseInstance::gameRoot() const
{
    return instanceRoot();
}

QString BaseInstance::name() const
{
    return this->m_settings->get("name").toString();
}

void BaseInstance::setName(QString val)
{
    //FIXME: if no change, do not set. setting involves saving a file.
    this->m_settings->set("name", val);
    emit propertiesChanged(this);
}

QString BaseInstance::windowTitle() const
{
    return BuildConfig.LAUNCHER_NAME + ": " + name().replace(QRegularExpression("[ \n\r\t]+"), " ");
}

QString BaseInstance::instanceTitle() const
{
    return name().replace(QRegularExpression("[ \n\r\t]+"), " ");
}

QString BaseInstance::iconKey() const
{
    return this->m_settings->get("iconKey").toString();
}

void BaseInstance::setIconKey(QString val)
{
    //FIXME: if no change, do not set. setting involves saving a file.
    this->m_settings->set("iconKey", val);
    emit propertiesChanged(this);
}

QString BaseInstance::notes() const
{
    return this->m_settings->get("notes").toString();
}

void BaseInstance::setNotes(QString val)
{
    //FIXME: if no change, do not set. setting involves saving a file.
    this->m_settings->set("notes", val);
}

QString BaseInstance::getPreLaunchCommand() const
{
    return settings()->get("PreLaunchCommand").toString();
}

QString BaseInstance::getPostExitCommand() const
{
    return settings()->get("PostExitCommand").toString();
}

QString BaseInstance::getWrapperCommand() const
{
    return settings()->get("WrapperCommand").toString();
}

bool BaseInstance::isManagedPack() const
{
    return settings()->get("ManagedPack").toBool();
}

QString BaseInstance::getManagedPackType() const
{
    return settings()->get("ManagedPackType").toString();
}

QString BaseInstance::getManagedPackID() const
{
    return settings()->get("ManagedPackID").toString();
}

QString BaseInstance::getManagedPackName() const
{
    return settings()->get("ManagedPackName").toString();
}

QString BaseInstance::getManagedPackVersionID() const
{
    return settings()->get("ManagedPackVersionID").toString();
}

QString BaseInstance::getManagedPackVersionName() const
{
    return settings()->get("ManagedPackVersionName").toString();
}

void BaseInstance::setManagedPack(const QString& type, const QString& id, const QString& name, const QString& versionId, const QString& version) const
{
    settings()->set("ManagedPack", true);
    settings()->set("ManagedPackType", type);
    settings()->set("ManagedPackID", id);
    settings()->set("ManagedPackName", name);
    settings()->set("ManagedPackVersionID", versionId);
    settings()->set("ManagedPackVersionName", version);
}

MessageLevel::Enum BaseInstance::guessLevel(const QString& line, MessageLevel::Enum level)
{
    return level;
}
QStringList BaseInstance::extraArguments() const
{
    return Commandline::splitArgs(settings()->get("JvmArgs").toString());
}
qint64 BaseInstance::lastLaunch() const
{
    return this->m_settings->get("lastLaunchTime").value<qint64>();
}

void BaseInstance::setLastLaunch(qint64 val)
{
    //FIXME: if no change, do not set. setting involves saving a file.
    this->m_settings->set("lastLaunchTime", val);
    emit propertiesChanged(this);
}

SettingsObjectPtr BaseInstance::settings() const
{
    return this->m_settings;
}

std::shared_ptr<LaunchTask> BaseInstance::getLaunchTask()
{
    return this->m_launchProcess;
}

bool BaseInstance::hasVersionBroken() const
{
    return this->m_hasBrokenVersion;
}

void BaseInstance::setVersionBroken(bool value)
{
    if (this->m_hasBrokenVersion != value)
    {
        this->m_hasBrokenVersion = value;
        emit propertiesChanged(this);
    }
}

bool BaseInstance::hasUpdateAvailable() const
{
    return this->m_hasUpdate;
}

void BaseInstance::setUpdateAvailable(bool value)
{
    if (this->m_hasUpdate != value)
    {
        this->m_hasUpdate = value;
        emit propertiesChanged(this);
    }
}

bool BaseInstance::hasCrashed() const
{
    return this->m_crashed;
}

void BaseInstance::setCrashed(bool value)
{
    if (this->m_crashed != value)
    {
        this->m_crashed = value;
        emit propertiesChanged(this);
    }
}

bool BaseInstance::canLaunch() const
{
    return (!hasVersionBroken() && !isRunning());
}

bool BaseInstance::reloadSettings()
{
    return this->m_settings->reload();
}

BaseInstance::Status BaseInstance::currentStatus() const
{
    return this->m_status;
}

int BaseInstance::getConsoleMaxLines() const
{
    auto lineSetting = settings()->getSetting("ConsoleMaxLines");
    bool conversionOk = false;
    int maxLines = lineSetting->get().toInt(&conversionOk);
    if (!conversionOk)
    {
        maxLines = lineSetting->defValue().toInt();
        qWarning() << "ConsoleMaxLines has nonsensical value, defaulting to" << maxLines;
    }
    return maxLines;
}

bool BaseInstance::shouldStopOnConsoleOverflow() const
{
    return settings()->get("ConsoleOverflowStop").toBool();
}

void BaseInstance::changeStatus(Status newStatus)
{
    Status status = currentStatus();
    if (status != newStatus)
    {
        this->m_status = newStatus;
        emit statusChanged(status, newStatus);
    }
}

void BaseInstance::iconUpdated(QString key)
{
    if (iconKey() == key)
    {
        emit propertiesChanged(this);
    }
}