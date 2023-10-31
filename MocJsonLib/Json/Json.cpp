#include "pch.h"
#include "Json.h"

Json::SomJson::iterator Json::SomJson::begin() noexcept
{
	return iterator(this->value.get());
}

Json::SomJson::iterator Json::SomJson::end() noexcept
{
	return iterator((*this->value->object_value.end()).second.value.get());
}

Json::SomJson::const_iterator Json::SomJson::begin() const noexcept
{
	return const_iterator(this->value.get());
}

Json::SomJson::const_iterator Json::SomJson::end() const noexcept
{
	return const_iterator((*this->value->object_value.end()).second.value.get());
}

Json::SomJson::SomJson()
{
	//this->value->object_value = std::unordered_map<std::string, Json::SomJson>();
	//this->value->is_null = false;
}

Json::SomJson::SomJson(Node json)
{
	this->value = std::make_shared<Node>(json);
}

Json::SomJson::SomJson(const Json::SomJson& json)
{
	if (json.value != nullptr)
	{
		this->value = json.value;
	}
}

Json::SomJson::SomJson(std::nullptr_t null)
{
	this->value = std::make_shared<Node>();
}

Json::SomJson::~SomJson()
{
}

void Json::SomJson::add_value(const std::string& key, const Node& value)
{
	this->value->object_value.insert(std::make_pair(key, value));
}

void Json::SomJson::add_value(const std::string& key, const Json::SomJson& value)
{
	this->value->object_value.insert(std::make_pair(key, value));
}

void Json::SomJson::add_value(const std::pair<std::string, Json::SomJson>& pair)
{
	this->value->object_value.insert(pair);
}

void Json::SomJson::add_value(const Node& value)
{
	this->value->array_value.push_back(value);
}

void Json::SomJson::add_value(const Json::SomJson& value)
{
	this->add_value(*value.value);
}

void Json::SomJson::replace_value(const size_t& index, const Node& value)
{
	this->value->array_value[index] = value;
}

void Json::SomJson::replace_value(const std::string& key, const Node& value)
{
	if (this->get_type() == Json::JsonTypes::Object)
	{
		if (!this->is_exist(key))
		{
			this->add_value(std::make_pair(key, value));
		}
		else
		{
			this->value->object_value[key] = value;
		}
	}
	else if (this->get_type() == Json::JsonTypes::Array)
	{
		/*if (!this->is_exist(key))
		{
			this->add_value(std::make_pair(key, value));
		}
		else
		{
			this->value->object_value[key] = value;
		}*/
	}
}

long double& Json::SomJson::get_number()
{
	return this->value->number_value;
}

bool& Json::SomJson::get_bool()
{
	return this->value->bool_value;
}

std::string& Json::SomJson::get_string()
{
	return this->value->string_value;
}

std::nullptr_t& Json::SomJson::get_null()
{
	return this->value->null_value;
}

std::unordered_map<std::string, Json::SomJson>& Json::SomJson::get_object()
{
	return this->value->object_value;
}

std::vector<Json::SomJson>& Json::SomJson::get_array()
{
	return this->value->array_value;
}

std::string Json::SomJson::to_string()
{
	std::string builder = "";

	if (this->get_type() == Json::JsonTypes::Object)
	{
		builder += "{";

		bool first = true;

		for (auto& elem : this->value->object_value)
		{
			if (!first)
				builder += ",";

			std::string value;

			value = "\"" + elem.first + "\":" + elem.second.to_string();

			builder += value;
			first = false;
		}

		builder += "}";

		return builder;
	}
	else if (this->get_type() == Json::JsonTypes::Array)
	{
		builder = "[";

		for (int i = 0; i < this->value->array_value.size(); ++i)
		{
			if (i > 0)
				builder += ",";

			builder += this->value->array_value[i].to_string();
		}

		builder += "]";

		return builder;
	}
	else if (this->get_type() == Json::JsonTypes::Bool)
	{
		if (this->value->bool_value)
		{
			builder = "true";
		}
		else
		{
			builder = "false";
		}

		return builder;
	}
	else if (this->get_type() == Json::JsonTypes::Null)
	{
		return "null";
	}
	else if (this->get_type() == Json::JsonTypes::Number)
	{
		if (std::abs(this->value->number_value) - std::abs(int(this->value->number_value)) < 0.000001)
		{
			return std::to_string(static_cast<int>(this->value->number_value));
		}
		else
		{
			return std::to_string(this->value->number_value);
		}
	}
	else if (this->get_type() == Json::JsonTypes::String)
	{
		return this->value->string_value;
	}

	return builder;
}

