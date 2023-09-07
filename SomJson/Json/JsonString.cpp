#include "Json.h"

Json::JsonString::JsonString(const std::wstring& value) : JsonNode(JsonTypes::String)
{
	this->value = Additionals::Convectors::ConvertWStringToString(value);
}

Json::JsonString::JsonString(const std::string& value) : JsonNode(JsonTypes::String)
{
	this->value = value;
}

std::string Json::JsonString::_as_string()
{
	return "\"" + this->value + "\"";
}

std::string Json::JsonString::to_string()
{
	return  this->value;
}

Json::JsonTypes Json::JsonString::get_type()
{
	return this->type;
}

Json::JsonValue Json::JsonString::operator+(Json::JsonValue value)
{
	this->value += value->to_string();
	return shared_from_this();
}

Json::JsonValue Json::JsonString::operator=(const std::string& value)
{
	this->value = value;
	return shared_from_this();
}

Json::JsonValue Json::JsonString::operator=(Json::JsonValue value)
{
	this->value = value->to_string();
	return shared_from_this();
}

std::wstring Json::JsonString::to_stringW()
{
	return Additionals::Convectors::ConvertStringToWcharPtr(this->value);
}

void Json::JsonString::_JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent)
{
	builder += "\"" + json_value->to_string() + "\"";
}

Json::JsonValue Json::JsonString::operator=(const std::wstring& value)
{
	if (!this->is_exist(this->value))
	{
		/*Json::JsonString* add_value = new Json::JsonString(value);
		this->add_value();*/
	}
	else
	{
		this->value = Additionals::Convectors::ConvertWStringToString(value);
	}
	return shared_from_this();
}