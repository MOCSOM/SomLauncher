#include "AccountData.h"

namespace 
{
    void tokenToJSONV3(QJsonObject& parent, Katabasis::Token t, const char* tokenName) 
    {
        if (!t.persistent) 
        {
            return;
        }
        QJsonObject out;
        if (t.issueInstant.isValid()) 
        {
            out["iat"] = QJsonValue(t.issueInstant.toMSecsSinceEpoch() / 1000);
        }

        if (t.notAfter.isValid()) 
        {
            out["exp"] = QJsonValue(t.notAfter.toMSecsSinceEpoch() / 1000);
        }

        bool save = false;
        if (!t.token.isEmpty()) 
        {
            out["token"] = QJsonValue(t.token);
            save = true;
        }
        if (!t.refresh_token.isEmpty()) 
        {
            out["refresh_token"] = QJsonValue(t.refresh_token);
            save = true;
        }
        if (t.extra.size()) 
        {
            out["extra"] = QJsonObject::fromVariantMap(t.extra);
            save = true;
        }
        if (save)
        {
            parent[tokenName] = out;
        }
    }

    Katabasis::Token tokenFromJSONV3(const QJsonObject& parent, const char* tokenName) 
    {
        Katabasis::Token out;
        auto tokenObject = parent.value(tokenName).toObject();
        if (tokenObject.isEmpty()) 
        {
            return out;
        }
        auto issueInstant = tokenObject.value("iat");
        if (issueInstant.isDouble()) 
        {
            out.issueInstant = QDateTime::fromMSecsSinceEpoch(((int64_t)issueInstant.toDouble()) * 1000);
        }

        auto notAfter = tokenObject.value("exp");
        if (notAfter.isDouble()) 
        {
            out.notAfter = QDateTime::fromMSecsSinceEpoch(((int64_t)notAfter.toDouble()) * 1000);
        }

        auto token = tokenObject.value("token");
        if (token.isString()) 
        {
            out.token = token.toString();
            out.validity = Katabasis::Validity::Assumed;
        }

        auto refresh_token = tokenObject.value("refresh_token");
        if (refresh_token.isString()) 
        {
            out.refresh_token = refresh_token.toString();
        }

        auto extra = tokenObject.value("extra");
        if (extra.isObject()) 
        {
            out.extra = extra.toObject().toVariantMap();
        }
        return out;
    }

    void profileToJSONV3(QJsonObject& parent, MinecraftProfile p, const char* tokenName) 
    {
        if (p.id.isEmpty()) 
        {
            return;
        }
        QJsonObject out;
        out["id"] = QJsonValue(p.id);
        out["name"] = QJsonValue(p.name);
        if (!p.currentCape.isEmpty()) 
        {
            out["cape"] = p.currentCape;
        }

        {
            QJsonObject skinObj;
            skinObj["id"] = p.skin.id;
            skinObj["url"] = p.skin.url;
            skinObj["variant"] = p.skin.variant;
            if (p.skin.data.size()) 
            {
                skinObj["data"] = QString::fromLatin1(p.skin.data.toBase64());
            }
            out["skin"] = skinObj;
        }

        QJsonArray capesArray;
        for (auto& cape : p.capes) 
        {
            QJsonObject capeObj;
            capeObj["id"] = cape.id;
            capeObj["url"] = cape.url;
            capeObj["alias"] = cape.alias;
            if (cape.data.size()) 
            {
                capeObj["data"] = QString::fromLatin1(cape.data.toBase64());
            }
            capesArray.push_back(capeObj);
        }
        out["capes"] = capesArray;
        parent[tokenName] = out;
    }

