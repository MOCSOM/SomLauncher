#ifndef FLOWS_MOJANG_H_
#define FLOWS_MOJANG_H_

#include <QString>

#include "AuthFlow.h"
#include "../AccountData.h"
//#include "../steps/YggdrasilStep.h"
//#include "../steps/MinecraftProfileStep.h"
//#include "../steps/ForcedMigrationStep.h"
//#include "../steps/MigrationEligibilityStep.h"
//#include "../steps/GetSkinStep.h"

class MojangRefresh : public AuthFlow
{
	Q_OBJECT

public:
	explicit MojangRefresh(
		AccountData* data,
		QObject* parent = 0
	);
};

class MojangLogin : public AuthFlow
{
	Q_OBJECT

private:
	QString m_password;

public:
	explicit MojangLogin(
		AccountData* data,
		QString password,
		QObject* parent = 0
	);
};

#endif // !FLOWS_MOJANG_H_
