#ifndef STEPS_MSASTEP_H_
#define STEPS_MSASTEP_H_

#include <QObject>
#include <QNetworkRequest>

#include <katabasis/DeviceFlow.h>

#include "../AuthStep.h"
#include "../../Application.h"
//#include "../AuthRequest.h"
//#include "../Parsers.h"

class MSAStep : public AuthStep 
{
    Q_OBJECT

public:
    enum Action 
    {
        Refresh,
        Login
    };

private:
    std::shared_ptr<Katabasis::DeviceFlow> m_oauth2 = nullptr;
    Action m_action;

public:
    explicit MSAStep(AccountData* data, Action action);
    virtual ~MSAStep() noexcept = default;

    void perform() override;
    void rehydrate() override;

    QString describe() override;

private slots:
    void onOAuthActivityChanged(Katabasis::Activity activity);
};

#endif // !STEPS_MSASTEP_H_
