#include "Json.h"

//#include <cliext/vector>
//#include <cliext/map>
//#include <ctype.h>

Json::JsonArray::JsonArray(): Json::JsonValue(JsonTypes::Array) 
{
	this->values = std::vector<Json::JsonValue*>();
}

//Json::JsonArray::~JsonArray()
//{
//	//for (auto& value : this->values)
//	//{
//	//	/*value->~JsonValue();
//	//	delete[] value;*/
//	//}
//	this->values.clear();
//}

int Json::JsonArray::get_count()
{
	return this->values.size();
}

void Json::JsonArray::add_value(Json::JsonValue* value)
{
	if (value->get_type() == Json::JsonTypes::Array)
	{
		for (auto& var : value->get_value_list())
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

Json::JsonValue* Json::JsonArray::FindValueInJsonValue(Json::JsonValue* jsonValue, std::string key)
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
	return this;
}

int Json::JsonArray::get_size()
{
	return this->values.size();
}

std::vector<Json::JsonValue*> Json::JsonArray::get_value_list()
{
	return this->values;
}

Json::JsonValue* Json::JsonArray::get_value(std::string key)
{
	for (auto& value : this->values)
	{
		Json::JsonValue* result = FindValueInJsonValue(value, key);

		if (result != this) 
		{
			return result;
		}
	}

	return this;
}

Json::JsonValue* Json::JsonArray::operator[](int index)
{
	return this->values[index];
}

Json::JsonValue* Json::JsonArray::operator=(Json::JsonValue* value)
{
	this->values.clear();
	this->values.push_back(value);

	return this;
}

Json::JsonValue* Json::JsonArray::operator+(Json::JsonValue* value)
{
	this->Json::JsonArray::add_value(value);

	return this;
}

//Json::JsonValue* Json::JsonArray::operator[](const wchar_t* key)
//{
//	for (auto& value : this->values)
//	{
//		Json::JsonValue* result = FindValueInJsonValue(value, Additionals::Convectors::ConvertWcharPtrToString(key));
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
//Json::JsonValue* Json::JsonArray::operator[](const std::string& key)
//{
//	for (auto& value : this->values)
//	{
//		Json::JsonValue* result = FindValueInJsonValue(value, key);
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

wchar_t* Json::JsonArray::to_stringW()
{
	const wchar_t* start = L"[";
	wchar_t* result = nullptr;

	for (int i = 0; i < this->values.size(); ++i)
	{
		if (i > 0) 
			start = StrDogW(start, L",");

		start = StrDogW(start, this->values[i]->to_stringW());
	}

	result = StrDogW(start, L"]");

	return result;
}

void Json::JsonArray::_JsonValueToStringHelper(Json::JsonValue* json_value, std::string builder, int current_indent, int indent)
{
	builder += "[\n";
	for (int i = 0; i < json_value->get_count(); i++)
	{
		_Indent(builder, current_indent + indent);
		_JsonValueToStringHelper((*json_value)[i], builder, current_indent + indent, indent);
		if (i != json_value->get_count() - 1)
		{
			builder += ",";
		}
		builder += "\n";
	}
	_Indent(builder, current_indent);
	builder += "]";
}

//cliext::map<System::String^, Json::JsonValue^> Json::JsonObject::operator=(cliext::map<System::String^, Json::JsonValue^> value)
//{
//    return this->values = value;
//}

Json::JsonObject::JsonObject() : Json::JsonValue(Json::JsonTypes::Object)
{
	this->values = std::unordered_map<std::string, Json::JsonValue*>();
}

//Json::JsonObject::~JsonObject()
//{
//	/*for (auto& var : this->values)
//	{
//		delete var;
//	}*/
//	this->values.clear();
//}

void Json::JsonObject::add_value(std::string key, Json::JsonValue* value)
{
	this->values.insert(std::make_pair(key, value));
}

int Json::JsonObject::GetSize()
{
	return this->values.size(); /*values.size();*/
}

Json::JsonTypes Json::JsonObject::get_type()
{
	return this->type;
}

Json::JsonValue* Json::JsonObject::operator[](const wchar_t* key)
{
	/*auto search = this->values.find(Additionals::Convectors::ConvertWcharPtrToString(key));
	if (search != this->values.end())
	{
		std::cout << "Not found value in map, start reqursive seacrh" << std::endl;

		for (auto& value : this->values)
		{
			Json::JsonValue* result = _FindValueInJsonValue(value.second, Additionals::Convectors::ConvertWcharPtrToString(key));

			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return this->values[Additionals::Convectors::ConvertWcharPtrToString(key)];*/
	auto search = this->values.find(Additionals::Convectors::ConvertWcharPtrToString(key));
	if (search != this->values.end())
	{
		return search->second;
	}

	return nullptr;
}

Json::JsonValue* Json::JsonObject::operator[](const std::string& key)
{
	auto search = this->values.find(key);
	if (search != this->values.end())
	{
		return search->second;
	}

	return nullptr;
}

Json::JsonValue* Json::JsonObject::_FindValueInJsonValue(Json::JsonValue* jsonValue, std::string key)
{
	if (jsonValue->get_type() == JsonTypes::Object)
	{
		return jsonValue->get_value(key);
	}

	else if (jsonValue->get_type() == JsonTypes::Array)
	{
		return jsonValue->get_value(key);
	}

	// Handle other value types if needed (e.g., JsonString, JsonNumber, etc.)
	return this;
}

Json::JsonValue* Json::JsonObject::get_value(std::string key)
{
	auto search = this->values.find(key);
	if (search != this->values.end())
	{
		std::cout << "Not found value in map, start reqursive seacrh" << std::endl;

		for (auto& value : this->values)
		{
			Json::JsonValue* result = _FindValueInJsonValue(value.second, key);
			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return this->values[key];
}

//cliext::map<System::String^, Json::JsonValue^> Json::JsonObject::get_value()
//{
//	return this->values;
//}

std::unordered_map<std::string, Json::JsonValue*> Json::JsonObject::get_value()
{
	return this->values;
}

std::string Json::JsonObject::get_pair(std::string key)
{
	return std::string();
}

bool Json::JsonObject::is_exist(std::string key)
{
	auto search = this->values.find(key);
	if (search != this->values.end())
	{
		return true;
	}
	return false;
}

void Json::JsonObject::add_value(std::pair<std::string, Json::JsonValue*> value)
{
	this->values.insert(value);
}

void Json::JsonObject::replaceValue(const std::string& key, const std::wstring value)
{
	if (!this->is_exist(key))
	{
		Json::JsonString* val = new Json::JsonString(value);
		this->add_value(std::make_pair(key, val));
	}
	else
	{
		Json::JsonString* val = new Json::JsonString(value);
		this->values[key] = val;
	}
}

std::string Json::JsonObject::to_string()
{
	std::string builder;
	builder += "{";

	bool first = true;

	for (auto& var : this->values)
	{
		if (!first)
			builder += ",";

		std::string key = var.first;
		std::string value;

		if (var.second->get_type() == Json::JsonTypes::String)
		{
			value = "\"" + key + "\":" + var.second->_as_string();
		}
		else
		{
			value = "\"" + key + "\":" + var.second->to_string();
		}

		builder += value;
		first = false;
	}

	builder += "}";

	return builder;
}

wchar_t* Json::JsonObject::to_stringW()
{
	const wchar_t* start = L"{";
	wchar_t* result;
	bool first = true;

	for (auto& it : this->values)
	{
		if (!first) 
			result = StrDogW(start, L",");

		result = StrDogWA(L"\"", it.first.c_str());
		result = StrDogW(result, L"\":");
		result = StrDogW(result, it.second->to_stringW());

		first = false;
	}

	result = StrDogW(result, L"}");

	return result;
}

int Json::JsonObject::get_count()
{
	return this->GetSize();
}

void Json::JsonObject::_JsonValueToStringHelper(Json::JsonValue* json_value, std::string builder, int current_indent, int indent)
{
	builder += "{\n";
	int i = 0;

	for (auto& kvp : json_value->get_value())
	{
		_Indent(builder, current_indent + indent);

		builder += "\"" + kvp.first + "\": ";

		kvp.second->_JsonValueToStringHelper(kvp.second, builder, current_indent + indent, indent);

		if (i != json_value->get_count() - 1)
		{
			builder += ",";
		}
		builder += "\n";
		++i;
	}
	_Indent(builder, current_indent);
	builder += "}";
}

Json::JsonValue* Json::JsonParcer::ParseFile(const wchar_t* filename)
{
	if (!std::filesystem::exists(Additionals::Convectors::ConvertWcharPtrToString(filename))) 
	{
		std::cout << "Unable to open file: " << filename << std::endl;
		return nullptr;
	}

	std::fstream file(filename, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "failed to open " << filename << std::endl;

		return nullptr;
	}
	else
	{
		std::string json_str;

		std::string line;

		while (std::getline(file, line))
		{
			json_str += line + '\n';
		}

		file.close();

		return ParseJson(json_str);
	}
}

Json::JsonValue* Json::JsonParcer::ParseFile(std::string filename)
{
	if (!std::filesystem::exists(filename))
	{
		std::cout << "Unable to open file: " << filename << std::endl;
		return nullptr;
	}

	std::fstream file(filename, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "failed to open " << filename << std::endl;
		return nullptr;
	}
	else
	{
		std::string json_str;

		std::string line;

		while (std::getline(file, line))
		{
			json_str += line + '\n';
		}

		file.close();

		return ParseJson(json_str);
	}
}

Json::JsonValue* Json::JsonParcer::ParseJson(std::string json_str)
{
	_pos = 0;
	return ParseValue(json_str);
}

void Json::JsonValue::SaveJsonToFile(std::string file_name, int indent)
{
	std::fstream file{file_name, file.binary | file.trunc | file.in | file.out};

	if (!file.is_open())
	{
		std::cout << "failed to open " << file_name << '\n';
	}
	else
	{
		// write
		file << _JsonValueToString(indent);
	}

	file.close();
}

void Json::JsonValue::SaveJsonToFile(std::wstring file_name, int indent)
{
	std::fstream file{file_name, file.binary | file.trunc | file.in | file.out};

	if (!file.is_open())
	{
		std::cout << "failed to open " << file_name.c_str() << '\n';
	}
	else
	{
		// write
		file << _JsonValueToString(indent);
	}

	file.close();
}

void Json::JsonParcer::SkipWhitespace(std::string json_str)
{
	while (_pos < json_str.size())
	{
		#ifdef IS_SKIP_COMMENTS
		// Пропустить однострочные комментарии
		if (json_str[_pos] == '/' && json_str[_pos + 1] == '/')
		{
			_pos += 2;
			while (_pos < json_str.size() && json_str[_pos] != '\n')
			{
				++_pos;
			}
			continue;
		}

		// Пропустить многострочные комментарии
		if (json_str[_pos] == '/' && json_str[_pos + 1] == '*')
		{
			_pos += 2;
			while (_pos < json_str.size() && (json_str[_pos] != '*' || json_str[_pos + 1] != '/'))
			{
				++_pos;
			}
			if (_pos < json_str.size())
			{
				_pos += 2;
			}
			continue;
		}
		#endif

		if (!isspace(json_str[_pos]))
		{
			break;
		}

		++_pos;
	}
}

Json::JsonValue* Json::JsonParcer::ParseValue(std::string json_str)
{
	SkipWhitespace(json_str);

	if (_pos >= json_str.size())
	{
		std::cout << "Unexpected end of JSON string" << std::endl;
		return nullptr;
	}

	switch (json_str[_pos]) 
	{
	case 'n':
		return ParseNull(json_str);
	case 't':
	case 'f':
		return ParseBool(json_str);
	case '-':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return ParseNumber(json_str);
	case '"':
		return ParseString(json_str);
	case '[':
		return ParseArray(json_str);
	case '{':
		return ParseObject(json_str);
	default:
		std::cout << "Unexpected character: " << json_str[_pos] << std::endl;
		return nullptr;
	}
}

Json::JsonValue* Json::JsonParcer::ParseNull(std::string json_str)
{
	std::string expectedValue = "null";
	std::string actualValue = json_str.substr(_pos, expectedValue.size());

	if (actualValue != expectedValue) 
	{
		std::cout << "Expected " << expectedValue << " but found: " << actualValue << std::endl;
		return nullptr;
	}

	_pos += expectedValue.size();

	return new Json::JsonNull;
}

Json::JsonValue* Json::JsonParcer::ParseBool(std::string json_str)
{
	bool value = (json_str[_pos] == 't');

	std::string expectedValue = (value ? "true" : "false");
	std::string actualValue = json_str.substr(_pos, expectedValue.size());

	if (actualValue != expectedValue) 
	{
		std::cout << "Expected " << expectedValue << " but found: " << actualValue << std::endl;
		return nullptr;
	}

	_pos += expectedValue.size();

	return new Json::JsonBool(value);
}

Json::JsonValue* Json::JsonParcer::ParseNumber(std::string json_str)
{
	std::string num_str;

	while (_pos < json_str.size() && (isdigit(json_str[_pos]) || json_str[_pos] == '.' || json_str[_pos] == '-'))
	{
		num_str += json_str[_pos];
		++_pos;
	}

	return new Json::JsonNumber(::atof(num_str.c_str()));
}

Json::JsonValue* Json::JsonParcer::ParseString(std::string json_str)
{
	if (json_str[_pos] != '\"') 
	{
		std::cout << "Expected string but found: " << json_str[_pos] << std::endl;
		return nullptr;
	}

	++_pos;

	std::string value_str;

	while (_pos < json_str.size() && json_str[_pos] != '\"')
	{
		if (json_str[_pos] == '\\') 
		{
			++_pos;

			if (_pos >= json_str.size())
			{
				std::cout << "Unexpected end of JSON string" << std::endl;
				return nullptr;
			}

			switch (json_str[_pos]) 
			{
			case '\"':
				value_str += '\"';
				break;
			case '\\':
				value_str += '\\';
				break;
			case '/':
				value_str += '/';
				break;
			case 'b':
				value_str += '\b';
				break;
			case 'f':
				value_str += '\f';
				break;
			case 'n':
				value_str += '\n';
				break;
			case 'r':
				value_str += '\r';
				break;
			case 't':
				value_str += '\t';
				break;
			case 'u':
				value_str += ParseUnicode(json_str);
				break;
			default:
				std::cout << "Unknown escape character: \\" << json_str[_pos] << std::endl;
				return nullptr;
			}
		}
		else 
		{
			value_str += json_str[_pos];
		}

		++_pos;
	}

	if (_pos >= json_str.size()) 
	{
		std::cout << "Unexpected end of JSON string" << std::endl;
		return nullptr;
	}

	++_pos;

	return new Json::JsonString(value_str);
}

std::string Json::JsonParcer::ParseUnicode(std::string json_str)
{
	if (json_str.substr(_pos, 2) != "\\u") 
	{
		std::cout << "Expected unicode escape sequence but found: " << json_str.substr(_pos, 2) << std::endl;
		return "";
	}

	_pos += 2;

	std::string hex_str = json_str.substr(_pos, 4);
	_pos += 4;

	int codepoint = std::stoi(hex_str);

	if (codepoint < 0 || (codepoint >= 0xD800 && codepoint <= 0xDFFF) || codepoint > 0x10FFFF) 
	{
		std::cout << "Invalid Unicode code point: " << hex_str << std::endl;
		return "";
	}

	std::string result;
	if (codepoint < 0x80) 
	{
		result = std::string(static_cast<wchar_t>(codepoint), 1);
	}
	else if (codepoint < 0x800) 
	{
		result = std::string(static_cast<wchar_t>((codepoint >> 6) | 0xC0), 1);
		result += std::string(static_cast<wchar_t>((codepoint & 0x3F) | 0x80), 1);
	}
	else if (codepoint < 0x10000) 
	{
		result = std::string(static_cast<wchar_t>((codepoint >> 12) | 0xE0), 1);
		result += std::string(static_cast<wchar_t>(((codepoint >> 6) & 0x3F) | 0x80), 1);
		result += std::string(static_cast<wchar_t>((codepoint & 0x3F) | 0x80), 1);
	}
	else 
	{
		result = std::string(static_cast<wchar_t>((codepoint >> 18) | 0xF0), 1);
		result += std::string(static_cast<wchar_t>(((codepoint >> 12) & 0x3F) | 0x80), 1);
		result += std::string(static_cast<wchar_t>(((codepoint >> 6) & 0x3F) | 0x80), 1);
		result += std::string(static_cast<wchar_t>((codepoint & 0x3F) | 0x80), 1);
	}
	return result;
}


Json::JsonValue* Json::JsonParcer::ParseArray(std::string json_str)
{
	if (json_str[_pos] != '[') 
	{
		std::cout << "Expected array but found: " << json_str[_pos] << std::endl;
		return nullptr;
	}

	++_pos;

	Json::JsonArray* arr = new Json::JsonArray;

	SkipWhitespace(json_str);

	if (json_str[_pos] == ']') 
	{
		++_pos;
		return arr;
	}

	while (true) 
	{
		Json::JsonValue* value = ParseValue(json_str);

		if (value == nullptr) 
		{
			return nullptr;
		}

		arr->add_value(value);
		SkipWhitespace(json_str);

		if (json_str[_pos] == ']') 
		{
			++_pos;
			return arr;
		}

		if (json_str[_pos] != ',') 
		{
			std::cout << "Expected ',' or '}' but found: " << json_str[_pos] << std::endl;
			return nullptr;
		}

		++_pos;
		SkipWhitespace(json_str);
	}
}

Json::JsonValue* Json::JsonParcer::ParseObject(std::string json_str)
{
	if (json_str[_pos] != '{') 
	{
		std::cout << "Expected object but found : " << json_str[_pos] << std::endl;
		return nullptr;
	}

	Json::JsonObject* obj = new Json::JsonObject;

	++_pos;
	SkipWhitespace(json_str);

	if (json_str[_pos] == '}') 
	{
		++_pos;
		return obj;
	}

	while (true) 
	{
		Json::JsonValue* key = ParseString(json_str);

		if (key == nullptr) 
		{
			std::cout << "Expected string as object key" << std::endl;
			return nullptr;
		}

		SkipWhitespace(json_str);

		if (json_str[_pos] != ':') 
		{
			std::cout << "Expected ':' after object key but found: " << json_str[_pos] << std::endl;
			return nullptr;
		}

		++_pos;
		SkipWhitespace(json_str);

		Json::JsonValue* value = ParseValue(json_str);

		if (value == nullptr) 
		{
			return nullptr;
		}

		obj->add_value(key->to_string(), value);

		SkipWhitespace(json_str);

		if (json_str[_pos] == '}') 
		{
			++_pos;
			return obj;
		}

		if (json_str[_pos] != ',') 
		{
			std::cout << "Expected ',' or '}' but found: " << json_str[_pos] << std::endl;
			return nullptr;
		}

		++_pos;
		SkipWhitespace(json_str);
	}
}


Json::JsonNumber::JsonNumber(double value) : JsonValue(JsonTypes::Number), value(value)
{
}

Json::JsonValue* Json::JsonNumber::operator=(double value)
{
	this->value = value;
	return this;
}

Json::JsonValue* Json::JsonNumber::operator=(int value)
{
	this->value = value;
	return this;
}

Json::JsonValue* Json::JsonNumber::operator+(Json::JsonValue* value)
{
	//value += value->to_double();
	return this;
}

std::string Json::JsonNumber::to_string()
{
	return std::to_string(this->value);
}

Json::JsonTypes Json::JsonNumber::get_type()
{
	return type;
}

wchar_t* Json::JsonNumber::to_stringW()
{
	return Additionals::Convectors::ConvertStringToWcharPtr(std::to_string(this->value));
}

double Json::JsonNumber::to_double()
{
	return this->value;
}

int Json::JsonNumber::to_int()
{
	return this->value;
}

void Json::JsonNumber::_JsonValueToStringHelper(Json::JsonValue* json_value, std::string builder, int current_indent, int indent)
{
	builder += json_value->to_string();
}

Json::JsonString::JsonString(std::string& value) : JsonValue(JsonTypes::String), value(value)
{
}

Json::JsonString::JsonString(const std::wstring& value) : JsonValue(JsonTypes::String)
{
	this->value = Additionals::Convectors::ConvertWStringToString(value);
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

Json::JsonValue* Json::JsonString::operator+(Json::JsonValue* value)
{
	this->value += value->to_string();
	return this;
}

Json::JsonValue* Json::JsonString::operator=(std::string value)
{
	this->value = value;
	return this;
}

Json::JsonValue* Json::JsonString::operator=(Json::JsonValue* value)
{
	this->value = value->to_string();
	return this;
}

wchar_t* Json::JsonString::to_stringW()
{
	return Additionals::Convectors::ConvertStringToWcharPtr(this->value);
}

void Json::JsonString::_JsonValueToStringHelper(Json::JsonValue* json_value, std::string builder, int current_indent, int indent)
{
	builder += "\"" + json_value->to_string() + "\"";
}

Json::JsonValue* Json::JsonString::operator=(std::wstring value)
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
	return this;
}

//cliext::map<System::String^, Json::JsonValue^> Json::JsonValue::get_value()
//{
//	return cliext::map<System::String^, Json::JsonValue^>();
//}

Json::JsonValue::JsonValue(const Json::JsonTypes& type) : type(type)
{
}

Json::JsonValue::JsonValue()
{
}

Json::JsonValue::JsonValue(std::nullptr_t values)
{
	this->type = Json::JsonTypes::Null;
}

Json::JsonValue::~JsonValue()
{
}

Json::JsonValue* Json::JsonValue::operator[](const wchar_t* key)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator[](const std::string& key)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator[](int index)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator=(Json::JsonValue* value)
{
	if (!this->is_exist(value->to_string()))
	{
		this->add_value(value);
	}
	else
	{
		this->get_value() = value->get_value();
	}
	return this;
}

bool Json::JsonValue::operator!=(Json::JsonValue* value)
{
	return !(this->type == value->get_type());
}

bool Json::JsonValue::operator==(Json::JsonValue* value)
{
	return this->type == value->get_type();
}

Json::JsonValue* Json::JsonValue::operator=(double value)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator=(std::string value)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator=(std::wstring value)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator=(int value)
{
	return new Json::JsonValue;
}

Json::JsonValue* Json::JsonValue::operator+(Json::JsonValue* value)
{
	return new Json::JsonValue;
}

std::unordered_map<std::string, Json::JsonValue*> Json::JsonValue::get_value()
{
	return std::unordered_map<std::string, Json::JsonValue*>();
}

std::vector<Json::JsonValue*> Json::JsonValue::get_value_list()
{
	return std::vector<Json::JsonValue*>();
}

Json::JsonValue* Json::JsonValue::get_value(std::string key)
{
	return new Json::JsonValue;
}

std::string Json::JsonValue::to_string()
{
	return std::string();
}

wchar_t* Json::JsonValue::to_stringW()
{
	return nullptr;
}

std::string Json::JsonValue::_as_string()
{
	return std::string();
}

bool Json::JsonValue::HasKey(wchar_t*& key)
{
	return false;
}

int Json::JsonValue::get_count()
{
	return 0;
}

double Json::JsonValue::to_double()
{
	return 0.0;
}

int Json::JsonValue::to_int()
{
	return 0;
}

bool Json::JsonValue::is_exist(std::string key)
{
	return false;
}

//Json::JsonValue^% Json::JsonValue::get_value(System::String^ key)
//{
//	return Json::JsonValue(Json::JsonTypes::Null);
//}

void Json::JsonValue::replaceValue(const std::string& key, const std::wstring value){}

void Json::JsonValue::add_value(Json::JsonValue* value){}

void Json::JsonValue::add_value(std::pair<std::string, Json::JsonValue*> value){}

void Json::JsonValue::add_value(std::string key, Json::JsonValue* value){}

Json::JsonTypes Json::JsonValue::get_type()
{
	return type;
}

std::string Json::JsonValue::_JsonValueToString(int indent)
{
	std::string builder;
	_JsonValueToStringHelper(this, builder, 0, indent);
	return builder;
}

void Json::JsonValue::_JsonValueToStringHelper(Json::JsonValue* jsonValue, std::string builder, int current_indent, int indent){}

void Json::JsonValue::_Indent(std::string builder, int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		builder += " ";
	}
}

Json::JsonNull::JsonNull() : JsonValue(JsonTypes::Null)
{
}

std::string Json::JsonNull::to_string()
{
	return "null";
}

wchar_t* Json::JsonNull::to_stringW()
{
	return const_cast<wchar_t*>(L"null");
}

Json::JsonTypes Json::JsonNull::get_type()
{
	return type;
}

void Json::JsonNull::_JsonValueToStringHelper(Json::JsonValue* json_value, std::string builder, int current_indent, int indent)
{
	builder += json_value->to_string();
}

Json::JsonBool::JsonBool(bool value) : JsonValue(JsonTypes::Bool), value(value)
{
}

std::string Json::JsonBool::to_string()
{
	return this->value ? "true" : "false";
}

wchar_t* Json::JsonBool::to_stringW()
{
	return const_cast<wchar_t*>(this->value ? L"true" : L"false");
}

Json::JsonTypes Json::JsonBool::get_type()
{
	return type;
}

void Json::JsonBool::_JsonValueToStringHelper(Json::JsonValue* json_value, std::string builder, int current_indent, int indent)
{
	builder += json_value->to_string();
}
