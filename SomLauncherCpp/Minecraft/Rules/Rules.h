#ifndef RULES_RULES_H_
#define RULES_RULES_H_

#include <QStringList>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QVector>
#include <QDir>

#include "../Launcher/GameProfile.h"
#include "../Minecraftus.h"

namespace rules
{
	namespace utils
	{
		bool parseRuleList(Json::JsonValue& data, const QString& rule_string);
		bool parseSingleRule(Json::JsonValue& rule);
	}
}

#endif // !RULES_RULES_H_