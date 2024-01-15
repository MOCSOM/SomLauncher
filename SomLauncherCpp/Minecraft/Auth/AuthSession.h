#ifndef AUTH_AUTHSESSION_H_
#define AUTH_AUTHSESSION_H_

#include <QJsonDocument>
#include <QJsonObject>
#include <QMultiMap>
#include <QString>

#include <memory>

class MinecraftAccount;
class QNetworkAccessManager;
struct AuthSession;

typedef std::shared_ptr<AuthSession> AuthSessionPtr;

struct AuthSession
{
    bool MakeOffline(QString offline_playername);
    void MakeDemo();

    QString serializeUserProperties();

    enum Status
    {
        Undetermined,
        RequiresOAuth,
        RequiresPassword,
        RequiresProfileSetup,
        PlayableOffline,
        PlayableOnline,
        GoneOrMigrated
    } 
    status = Undetermined;

    // client token
    QString client_token;
    // account user name
    QString username;
    // combined session ID
    QString session;
    // volatile auth token
    QString access_token;
    // profile name
    QString player_name;
    // profile ID
    QString uuid;
    // 'legacy' or 'mojang', depending on account type
    QString user_type;
    // Did the auth server reply?
    bool auth_server_online = false;
    // Did the user request online mode?
    bool wants_online = true;

    //Is this a demo session?
    bool demo = false;
};

#endif // !AUTH_AUTHSESSION_H_
