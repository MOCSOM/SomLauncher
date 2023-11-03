#ifndef RULEDARGUMENT_H_
#define RULEDARGUMENT_H_

#include <vector>
#include <string>
#include <map>
#include <optional>
#include <memory>

#include "Argument.h"
#include "StringArgument.h"

class RuledArgument : public Argument
{
private:
	std::vector<CompatibilityRule> rules;
	std::vector<std::string> value;

public:
	RuledArgument() : rules(std::vector<CompatibilityRule>()), value(std::vector<std::string>()) {}

	RuledArgument(const std::vector<CompatibilityRule>& rules, const std::vector<std::string>& args)
		: rules(rules), value(args) {}

	std::vector<CompatibilityRule> getRules() const {
		return rules;
	}

	std::vector<std::string> getValue() const {
		return value;
	}

	std::unique_ptr<Argument> clone() const override {
		return std::make_unique<RuledArgument>(rules, value);
	}

	std::vector<std::string> toString(const std::map<std::string, std::string>& keys, const std::map<std::string, bool>& features) const override {
		if (CompatibilityRule::appliesToCurrentEnvironment(rules, features) && !value.empty()) {
			std::vector<std::string> result;
			for (const std::string& arg : value) {
				if (!arg.empty()) {
					StringArgument stringArg(arg);
					std::vector<std::string> stringArgResult = stringArg.toString(keys, features);
					if (!stringArgResult.empty()) {
						result.push_back(stringArgResult[0]);
					}
				}
			}
			return result;
		}
		return std::vector<std::string>();
	}
};

#endif // !RULEDARGUMENT_H_