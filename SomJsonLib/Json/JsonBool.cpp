#include "pch.h"

#include "Json.h"

Json::JsonBool::JsonBool(bool value) : JsonNode(JsonTypes::Bool), value(value)
{
}

std::string Json::JsonBool::to_string()
{
	return this->value ? "true" : "false";
}

std::wstring Json::JsonBool::to_stringW()
{
	return this->value ? L"true" : L"false";
}

bool Json::JsonBool::toBool()
{
	return this->value;
}

Json::JsonTypes Json::JsonBool::get_type()
{
	return type;
}

void Json::JsonBool::_JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent)
{
	builder += json_value->to_string();
}