#ifndef AUTHINFO_H_
#define AUTHINFO_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/basic_name_generator.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "../../Game/Command/Arguments.h"
#include "../../Minecraftus.h"
#include "../../MinecraftOptions.h"

class AuthInfo
{
public:
	const std::string USER_TYPE_MSA = "msa";
	const std::string USER_TYPE_MOJANG = "mojang";
	const std::string USER_TYPE_LEGACY = "legacy";

private:
	const std::string username;
	const boost::uuids::uuid uuid;
	const std::string accessToken;
	const std::string userType;
	const std::string userProperties;

public:
	AuthInfo(const std::string& username, const boost::uuids::uuid& uuid, const std::string& accessToken,
		const std::string& userType, const std::string& userProperties);

	const std::string& getUsername() const;

	const boost::uuids::uuid& getUUID() const;

	const std::string& getAccessToken() const;

	const std::string& getUserType() const;

	const std::string& getUserProperties() const;

	//static Arguments getLaunchArguments(const MinecraftCpp::option::LaunchOptions& options);

	virtual void close();
};

#endif // !AUTHINFO_H_