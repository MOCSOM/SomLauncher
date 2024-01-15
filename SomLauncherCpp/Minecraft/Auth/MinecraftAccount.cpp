#include "MinecraftAccount.h"

MinecraftAccount::MinecraftAccount(QObject* parent)
    : QObject(parent) 
{
    this->data.internal_id = QUuid::createUuid().toString().remove(QRegularExpression("[{}-]"));
}

MinecraftAccountPtr MinecraftAccount::createFromUsername(const QString& username)
{
    MinecraftAccountPtr account = std::make_shared<MinecraftAccount>();
    account->data.type = AccountType::Mojang;
    account->data.yggdrasil_token.extra["userName"] = username;
    account->data.yggdrasil_token.extra["clientToken"] = QUuid::createUuid().toString().remove(QRegularExpression("[{}-]"));
    return account;
}

MinecraftAccountPtr MinecraftAccount::createBlankMSA()
{
    MinecraftAccountPtr account = std::make_shared<MinecraftAccount>();
    account->data.type = AccountType::MSA;
    return account;
}

MinecraftAccountPtr MinecraftAccount::loadFromJsonV2(const QJsonObject& json)
{
    MinecraftAccountPtr account = std::make_shared<MinecraftAccount>();
    if (account->data.resumeStateFromV2(json)) 
    {
        return account;
    }
    return nullptr;
}

MinecraftAccountPtr MinecraftAccount::loadFromJsonV3(const QJsonObject& json)
{
    MinecraftAccountPtr account = std::make_shared<MinecraftAccount>();
    if (account->data.resumeStateFromV3(json)) 
    {
        return account;
    }
    return nullptr;
}

QJsonObject MinecraftAccount::saveToJson() const
{
    return data.saveState();
}

std::shared_ptr<AccountTask> MinecraftAccount::login(QString password)
{
    Q_ASSERT(m_currentTask.get() == nullptr);

    m_currentTask.reset(new MojangLogin(&data, password));
    connect(m_currentTask.get(), SIGNAL(succeeded()), SLOT(authSucceeded()));
    connect(m_currentTask.get(), SIGNAL(failed(QString)), SLOT(authFailed(QString)));
    emit activityChanged(true);
    return m_currentTask;
}

std::shared_ptr<AccountTask> MinecraftAccount::loginMSA()
{
    Q_ASSERT(m_currentTask.get() == nullptr);

    m_currentTask.reset(std::make_shared<MSAInteractive>(&data).get());
    connect(m_currentTask.get(), SIGNAL(succeeded()), SLOT(authSucceeded()));
    connect(m_currentTask.get(), SIGNAL(failed(QString)), SLOT(authFailed(QString)));
    emit activityChanged(true);
    return m_currentTask;
}

std::shared_ptr<AccountTask> MinecraftAccount::refresh()
{
    if (m_currentTask) 
    {
        return m_currentTask;
    }

    if (data.type == AccountType::MSA) 
    {
        m_currentTask.reset(std::make_shared<MSASilent>(&data).get());
    }
    else {
        m_currentTask.reset(std::make_shared<MojangRefresh>(&data).get());
    }

    connect(m_currentTask.get(), SIGNAL(succeeded()), SLOT(authSucceeded()));
    connect(m_currentTask.get(), SIGNAL(failed(QString)), SLOT(authFailed(QString)));
    emit activityChanged(true);
    return m_currentTask;
}

std::shared_ptr<AccountTask> MinecraftAccount::currentTask()
{
    return m_currentTask;
}

bool MinecraftAccount::isActive() const
{
    return m_currentTask != nullptr;
}

QPixmap MinecraftAccount::getFace() const
{
    QPixmap skinTexture;
    if (!skinTexture.loadFromData(data.minecraft_profile.skin.data, "PNG")) 
    {
        return QPixmap();
    }
    QPixmap skin = QPixmap(8, 8);
    QPainter painter(&skin);
    painter.drawPixmap(0, 0, skinTexture.copy(8, 8, 8, 8));
    painter.drawPixmap(0, 0, skinTexture.copy(40, 8, 8, 8));
    return skin.scaled(64, 64, Qt::KeepAspectRatio);
}

AccountState MinecraftAccount::accountState() const
{
    return data.account_state;
}