    MinecraftProfile profileFromJSONV3(const QJsonObject& parent, const char* tokenName) 
    {
        MinecraftProfile out;
        auto tokenObject = parent.value(tokenName).toObject();
        if (tokenObject.isEmpty()) 
        {
            return out;
        }
        {
            auto idV = tokenObject.value("id");
            auto nameV = tokenObject.value("name");
            if (!idV.isString() || !nameV.isString()) 
            {
                qWarning() << "mandatory profile attributes are missing or of unexpected type";
                return MinecraftProfile();
            }
            out.name = nameV.toString();
            out.id = idV.toString();
        }

        {
            auto skinV = tokenObject.value("skin");
            if (!skinV.isObject())
            {
                qWarning() << "skin is missing";
                return MinecraftProfile();
            }
            auto skinObj = skinV.toObject();
            auto idV = skinObj.value("id");
            auto urlV = skinObj.value("url");
            auto variantV = skinObj.value("variant");
            if (!idV.isString() || !urlV.isString() || !variantV.isString()) 
            {
                qWarning() << "mandatory skin attributes are missing or of unexpected type";
                return MinecraftProfile();
            }
            out.skin.id = idV.toString();
            out.skin.url = urlV.toString();
            out.skin.variant = variantV.toString();

            // data for skin is optional
            auto dataV = skinObj.value("data");
            if (dataV.isString()) 
            {
                // TODO: validate base64
                out.skin.data = QByteArray::fromBase64(dataV.toString().toLatin1());
            }
            else if (!dataV.isUndefined()) 
            {
                qWarning() << "skin data is something unexpected";
                return MinecraftProfile();
            }
        }

        {
            auto capesV = tokenObject.value("capes");
            if (!capesV.isArray()) 
            {
                qWarning() << "capes is not an array!";
                return MinecraftProfile();
            }
            auto capesArray = capesV.toArray();
            for (auto capeV : capesArray) 
            {
                if (!capeV.isObject()) 
                {
                    qWarning() << "cape is not an object!";
                    return MinecraftProfile();
                }
                auto capeObj = capeV.toObject();
                auto idV = capeObj.value("id");
                auto urlV = capeObj.value("url");
                auto aliasV = capeObj.value("alias");
                if (!idV.isString() || !urlV.isString() || !aliasV.isString()) 
                {
                    qWarning() << "mandatory skin attributes are missing or of unexpected type";
                    return MinecraftProfile();
                }
                Cape cape;
                cape.id = idV.toString();
                cape.url = urlV.toString();
                cape.alias = aliasV.toString();

                // data for cape is optional.
                auto dataV = capeObj.value("data");
                if (dataV.isString()) 
                {
                    // TODO: validate base64
                    cape.data = QByteArray::fromBase64(dataV.toString().toLatin1());
                }
                else if (!dataV.isUndefined()) 
                {
                    qWarning() << "cape data is something unexpected";
                    return MinecraftProfile();
                }
                out.capes[cape.id] = cape;
            }
        }
        // current cape
        {
            auto capeV = tokenObject.value("cape");
            if (capeV.isString()) 
            {
                auto currentCape = capeV.toString();
                if (out.capes.contains(currentCape)) 
                {
                    out.currentCape = currentCape;
                }
            }
        }
        out.validity = Katabasis::Validity::Assumed;
        return out;
    }

    void entitlementToJSONV3(QJsonObject& parent, MinecraftEntitlement p) 
    {
        if (p.validity == Katabasis::Validity::None) 
        {
            return;
        }
        QJsonObject out;
        out["ownsMinecraft"] = QJsonValue(p.ownsMinecraft);
        out["canPlayMinecraft"] = QJsonValue(p.canPlayMinecraft);
        parent["entitlement"] = out;
    }

    bool entitlementFromJSONV3(const QJsonObject& parent, MinecraftEntitlement& out) 
    {
        auto entitlementObject = parent.value("entitlement").toObject();
        if (entitlementObject.isEmpty()) 
        {
            return false;
        }
        {
            auto ownsMinecraftV = entitlementObject.value("ownsMinecraft");
            auto canPlayMinecraftV = entitlementObject.value("canPlayMinecraft");
            if (!ownsMinecraftV.isBool() || !canPlayMinecraftV.isBool()) 
            {
                qWarning() << "mandatory attributes are missing or of unexpected type";
                return false;
            }
            out.canPlayMinecraft = canPlayMinecraftV.toBool(false);
            out.ownsMinecraft = ownsMinecraftV.toBool(false);
            out.validity = Katabasis::Validity::Assumed;
        }
        return true;
    }

}

QJsonObject AccountData::saveState() const
{
    QJsonObject output;
    if (this->type == AccountType::Mojang)
    {
        output["type"] = "Mojang";
        if (this->legacy)
        {
            output["legacy"] = true;
        }
        if (this->can_migrate_to_msa)
        {
            output["can_migrate_to_msa"] = true;
        }
        if (this->must_migrate_to_msa)
        {
            output["must_migrate_to_msa"] = true;
        }
    }
    else if (this->type == AccountType::MSA)
    {
        output["type"] = "MSA";
        tokenToJSONV3(output, this->msa_token, "msa");
        tokenToJSONV3(output, this->user_token, "utoken");
        tokenToJSONV3(output, this->xbox_api_token, "xrp-main");
        tokenToJSONV3(output, this->mojangservices_token, "xrp-mc");
    }

    tokenToJSONV3(output, this->yggdrasil_token, "ygg");
    profileToJSONV3(output, this->minecraft_profile, "profile");
    entitlementToJSONV3(output, this->minecraft_entitlement);
    return output;
}

