#include "pch.h"

#include "Json.h"

Json::JsonNull::JsonNull() : Json::JsonNode(Json::JsonTypes::Null)
{
}

std::string Json::JsonNull::to_string()
{
	return "null";
}

std::wstring Json::JsonNull::to_stringW()
{
	return L"null";
}

Json::JsonTypes Json::JsonNull::get_type()
{
	return type;
}

void Json::JsonNull::_JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent)
{
	builder += json_value->to_string();
}