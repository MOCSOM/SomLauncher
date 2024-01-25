#ifndef AUTH_MINECRAFTACCOUNT_H_
#define AUTH_MINECRAFTACCOUNT_H_

#include <QObject>
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QPair>
#include <QMap>
#include <QPixmap>
#include <QUuid>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QJsonDocument>
#include <QDebug>
#include <QPainter>

#include <memory>

#include "Flows/MSA.h"
#include "Flows/Mojang.h"
#include "AuthSession.h"
#include "../Usable.h"
#include "AccountData.h"
#include "AccountTask.h"
#include "../Launch/Task/Task.h"
#include "../QObjectPtr.h"

class MinecraftAccount;

typedef shared_qobject_ptr<MinecraftAccount> MinecraftAccountPtr;
Q_DECLARE_METATYPE(MinecraftAccountPtr);

/**
 * A profile within someone's Mojang account.
 *
 * Currently, the profile system has not been implemented by Mojang yet,
 * but we might as well add some things for it in MultiMC right now so
 * we don't have to rip the code to pieces to add it later.
 */

struct AccountProfile
{
	QString id;
	QString name;
	bool legacy;
};

/**
 * Object that stores information about a certain Mojang account.
 *
 * Said information may include things such as that account's username, client token, and access
 * token if the user chose to stay logged in.
 */
class MinecraftAccount : public QObject, public Usable
{
	Q_OBJECT

protected: /* variables */
	AccountData data;

	// current task we are executing here
	shared_qobject_ptr<AccountTask> m_currentTask;

public: /* construction */
	//! Do not copy accounts. ever.
	explicit MinecraftAccount(const MinecraftAccount& other, QObject* parent) = delete;

	//! Default constructor
	explicit MinecraftAccount(QObject* parent = 0);
	~MinecraftAccount() noexcept = default;

	static MinecraftAccountPtr createFromUsername(const QString& username);

	static MinecraftAccountPtr createBlankMSA();

	static MinecraftAccountPtr loadFromJsonV2(const QJsonObject& json);
	static MinecraftAccountPtr loadFromJsonV3(const QJsonObject& json);

	//! Saves a MinecraftAccount to a JSON object and returns it.
	QJsonObject saveToJson() const;

public: /* manipulation */

	/**
	 * Attempt to login. Empty password means we use the token.
	 * If the attempt fails because we already are performing some task, it returns false.
	 */
	shared_qobject_ptr<AccountTask> login(QString password);

	shared_qobject_ptr<AccountTask> loginMSA();

	shared_qobject_ptr<AccountTask> refresh();

	shared_qobject_ptr<AccountTask> currentTask();

public: /* queries */
	QString internalId() const;

	QString accountDisplayString() const;

	QString mojangUserName() const;

	QString accessToken() const;

	QString profileId() const;

	QString profileName() const;

	bool isActive() const;

	bool canMigrate() const;

	bool isMSA() const;

	bool ownsMinecraft() const;

	bool hasProfile() const;

	QString typeString() const;

	QPixmap getFace() const;

	//! Returns the current state of the account
	AccountState accountState() const;

	AccountData* accountData();

	bool shouldRefresh() const;

	void fillSession(AuthSessionPtr session);

	QString lastError() const;

signals:
	/**
	 * This signal is emitted when the account changes
	 */
	void changed();
signals:
	void activityChanged(bool active);

	// TODO: better signalling for the various possible state changes - especially errors

protected: /* methods */

	void incrementUses() override;
	void decrementUses() override;

private slots:
	void authSucceeded();
	void authFailed(QString reason);
};

#endif // !AUTH_MINECRAFTACCOUNT_H_
