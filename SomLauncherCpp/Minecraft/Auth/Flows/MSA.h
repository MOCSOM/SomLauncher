#ifndef FLOWS_MSA_H_
#define FLOWS_MSA_H_

#include "AuthFlow.h"
#include "../steps/MSAStep.h"
//#include "../steps/XboxUserStep.h"
//#include "../steps/XboxAuthorizationStep.h"
//#include "../steps/LauncherLoginStep.h"
//#include "../steps/XboxProfileStep.h"
//#include "../steps/EntitlementsStep.h"
//#include "../steps/MinecraftProfileStep.h"
//#include "../steps/GetSkinStep.h"

class MSAInteractive : public AuthFlow
{
    Q_OBJECT

public:
    explicit MSAInteractive(AccountData* data, QObject* parent = 0);
    ~MSAInteractive() = default;
};

class MSASilent : public AuthFlow
{
    Q_OBJECT

public:
    explicit MSASilent(AccountData* data, QObject* parent = 0);
    ~MSASilent() = default;
};

#endif // !FLOWS_MSA_H_
