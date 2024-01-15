#ifndef MINECRAFT_VERSIONFILTERDATA_H_
#define MINECRAFT_VERSIONFILTERDATA_H_

#include <QMap>
#include <QString>
#include <QSet>
#include <QDateTime>

#include "ParseUtils.h"

struct FMLlib
{
    QString filename;
    QString checksum;
};

struct VersionFilterData
{
    VersionFilterData();
    ~VersionFilterData() noexcept = default;

    // mapping between minecraft versions and FML libraries required
    QMap<QString, QList<FMLlib>> fmlLibsMapping;
    // set of minecraft versions for which using forge installers is blacklisted
    QSet<QString> forgeInstallerBlacklist;
    // no new versions below this date will be accepted from Mojang servers
    QDateTime legacyCutoffDate;
    // Libraries that belong to LWJGL
    QSet<QString> lwjglWhitelist;
    // release date of first version to require Java 8 (17w13a)
    QDateTime java8BeginsDate;
    // release data of first version to require Java 16 (21w19a)
    QDateTime java16BeginsDate;
    // release data of first version to require Java 17 (1.18 Pre Release 2)
    QDateTime java17BeginsDate;
    // release date of first version to use --quickPlayMultiplayer instead of --server/--port for directly joining servers
    QDateTime quickPlayBeginsDate;
};

extern VersionFilterData g_VersionFilterData;

#endif // !MINECRAFT_VERSIONFILTERDATA_H_
