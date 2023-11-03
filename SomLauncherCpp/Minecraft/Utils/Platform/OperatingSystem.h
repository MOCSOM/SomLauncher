#ifndef OPERATINGSYSTEM_H_
#define OPERATINGSYSTEM_H_

//#include <string>
//#include <regex>
//#include <iostream>
//#include <fstream>
//#include <optional>
//
//class OperatingSystem {
//public:
//	enum OSName {
//		WINDOWS,
//		LINUX,
//		OSX,
//		UNKNOWN
//	};
//
//	OperatingSystem(OSName name, const std::string& checkedName)
//		: name(name), checkedName(checkedName) {}
//
//	const std::string& getCheckedName() const {
//		return checkedName;
//	}
//
//	static const OperatingSystem CURRENT_OS;
//
//	static const int TOTAL_MEMORY;
//	static const int SUGGESTED_MEMORY;
//	static const std::string PATH_SEPARATOR;
//	static const std::string FILE_SEPARATOR;
//	static const std::string LINE_SEPARATOR;
//	static const std::string NATIVE_CHARSET;
//	static const int SYSTEM_BUILD_NUMBER;
//	static const std::string SYSTEM_NAME;
//	static const std::string SYSTEM_VERSION;
//	static const std::regex INVALID_RESOURCE_CHARACTERS;
//	static const std::vector<std::string> INVALID_RESOURCE_BASENAMES;
//	static const std::vector<std::string> INVALID_RESOURCE_FULLNAMES;
//
//	static OSName parseOSName(const std::string& name);
//
//	static std::optional<PhysicalMemoryStatus> getPhysicalMemoryStatus();
//
//	static void forceGC();
//
//	static std::string getWorkingDirectory(const std::string& folder);
//
//	static bool isNameValid(const std::string& name);
//
//	struct PhysicalMemoryStatus {
//		long total;
//		long available;
//
//		double getTotalGB() {
//			return toGigaBytes(total);
//		}
//
//		bool hasAvailable() const {
//			return available >= 0;
//		}
//
//		long getUsed() const {
//			return hasAvailable() ? total - available : 0;
//		}
//
//		double getUsedGB() {
//			return toGigaBytes(getUsed());
//		}
//
//		double getAvailableGB() {
//			return toGigaBytes(available);
//		}
//
//		bool hasAvailable() {
//			return available >= 0;
//		}
//
//		static double toGigaBytes(long bytes) {
//			return bytes / 1024. / 1024. / 1024.;
//		}
//	};
//};
//
//const OperatingSystem OperatingSystem::CURRENT_OS = OperatingSystem(UNKNOWN, "");
//
//const int OperatingSystem::TOTAL_MEMORY = 1024;
//const int OperatingSystem::SUGGESTED_MEMORY = 8192;
//const std::string OperatingSystem::PATH_SEPARATOR = "/";
//const std::string OperatingSystem::FILE_SEPARATOR = "/";
//const std::string OperatingSystem::LINE_SEPARATOR = "\n";
//const std::string OperatingSystem::NATIVE_CHARSET = "UTF-8";
//const int OperatingSystem::SYSTEM_BUILD_NUMBER = -1;
//const std::string OperatingSystem::SYSTEM_NAME = "Unknown OS";
//const std::string OperatingSystem::SYSTEM_VERSION = "Unknown Version";
//const std::regex OperatingSystem::INVALID_RESOURCE_CHARACTERS = std::regex("[/\"<>|?*:\\\\]");
//const std::vector<std::string> OperatingSystem::INVALID_RESOURCE_BASENAMES = {};
//const std::vector<std::string> OperatingSystem::INVALID_RESOURCE_FULLNAMES = {};

#endif // !OPERATINGSYSTEM_H_