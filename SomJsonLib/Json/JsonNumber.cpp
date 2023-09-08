#include "pch.h"

#include "Json.h"

Json::JsonNumber::JsonNumber(double value) : JsonNode(JsonTypes::Number), value(value)
{
}

Json::JsonValue Json::JsonNumber::operator=(double value)
{
	this->value = value;
	return shared_from_this();
}

Json::JsonValue Json::JsonNumber::operator=(int value)
{
	this->value = value;
	return shared_from_this();
}

Json::JsonValue Json::JsonNumber::operator+(Json::JsonValue value)
{
	//value += value->to_double();
	return shared_from_this();
}

std::string Json::JsonNumber::to_string()
{
	return std::to_string(this->value);
}

Json::JsonTypes Json::JsonNumber::get_type()
{
	return type;
}

std::wstring Json::JsonNumber::to_stringW()
{
	return std::wstring(Additionals::Convectors::ConvertStringToWcharPtr(std::to_string(this->value)));
}

double Json::JsonNumber::to_double()
{
	return this->value;
}

int Json::JsonNumber::to_int()
{
	return this->value;
}

void Json::JsonNumber::_JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent)
{
	builder += json_value->to_string();
}