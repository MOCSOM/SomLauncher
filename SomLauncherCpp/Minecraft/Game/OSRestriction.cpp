#include "OSRestriction.h"

OSRestriction::OSRestriction()
	: name(OS), version(""), arch("")
{
}

OSRestriction::OSRestriction(const std::string& name, const std::string& version, const std::string& arch)
	: name(name), version(version), arch(arch)
{
}

const std::string& OSRestriction::getName() const
{
	return this->name;
}

const std::string& OSRestriction::getVersion() const
{
	return this->version;
}

const std::string& OSRestriction::getArch() const
{
	return this->arch;
}

bool OSRestriction::allow() const
{
	if (this->name != "" && this->name != OS) {
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
