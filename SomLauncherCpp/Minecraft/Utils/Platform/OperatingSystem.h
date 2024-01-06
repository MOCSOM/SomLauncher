#ifndef OPERATINGSYSTEM_H_
#define OPERATINGSYSTEM_H_

#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <optional>
#include <filesystem>

class OperatingSystem
{
private:
	std::string checked_name;

public:
	enum OSName
	{
		WINDOWS,
		LINUX,
		OSX,
		UNKNOWN
	}
	os_name;

	class PhysicalMemoryStatus;

public:
	OperatingSystem(OSName name, const std::string& checkedName);
	~OperatingSystem() = default;


public:
	const std::string& getCheckedName() const;

public:
	static OperatingSystem CURRENT_OS;

public:
	static std::optional<PhysicalMemoryStatus> getPhysicalMemoryStatus();

	static int TOTAL_MEMORY;
	static int SUGGESTED_MEMORY;
	static wchar_t PATH_SEPARATOR;
	static wchar_t FILE_SEPARATOR;
	static wchar_t LINE_SEPARATOR;
	static std::string NATIVE_CHARSET;
	static int SYSTEM_BUILD_NUMBER;
	static std::string SYSTEM_NAME;
	static std::string SYSTEM_VERSION;
	static std::regex INVALID_RESOURCE_CHARACTERS;
	static std::vector<std::string> INVALID_RESOURCE_BASENAMES;
	static std::vector<std::string> INVALID_RESOURCE_FULLNAMES;

	static OSName parseOSName(const std::string& name);

	static void forceGC();

	static std::string getWorkingDirectory(const std::string& folder);

	static bool isNameValid(const std::string& name);

	class PhysicalMemoryStatus
	{
	private:
		long total;
		long available;

	public:
		long getTotal() const;

	public:
		double getTotalGB() const;
		bool hasAvailable() const;
		long getUsed() const;
		double getUsedGB() const;
		double getAvailableGB();
		static double toGigaBytes(long bytes);
	};

	static void initStaticVariables();
};



#endif // !OPERATINGSYSTEM_H_