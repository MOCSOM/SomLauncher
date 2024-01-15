#ifndef JAVA_JAVAINSTALL_H_
#define JAVA_JAVAINSTALL_H_

#include "../BaseVersion.h"
#include "JavaVersion.h"
#include "../MMCStrings.h"

struct JavaInstall : public BaseVersion
{
    JavaVersion id;
    QString arch;
    QString path;
    bool recommended = false;

    JavaInstall() = default;
    JavaInstall(QString id, QString arch, QString path);

    virtual QString descriptor();

    virtual QString name();

    virtual QString typeString() const;

    bool operator<(const JavaInstall& rhs);
    bool operator==(const JavaInstall& rhs);
    bool operator>(const JavaInstall& rhs);
};

typedef std::shared_ptr<JavaInstall> JavaInstallPtr;

#endif // !JAVA_JAVAINSTALL_H_