#ifndef JAVA_JAVAUTILS_H_
#define JAVA_JAVAUTILS_H_

#include <QStringList>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QDir>
#include <QStringList>

#include <filesystem>

#include "JavaChecker.h"
#include "JavaInstallList.h"
#include "../Settings/Setting.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#define IBUS "@im=ibus"

QProcessEnvironment CleanEnviroment();

class JavaUtils : public QObject
{
    Q_OBJECT

public:
    JavaUtils() = default;
    ~JavaUtils() noexcept = default;

    JavaInstallPtr MakeJavaPtr(QString path, QString id = "unknown", QString arch = "unknown");
    QList<QString> FindJavaPaths();
    JavaInstallPtr GetDefaultJava();

#ifdef Q_OS_WIN
    QList<JavaInstallPtr> FindJavaFromRegistryKey(DWORD keyType, QString keyName, QString keyJavaDir, QString subkeySuffix = "");
#endif
};

#endif // !JAVA_JAVAUTILS_H_
