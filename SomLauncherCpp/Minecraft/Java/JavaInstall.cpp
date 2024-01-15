#include "JavaInstall.h"

JavaInstall::JavaInstall(QString id, QString arch, QString path)
    : id(id), arch(arch), path(path)
{
}

QString JavaInstall::descriptor()
{
    return this->id.toString();
}

QString JavaInstall::name()
{
    return this->id.toString();
}

QString JavaInstall::typeString() const
{
    return this->arch;
}

bool JavaInstall::operator<(const JavaInstall& rhs)
{
    auto archCompare = Strings::naturalCompare(this->arch, rhs.arch, Qt::CaseInsensitive);
    if (archCompare != 0)
        return archCompare < 0;
    if (this->id < rhs.id)
    {
        return true;
    }
    if (this->id > rhs.id)
    {
        return false;
    }
    return Strings::naturalCompare(this->path, rhs.path, Qt::CaseInsensitive) < 0;
}

bool JavaInstall::operator==(const JavaInstall& rhs)
{
    return this->arch == rhs.arch && this->id == rhs.id && this->path == rhs.path;
}

bool JavaInstall::operator>(const JavaInstall& rhs)
{
    return (!operator<(rhs)) && (!operator==(rhs));
}