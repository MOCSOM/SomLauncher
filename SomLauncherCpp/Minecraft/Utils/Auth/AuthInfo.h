#ifndef AUTHINFO_H_
#define AUTHINFO_H_

#include <iostream>
#include <string>
//#include <uuid/uuid.h>
#include <stdexcept>
#include <memory>

#include "../../Game/Arguments.h"
#include "../../Minecraftus.h"
#include "../../MinecraftOptions.h"

class AuthInfo {
public:
	static const std::string USER_TYPE_MSA;
	static const std::string USER_TYPE_MOJANG;
	static const std::string USER_TYPE_LEGACY;

private:
	const std::string username;
	uuid_t uuid = uuid_t();
	const std::string accessToken;
	const std::string userType;
	const std::string userProperties;

public:
	AuthInfo(const std::string& username, const uuid_t& uuid, const std::string& accessToken, const std::string& userType, const std::string& userProperties)
		: username(username), accessToken(accessToken), userType(userType), userProperties(userProperties)
	{
		memcpy(&this->uuid, &uuid, sizeof(uuid_t));
	}

	const std::string& getUsername() const {
		return username;
	}

	const uuid_t& getUUID() const {
		return uuid;
	}

	const std::string& getAccessToken() const {
		return accessToken;
	}

	const std::string& getUserType() const {
		return userType;
	}

	const std::string& getUserProperties() const {
		return userProperties;
	}

	/*static Arguments getLaunchArguments(const MinecraftCpp::option::LaunchOptions& options) {
		return nullptr;
	}*/

	virtual void close() {
	}
};

#endif // !AUTHINFO_H_