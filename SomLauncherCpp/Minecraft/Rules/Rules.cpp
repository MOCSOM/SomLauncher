#include "Rules.h"

bool rules::utils::parseRuleList(Json::JsonValue& data, const QString& rule_string)
{
	/*
	Parse a list of rules
	*/

	if (!data.is_exist(rule_string.toStdString()))
	{
		return true;
	}
	for (Json::JsonValue var : data[rule_string.toStdString()].get_array())
	{
		if (!parseSingleRule(var))
		{
			return false;
		}
	}
	return true;
}

bool rules::utils::parseSingleRule(Json::JsonValue& rule)
{
	/*
	Parse a single rule from the versions.json
	*/
	bool returnvalue = false;
	if (rule["action"].to_string() == "allow")
	{
		returnvalue = false;
	}
	else if (rule["action"].to_string() == "disallow")
	{
		returnvalue = true;
	}
	if (rule.is_exist("os"))
	{
		for (auto& var : rule["os"].get_object())
		{
			if (var.first == "name")
			{
				if (var.second.to_string() == "windows" && OS != "Windows")
				{
					return returnvalue;
				}
				else if (var.second.to_string() == "osx" && OS != "Darwin")
				{
					return returnvalue;
				}
				else if (var.second.to_string() == "linux" && OS != "Linux")
				{
					return returnvalue;
				}
			}
			else if (var.first == "arch")
			{
				if (var.second.to_string() == "x86" && ARCH != "x86")
				{
					return returnvalue;
				}
			}
			else if (var.first == "version")
			{
				if (var.second.to_string() != OS)
				{
					return returnvalue;
				}
			}
		}
	}
	if (rule.is_exist("features"))
	{
		for (auto& var : rule["features"].get_object())
		{
			/*if (var.first == "has_custom_resolution" && !options.get("customResolution", false))
			{
				return returnvalue;
			}
			else if (var.first == "is_demo_user" && !options.get("demo", false))
			{
				return returnvalue;
			}*/
			qWarning() << "resolution and demo dosent exist";
		}
	}
	return !returnvalue;
}
