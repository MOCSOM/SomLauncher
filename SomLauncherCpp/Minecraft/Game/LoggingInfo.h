#ifndef GAME_LOGGINGINFO_H_
#define GAME_LOGGINGINFO_H_

#include <string>

#include "../Utils/Validation.h"
#include "IdDownloadInfo.h"

class LoggingInfo : public Validation
{
private:
	IdDownloadInfo file;
	std::string argument;
	std::string type;

public:
	LoggingInfo();
	LoggingInfo(IdDownloadInfo file, std::string argument = "", std::string type = "");
	~LoggingInfo();

public:
	const IdDownloadInfo& getFile();
	const std::string& getArgument();
	const std::string& getType();

public:
	bool empty() const;

private:
	// Унаследовано через Validation
	void validate() override;

};

#endif // !GAME_LOGGINGINFO_H_

