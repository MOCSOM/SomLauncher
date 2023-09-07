#include "Json.h"

//cliext::map<System::String^, Json::JsonNode^> Json::JsonNode::get_value()
//{
//	return cliext::map<System::String^, Json::JsonNode^>();
//}

Json::JsonNode::~JsonNode()
{
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator[](const std::wstring& key)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator[](const std::string& key)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator[](int index)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator=(double value)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator=(const std::string& value)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator=(const std::wstring& value)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator=(int value)
{
	return nullptr;
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator+(std::shared_ptr<Json::JsonNode> value)
{
	return nullptr;
}

std::unordered_map<std::string, std::shared_ptr<Json::JsonNode>> Json::JsonNode::get_value()
{
	return std::unordered_map<std::string, std::shared_ptr<Json::JsonNode>>();
}

std::vector<std::shared_ptr<Json::JsonNode>> Json::JsonNode::get_value_list()
{
	return std::vector<std::shared_ptr<Json::JsonNode>>();
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::get_value(const std::string& key)
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

void Json::JsonNode::add_value(std::shared_ptr<Json::JsonNode> value) {}

void Json::JsonNode::add_value(std::pair<std::string, std::shared_ptr<Json::JsonNode>> value) {}

void Json::JsonNode::add_value(const std::string& key, std::shared_ptr<Json::JsonNode> value) {}

void Json::JsonNode::_JsonValueToStringHelper(std::shared_ptr<Json::JsonNode> jsonValue, std::string& builder, int current_indent, int indent) {}