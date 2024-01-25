#ifndef AUTH_AUTHSTEP_H_
#define AUTH_AUTHSTEP_H_

#include <QObject>
#include <QList>
#include <QNetworkReply>

#include <memory>

#include "AccountData.h"
#include "AccountTask.h"
#include "../QObjectPtr.h"

class AuthStep : public QObject
{
	Q_OBJECT

protected:
	AccountData* m_data;

public:
	using Ptr = shared_qobject_ptr<AuthStep>;

public:
	explicit AuthStep(AccountData* data);
	virtual ~AuthStep() noexcept = default;

	virtual QString describe() = 0;

public slots:
	virtual void perform() = 0;
	virtual void rehydrate() = 0;

signals:
	void finished(AccountTaskState resultingState, QString message);
signals:
	void showVerificationUriAndCode(const QUrl& uri, const QString& code, int expiresIn);
signals:
	void hideVerificationUriAndCode();
};

#endif // !AUTH_AUTHSTEP_H_
