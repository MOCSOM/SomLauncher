#ifndef LAUNCHER_LAUNCHERRULE_H_
#define LAUNCHER_LAUNCHERRULE_H_

#include <QString>
#include <QVector>
#include <QPair>

struct LauncherRule
{
	enum class Action
	{
		ALLOW,
		DISALLOW
	} action;
	QVector<QPair<QString, QString>> conditions;
};

using Rules = QVector<LauncherRule>;

#endif // !LAUNCHER_LAUNCHERRULE_H_
