#ifndef LAUNCH_LAUNCHCOMMAND_H_
#define LAUNCH_LAUNCHCOMMAND_H_ 

#include <QStringList>
#include <QString>
#include <QDebug>
#include <QVariant>

#include <SomJson.h>

#include "GameProfile.h"
#include "../Minecraftus.h"

namespace commandline
{
	QStringList generateCommand(const GameProfile& profile/*, const Customizer& customizer*/);
}


#endif // !LAUNCH_LAUNCHCOMMAND_H_