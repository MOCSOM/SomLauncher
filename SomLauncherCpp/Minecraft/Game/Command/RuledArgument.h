#ifndef RULEDARGUMENT_H_
#define RULEDARGUMENT_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Argument.h"
#include "StringArgument.h"

class RuledArgument : public Argument
{
private:
	std::vector<CompatibilityRule> rules;
	std::vector<std::string> value;

public:
	RuledArgument();

	RuledArgument(const std::vector<CompatibilityRule>& rules, const std::vector<std::string>& args);

	std::vector<CompatibilityRule> getRules() const;

	std::vector<std::string> getValue() const;

	std::shared_ptr<Argument> clone() const override;

	std::vector<std::string> toString(const std::map<std::string, std::string>& keys,
		const std::map<std::string, bool>& features) const override;
};

#endif // !RULEDARGUMENT_H_