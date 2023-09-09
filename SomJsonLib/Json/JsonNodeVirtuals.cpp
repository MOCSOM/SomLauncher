#include "pch.h"

#include "Json.h"

//cliext::map<System::String^, Json::JsonNode^> Json::JsonNode::get_value()
//{
//	return cliext::map<System::String^, Json::JsonNode^>();
//}

Json::JsonNode::~JsonNode()
{
}

Json::JsonValue Json::JsonNode::operator[](const std::wstring& key)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator[](const std::string& key)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator[](int index)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator=(double value)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator=(const std::string& value)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator=(const std::wstring& value)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator=(int value)
{
	return nullptr;
}

Json::JsonValue Json::JsonNode::operator+(Json::JsonValue value)
{
	return nullptr;
}

std::unordered_map<std::string, Json::JsonValue> Json::JsonNode::get_value()
{
	return std::unordered_map<std::string, Json::JsonValue>();
}

std::vector<Json::JsonValue> Json::JsonNode::get_value_list()
{
	return std::vector<Json::JsonValue>();
}

Json::JsonValue Json::JsonNode::get_value(const std::string& key)
{
	return nullptr;
}

std::string Json::JsonNode::to_string()
{
	return std::string();
}

std::wstring Json::JsonNode::to_stringW()
{
	return std::wstring();
}

std::string Json::JsonNode::_as_string()
{
	return std::string();
}

bool Json::JsonNode::HasKey(const std::wstring& key)
{
	return false;
}

int Json::JsonNode::get_count()
{
	return 0;
}

double Json::JsonNode::to_double()
{
	return 0.0;
}

int Json::JsonNode::to_int()
{
	return 0;
}

bool Json::JsonNode::is_exist(const std::string& key)
{
	return false;
}

//Json::JsonNode^% Json::JsonNode::get_value(System::String^ key)
//{
//	return Json::JsonNode(Json::JsonTypes::Null);
//}

void Json::JsonNode::replaceValue(const std::string& key, const std::string& value) {}

void Json::JsonNode::add_value(Json::JsonValue value) {}

void Json::JsonNode::add_value(std::pair<std::string, Json::JsonValue> value) {}

void Json::JsonNode::add_value(const std::string& key, Json::JsonValue value) {}

void Json::JsonNode::setValue(Json::JsonValue value) {}

void Json::JsonNode::_JsonValueToStringHelper(Json::JsonValue jsonValue, std::string& builder, int current_indent, int indent) {}