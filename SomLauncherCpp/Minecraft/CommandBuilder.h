#ifndef COMMANDBUILDER_H_
#define COMMANDBUILDER_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

#include "Minecraftus.h"

class CommandBuilder
{
private:
	const std::regex UNSTABLE_OPTION_PATTERN;
	const std::regex UNSTABLE_BOOLEAN_OPTION_PATTERN;

	std::vector<std::string> raw;

public:
	CommandBuilder() = default;
	~CommandBuilder() = default;

	std::string parse(const std::string& s);

	CommandBuilder& add(const std::vector<std::string>& args);
	template<class... ARGS>
	CommandBuilder& add(ARGS... args);

	CommandBuilder& addAll(const std::vector<std::string>& args);

	CommandBuilder& addWithoutParsing(const std::vector<std::string>& args);

	CommandBuilder& addAllWithoutParsing(const std::vector<std::string>& args);

	void addAllDefault(const std::vector<std::string>& args, bool parse);
	void addAllDefault(const std::vector<std::string>& args);

	void addAllDefaultWithoutParsing(const std::vector<std::string>& args);

	std::string addDefault(const std::string& opt, const std::string& value);
	std::string addDefault(const std::string& opt, const std::string& value, bool parse);

	std::string addUnstableDefault(const std::string& opt, bool value);
	std::string addUnstableDefault(const std::string& opt, bool value, bool parse);
	std::string addUnstableDefault(const std::string& opt, const std::string& value);
	std::string addUnstableDefault(const std::string& opt, const std::string& value, bool parse);

	bool removeIf(std::function<bool(const std::string&)> pred);

	bool noneMatch(std::function<bool(const std::string&)> predicate);

	std::string toString();

	std::vector<std::string> asList();

	std::vector<std::string> asMutableList();

private:
	std::string escape(const std::string& str, const std::string& escapeChars);

	std::string toBatchStringLiteral(const std::string& s);

	std::string toShellStringLiteral(const std::string& s);
};

template<class ...ARGS>
inline CommandBuilder& CommandBuilder::add(ARGS ...args)
{
	for (const std::string& s : args)
	{
		raw.push_back(s);
	}
	return *this;
}

#endif // !COMMANDBUILDER_H_
