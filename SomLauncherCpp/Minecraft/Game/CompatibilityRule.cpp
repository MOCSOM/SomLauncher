#include "CompatibilityRule.h"

CompatibilityRule::CompatibilityRule()
	: action(CompatibilityRule::Action::ALLOW), os(nullptr), features(nullptr)
{
}

CompatibilityRule::CompatibilityRule(CompatibilityRule::Action action, const OSRestriction* os,
	const std::map<std::string, bool>* features)
	: action(action), os(os), features(features)
{
}

std::optional<CompatibilityRule::Action> CompatibilityRule::getAppliedAction(
	const std::map<std::string, bool>& supported_features) const
{
	if (this->os != nullptr && !this->os->allow())
		return std::nullopt;

	if (this->features != nullptr)
	{
		for (const auto& entry : *features)
		{
			auto feature_it = supported_features.find(entry.first);
			if (feature_it == supported_features.end() || feature_it->second != entry.second)
			{
				return std::nullopt;
			}
		}
	}

	return action;
}

bool CompatibilityRule::appliesToCurrentEnvironment(const std::vector<CompatibilityRule>& rules,
	const std::map<std::string, bool>& features)
{
	if (rules.empty())
		return true;

	Action action = Action::DISALLOW;
	for (const CompatibilityRule& rule : rules)
	{
		std::optional<Action> this_action = rule.getAppliedAction(features);
		if (this_action.has_value())
		{
			action = this_action.value();
		}
	}

	return action == Action::ALLOW;
}

const CompatibilityRule::Action& CompatibilityRule::getAction() const
{
	return this->action;
}

const OSRestriction* CompatibilityRule::getOs() const
{
	return this->os;
}

const std::map<std::string, bool>* CompatibilityRule::getFeatures() const
{
	return this->features;
}

bool operator==(const std::vector<CompatibilityRule>& rules1, const std::vector<CompatibilityRule>& rules2)
{
	return rules1 == rules2;
}

bool operator==(const CompatibilityRule& left, const CompatibilityRule& right)
{
	return left.getAction() == right.getAction() &&
		left.getOs() == right.getOs() &&
		left.getFeatures() == right.getFeatures();
}