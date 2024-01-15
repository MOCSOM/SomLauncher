#include "BaseVersionList.h"

BaseVersionList::BaseVersionList(QObject* parent)
	: QAbstractListModel(parent)
{
}

QVariant BaseVersionList::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > count())
        return QVariant();

    BaseVersionPtr version = at(index.row());

    switch (role)
    {
    case VersionPointerRole:
        return QVariant::fromValue(version);

    case VersionRole:
        return version->name();

    case VersionIdRole:
        return version->descriptor();

    case TypeRole:
        return version->typeString();

    default:
        return QVariant();
    }
}

int BaseVersionList::rowCount(const QModelIndex& parent) const
{
    // Return count
    return count();
}

int BaseVersionList::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QHash<int, QByteArray> BaseVersionList::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(VersionRole, "version");
    roles.insert(VersionIdRole, "versionId");
    roles.insert(ParentVersionRole, "parentGameVersion");
    roles.insert(RecommendedRole, "recommended");
    roles.insert(LatestRole, "latest");
    roles.insert(TypeRole, "type");
    roles.insert(BranchRole, "branch");
    roles.insert(PathRole, "path");
    roles.insert(ArchitectureRole, "architecture");
    return roles;
}

BaseVersionList::RoleList BaseVersionList::providesRoles() const
{
    return { VersionPointerRole, VersionRole, VersionIdRole, TypeRole };
}

BaseVersionPtr BaseVersionList::findVersion(const QString& descriptor)
{
    for (int i = 0; i < count(); i++)
    {
        if (at(i)->descriptor() == descriptor)
            return at(i);
    }
    return BaseVersionPtr();
}

BaseVersionPtr BaseVersionList::getRecommended() const
{
    if (count() <= 0)
        return BaseVersionPtr();
    else
        return at(0);
}
