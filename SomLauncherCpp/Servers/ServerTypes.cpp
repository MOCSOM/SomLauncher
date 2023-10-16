#include "ServerTypes.h"

std::string ServerTypesToString(ServerTypes type)
{
	switch (type)
	{
	case ServerTypes::LIVE:
		return "LIVE";
		break;
	case ServerTypes::TEST:
		return "TEST";
		break;
	case ServerTypes::BETA:
		return "BETA";
		break;
	default:
		break;
	}
	return std::string();
}