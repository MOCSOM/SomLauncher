#ifndef FLOWS_MOJANG_H_
#define FLOWS_MOJANG_H_

#include "AuthFlow.h"
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
public:
    explicit MojangLogin(
        AccountData* data,
        QString password,
        QObject* parent = 0
    );

private:
    QString m_password;
};

#endif // !FLOWS_MOJANG_H_
