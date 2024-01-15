#include "AuthSession.h"

bool AuthSession::MakeOffline(QString offline_playername)
{
    if (this->status != PlayableOffline && this->status != PlayableOnline)
    {
        return false;
    }
    this->session = "-";
    this->player_name = offline_playername;
    this->status = PlayableOffline;
    return true;
}

void AuthSession::MakeDemo()
{
    this->player_name = "Player";
    this->demo = true;
}

QString AuthSession::serializeUserProperties()
{
    QJsonObject userAttrs;
    /*
    for (auto key : u.properties.keys())
    {
        auto array = QJsonArray::fromStringList(u.properties.values(key));
        userAttrs.insert(key, array);
    }
    */
    QJsonDocument value(userAttrs);
    return value.toJson(QJsonDocument::Compact);

}
