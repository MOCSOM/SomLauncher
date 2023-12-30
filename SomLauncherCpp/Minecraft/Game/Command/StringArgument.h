#ifndef STRINGARGUMENT_H_
#define STRINGARGUMENT_H_

#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "Argument.h"

class StringArgument : public Argument
{
private:
	std::string argument;

public:
	StringArgument(const std::string& argument);

	std::string getArgument() const;

	std::shared_ptr<Argument> clone() const override;

	std::vector<std::string> toString(const std::map<std::string, std::string>& keys, const std::map<std::string, bool>& features) const override;

	std::string toString() const;
};

#endif // !RULEDARGUMENT_H_