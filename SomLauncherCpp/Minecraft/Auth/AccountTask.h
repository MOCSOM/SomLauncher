#ifndef AUTH_ACCOUNTTASK_H_
#define AUTH_ACCOUNTTASK_H_

#include <QJsonObject>
#include <QSSLError>
#include <QString>
#include <QTimer>
#include <QNetworkReply>

#include "../Launch/Task/Task.h"
#include "MinecraftAccount.h"
#include "AccountData.h"

/**
 * Enum for describing the state of the current task.
 * Used by the getStateMessage function to determine what the status message should be.
 */
enum AccountTaskState
{
	STATE_CREATED,
	STATE_WORKING,
	STATE_SUCCEEDED,
	STATE_FAILED_SOFT, //!< soft failure. authentication went through partially
	STATE_FAILED_MUST_MIGRATE, //!< soft failure. main tokens are valid, but the account must be migrated
	STATE_FAILED_HARD, //!< hard failure. main tokens are invalid
	STATE_FAILED_GONE, //!< hard failure. main tokens are invalid, and the account no longer exists
	STATE_OFFLINE //!< soft failure. authentication failed in the first step in a 'soft' way
};

class AccountTask : public Task
{
	Q_OBJECT

public:
	AccountTaskState m_taskState = AccountTaskState::STATE_CREATED;

protected:
	AccountData* m_data = nullptr;

public:
	explicit AccountTask(AccountData* data, QObject* parent = 0);
	virtual ~AccountTask() = default;

	AccountTaskState taskState() const;

signals:
	void showVerificationUriAndCode(const QUrl& uri, const QString& code, int expiresIn);
signals:
	void hideVerificationUriAndCode();

protected:
	/**
	 * Returns the state message for the given state.
	 * Used to set the status message for the task.
	 * Should be overridden by subclasses that want to change messages for a given state.
	 */
	virtual QString getStateMessage() const;

protected slots:
	// NOTE: true -> non-terminal state, false -> terminal state
	bool changeState(AccountTaskState newState, QString reason = QString());
};

#endif // !AUTH_ACCOUNTTASK_H_