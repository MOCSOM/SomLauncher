#include "CommandBuilder.h"

std::string CommandBuilder::parse(const std::string& s)
{
	if (OS == "windows") {
		return toBatchStringLiteral(s);
	}
	else {
		return toShellStringLiteral(s);
	}
}

CommandBuilder& CommandBuilder::add(const std::vector<std::string>& args)
{
	for (const std::string& s : args)
	{
		raw.push_back(s);
	}
	return *this;
}

CommandBuilder& CommandBuilder::addAll(const std::vector<std::string>& args)
{
	return add(args);
}

CommandBuilder& CommandBuilder::addWithoutParsing(const std::vector<std::string>& args)
{
	for (const std::string& s : args) {
		raw.push_back(s);
	}
	return *this;
}

CommandBuilder& CommandBuilder::addAllWithoutParsing(const std::vector<std::string>& args)
{
	return addWithoutParsing(args);
}

void CommandBuilder::addAllDefault(const std::vector<std::string>& args, bool parse)
{
	for (const std::string& arg : args)
	{
		if (arg.rfind("-D", 0) == 0)
		{
			size_t idx = arg.find('=');
			if (idx != std::string::npos)
			{
				addDefault(arg.substr(0, idx + 1), arg.substr(idx + 1), parse);
			}
			else
			{
				std::string opt = arg + "=";
				bool suppressed = false;
				for (const std::string& item : this->raw)
				{
					if (item.rfind(opt, 0) == 0)
					{
						std::cout << "Default option '" << arg << "' is suppressed by '" << item << "'" << std::endl;
						suppressed = true;
						break;
					}
					else if (item == arg)
					{
						suppressed = true;
						break;
					}
				}
				if (!suppressed)
				{
					this->raw.push_back(arg);
				}
			}
		}
		else if (arg.rfind("-XX:", 0) == 0)
		{
			std::smatch matches;
			if (std::regex_match(arg, matches, this->UNSTABLE_OPTION_PATTERN))
			{
				addUnstableDefault(matches[1], matches[2], parse);
			}
			else
			{
				if (std::regex_match(arg, matches, this->UNSTABLE_BOOLEAN_OPTION_PATTERN))
				{
					addUnstableDefault(matches[2], (matches[1] == "+"), parse);
				}
				else
				{
					for (const std::string& item : this->raw)
					{
						if (item == arg)
						{
							break;
						}
					}
					raw.push_back(arg);
				}
			}
		}
		else if (arg.rfind("-X", 0) == 0)
		{
			std::string opt;
			std::string value;
			for (const std::string& prefix : { "-Xmx", "-Xms", "-Xmn", "-Xss" })
			{
				if (arg.rfind(prefix, 0) == 0)
				{
					opt = prefix;
					value = arg.substr(prefix.size());
					addDefault(opt, value, parse);
					break;
				}
			}
		}
		else
		{
			if (std::find(raw.begin(), raw.end(), arg) == this->raw.end())
			{
				raw.push_back(arg);
			}
		}
	}
}

void CommandBuilder::addAllDefault(const std::vector<std::string>& args)
{
	addAllDefault(args, true);
}

void CommandBuilder::addAllDefaultWithoutParsing(const std::vector<std::string>& args)
{
	addAllDefault(args, false);
}

std::string CommandBuilder::addDefault(const std::string& opt, const std::string& value)
{
	return addDefault(opt, value, true);
}

std::string CommandBuilder::addDefault(const std::string& opt, const std::string& value, bool parse)
{
	for (const std::string& item : this->raw)
	{
		if (item.find(opt) == 0)
		{
			std::cout << "Default option '" << opt << value << "' is suppressed by '" << item << "'" << std::endl;
			return item;
		}
	}
	this->raw.push_back(opt + value);
	return "";
}

std::string CommandBuilder::addUnstableDefault(const std::string& opt, bool value)
{
	return addUnstableDefault(opt, value, true);
}

std::string CommandBuilder::addUnstableDefault(const std::string& opt, bool value, bool parse)
{
	for (const std::string& item : this->raw)
	{
		std::smatch matches;
		if (std::regex_match(item, matches, UNSTABLE_BOOLEAN_OPTION_PATTERN))
		{
			if (matches[2] == opt)
			{
				return item;
			}
		}
	}

	if (value)
	{
		raw.push_back("-XX:+" + opt);
	}
	else
	{
		raw.push_back("-XX:-" + opt);
	}
	return "";
}

std::string CommandBuilder::addUnstableDefault(const std::string& opt, const std::string& value)
{
	return addUnstableDefault(opt, value, true);
}

std::string CommandBuilder::addUnstableDefault(const std::string& opt, const std::string& value, bool parse)
{
	for (const std::string& item : this->raw)
	{
		std::smatch matches;
		if (std::regex_match(item, matches, this->UNSTABLE_OPTION_PATTERN))
		{
			if (matches[1] == opt)
			{
				return item;
			}
		}
	}

	this->raw.push_back("-XX:" + opt + "=" + value);
	return "";
}

bool CommandBuilder::removeIf(std::function<bool(const std::string&)> pred)
{
	auto it = std::remove_if(this->raw.begin(), this->raw.end(), pred);
	if (it != this->raw.end())
	{
		this->raw.erase(it, this->raw.end());
		return true;
	}
	return false;
}

bool CommandBuilder::noneMatch(std::function<bool(const std::string&)> predicate)
{
	return std::none_of(this->raw.begin(), this->raw.end(), predicate);
}

std::string CommandBuilder::toString()
{
	std::string result;
	for (const std::string& item : raw)
	{
		result += parse(item) + " ";
	}
	return result;
}

std::vector<std::string> CommandBuilder::asList()
{
	return this->raw;
}

std::vector<std::string> CommandBuilder::asMutableList()
{
	//TODO: Сделать функцию mutable
	return this->raw;
}

std::string CommandBuilder::escape(const std::string& str, const std::string& escapeChars)
{
	std::string result = str;
	for (char ch : escapeChars)
	{
		size_t pos = 0;
		while ((pos = result.find(ch, pos)) != std::string::npos)
		{
			result.replace(pos, 1, "\\" + std::string(1, ch));
			pos += 2;
		}
	}
	return result;
}

std::string CommandBuilder::toBatchStringLiteral(const std::string& s)
{
	const std::string escapeChars = " \t\"^&<>|";
	return (s.find_first_of(escapeChars) != std::string::npos) ? "\"" + escape(s, escapeChars) + "\"" : s;
}

std::string CommandBuilder::toShellStringLiteral(const std::string& s)
{
	const std::string escapeChars = " \t\"!#$&'()*,;<=>?[\\]^`{|}~";
	return (s.find_first_of(escapeChars) != std::string::npos) ? "\"" + escape(s, escapeChars) + "\"" : s;
}