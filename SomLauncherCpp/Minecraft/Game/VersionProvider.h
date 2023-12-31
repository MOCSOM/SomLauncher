#ifndef GAME_VERSIONPROVIDER_H_
#define GAME_VERSIONPROVIDER_H_

#include <string>

#include "../Version.h"

class VersionProvider
{
public:
	VersionProvider() = default;
	virtual ~VersionProvider() = 0;

public:
	/**
	* Does the version of id exist?
	*
	* @param id the id of version
	* @return true if the version exists
	*/
	virtual bool hasVersion() const = 0;

	/**
	* Get the version
	*
	* @param id the id of version
	* @return the version you want
	*/
	virtual const Version& getVersion(const std::string& id) const = 0;
};

#endif // !GAME_VERSIONPROVIDER_H_
