#include "../pch.h"

#include "Json.h"

Json::JsonArray::JsonArray() : Json::JsonNode(Json::JsonTypes::Array)
{
	this->values = std::vector<Json::JsonValue>();
}

Json::JsonArray::~JsonArray()
{
	for (Json::JsonValue value : this->values)
	{
		if (value->get_type() == Json::JsonTypes::Array)
		{
			value->~JsonNode();

			value.~shared_ptr();
		}
		else
		{
			value->~JsonNode();
		}
	}
	this->values.clear();
}

int Json::JsonArray::get_count()
{
	return this->values.size();
}

void Json::JsonArray::add_value(Json::JsonValue value)
{
	if (value->get_type() == Json::JsonTypes::Array)
	{
		for (Json::JsonValue var : value->get_value_list())
		{
			this->values.push_back(var);
		}
	}
	else
	{
		this->values.push_back(value);
	}
}

void Json::JsonArray::add_value_list(Json::JsonArray value)
{
	for (auto& var : value.get_value_list())
	{
		this->values.push_back(var);
	}
}

Json::JsonValue Json::JsonArray::findValueInJsonValue(Json::JsonValue jsonValue, const std::string& key)
{
	if (jsonValue->get_type() == Json::JsonTypes::Object)
	{
		return jsonValue->get_value(key);
	}

	else if (jsonValue->get_type() == Json::JsonTypes::Array)
	{
		return jsonValue->get_value(key);
	}

	// Handle other value types if needed (e.g., JsonString, JsonNumber, etc.)
	return shared_from_this();
}

int Json::JsonArray::get_size()
{
	return this->values.size();
}

std::vector<Json::JsonValue> Json::JsonArray::get_value_list()
{
	return this->values;
}

Json::JsonValue Json::JsonArray::get_value(const std::string& key)
{
	for (auto& value : this->values)
	{
		Json::JsonValue result = findValueInJsonValue(value, key);

		if (result != shared_from_this())
		{
			return result;
		}
	}

	return shared_from_this();
}

Json::JsonValue Json::JsonArray::operator[](int index)
{
	return this->values[index];
}

Json::JsonValue Json::JsonArray::operator=(Json::JsonValue value)
{
	this->values = value->get_value_list();

	/*this->values.clear();

	for (auto& var : value->get_value_list())
	{
		this->values.push_back(var);
	}*/
	/*for (auto& var : value->get_value())
	{
		this->values.push_back(var.second);
	}*/

	return shared_from_this();
}

Json::JsonValue Json::JsonArray::operator+(Json::JsonValue value)
{
	this->Json::JsonArray::add_value(value);

	return shared_from_this();
}

//Json::JsonNode* Json::JsonArray::operator[](const wchar_t* key)
//{
//	for (auto& value : this->values)
//	{
//		Json::JsonNode* result = FindValueInJsonValue(value, Additionals::Convectors::ConvertWcharPtrToString(key));
//
//		if (result != this)
//		{
//			return result;
//		}
//	}
//
//	return this;
//}
//
//Json::JsonNode* Json::JsonArray::operator[](const std::string& key)
//{
//	for (auto& value : this->values)
//	{
//		Json::JsonNode* result = FindValueInJsonValue(value, key);
//
//		if (result != this)
//		{
//			return result;
//		}
//	}
//	return this;
//}

Json::JsonTypes Json::JsonArray::get_type()
{
	return this->type;
}

std::string Json::JsonArray::to_string()
{
	std::string result = "[";

	for (int i = 0; i < this->values.size(); ++i)
	{
		if (i > 0)
			result += ",";

		result += this->values[i]->to_string();
	}

	result += "]";

	return result;
}

std::wstring Json::JsonArray::to_stringW()
{
	std::wstring start = L"[";
	std::wstring result;

	for (int i = 0; i < this->values.size(); ++i)
	{
		if (i > 0)
			start += L",";

		start += this->values[i]->to_stringW();
	}

	result = start + L"]";

	return result;
}

void Json::JsonArray::_JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent)
{
	builder += "[\n";
	for (int i = 0; i < json_value->get_count(); i++)
	{
		_Indent(builder, current_indent + indent);

		if ((*json_value)[i]->get_type() == Json::JsonTypes::Object)
		{
			Json::JsonObject obj;
			obj._JsonValueToStringHelper((*json_value)[i], builder, current_indent + indent, indent);
		}
		else
		{
			_JsonValueToStringHelper((*json_value)[i], builder, current_indent + indent, indent);
		}

		if (i != json_value->get_count() - 1)
		{
			builder += ",";
		}
		builder += "\n";
	}
	_Indent(builder, current_indent);
	builder += "]";
}