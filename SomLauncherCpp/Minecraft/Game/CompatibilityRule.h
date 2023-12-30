#ifndef COMPATIBILITYRULE_H_
#define COMPATIBILITYRULE_H_

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "OSRestriction.h"

class CompatibilityRule
{
public:
	enum class Action
	{
		ALLOW,
		DISALLOW
	};

private:
	CompatibilityRule::Action action;
	const OSRestriction* os;
	const std::map<std::string, bool>* features;

public:
	CompatibilityRule();
	CompatibilityRule(CompatibilityRule::Action action, const OSRestriction* os = nullptr,
		const std::map<std::string, bool>* features = nullptr);
	~CompatibilityRule() = default;

public:
	std::optional<CompatibilityRule::Action> getAppliedAction(
		const std::map<std::string, bool>& supported_features) const;

	static bool appliesToCurrentEnvironment(const std::vector<CompatibilityRule>& rules,
		const std::map<std::string, bool>& features = std::map<std::string, bool>());

public:
	const CompatibilityRule::Action& getAction() const;
	const OSRestriction* getOs() const;
	const std::map<std::string, bool>* getFeatures() const;
};

inline bool operator==(const std::vector<CompatibilityRule>& rules1, const std::vector<CompatibilityRule>& rules2);
inline bool operator==(const CompatibilityRule& left, const CompatibilityRule& right);

#endif // !COMPATIBILITYRULE_H_