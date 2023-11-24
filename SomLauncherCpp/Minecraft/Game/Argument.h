#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <vector>
#include <string>
#include <map>

#include "CompatibilityRule.h"

class Argument
{
public:
	Argument() {}

	virtual std::vector<std::string> toString(const std::map<std::string, std::string>& keys, const std::map<std::string, bool>& features) const = 0;

	virtual std::unique_ptr<Argument> clone() const = 0;
	// В C++ вместо аннотации @Immutable можно использовать const-квалификаторы и дизайн класса, чтобы обеспечить неизменяемость.
};

#endif // !ARGUMENT_H_