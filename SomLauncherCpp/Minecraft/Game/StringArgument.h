#ifndef STRINGARGUMENT_H_
#define STRINGARGUMENT_H_

#include <string>
#include <vector>
#include <map>

#include "Argument.h"

class StringArgument : public Argument
{
private:
	std::string argument;

public:
	StringArgument(const std::string& argument) : argument(argument) {}

	std::string getArgument() const {
		return argument;
	}

	std::unique_ptr<Argument> clone() const override {
		return std::make_unique<StringArgument>(argument);
	}

	std::vector<std::string> toString(const std::map<std::string, std::string>& keys, const std::map<std::string, bool>& features) const override {
		std::string res = argument;
		std::regex pattern("\\$\\{(.*?)}");
		std::smatch m;
		while (std::regex_search(res, m, pattern)) {
			std::string entry = m[0];
			auto it = keys.find(entry);
			if (it != keys.end()) {
				res = std::regex_replace(res, pattern, it->second);
			}
			else {
				res = std::regex_replace(res, pattern, entry);
			}
		}
		return { res };
	}

	std::string toString() const {
		return argument;
	}
};

#endif // !RULEDARGUMENT_H_