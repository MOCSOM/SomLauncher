#include "../pch.h"

#include "Json.h"

//cliext::map<System::String^, Json::JsonNode^> Json::JsonObject::operator=(cliext::map<System::String^, Json::JsonNode^> value)
//{
//    return this->values = value;
//}

Json::JsonObject::JsonObject() : Json::JsonNode(Json::JsonTypes::Object)
{
	this->values = std::unordered_map<std::string, Json::JsonValue>();
}

Json::JsonObject::~JsonObject()
{
	/*for (auto& var : this->values)
	{
		if (var.second->get_type() == Json::JsonTypes::Object)
		{
			var.second->~JsonNode();
		}
		else
		{
			var.second->~JsonNode();
			delete var.second;
		}
	}*/

	this->values.clear();
}

void Json::JsonObject::add_value(const std::string& key, Json::JsonValue value)
{
	this->values.insert(std::make_pair(key, value));
}

int Json::JsonObject::GetSize()
{
	return this->values.size(); /*values.size();*/
}

Json::JsonTypes Json::JsonObject::get_type()
{
	return this->type;
}

Json::JsonValue Json::JsonObject::operator[](const std::wstring& key)
{
	/*auto search = this->values.find(Additionals::Convectors::ConvertWcharPtrToString(key));
	if (search != this->values.end())
	{
		std::cout << "Not found value in map, start reqursive seacrh" << std::endl;

		for (auto& value : this->values)
		{
			Json::JsonNode* result = _FindValueInJsonValue(value.second, Additionals::Convectors::ConvertWcharPtrToString(key));

			if (result != this)
			{
				return result;
			}
		}
		return this;
	}
	return this->values[Additionals::Convectors::ConvertWcharPtrToString(key)];*/
	auto search = this->values.find(Additionals::Convectors::ConvertWStringToString(key));
	if (search != this->values.end())
	{
		return search->second;
	}

	return nullptr;
}

Json::JsonValue Json::JsonObject::operator[](const std::string& key)
{
	auto search = this->values.find(key);
	if (search != this->values.end())
	{
		return search->second;
	}

	return nullptr;
}

Json::JsonValue& Json::JsonObject::operator=(const Json::JsonValue& value)
{
	std::cout << "operator= values " << value->to_string() << std::endl;
	std::cout << "this->values[]->to_string() " << this->values["libraries"]->to_string() << std::endl;
	return shared_from_this();
}

Json::JsonValue Json::JsonObject::_FindValueInJsonValue(Json::JsonValue jsonValue,
	const std::string& key)
{
	if (jsonValue->get_type() == JsonTypes::Object)
	{
		return jsonValue->get_value(key);
	}

	else if (jsonValue->get_type() == JsonTypes::Array)
	{
		return jsonValue->get_value(key);
	}

	// Handle other value types if needed (e.g., JsonString, JsonNumber, etc.)
	return shared_from_this();
}

Json::JsonValue Json::JsonObject::get_value(const std::string& key)
{
	auto search = this->values.find(key);
	if (search != this->values.end())
	{
		std::cout << "Not found value in map, start reqursive seacrh" << std::endl;

		for (auto& value : this->values)
		{
			Json::JsonValue result = _FindValueInJsonValue(value.second, key);
			if (result != shared_from_this())
			{
				return result;
			}
		}
		return shared_from_this();
	}
	return this->values[key];
}

//cliext::map<System::String^, Json::JsonNode^> Json::JsonObject::get_value()
//{
//	return this->values;
//}

std::unordered_map<std::string, Json::JsonValue> Json::JsonObject::get_value()
{
	return this->values;
}

std::string Json::JsonObject::get_pair(const std::string& key)
{
	return std::string();
}

bool Json::JsonObject::is_exist(const std::string& key)
{
	auto search = this->values.find(key);
	if (search != this->values.end())
	{
		return true;
	}
	return false;
}

void Json::JsonObject::add_value(std::pair<std::string, Json::JsonValue> value)
{
	this->values.insert(value);
}

void Json::JsonObject::replaceValue(const std::string& key, const std::string& value)
{
	if (!this->is_exist(key))
	{
		Json::JsonString val = value;
		this->add_value(std::make_pair(key, std::make_shared<Json::JsonNode>(val)));
	}
	else
	{
		Json::JsonString val = value;
		this->values[key] = std::make_shared<Json::JsonNode>(val);
	}
}

std::string Json::JsonObject::to_string()
{
	std::string builder;
	builder += "{";

	bool first = true;

	for (auto& var : this->values)
	{
		if (!first)
			builder += ",";

		std::string key = var.first;
		std::string value;

		if (var.second->get_type() == Json::JsonTypes::String)
		{
			value = "\"" + key + "\":" + var.second->_as_string();
		}
		else
		{
			value = "\"" + key + "\":" + var.second->to_string();
		}

		builder += value;
		first = false;
	}

	builder += "}";

	return builder;
}

std::wstring Json::JsonObject::to_stringW()
{
	std::wstring start = L"{";
	std::wstring result = L"";
	bool first = true;

	for (auto& it : this->values)
	{
		if (!first)
			result = start + L",";

		result = L"\"" + std::wstring(Additionals::Convectors::ConvertStringToWcharPtr(it.first.c_str()));
		result += L"\":";
		result += it.second->to_stringW();

		first = false;
	}

	result += L"}";

	return result;
}

int Json::JsonObject::get_count()
{
	return this->GetSize();
}

void Json::JsonObject::_JsonValueToStringHelper(Json::JsonValue json_value,
	std::string& builder, int current_indent, int indent)
{
	builder += "{\n";
	int i = 0;

	for (auto& kvp : json_value->get_value())
	{
		_Indent(builder, current_indent + indent);

		builder += "\"" + kvp.first + "\": ";

		kvp.second->_JsonValueToStringHelper(kvp.second, builder, current_indent + indent, indent);

		if (i != json_value->get_count() - 1)
		{
			builder += ",";
		}
		builder += "\n";
		++i;
	}
	_Indent(builder, current_indent);
	builder += "}";
}