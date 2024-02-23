#include "Json.h"

SJson::SomJson::iterator SJson::SomJson::begin() noexcept
{
	return iterator(this->value.get());
}

SJson::SomJson::iterator SJson::SomJson::end() noexcept
{
	return iterator((*this->value->object_value.end()).second.value.get());
}

SJson::SomJson::const_iterator SJson::SomJson::begin() const noexcept
{
	return const_iterator(this->value.get());
}

SJson::SomJson::const_iterator SJson::SomJson::end() const noexcept
{
	return const_iterator((*this->value->object_value.end()).second.value.get());
}

SJson::SomJson::SomJson()
{
	//this->value->object_value = std::unordered_map<std::string, nlohmann::SomJson>();
	//this->value->is_null = false;
}

SJson::SomJson::SomJson(Node json)
{
	this->value = std::make_shared<Node>(json);
}

SJson::SomJson::SomJson(SJson::JsonTypes type)
{
	if (type == SJson::JsonTypes::Object)
	{
		this->value = std::make_shared<Node>(std::unordered_map<std::string, SJson::SomJson>());
		this->value->type = type;
	}
	else if (type == SJson::JsonTypes::Array)
	{
		this->value = std::make_shared<Node>(std::vector<SJson::SomJson>());
		this->value->type = type;
	}
	else if (type == SJson::JsonTypes::Bool)
	{
		this->value = std::make_shared<Node>(false);
		this->value->type = type;
	}
	else if (type == SJson::JsonTypes::Null)
	{
		this->value = std::make_shared<Node>(nullptr);
		this->value->type = type;
	}
	else if (type == SJson::JsonTypes::Number)
	{
		this->value = std::make_shared<Node>(0);
		this->value->type = type;
	}
	else if (type == SJson::JsonTypes::String)
	{
		this->value = std::make_shared<Node>("");
		this->value->type = type;
	}
}

SJson::SomJson::SomJson(const SJson::SomJson& json)
{
	if (json.value != nullptr)
	{
		this->value = json.value;
	}
}

SJson::SomJson::SomJson(std::nullptr_t null)
{
	this->value = std::make_shared<Node>();
}

SJson::SomJson::~SomJson()
{
}

void SJson::SomJson::add_value(const std::string& key, const Node& value)
{
	this->value->object_value.insert(std::make_pair(key, value));
}

void SJson::SomJson::add_value(const std::string& key, const SJson::SomJson& value)
{
	this->value->object_value.insert(std::make_pair(key, value));
}

void SJson::SomJson::add_value(const std::pair<std::string, SJson::SomJson>& pair)
{
	this->value->object_value.insert(pair);
}

void SJson::SomJson::add_value(const Node& value)
{
	this->value->array_value.push_back(value);
}

void SJson::SomJson::add_value(const SJson::SomJson& value)
{
	this->add_value(*value.value);
}

void SJson::SomJson::replace_value(const size_t& index, const Node& value)
{
	this->value->array_value[index] = value;
}

