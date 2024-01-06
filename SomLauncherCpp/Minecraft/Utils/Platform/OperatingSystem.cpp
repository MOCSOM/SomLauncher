#include "OperatingSystem.h"

OperatingSystem::OperatingSystem(OSName name, const std::string& checkedName)
	: os_name(name), checked_name(checkedName)
{
	initStaticVariables();
}



const std::string& OperatingSystem::getCheckedName() const
{
	return this->checked_name;
}

OperatingSystem::OSName OperatingSystem::parseOSName(const std::string& name)
{
	return OSName();
}

std::optional<OperatingSystem::PhysicalMemoryStatus> OperatingSystem::getPhysicalMemoryStatus()
{
	return std::optional<PhysicalMemoryStatus>();
}

void OperatingSystem::forceGC()
{
}

std::string OperatingSystem::getWorkingDirectory(const std::string& folder)
{
	return std::string();
}

bool OperatingSystem::isNameValid(const std::string& name)
{
	return false;
}

void OperatingSystem::initStaticVariables()
{
	TOTAL_MEMORY = getPhysicalMemoryStatus().value_or(1024).getTotalGB();

#if defined(_WIN32) || defined(_WIN64)
	CURRENT_OS = OperatingSystem(OperatingSystem::OSName::WINDOWS, "windows");
#elif defined(__APPLE__)
	CURRENT_OS = OperatingSystem(OperatingSystem::OSName::OSX, "");
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
	CURRENT_OS = OperatingSystem(OperatingSystem::OSName::LINUX, "");
#else
#error unsupported platform
#endif


	TOTAL_MEMORY = 0;
	SYSTEM_BUILD_NUMBER = -1;
	SUGGESTED_MEMORY = TOTAL_MEMORY >= 32768 ? 8192 : static_cast<int>((1 * TOTAL_MEMORY / 4 / 128) * 128);
	PATH_SEPARATOR = std::filesystem::path::preferred_separator;
	FILE_SEPARATOR = std::filesystem::path::preferred_separator;
	LINE_SEPARATOR = L'\n';
	NATIVE_CHARSET = "UTF-8";
	SYSTEM_BUILD_NUMBER = -1;
	SYSTEM_NAME = CURRENT_OS.checked_name;
	SYSTEM_VERSION = "Unknown Version";

#if defined(_WIN32) || defined(_WIN64)
	INVALID_RESOURCE_CHARACTERS = std::regex("[/\"<>|?*:\\\\]"); //std::regex("^(?<key>.*?):\\s+(?<value>\\d+) kB?$");
	INVALID_RESOURCE_BASENAMES = { "aux", "com1", "com2", "com3", "com4",
						"com5", "com6", "com7", "com8", "com9", "con", "lpt1", "lpt2",
						"lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9", "nul", "prn"
	};
	INVALID_RESOURCE_FULLNAMES = { "clock$" };
#elif defined(__APPLE__)
	INVALID_RESOURCE_CHARACTERS = std::regex();
	INVALID_RESOURCE_BASENAMES = {};
	INVALID_RESOURCE_FULLNAMES = {};
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
	INVALID_RESOURCE_CHARACTERS = std::regex();
	INVALID_RESOURCE_BASENAMES = {};
	INVALID_RESOURCE_FULLNAMES = {};
#else
#error unsupported platform
#endif
}

long OperatingSystem::PhysicalMemoryStatus::getTotal() const
{
	return this->total;
}

double OperatingSystem::PhysicalMemoryStatus::getTotalGB() const
{
	return toGigaBytes(this->total);
}

bool OperatingSystem::PhysicalMemoryStatus::hasAvailable() const
{
	return this->available >= 0;
}

long OperatingSystem::PhysicalMemoryStatus::getUsed() const
{
	return hasAvailable() ? this->total - this->available : 0;
}

double OperatingSystem::PhysicalMemoryStatus::getUsedGB() const
{
	return toGigaBytes(getUsed());
}

double OperatingSystem::PhysicalMemoryStatus::getAvailableGB()
{
	return toGigaBytes(this->available);
}

double OperatingSystem::PhysicalMemoryStatus::toGigaBytes(long bytes)
{
	return bytes / 1024. / 1024. / 1024.;
}