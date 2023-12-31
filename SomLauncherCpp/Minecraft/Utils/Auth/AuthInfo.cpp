#include "AuthInfo.h"

AuthInfo::AuthInfo(const std::string& username, const boost::uuids::uuid& uuid, const std::string& accessToken,
	const std::string& userType, const std::string& userProperties)
	: username(username), accessToken(accessToken), userType(userType),
	userProperties(userProperties), uuid(uuid)
{
}

const std::string& AuthInfo::getUsername() const
{
	return this->username;
}

const boost::uuids::uuid& AuthInfo::getUUID() const
{
	return this->uuid;
}

const std::string& AuthInfo::getAccessToken() const
{
	return this->accessToken;
}

const std::string& AuthInfo::getUserType() const
{
	return this->userType;
}

const std::string& AuthInfo::getUserProperties() const
{
	return this->userProperties;
}

//Arguments AuthInfo::getLaunchArguments(const MinecraftCpp::option::LaunchOptions& options)
//{
//	return Arguments();
//}

void AuthInfo::close()
{
}