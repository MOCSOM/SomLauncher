#ifndef AUTH_YHHDRASIL_H_
#define AUTH_YHHDRASIL_H_

#include <QString>
#include <QJsonObject>
#include <QTimer>
#include <QSSLError>

#include "AccountTask.h"
#include "MinecraftAccount.h"
#include "../Application.h"

class QNetworkAccessManager;
class QNetworkReply;

/**
 * A Yggdrasil task is a task that performs an operation on a given mojang account.
 */
class Yggdrasil : public AccountTask
{
    Q_OBJECT

protected:
    QNetworkReply* m_netReply = nullptr;
    QTimer timeout_keeper;
    QTimer counter;
    int count = 0; // num msec since time reset

    const int timeout_max = 30000;
    const int time_step = 50;

public:
    explicit Yggdrasil(AccountData* data, QObject* parent = 0);
    virtual ~Yggdrasil() = default;

    void refresh();
    void login(QString password);

    struct Error
    {
        QString m_errorMessageShort;
        QString m_errorMessageVerbose;
        QString m_cause;
    };

    std::shared_ptr<Error> m_error;

    enum AbortedBy
    {
        BY_NOTHING,
        BY_USER,
        BY_TIMEOUT
    } 
    m_aborted = BY_NOTHING;

protected:
    void executeTask() override;

    /**
     * Processes the response received from the server.
     * If an error occurred, this should emit a failed signal.
     * If Yggdrasil gave an error response, it should call setError() first, and then return false.
     * Otherwise, it should return true.
     * Note: If the response from the server was blank, and the HTTP code was 200, this function is called with
     * an empty QJsonObject.
     */
    void processResponse(QJsonObject responseData);

    /**
     * Processes an error response received from the server.
     * The default implementation will read data from Yggdrasil's standard error response format and set it as this task's Error.
     * \returns a QString error message that will be passed to emitFailed.
     */
    virtual void processError(QJsonObject responseData);

protected slots:
    void processReply();
    void refreshTimers(qint64, qint64);
    void heartbeat();
    void sslErrors(QList<QSslError> errors);
    void abortByTimeout();

public slots:
    virtual bool abort() override;

private:
    void sendRequest(QUrl endpoint, QByteArray content);
};

#endif // !AUTH_YHHDRASIL_H_