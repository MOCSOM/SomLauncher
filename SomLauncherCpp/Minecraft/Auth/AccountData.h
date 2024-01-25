#ifndef AUTH_ACCOUNTDATA_H_
#define AUTH_ACCOUNTDATA_H_

#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QMap>

#include <katabasis/Bits.h>

struct Skin
{
	QString id;
	QString url;
	QString variant;

	QByteArray data;
};

struct Cape
{
	QString id;
	QString url;
	QString alias;

	QByteArray data;
};

struct MinecraftEntitlement
{
	bool ownsMinecraft = false;
	bool canPlayMinecraft = false;
	Katabasis::Validity validity = Katabasis::Validity::None;
};

struct MinecraftProfile
{
	QString id;
	QString name;
	Skin skin;
	QString currentCape;
	QMap<QString, Cape> capes;
	Katabasis::Validity validity = Katabasis::Validity::None;
};

enum class AccountType
{
	MSA,
	Mojang
};

enum class AccountState
{
	Unchecked,
	Offline,
	Working,
	Online,
	Errored,
	Expired,
	Gone,
	MustMigrate
};

struct AccountData
{
	AccountType type = AccountType::MSA;
	bool legacy = false;
	bool can_migrate_to_msa = false;
	bool must_migrate_to_msa = false;

	Katabasis::Token msa_token;
	Katabasis::Token user_token;
	Katabasis::Token xbox_api_token;
	Katabasis::Token mojangservices_token;

	Katabasis::Token yggdrasil_token;
	MinecraftProfile minecraft_profile;
	MinecraftEntitlement minecraft_entitlement;
	Katabasis::Validity validity_ = Katabasis::Validity::None;

	// runtime only information (not saved with the account)
	QString internal_id;
	QString error_string;
	AccountState account_state = AccountState::Unchecked;


	QJsonObject saveState() const;
	bool resumeStateFromV2(QJsonObject data);
	bool resumeStateFromV3(QJsonObject data);

	//! userName for Mojang accounts, gamertag for MSA
	QString accountDisplayString() const;

	//! Only valid for Mojang accounts. MSA does not preserve this information
	QString userName() const;

	//! Only valid for Mojang accounts.
	QString clientToken() const;
	void setClientToken(QString clientToken);
	void invalidateClientToken();
	void generateClientTokenIfMissing();

	//! Yggdrasil access token, as passed to the game.
	QString accessToken() const;

	QString profileId() const;
	QString profileName() const;

	QString lastError() const;
};

#endif // !AUTH_ACCOUNTDATA_H_