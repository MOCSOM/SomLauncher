#ifndef COMPATIBILITYRULE_H_
#define COMPATIBILITYRULE_H_

#include <vector>
#include <map>
#include <optional>
#include <string>

#include "OSRestriction.h"

class CompatibilityRule {
public:
	enum class Action {
		ALLOW,
		DISALLOW
	};

	CompatibilityRule() : action(Action::ALLOW), os(nullptr), features(nullptr) {}

	CompatibilityRule(Action action, const OSRestriction* os = nullptr, const std::map<std::string, bool>* features = nullptr)
		: action(action), os(os), features(features) {}

	std::optional<Action> getAppliedAction(const std::map<std::string, bool>& supportedFeatures) const {
		if (os != nullptr && !os->allow())
			return std::nullopt;

		if (features != nullptr) {
			for (const auto& entry : *features) {
				auto featureIt = supportedFeatures.find(entry.first);
				if (featureIt == supportedFeatures.end() || featureIt->second != entry.second) {
					return std::nullopt;
				}
			}
		}

		return action;
	}

	static bool appliesToCurrentEnvironment(const std::vector<CompatibilityRule>& rules) {
		return appliesToCurrentEnvironment(rules, std::map<std::string, bool>());
	}

	static bool appliesToCurrentEnvironment(const std::vector<CompatibilityRule>& rules, const std::map<std::string, bool>& features) {
		if (rules.empty())
			return true;

		Action action = Action::DISALLOW;
		for (const CompatibilityRule& rule : rules) {
			std::optional<Action> thisAction = rule.getAppliedAction(features);
			if (thisAction.has_value()) {
				action = thisAction.value();
			}
		}

		return action == Action::ALLOW;
	}

	static bool equals(const std::vector<CompatibilityRule>& rules1, const std::vector<CompatibilityRule>& rules2) {
		return rules1 == rules2;
	}

	bool operator==(const CompatibilityRule& other) const {
		return action == other.action && os == other.os && features == other.features;
	}

private:
	Action action;
	const OSRestriction* os;
	const std::map<std::string, bool>* features;
};

#endif // !COMPATIBILITYRULE_H_