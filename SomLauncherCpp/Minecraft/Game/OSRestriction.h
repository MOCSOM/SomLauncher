#ifndef OSRESTRICTION_H_
#define OSRESTRICTION_H_

#include <string>
#include <regex>

#include "../../Web/DownloadClasses.h"

class OSRestriction {
public:
	OSRestriction() : name(OS), version(""), arch("") {}

	OSRestriction(const std::string& name) : name(name), version(""), arch("") {}

	OSRestriction(const std::string& name, const std::string& version) : name(name), version(version), arch("") {}

	OSRestriction(const std::string& name, const std::string& version, const std::string& arch)
		: name(name), version(version), arch(arch) {}

	const std::string& getName() const {
		return name;
	}

	const std::string& getVersion() const {
		return version;
	}

	const std::string& getArch() const {
		return arch;
	}

	bool allow() const {
		if (name != "" && name != OS) {
			return false;
		}

		/*if (!version.empty()) {
			std::regex versionRegex(version);
			if (!std::regex_match(OperatingSystem::SYSTEM_VERSION, versionRegex)) {
				return false;
			}
		}*/

		/*if (!arch.empty()) {
			std::regex archRegex(arch);
			if (!std::regex_match(Architecture::SYSTEM_ARCH.getCheckedName(), archRegex)) {
				return false;
			}
		}*/

		return true;
	}

private:
	std::string name;
	std::string version;
	std::string arch;
};

#endif // !OSRESTRICTION_H_