#include "RuledArgument.h"

RuledArgument::RuledArgument()
	: rules(std::vector<CompatibilityRule>()), value(std::vector<std::string>())
{
}

RuledArgument::RuledArgument(const std::vector<CompatibilityRule>& rules, const std::vector<std::string>& args)
	: rules(rules), value(args)
{
}

std::vector<CompatibilityRule> RuledArgument::getRules() const
{
	return rules;
}

std::vector<std::string> RuledArgument::getValue() const
{
	return value;
}

std::shared_ptr<Argument> RuledArgument::clone() const
{
	return std::make_shared<RuledArgument>(this->rules, this->value);
}

std::vector<std::string> RuledArgument::toString(const std::map<std::string, std::string>& keys,
	const std::map<std::string, bool>& features) const
{
	if (CompatibilityRule::appliesToCurrentEnvironment(this->rules, features) && !this->value.empty())
	{
		std::vector<std::string> result;
		for (const std::string& arg : value)
		{
			if (!arg.empty())
			{
				StringArgument string_arg(arg);
				std::vector<std::string> string_arg_result = string_arg.toString(keys, features);
				if (!string_arg_result.empty())
				{
					result.push_back(string_arg_result[0]);
				}
			}
		}
		return result;
	}
	return std::vector<std::string>();
}