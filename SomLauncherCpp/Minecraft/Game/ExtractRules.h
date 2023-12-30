#ifndef EXTRACTRULES_H_
#define EXTRACTRULES_H_

#include <algorithm>
#include <string>
#include <vector>

class ExtractRules
{
private:
	std::vector<std::string> exclude;

public:
	static const ExtractRules EMPTY;

public:
	ExtractRules();
	ExtractRules(const std::vector<std::string>& exclude);

public:
	const std::vector<std::string>& getExclude() const;

public:
	bool shouldExtract(const std::string& path) const;
};

#endif // !EXTRACTRULES_H_