void SJson::SomJson::replace_value(const std::string& key, const Node& value)
{
	if (this->get_type() == SJson::JsonTypes::Object)
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
	else if (this->get_type() == SJson::JsonTypes::Array)
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

long double& SJson::SomJson::get_number()
{
	return this->value->number_value;
}

bool& SJson::SomJson::get_bool()
{
	return this->value->bool_value;
}

std::string& SJson::SomJson::get_string()
{
	return this->value->string_value;
}

std::nullptr_t& SJson::SomJson::get_null()
{
	return this->value->null_value;
}

std::unordered_map<std::string, SJson::SomJson>& SJson::SomJson::get_object()
{
	return this->value->object_value;
}

std::vector<SJson::SomJson>& SJson::SomJson::get_array()
{
	return this->value->array_value;
}

std::string SJson::SomJson::to_string()
{
	std::string builder = "";

	if (this->get_type() == SJson::JsonTypes::Object)
	{
		builder += "{";

		bool first = true;

		for (auto& elem : this->value->object_value)
		{
			if (!first)
				builder += ",";

			std::string value;
			std::string val = elem.second.to_string();
			value = "\"" + elem.first + "\":" + val;

			builder += value;
			first = false;
		}

		builder += "}";

		return builder;
	}
	else if (this->get_type() == SJson::JsonTypes::Array)
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
	else if (this->get_type() == SJson::JsonTypes::Bool)
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
	else if (this->get_type() == SJson::JsonTypes::Null)
	{
		return "null";
	}
	else if (this->get_type() == SJson::JsonTypes::Number)
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
	else if (this->get_type() == SJson::JsonTypes::String)
	{
		return this->value->string_value;
	}

	return builder;
}

std::wstring SJson::SomJson::to_stringW()
{
	std::wstring builder = L"";

	if (this->get_type() == SJson::JsonTypes::Object)
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
	else if (this->get_type() == SJson::JsonTypes::Array)
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
	else if (this->get_type() == SJson::JsonTypes::Bool)
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
	else if (this->get_type() == SJson::JsonTypes::Null)
	{
		return L"null";
	}
	else if (this->get_type() == SJson::JsonTypes::Number)
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
	else if (this->get_type() == SJson::JsonTypes::String)
	{
		return Additionals::Convectors::ConvertStringToWString(this->value->string_value);
	}

	return builder;
}

int SJson::SomJson::to_int()
{
	return static_cast<int>(this->value->number_value);
}

bool SJson::SomJson::is_exist(const std::string& key)
{
	if (this->value)
	{
		if (!this->value->object_value.empty())
		{
			auto search = this->value->object_value.find(key);
			if (search != this->value->object_value.end())
			{
				return true;
			}
		}
		if (!this->value->array_value.empty())
		{
			for (auto& elem : this->value->array_value)
			{
				if (elem.get_string() == key)
				{
					return true;
				}
			}
		}
	}
	return false;
}

SJson::SomJson& SJson::SomJson::operator[](const std::string& key)
{
	return this->value->object_value[key];
}

SJson::SomJson& SJson::SomJson::operator[](const size_t& index)
{
	return this->value->array_value[index];
}

SJson::SomJson& SJson::SomJson::operator=(const SJson::SomJson& value)
{
	if (this->value != nullptr)
	{
		this->add_value(value);
	}
	if (value.value != nullptr)
	{
		this->value = value.value;
	}
	return *this;
}

SJson::SomJson& SJson::SomJson::operator=(const Node& value)
{
	/*if (this->value != nullptr)
	{
		this->add_value(value);
	}*/
	if (value != nullptr)
	{
		*this->value = value;
	}
	return *this;
}

SJson::SomJson& SJson::SomJson::operator+=(const SJson::SomJson& value)
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

SJson::SomJson SJson::SomJson::operator+(const SJson::SomJson& value)
{
	SJson::SomJson temp = *this;
	temp += value;
	return temp;
}

bool SJson::SomJson::operator==(const std::nullptr_t& null)
{
	if (this->value == nullptr)
	{
		return true;
	}
	return false;
}

bool SJson::SomJson::operator!=(const std::nullptr_t& null)
{
	return !(*this == null);
}

bool SJson::SomJson::operator==(const SJson::SomJson& value) const
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

bool SJson::SomJson::operator!=(const SJson::SomJson& value) const
{
	return !(*this == value);
}

void SJson::SomJson::save_json_to_file(const std::string& file_name, int indent)
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

std::string SJson::SomJson::_json_value_to_string(int indent)
{
	std::string builder;
	_json_value_to_string_helper(*this, builder, 0, indent);
	return builder;
}

void SJson::SomJson::_json_value_to_string_helper(SJson::SomJson json_value, std::string& builder, int current_indent, int indent)
{
	if (json_value.get_type() == SJson::JsonTypes::Object)
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
	else if (json_value.get_type() == SJson::JsonTypes::Array)
	{
		builder += "[\n";
		for (int i = 0; i < json_value.get_count(); i++)
		{
			_indent(builder, current_indent + indent);

			if (json_value[i].get_type() == SJson::JsonTypes::Object)
			{
				SJson::SomJson obj = SJson::SomJson(std::unordered_map<std::string, SJson::SomJson>());
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
	else if (json_value.get_type() == SJson::JsonTypes::Bool)
	{
		builder += json_value.to_string();
	}
	else if (json_value.get_type() == SJson::JsonTypes::Null)
	{
		builder += json_value.to_string();
	}
	else if (json_value.get_type() == SJson::JsonTypes::Number)
	{
		builder += json_value.to_string();
	}
	else if (json_value.get_type() == SJson::JsonTypes::String)
	{
		builder += "\"" + json_value.to_string() + "\"";
	}
}

void SJson::SomJson::_indent(std::string& builder, int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		builder += " ";
	}
}

SJson::SomJson::Node::Node()
{
	this->type = SJson::JsonTypes::NotImplemented;
}

SJson::SomJson::Node::Node(SJson::JsonTypes type)
{
	switch (type)
	{
	case SJson::JsonTypes::String:
		this->type = SJson::JsonTypes::String;
		this->string_value = std::string();
		break;
	case SJson::JsonTypes::Number:
		this->type = SJson::JsonTypes::Number;
		this->number_value = NULL;
		break;
	case SJson::JsonTypes::Bool:
		this->type = SJson::JsonTypes::Bool;
		this->bool_value = NULL;
		break;
	case SJson::JsonTypes::Array:
		this->type = SJson::JsonTypes::Array;
		this->array_value = std::vector<SomJson>();
		break;
	case SJson::JsonTypes::Object:
		this->type = SJson::JsonTypes::Object;
		this->object_value = std::unordered_map<std::string, SJson::SomJson>();
		break;
	case SJson::JsonTypes::Null:
		this->type = SJson::JsonTypes::Null;
		this->null_value = std::nullptr_t();
		break;
	case SJson::JsonTypes::NotImplemented:
		this->type = SJson::JsonTypes::NotImplemented;
		break;
	default:
		this->type = SJson::JsonTypes::NotImplemented;
		break;
	}
}

SJson::SomJson::Node::Node(long double number_value)
{
	this->type = SJson::JsonTypes::Number;
	this->number_value = number_value;
}

SJson::SomJson::Node::Node(double number_value)
{
	this->type = SJson::JsonTypes::Number;
	this->number_value = number_value;
}

SJson::SomJson::Node::Node(int number_value)
{
	this->type = SJson::JsonTypes::Number;
	this->number_value = static_cast<long double>(number_value);
}

SJson::SomJson::Node::Node(long long number_value)
{
	this->type = SJson::JsonTypes::Number;
	this->number_value = static_cast<long double>(number_value);
}

SJson::SomJson::Node::Node(bool bool_value)
{
	this->type = SJson::JsonTypes::Bool;
	this->bool_value = bool_value;
}

SJson::SomJson::Node::Node(std::string string_value)
{
	this->type = SJson::JsonTypes::String;
	this->string_value = string_value;
}

SJson::SomJson::Node::Node(const char* string_value)
{
	this->type = SJson::JsonTypes::String;
	this->string_value = string_value;
}

SJson::SomJson::Node::Node(std::nullptr_t null_value)
{
	this->type = SJson::JsonTypes::Null;
	this->null_value = null_value;
}

SJson::SomJson::Node::Node(std::unordered_map<std::string, SJson::SomJson> object_value)
{
	this->type = SJson::JsonTypes::Object;
	this->object_value = object_value;
}

SJson::SomJson::Node::Node(std::vector<SJson::SomJson> array_value)
{
	this->type = SJson::JsonTypes::Array;
	this->array_value = array_value;
}

bool SJson::SomJson::Node::operator==(const Node& value) const
{
	if (this->type != value.type)
	{
		return false;
	}
	if (this->type == SJson::JsonTypes::Object)
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
	else if (this->type == SJson::JsonTypes::Array)
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
	else if (this->type == SJson::JsonTypes::Bool)
	{
		return this->bool_value == value.bool_value;
	}
	else if (this->type == SJson::JsonTypes::Number)
	{
		return this->number_value == value.number_value;
	}
	else if (this->type == SJson::JsonTypes::String)
	{
		return this->string_value == value.string_value;
	}
	else if (this->type == SJson::JsonTypes::NotImplemented)
	{
		return false;
	}
	/*else
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
	}*/

	return false;
}

bool SJson::SomJson::Node::operator!=(const Node& value) const
{
	return !(*this == value);
}

size_t SJson::SomJson::get_count()
{
	if (this->value == nullptr || this->get_type() == SJson::JsonTypes::NotImplemented)
	{
		return 0;
	}
	else if (this->get_type() == SJson::JsonTypes::Object)
	{
		return this->value->object_value.size();
	}
	else if (this->get_type() == SJson::JsonTypes::Array)
	{
		return this->value->array_value.size();
	}

	return 1;
}

SJson::JsonTypes SJson::SomJson::get_type()
{
	//return this->value->type;
	if (this->value)
	{
		return this->value->type;
	}
	else
	{
		return JsonTypes::NotImplemented;
	}
}