std::wstring Json::SomJson::to_stringW()
{
	std::wstring builder = L"";

	if (this->get_type() == Json::JsonTypes::Object)
	{
		builder += L"{";

		bool first = true;

		for (auto& elem : this->value->object_value)
		{
			if (!first)
				builder += L",";

			std::wstring value;

			value = L"\"" + Additionals::Convectors::ConvertStringToWString(elem.first) + L"\":" + elem.second.to_stringW();

			builder += value;
			first = false;
		}

		builder += L"}";

		return builder;
	}
	else if (this->get_type() == Json::JsonTypes::Array)
	{
		builder = L"[";

		for (int i = 0; i < this->value->array_value.size(); ++i)
		{
			if (i > 0)
				builder += L",";

			builder += this->value->array_value[i].to_stringW();
		}

		builder += L"]";

		return builder;
	}
	else if (this->get_type() == Json::JsonTypes::Bool)
	{
		if (this->value->bool_value)
		{
			builder = L"true";
		}
		else
		{
			builder = L"false";
		}

		return builder;
	}
	else if (this->get_type() == Json::JsonTypes::Null)
	{
		return L"null";
	}
	else if (this->get_type() == Json::JsonTypes::Number)
	{
		if (std::abs(this->value->number_value) - std::abs(int(this->value->number_value)) < 0.000001)
		{
			return std::to_wstring(static_cast<int>(this->value->number_value));
		}
		else
		{
			return std::to_wstring(this->value->number_value);
		}
	}
	else if (this->get_type() == Json::JsonTypes::String)
	{
		return Additionals::Convectors::ConvertStringToWString(this->value->string_value);
	}

	return builder;
}

int Json::SomJson::to_int()
{
	return static_cast<int>(this->value->number_value);
}

bool Json::SomJson::is_exist(const std::string& key)
{
	auto search = this->value->object_value.find(key);
	if (search != this->value->object_value.end())
	{
		return true;
	}
	return false;
}

Json::SomJson& Json::SomJson::operator[](const std::string& key)
{
	return this->value->object_value[key];
}

Json::SomJson& Json::SomJson::operator[](const size_t& index)
{
	return this->value->array_value[index];
}

Json::SomJson& Json::SomJson::operator=(const Json::SomJson& value)
{
	if (value.value != nullptr)
	{
		this->value = value.value;
	}
	return *this;
}

Json::SomJson& Json::SomJson::operator=(const Node& value)
{
	*this->value = value;
	return *this;
}

Json::SomJson& Json::SomJson::operator+=(const Json::SomJson& value)
{
	for (auto& elem : value.value->object_value)
	{
		this->add_value(elem.first, elem.second);
	}
	for (auto& elem : value.value->array_value)
	{
		this->add_value(*elem.value);
	}
	return *this;
}

Json::SomJson Json::SomJson::operator+(const Json::SomJson& value)
{
	Json::SomJson temp = *this;
	temp += value;
	return temp;
}

bool Json::SomJson::operator==(const std::nullptr_t& null)
{
	if (this->value == nullptr)
	{
		return true;
	}
	return false;
}

bool Json::SomJson::operator!=(const std::nullptr_t& null)
{
	return !(*this == null);
}

bool Json::SomJson::operator==(const Json::SomJson& value) const
{
	for (auto& elem : value)
	{
		if (elem != *this->value)
		{
			return false;
		}
	}
	return true;
}

bool Json::SomJson::operator!=(const Json::SomJson& value) const
{
	return !(*this == value);
}

void Json::SomJson::save_json_to_file(const std::string& file_name, int indent)
{
	std::ofstream file(file_name, std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "failed to open " << file_name << '\n';
	}
	else
	{
		// write
		std::string string_to_write = _json_value_to_string(indent);
		file.write(string_to_write.c_str(), string_to_write.size());
	}

	file.close();
}

std::string Json::SomJson::_json_value_to_string(int indent)
{
	std::string builder;
	_json_value_to_string_helper(*this, builder, 0, indent);
	return builder;
}

