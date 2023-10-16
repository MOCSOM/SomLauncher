#ifndef SERVERTYPES_H_
#define SERVERTYPES_H_

#include <string>

enum class ServerTypes
{
	LIVE,
	TEST,
	BETA
};

std::string ServerTypesToString(ServerTypes type);

#endif /*!SERVERTYPES_H_*/
