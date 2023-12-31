#ifndef OSRESTRICTION_H_
#define OSRESTRICTION_H_

#include <regex>
#include <string>

#include "../../Web/DownloadClasses.h"

class OSRestriction
{
private:
	std::string name;
	std::string version;
	std::string arch;

public:
	OSRestriction();
	OSRestriction(const std::string& name, const std::string& version = "", const std::string& arch = "");
	~OSRestriction() = default;

public:
	const std::string& getName() const;
	const std::string& getVersion() const;
	const std::string& getArch() const;

public:
	bool allow() const;
};

#endif // !OSRESTRICTION_H_