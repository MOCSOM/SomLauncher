#ifndef EXTRACTRULES_H_
#define EXTRACTRULES_H_

#include <vector>
#include <string>
#include <algorithm>

class ExtractRules
{
public:
	static const ExtractRules EMPTY;

	ExtractRules() {
		// Initialize an empty list of exclusions
		exclude = std::vector<std::string>();
	}

	ExtractRules(const std::vector<std::string>& exclude) : exclude(exclude) {}

	const std::vector<std::string>& getExclude() const {
		return exclude;
	}

	bool shouldExtract(const std::string& path) const {
		// Check if any exclusion matches the path
		return std::none_of(exclude.begin(), exclude.end(), [&path](const std::string& exclusion) {
			return path.find(exclusion) == 0;
			});
	}

private:
	std::vector<std::string> exclude;
};

#endif // !EXTRACTRULES_H_