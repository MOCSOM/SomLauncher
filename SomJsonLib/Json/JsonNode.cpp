#include "pch.h"

#include "Json.h"

Json::JsonNode::JsonNode(const Json::JsonTypes& type) : type(type)
{
}

Json::JsonNode::JsonNode()
{
	this->type = Json::JsonTypes::NotImplemented;
}

//Json::JsonNode::JsonNode(std::nullptr_t values)
//{
//	this->type = Json::JsonTypes::Null;
//}

void Json::JsonNode::SaveJsonToFile(const std::string& file_name, int indent)
{
	std::ofstream file(file_name, std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "failed to open " << file_name << '\n';
	}
	else
	{
		// write
		std::string string_to_write = _JsonValueToString(indent);
		file.write(string_to_write.c_str(), string_to_write.size());
	}

	file.close();
}

void Json::JsonNode::SaveJsonToFile(const std::wstring& file_name, int indent)
{
	std::ofstream file(file_name, std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "failed to open " << file_name.c_str() << '\n';
	}
	else
	{
		// write
		std::string string_to_write = _JsonValueToString(indent);
		file.write(string_to_write.c_str(), string_to_write.size());
	}

	file.close();
}

Json::JsonTypes Json::JsonNode::get_type()
{
	return type;
}

std::string Json::JsonNode::_JsonValueToString(int indent)
{
	std::string builder;
	_JsonValueToStringHelper(shared_from_this(), builder, 0, indent);
	return builder;
}

void Json::JsonNode::_Indent(std::string& builder, int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		builder += " ";
	}
}

std::shared_ptr<Json::JsonNode> Json::JsonNode::operator=(std::shared_ptr<Json::JsonNode> value)
{
	if (!this->is_exist(value->to_string()))
	{
		this->add_value(value);
	}
	else
	{
		//this->get_value() = value->get_value();
	}
	return shared_from_this();
}

bool Json::JsonNode::operator!=(std::shared_ptr<Json::JsonNode> value)
{
	return !(this->type == value->get_type());
}

bool Json::JsonNode::operator==(std::shared_ptr<Json::JsonNode> value)
{
	return this->type == value->get_type();
}