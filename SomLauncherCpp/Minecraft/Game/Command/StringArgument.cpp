#include "StringArgument.h"

StringArgument::StringArgument(const std::string& argument)
	: argument(argument)
{
}

std::string StringArgument::getArgument() const
{
	return this->argument;
}

std::shared_ptr<Argument> StringArgument::clone() const
{
	return std::make_shared<StringArgument>(this->argument);
}

std::vector<std::string> StringArgument::toString(const std::map<std::string, std::string>& keys,
	const std::map<std::string, bool>& features) const
{
	std::string res = this->argument;
	std::regex pattern("\\$\\{(.*?)}");
	std::smatch m;
	while (std::regex_search(res, m, pattern))
	{
		std::string entry = m[0];
		auto it = keys.find(entry);
		if (it != keys.end())
		{
			res = std::regex_replace(res, pattern, it->second);
		}
		else
		{
			res = std::regex_replace(res, pattern, entry);
		}
	}
	return { res };
}

std::string StringArgument::toString() const
{
	return this->argument;
}