void Json::SomJson::_json_value_to_string_helper(Json::SomJson json_value, std::string& builder, int current_indent, int indent)
{
	if (json_value.get_type() == Json::JsonTypes::Object)
	{
		builder += "{\n";
		int i = 0;

		for (auto& kvp : json_value.get_object())
		{
			_indent(builder, current_indent + indent);

			builder += "\"" + kvp.first + "\": ";

			kvp.second._json_value_to_string_helper(kvp.second, builder, current_indent + indent, indent);

			if (i != json_value.get_count() - 1)
			{
				builder += ",";
			}
			builder += "\n";
			++i;
		}
		_indent(builder, current_indent);
		builder += "}";
	}
	else if (json_value.get_type() == Json::JsonTypes::Array)
	{
		builder += "[\n";
		for (int i = 0; i < json_value.get_count(); i++)
		{
			_indent(builder, current_indent + indent);

			if (json_value[i].get_type() == Json::JsonTypes::Object)
			{
				Json::SomJson obj = Json::SomJson(std::unordered_map<std::string, Json::SomJson>());
				obj._json_value_to_string_helper(json_value[i], builder, current_indent + indent, indent);
			}
			else
			{
				_json_value_to_string_helper(json_value[i], builder, current_indent + indent, indent);
			}

			if (i != json_value.get_count() - 1)
			{
				builder += ",";
			}
			builder += "\n";
		}
		_indent(builder, current_indent);
		builder += "]";
	}
	else if (json_value.get_type() == Json::JsonTypes::Bool)
	{
		builder += json_value.to_string();
	}
	else if (json_value.get_type() == Json::JsonTypes::Null)
	{
		builder += json_value.to_string();
	}
	else if (json_value.get_type() == Json::JsonTypes::Number)
	{
		builder += json_value.to_string();
	}
	else if (json_value.get_type() == Json::JsonTypes::String)
	{
		builder += "\"" + json_value.to_string() + "\"";
	}
}

void Json::SomJson::_indent(std::string& builder, int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		builder += " ";
	}
}

Json::SomJson::Node::Node()
{
	this->type = Json::JsonTypes::NotImplemented;
}

Json::SomJson::Node::Node(long double number_value)
{
	this->type = Json::JsonTypes::Number;
	this->number_value = number_value;
}

Json::SomJson::Node::Node(double number_value)
{
	this->type = Json::JsonTypes::Number;
	this->number_value = number_value;
}

Json::SomJson::Node::Node(int number_value)
{
	this->type = Json::JsonTypes::Number;
	this->number_value = static_cast<long double>(number_value);
}

Json::SomJson::Node::Node(long long number_value)
{
	this->type = Json::JsonTypes::Number;
	this->number_value = static_cast<long double>(number_value);
}

Json::SomJson::Node::Node(bool bool_value)
{
	this->type = Json::JsonTypes::Bool;
	this->bool_value = bool_value;
}

Json::SomJson::Node::Node(std::string string_value)
{
	this->type = Json::JsonTypes::String;
	this->string_value = string_value;
}

Json::SomJson::Node::Node(const char* string_value)
{
	this->type = Json::JsonTypes::String;
	this->string_value = string_value;
}

Json::SomJson::Node::Node(std::nullptr_t null_value)
{
	this->type = Json::JsonTypes::Null;
	this->null_value = null_value;
}

Json::SomJson::Node::Node(std::unordered_map<std::string, Json::SomJson> object_value)
{
	this->type = Json::JsonTypes::Object;
	this->object_value = object_value;
}

Json::SomJson::Node::Node(std::vector<Json::SomJson> array_value)
{
	this->type = Json::JsonTypes::Array;
	this->array_value = array_value;
}

bool Json::SomJson::Node::operator==(const Node& value) const
{
	if (this->type == Json::JsonTypes::Object)
	{
		for (auto& elem : this->object_value)
		{
			auto search = this->object_value.find(elem.first);
			if (search != this->object_value.end())
			{
				return true;
			}
		}

		return false;
	}
	else if (this->type == Json::JsonTypes::Array)
	{
		for (auto& elem : this->array_value)
		{
			if (elem != elem)
			{
				return false;
			}
		}

		return true;
	}
	else if (this->type == Json::JsonTypes::NotImplemented)
	{
		return false;
	}
	else
	{
		if (this->bool_value == value.bool_value)
		{
			return true;
		}
		if (this->null_value == value.null_value)
		{
			return true;
		}
		if (this->number_value == value.number_value)
		{
			return true;
		}
		if (this->string_value == value.string_value)
		{
			return true;
		}
	}

	return false;
}

bool Json::SomJson::Node::operator!=(const Node& value) const
{
	return !(*this == value);
}

size_t Json::SomJson::get_count()
{
	if (this->value == nullptr || this->get_type() == Json::JsonTypes::NotImplemented)
	{
		return 0;
	}
	else if (this->get_type() == Json::JsonTypes::Object)
	{
		return this->value->object_value.size();
	}
	else if (this->get_type() == Json::JsonTypes::Array)
	{
		return this->value->array_value.size();
	}
	
	return 1;
}

Json::JsonTypes Json::SomJson::get_type()
{
	return this->value->type;
}