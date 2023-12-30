#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <vector>
#include <string>
#include <map>

#include "../CompatibilityRule.h"

class Argument
{
protected:
	std::string argument_key = "";
	std::string argument_values = "";

public:
	Argument() = default;

	virtual std::vector<std::string> toString(const std::map<std::string, std::string>& keys, const std::map<std::string, bool>& features) const = 0;

	virtual std::shared_ptr<Argument> clone() const = 0;
};

#endif // !ARGUMENT_H_