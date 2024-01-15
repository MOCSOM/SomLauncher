#ifndef FLOWS_AUTHFLOW_H_
#define FLOWS_AUTHFLOW_H_

#include <QObject>
#include <QList>
#include <QVector>
#include <QSet>
#include <QNetworkReply>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

#include "katabasis/Globals.h"
#include <katabasis/DeviceFlow.h>

#include "AuthFlow.h"
#include "../Yggdrasil.h"
#include "../AccountData.h"
#include "../AccountTask.h"
#include "../AuthStep.h"
#include "../../Application.h"

class AuthFlow : public AccountTask
{
    Q_OBJECT

protected:
    QList<AuthStep::Ptr> m_steps;
    AuthStep::Ptr m_currentStep;

public:
    explicit AuthFlow(AccountData* data, QObject* parent = 0);
    ~AuthFlow() noexcept = default;

    Katabasis::Validity validity();

    QString getStateMessage() const override;

    void executeTask() override;

signals:
    void activityChanged(Katabasis::Activity activity);

private slots:
    void stepFinished(AccountTaskState resultingState, QString message);

protected:
    void succeed();
    void nextStep();
};

#endif // !FLOWS_AUTHFLOW_H_