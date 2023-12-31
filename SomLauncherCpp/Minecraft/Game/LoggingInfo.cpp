#include "LoggingInfo.h"

LoggingInfo::LoggingInfo()
{
}

LoggingInfo::LoggingInfo(IdDownloadInfo file, std::string argument, std::string type)
{
	this->file = file;
	this->argument = argument;
	this->type = type;
}

LoggingInfo::~LoggingInfo()
{
}

const IdDownloadInfo& LoggingInfo::getFile()
{
	return this->file;
}

const std::string& LoggingInfo::getArgument()
{
	return this->argument;
}

const std::string& LoggingInfo::getType()
{
	return this->type;
}

bool LoggingInfo::empty() const
{
	return this->argument.empty() && this->file.empty() && this->type.empty();
}

void LoggingInfo::validate()
{
	this->file.validate();

	if (this->argument.empty())
	{
		throw JsonParseException("LoggingInfo.argument is empty.");
	}
	if (this->type.empty())
	{
		throw JsonParseException("LoggingInfo.type is empty.");
	}
}
