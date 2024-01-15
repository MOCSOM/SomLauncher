#ifndef TOOLS_BASEEXTERNALTOOLS_H_
#define TOOLS_BASEEXTERNALTOOLS_H_

#include <QObject>
#include <QProcess>
#include <QDir>

#include "../BaseInstance.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif


class BaseExternalTool : public QObject
{
    Q_OBJECT

protected:
    InstancePtr m_instance;
    SettingsObjectPtr globalSettings;

public:
    explicit BaseExternalTool(SettingsObjectPtr settings, InstancePtr instance, QObject* parent = 0);
    virtual ~BaseExternalTool() = default;
};

class BaseDetachedTool : public BaseExternalTool
{
    Q_OBJECT
public:
    explicit BaseDetachedTool(SettingsObjectPtr settings, InstancePtr instance, QObject* parent = 0);
    ~BaseDetachedTool() = default;

public slots:
    void run();

protected:
    virtual void runImpl() = 0;
};

class BaseExternalToolFactory
{
protected:
    SettingsObjectPtr globalSettings;

public:
    BaseExternalToolFactory() = default;
    virtual ~BaseExternalToolFactory() = default;

    virtual QString name() const = 0;

    virtual void registerSettings(SettingsObjectPtr settings) = 0;

    virtual BaseExternalTool* createTool(InstancePtr instance, QObject* parent = 0) = 0;

    virtual bool check(QString* error) = 0;
    virtual bool check(const QString& path, QString* error) = 0;
};

class BaseDetachedToolFactory : public BaseExternalToolFactory
{
public:
    virtual BaseDetachedTool* createDetachedTool(InstancePtr instance, QObject* parent = 0);
};

#endif // !TOOLS_BASEEXTERNALTOOLS_H_