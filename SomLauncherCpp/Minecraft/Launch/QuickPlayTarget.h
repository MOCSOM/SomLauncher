#ifndef LAUNCH_QUICKPLAYTARGET_H_
#define LAUNCH_QUICKPLAYTARGET_H_

#include <memory>

#include <QString>
#include <QStringList>

struct QuickPlayTarget;

typedef std::shared_ptr<QuickPlayTarget> QuickPlayTargetPtr;

struct QuickPlayTarget 
{
    // Multiplayer
    QString address;
    quint16 port;

    // Singleplayer
    QString world;

    static QuickPlayTarget parseMultiplayer(const QString& fullAddress);
    static QuickPlayTarget parseSingleplayer(const QString& worldName);
};

#endif // !LAUNCH_QUICKPLAYTARGET_H_