bool MinecraftAccount::shouldRefresh() const
{
    /*
     * Never refresh accounts that are being used by the game, it breaks the game session.
     * Always refresh accounts that have not been refreshed yet during this session.
     * Don't refresh broken accounts.
     * Refresh accounts that would expire in the next 12 hours (fresh token validity is 24 hours).
     */
    if (isInUse()) 
    {
        return false;
    }
    switch (data.validity_) 
    {
    case Katabasis::Validity::Certain: 
    {
        break;
    }
    case Katabasis::Validity::None: 
    {
        return false;
    }
    case Katabasis::Validity::Assumed: 
    {

        return true;
    }
    }
    auto now = QDateTime::currentDateTimeUtc();
    auto& issuedTimestamp = data.yggdrasil_token.issueInstant;
    QDateTime expiresTimestamp = data.yggdrasil_token.notAfter;

    if (!expiresTimestamp.isValid()) 
    {
        expiresTimestamp = issuedTimestamp.addSecs(24 * 3600);
    }
    if (now.secsTo(expiresTimestamp) < (12 * 3600)) 
    {
        return true;
    }
    return false;
}

void MinecraftAccount::fillSession(AuthSessionPtr session)
{
    if (ownsMinecraft() && !hasProfile()) 
    {
        session->status = AuthSession::RequiresProfileSetup;
    }
    else 
    {
        if (session->wants_online) 
        {
            session->status = AuthSession::PlayableOnline;
        }
        else 
        {
            session->status = AuthSession::PlayableOffline;
        }
    }

    // the user name. you have to have an user name
    // FIXME: not with MSA
    session->username = data.userName();
    // volatile auth token
    session->access_token = data.accessToken();
    // the semi-permanent client token
    session->client_token = data.clientToken();
    // profile name
    session->player_name = data.profileName();
    // profile ID
    session->uuid = data.profileId();
    // 'legacy' or 'mojang', depending on account type
    session->user_type = typeString();
    if (!session->access_token.isEmpty())
    {
        session->session = "token:" + data.accessToken() + ":" + data.profileId();
    }
    else
    {
        session->session = "-";
    }
}

void MinecraftAccount::incrementUses()
{
    bool wasInUse = isInUse();
    Usable::incrementUses();
    if (!wasInUse)
    {
        emit changed();
        // FIXME: we now need a better way to identify accounts...
        qWarning() << "Profile" << data.profileId() << "is now in use.";
    }
}

void MinecraftAccount::decrementUses()
{
    Usable::decrementUses();
    if (!isInUse())
    {
        emit changed();
        // FIXME: we now need a better way to identify accounts...
        qWarning() << "Profile" << data.profileId() << "is no longer in use.";
    }
}

void MinecraftAccount::authSucceeded()
{
    m_currentTask.reset();
    emit changed();
    emit activityChanged(false);
}

void MinecraftAccount::authFailed(QString reason)
{
    switch (m_currentTask->taskState()) 
    {
    case AccountTaskState::STATE_OFFLINE:
    case AccountTaskState::STATE_FAILED_MUST_MIGRATE:
    case AccountTaskState::STATE_FAILED_SOFT: 
    {
        // NOTE: this doesn't do much. There was an error of some sort.
    }
                                            break;//?
    case AccountTaskState::STATE_FAILED_HARD: 
    {
        if (isMSA()) 
        {
            data.msa_token.token = QString();
            data.msa_token.refresh_token = QString();
            data.msa_token.validity = Katabasis::Validity::None;
            data.validity_ = Katabasis::Validity::None;
        }
        else 
        {
            data.yggdrasil_token.token = QString();
            data.yggdrasil_token.validity = Katabasis::Validity::None;
            data.validity_ = Katabasis::Validity::None;
        }
        emit changed();
    }
                                            break;
    case AccountTaskState::STATE_FAILED_GONE: 
    {
        data.validity_ = Katabasis::Validity::None;
        emit changed();
    }
                                            break;
    case AccountTaskState::STATE_CREATED:
    case AccountTaskState::STATE_WORKING:
    case AccountTaskState::STATE_SUCCEEDED: 
    {
        // Not reachable here, as they are not failures.
    }
    }
    m_currentTask.reset();
    emit activityChanged(false);
}