bool AccountData::resumeStateFromV2(QJsonObject data)
{
    // The JSON object must at least have a username for it to be valid.
    if (!data.value("username").isString())
    {
        qCritical() << "Can't load Mojang account info from JSON object. Username field is missing or of the wrong type.";
        return false;
    }

    QString userName = data.value("username").toString("");
    QString clientToken = data.value("clientToken").toString("");
    QString accessToken = data.value("accessToken").toString("");

    QJsonArray profileArray = data.value("profiles").toArray();
    if (profileArray.size() < 1)
    {
        qCritical() << "Can't load Mojang account with username \"" << userName << "\". No profiles found.";
        return false;
    }

    struct AccountProfile
    {
        QString id;
        QString name;
        bool legacy;
    };

    QList<AccountProfile> profiles;
    int currentProfileIndex = 0;
    int index = -1;
    QString currentProfile = data.value("activeProfile").toString("");
    for (QJsonValue profileVal : profileArray)
    {
        index++;
        QJsonObject profileObject = profileVal.toObject();
        QString id = profileObject.value("id").toString("");
        QString name = profileObject.value("name").toString("");
        bool legacy = profileObject.value("legacy").toBool(false);
        if (id.isEmpty() || name.isEmpty())
        {
            qWarning() << "Unable to load a profile" << name << "because it was missing an ID or a name.";
            continue;
        }
        if (id == currentProfile) 
        {
            currentProfileIndex = index;
        }
        profiles.append({ id, name, legacy });
    }
    auto& profile = profiles[currentProfileIndex];

    this->type = AccountType::Mojang;
    this->legacy = profile.legacy;

    this->minecraft_profile.id = profile.id;
    this->minecraft_profile.name = profile.name;
    this->minecraft_profile.validity = Katabasis::Validity::Assumed;

    this->yggdrasil_token.token = accessToken;
    this->yggdrasil_token.extra["clientToken"] = clientToken;
    this->yggdrasil_token.extra["userName"] = userName;
    this->yggdrasil_token.validity = Katabasis::Validity::Assumed;

    this->validity_ = minecraft_profile.validity;
    return true;
}

bool AccountData::resumeStateFromV3(QJsonObject data)
{
    auto typeV = data.value("type");
    if (!typeV.isString()) 
    {
        qWarning() << "Failed to parse account data: type is missing.";
        return false;
    }
    auto typeS = typeV.toString();
    if (typeS == "MSA") 
    {
        this->type = AccountType::MSA;
    }
    else if (typeS == "Mojang") 
    {
        this->type = AccountType::Mojang;
    }
    else 
    {
        qWarning() << "Failed to parse account data: type is not recognized.";
        return false;
    }

    if (this->type == AccountType::Mojang)
    {
        this->legacy = data.value("legacy").toBool(false);
        this->can_migrate_to_msa = data.value("can_migrate_to_msa").toBool(false);
        this->must_migrate_to_msa = data.value("must_migrate_to_msa").toBool(false);
    }

    if (this->type == AccountType::MSA)
    {
        this->msa_token = tokenFromJSONV3(data, "msa");
        this->user_token = tokenFromJSONV3(data, "utoken");
        this->xbox_api_token = tokenFromJSONV3(data, "xrp-main");
        this->mojangservices_token = tokenFromJSONV3(data, "xrp-mc");
    }

    this->yggdrasil_token = tokenFromJSONV3(data, "ygg");
    this->minecraft_profile = profileFromJSONV3(data, "profile");
    if (!entitlementFromJSONV3(data, this->minecraft_entitlement))
    {
        if (this->minecraft_profile.validity != Katabasis::Validity::None)
        {
            this->minecraft_entitlement.canPlayMinecraft = true;
            this->minecraft_entitlement.ownsMinecraft = true;
            this->minecraft_entitlement.validity = Katabasis::Validity::Assumed;
        }
    }

    this->validity_ = this->minecraft_profile.validity;
    return true;
}

QString AccountData::accountDisplayString() const
{
    switch (this->type)
    {
    case AccountType::Mojang: 
    {
        return userName();
    }
    case AccountType::MSA:
    {
        if (this->xbox_api_token.extra.contains("gtg"))
        {
            return this->xbox_api_token.extra["gtg"].toString();
        }
        return "Xbox profile missing";
    }
    default: 
    {
        return "Invalid Account";
    }
    }
}

QString AccountData::userName() const
{
    if (this->type != AccountType::Mojang)
    {
        return QString();
    }
    return this->yggdrasil_token.extra["userName"].toString();
}

QString AccountData::clientToken() const
{
    if (this->type != AccountType::Mojang)
    {
        return QString();
    }
    return this->yggdrasil_token.extra["clientToken"].toString();
}

void AccountData::setClientToken(QString clientToken)
{
    if (this->type != AccountType::Mojang)
    {
        return;
    }
    this->yggdrasil_token.extra["clientToken"] = clientToken;
}

void AccountData::invalidateClientToken()
{
    if (this->type != AccountType::Mojang)
    {
        return;
    }
    this->yggdrasil_token.extra["clientToken"] = QUuid::createUuid().toString().remove(QRegularExpression("[{-}]"));
}

void AccountData::generateClientTokenIfMissing()
{
    if (this->yggdrasil_token.extra.contains("clientToken"))
    {
        return;
    }
    invalidateClientToken();
}

QString AccountData::accessToken() const
{
    return this->yggdrasil_token.token;
}

QString AccountData::profileId() const
{
    return this->minecraft_profile.id;
}

QString AccountData::profileName() const
{
    if (this->minecraft_profile.name.size() == 0)
    {
        return QObject::tr("No profile (%1)").arg(accountDisplayString());
    }
    else 
    {
        return this->minecraft_profile.name;
    }
}

QString AccountData::lastError() const
{
    return this->error_string;
}
