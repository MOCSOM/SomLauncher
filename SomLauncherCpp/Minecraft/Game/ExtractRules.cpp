#include "ExtractRules.h"

ExtractRules::ExtractRules()
	: exclude()
{
}

ExtractRules::ExtractRules(const std::vector<std::string>& exclude)
	: exclude(exclude)
{
}

const std::vector<std::string>& ExtractRules::getExclude() const
{
	return this->exclude;
}

bool ExtractRules::shouldExtract(const std::string& path) const
{
	// Check if any exclusion matches the path
	return std::none_of(this->exclude.begin(), this->exclude.end(),
		[&path](const std::string& exclusion) -> bool
		{
			return path.find(exclusion) == 0;
		});
}