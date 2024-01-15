#include "QuickPlayTarget.h"

// FIXME: the way this is written, it can't ever do any sort of validation and can accept total junk
QuickPlayTarget QuickPlayTarget::parseMultiplayer(const QString& fullAddress)
{
    QStringList split = fullAddress.split(":");

    // The logic below replicates the exact logic minecraft uses for parsing server addresses.
    // While the conversion is not lossless and eats errors, it ensures the same behavior
    // within Minecraft and MultiMC when entering server addresses.
    if (fullAddress.startsWith("["))
    {
        int bracket = fullAddress.indexOf("]");
        if (bracket > 0)
        {
            QString ipv6 = fullAddress.mid(1, static_cast<qsizetype>(bracket) - 1);
            QString port = fullAddress.mid(static_cast<qsizetype>(bracket) + 1).trimmed();

            if (port.startsWith(":") && !ipv6.isEmpty())
            {
                port = port.mid(1);
                split = QStringList({ ipv6, port });
            }
            else
            {
                split = QStringList({ ipv6 });
            }
        }
    }

    if (split.size() > 2)
    {
        split = QStringList({ fullAddress });
    }

    QString realAddress = split[0];

    quint16 realPort = 25565;
    if (split.size() > 1)
    {
        bool ok;
        realPort = split[1].toUInt(&ok);

        if (!ok)
        {
            realPort = 25565;
        }
    }

    return QuickPlayTarget{ realAddress, realPort };
}

QuickPlayTarget QuickPlayTarget::parseSingleplayer(const QString& worldName)
{
    QuickPlayTarget target;
    target.world = worldName;
    return target;
}
