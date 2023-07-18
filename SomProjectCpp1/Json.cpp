﻿#include "Json.h"

//#include <cliext/vector>
#include <cliext/map>
#include <ctype.h>

Json::JsonArray::~JsonArray()
{
	for each (auto value in _values) 
	{
		delete value;
	}
}

void Json::JsonArray::add_value(Json::JsonValue^ value)
{
	if (value->get_type() == Json::JsonTypes::ARRAY)
	{
		for each (auto var in value->get_value_list())
		{
			_values.Add(var);
		}
	}
	else
	{
		_values.Add(value);
	}
}

void Json::JsonArray::add_value_list(Json::JsonArray^ value)
{
	for each (auto var in value->get_value_list())
	{
		_values.Add(var);
	}
}

Json::JsonValue^ Json::JsonArray::FindValueInJsonValue(Json::JsonValue^ jsonValue, System::String^ key)
{
	if (Json::JsonObject^ jsonObject = dynamic_cast<Json::JsonObject^>(jsonValue)) 
	{
		return jsonObject->get_value(key);
	}

	else if (Json::JsonArray^ jsonArray = dynamic_cast<Json::JsonArray^>(jsonValue)) 
	{
		return jsonArray->get_value(key);
	}

	// Handle other value types if needed (e.g., JsonString, JsonNumber, etc.)
	return this;
}

System::Collections::Generic::List<Json::JsonValue^>% Json::JsonArray::get_value_list()
{
	return _values;
}

Json::JsonValue^ Json::JsonArray::get_value(System::String^ key)
{
	for each (auto value in _values) 
	{
		Json::JsonValue^ result = FindValueInJsonValue(value, key);

		if (result != this) 
		{
			return result;
		}
	}

	return this;
}

Json::JsonValue^ Json::JsonArray::operator=(Json::JsonValue^ value)
{
	_values.Clear();
	_values.Add(value);

	return this;
}

Json::JsonValue^ Json::JsonArray::operator+(Json::JsonValue^ value)
{
	this->Json::JsonArray::add_value(value);

	return this;
}

Json::JsonValue^ Json::JsonArray::operator[](wchar_t*& key)
{
	for each (auto value in _values) 
	{
		Json::JsonValue^ result = FindValueInJsonValue(value, System::String(key).ToString());

		if (result != this) 
		{
			return result;
		}
	}

	return this;
}

Json::JsonValue^ Json::JsonArray::operator[](System::String^ key)
{
	for each (auto value in _values) 
	{
		Json::JsonValue^ result = FindValueInJsonValue(value, key);

		if (result != this) 
		{
			return result;
		}
	}
	return this;
}


void Json::JsonArray::Print()
{
	System::Console::Write("[");
	for (int i = 0; i < _values.Count; ++i) 
	{
		_values[i]->Print();

		if (i != _values.Count - 1) 
		{
			System::Console::Write(", ");
		}
	}
	System::Console::Write("]");
}

System::String^ Json::JsonArray::to_string()
{
	System::String^ result = "[";

	for (int i = 0; i < _values.Count; ++i) 
	{
		if (i > 0) 
			result += ",";

		result += _values[i]->ToString();
	}

	result += "]";

	return result;
}

wchar_t* Json::JsonArray::to_stringW()
{
	wchar_t* result = L"[";
	//wchar_t* val_wcr;
	for (int i = 0; i < _values.Count; ++i) 
	{
		if (i > 0) 
			result = StrDogW(result, L",");

		pin_ptr<const wchar_t> val_wcr = PtrToStringChars(_values[i]->ToString());
		result = StrDogW(result, const_cast<wchar_t*>(val_wcr));
	}

	result = StrDogW(result, L"]");

	return result;
}

//cliext::map<System::String^, Json::JsonValue^> Json::JsonObject::operator=(cliext::map<System::String^, Json::JsonValue^> value)
//{
//    return _values = value;
//}

Json::JsonValue^ Json::JsonObject::operator[](wchar_t*& key)
{
	if (!_values[System::String(key).ToString()])
	{
		for each (auto value in _values) 
		{
			Json::JsonValue^ result = _FindValueInJsonValue(value->second, System::String(key).ToString());

			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return _values[System::String(key).ToString()];
	//return _values[System::String(key).ToString()];
}

Json::JsonValue^ Json::JsonObject::operator[](System::String^ key)
{
	if (!_values[key])
	{
		for each (auto value in _values) 
		{
			Json::JsonValue^ result = _FindValueInJsonValue(value->second, key);

			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return _values[key];
	//return _values[key];
}

void Json::JsonObject::Print()
{
	System::Console::Write("{");
	int i = 0;
	for each (auto kv in _values) 
	{
		System::Console::Write("\"");
		System::Console::Write(kv->first);
		System::Console::Write("\": ");

		kv->second->Print();

		if (i != _values.size() - 1) 
		{
			System::Console::Write(", ");
		}
		++i;
	}
	System::Console::Write("}");
}

Json::JsonValue^ Json::JsonObject::_FindValueInJsonValue(Json::JsonValue^ jsonValue, System::String^ key)
{
	if (JsonObject^ jsonObject = dynamic_cast<JsonObject^>(jsonValue)) 
	{
		return jsonObject->get_value(key);
	}

	else if (JsonArray^ jsonArray = dynamic_cast<JsonArray^>(jsonValue)) 
	{
		return jsonArray->get_value(key);
	}

	// Handle other value types if needed (e.g., JsonString, JsonNumber, etc.)
	return this;
}

Json::JsonValue^ Json::JsonObject::get_value(System::String^ key)
{
	if (!_values[key])
	{
		for each (auto value in _values) 
		{
			Json::JsonValue^ result = _FindValueInJsonValue(value->second, key);
			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return _values[key];
}

cliext::map<System::String^, Json::JsonValue^> Json::JsonObject::get_value()
{
	return _values;
}

System::String^ Json::JsonObject::get_pair(System::String^ key)
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}

bool Json::JsonObject::is_exist(System::String^ key)
{
	if (_values[key])
	{
		return true;
	}
	return false;
}

void Json::JsonObject::add_value(Microsoft::VisualC::StlClr::GenericPair<System::String^, Json::JsonValue^>^ value)
{
	//_values.Add(value);
}


System::String^ Json::JsonObject::to_string()
{
	System::Text::StringBuilder^ builder = gcnew System::Text::StringBuilder();
	builder->Append("{");

	bool first = true;

	for each (auto var in _values)
	{
		if (!first)
			builder->Append(",");

		System::String^ key = var->first->ToString();
		System::String^ value;

		if (var->second->get_type() == Json::JsonTypes::STRING)
		{
			value = "\"" + key + "\":" + var->second->_as_string();
		}
		else
		{
			value = "\"" + key + "\":" + var->second->to_string();
		}

		builder->Append(value);
		first = false;
	}

	builder->Append("}");

	return builder->ToString();
}

wchar_t* Json::JsonObject::to_stringW()
{
	wchar_t* result = L"{";
	bool first = true;

	for (auto it = _values.begin(); it != _values.end(); ++it) 
	{
		if (!first) 
			result = StrDogW(result, L",");

		pin_ptr<const wchar_t> it_wcr = PtrToStringChars(it.ToString());

		result = StrDogW(L"\"", const_cast<wchar_t*>(it_wcr));
		result = StrDogW(result, L"\":");
		result = StrDogW(result, const_cast<wchar_t*>(it_wcr));

		first = false;
	}

	result = StrDogW(result, L"}");

	return result;
}

Json::JsonValue^ Json::JsonParcer::ParseFile(wchar_t* filename)
{
	if (!System::IO::File::Exists(System::String(filename).ToString())) 
	{
		System::Console::WriteLine("Unable to open file: " + System::String(filename).ToString());
		return nullptr;
	}

	System::IO::StreamReader^ file = System::IO::File::OpenText(System::String(filename).ToString());

	System::String^ json_str(file->ReadToEnd());

	file->Close();

	return ParseJson(json_str);
}

Json::JsonValue^ Json::JsonParcer::ParseFile(System::String^ filename)
{
	if (!System::IO::File::Exists(filename)) 
	{
		System::Console::WriteLine("Unable to open file: " + filename);
		return nullptr;
	}

	System::IO::StreamReader^ file = System::IO::File::OpenText(filename);

	System::String^ json_str(file->ReadToEnd());

	file->Close();

	return ParseJson(json_str);
}

Json::JsonValue^ Json::JsonParcer::ParseJson(System::String^ json_str)
{
	_pos = 0;
	return ParseValue(json_str);
}

void Json::JsonParcer::SkipWhitespace(System::String^ json_str)
{
	while (_pos < json_str->Length) 
	{
		#ifdef IS_SKIP_COMMENTS
		// Пропустить однострочные комментарии
		if (json_str[_pos] == '/' && json_str[_pos + 1] == '/')
		{
			_pos += 2;
			while (_pos < json_str->Length && json_str[_pos] != '\n')
			{
				++_pos;
			}
			continue;
		}

		// Пропустить многострочные комментарии
		if (json_str[_pos] == '/' && json_str[_pos + 1] == '*')
		{
			_pos += 2;
			while (_pos < json_str->Length && (json_str[_pos] != '*' || json_str[_pos + 1] != '/'))
			{
				++_pos;
			}
			if (_pos < json_str->Length)
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

Json::JsonValue^ Json::JsonParcer::ParseValue(System::String^ json_str)
{
	SkipWhitespace(json_str);

	if (_pos >= json_str->Length) 
	{
		System::Console::WriteLine("Unexpected end of JSON string", "\n");
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
		System::Console::WriteLine("Unexpected character: " + json_str[_pos] + "\n");
		return nullptr;
	}
}

Json::JsonValue^ Json::JsonParcer::ParseNull(System::String^ json_str)
{
	System::String^ expectedValue = "null";
	System::String^ actualValue = json_str->Substring(_pos, expectedValue->Length);

	if (actualValue != expectedValue) 
	{
		System::Console::WriteLine("Expected " + expectedValue + " but found: " + actualValue + "\n");
		return nullptr;
	}

	_pos += expectedValue->Length;

	return gcnew Json::JsonNull();
}

Json::JsonValue^ Json::JsonParcer::ParseBool(System::String^ json_str)
{
	bool value = (json_str[_pos] == 't');

	System::String^ expectedValue = (value ? "true" : "false");
	System::String^ actualValue = json_str->Substring(_pos, expectedValue->Length);

	if (actualValue != expectedValue) 
	{
		System::Console::WriteLine("Expected " + expectedValue + " but found: " + actualValue + "\n");
		return nullptr;
	}

	_pos += expectedValue->Length;

	return gcnew Json::JsonBool(value);
}

Json::JsonValue^ Json::JsonParcer::ParseNumber(System::String^ json_str)
{
	System::String^ num_str;

	while (_pos < json_str->Length && (isdigit(json_str[_pos]) || json_str[_pos] == '.' || json_str[_pos] == '-')) 
	{
		num_str += json_str[_pos];
		++_pos;
	}

	return gcnew Json::JsonNumber(System::Convert::ToDouble(num_str));
}

Json::JsonValue^ Json::JsonParcer::ParseString(System::String^ json_str)
{
	if (json_str[_pos] != '\"') 
	{
		System::Console::WriteLine("Expected string but found: " + json_str[_pos] + "\n");
		return nullptr;
	}

	++_pos;

	System::Text::StringBuilder^ value_str = gcnew System::Text::StringBuilder();

	while (_pos < json_str->Length && json_str[_pos] != '\"') 
	{
		if (json_str[_pos] == '\\') 
		{
			++_pos;

			if (_pos >= json_str->Length) 
			{
				System::Console::WriteLine("Unexpected end of JSON string\n");
				return nullptr;
			}

			switch (json_str[_pos]) 
			{
			case '\"':
				value_str->Append('\"');
				break;
			case '\\':
				value_str->Append('\\');
				break;
			case '/':
				value_str->Append('/');
				break;
			case 'b':
				value_str->Append('\b');
				break;
			case 'f':
				value_str->Append('\f');
				break;
			case 'n':
				value_str->Append('\n');
				break;
			case 'r':
				value_str->Append('\r');
				break;
			case 't':
				value_str->Append('\t');
				break;
			case 'u':
				value_str->Append(ParseUnicode(json_str));
				break;
			default:
				System::Console::WriteLine("Unknown escape character: \\" + json_str[_pos] + "\n");
				return nullptr;
			}
		}
		else 
		{
			value_str->Append(json_str[_pos]);
		}

		++_pos;
	}

	if (_pos >= json_str->Length) 
	{
		System::Console::WriteLine("Unexpected end of JSON string\n");
		return nullptr;
	}

	++_pos;

	return gcnew Json::JsonString(value_str->ToString());
}

System::String^ Json::JsonParcer::ParseUnicode(System::String^ json_str)
{
	if (json_str->Substring(_pos, 2) != "\\u") 
	{
		System::Console::WriteLine("Expected unicode escape sequence but found: " + json_str->Substring(_pos, 2) + "\n");
		return "";
	}

	_pos += 2;

	System::String^ hex_str = json_str->Substring(_pos, 4);
	_pos += 4;

	int codepoint = System::Convert::ToInt32(hex_str, 16);

	if (codepoint < 0 || (codepoint >= 0xD800 && codepoint <= 0xDFFF) || codepoint > 0x10FFFF) 
	{
		System::Console::WriteLine("Invalid Unicode code point: " + hex_str + "\n");
		return "";
	}

	System::String^ result;
	if (codepoint < 0x80) 
	{
		result = gcnew System::String(static_cast<wchar_t>(codepoint), 1);
	}
	else if (codepoint < 0x800) 
	{
		result = gcnew System::String(static_cast<wchar_t>((codepoint >> 6) | 0xC0), 1);
		result += gcnew System::String(static_cast<wchar_t>((codepoint & 0x3F) | 0x80), 1);
	}
	else if (codepoint < 0x10000) 
	{
		result = gcnew System::String(static_cast<wchar_t>((codepoint >> 12) | 0xE0), 1);
		result += gcnew System::String(static_cast<wchar_t>(((codepoint >> 6) & 0x3F) | 0x80), 1);
		result += gcnew System::String(static_cast<wchar_t>((codepoint & 0x3F) | 0x80), 1);
	}
	else 
	{
		result = gcnew System::String(static_cast<wchar_t>((codepoint >> 18) | 0xF0), 1);
		result += gcnew System::String(static_cast<wchar_t>(((codepoint >> 12) & 0x3F) | 0x80), 1);
		result += gcnew System::String(static_cast<wchar_t>(((codepoint >> 6) & 0x3F) | 0x80), 1);
		result += gcnew System::String(static_cast<wchar_t>((codepoint & 0x3F) | 0x80), 1);
	}
	return result;
}

Json::JsonValue^ Json::JsonParcer::ParseArray(System::String^ json_str)
{
	if (json_str[_pos] != '[') 
	{
		System::Console::WriteLine("Expected array but found: ", json_str[_pos], "\n");
		return nullptr;
	}

	++_pos;

	Json::JsonArray^ arr = gcnew Json::JsonArray();

	SkipWhitespace(json_str);

	if (json_str[_pos] == ']') 
	{
		++_pos;
		return arr;
	}

	while (true) 
	{
		Json::JsonValue^ value = ParseValue(json_str);

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
			System::Console::WriteLine("Expected ',' or '}' but found: " + json_str[_pos] + "\n");
			return nullptr;
		}

		++_pos;
		SkipWhitespace(json_str);
	}
}

Json::JsonValue^ Json::JsonParcer::ParseObject(System::String^ json_str)
{
	if (json_str[_pos] != '{') 
	{
		System::Console::WriteLine("Expected object but found: " + json_str[_pos] + "\n");
		return nullptr;
	}

	Json::JsonObject^ obj = gcnew Json::JsonObject();

	++_pos;
	SkipWhitespace(json_str);

	if (json_str[_pos] == '}') 
	{
		++_pos;
		return obj;
	}

	while (true) 
	{
		Json::JsonValue^ key = ParseString(json_str);

		if (key == nullptr) 
		{
			System::Console::WriteLine("Expected string as object key\n");
			return nullptr;
		}

		SkipWhitespace(json_str);

		if (json_str[_pos] != ':') 
		{
			System::Console::WriteLine("Expected ':' after object key but found: " + json_str[_pos] + "\n");
			return nullptr;
		}

		++_pos;
		SkipWhitespace(json_str);

		Json::JsonValue^ value = ParseValue(json_str);

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
			System::Console::WriteLine("Expected ',' or '}' but found: " + json_str[_pos] + "\n");
			return nullptr;
		}

		++_pos;
		SkipWhitespace(json_str);
	}
}

Json::JsonValue^ Json::JsonParcer::Parse(System::String^ json_str)
{
	_pos = 0;
	SkipWhitespace(json_str);

	Json::JsonValue^ value = ParseValue(json_str);

	if (value == nullptr) 
	{
		System::Console::WriteLine("Failed to parse JSON string: ", json_str, "\n");
	}
	return value;
}

Json::JsonValue^ Json::JsonNumber::operator=(double^ value)
{
	_value = value;
	return this;
}

Json::JsonValue^ Json::JsonNumber::operator=(int^ value)
{
	_value = System::Convert::ToDouble(value);
	return this;
}

Json::JsonValue^ Json::JsonNumber::operator+(Json::JsonValue^ value)
{
	//_value += value->to_double();
	return this;
}

System::Double^ Json::JsonNumber::to_double()
{
	return _value;
}

int Json::JsonNumber::to_int()
{
	return System::Convert::ToInt32(_value);
}

Json::JsonValue^ Json::JsonString::operator+(Json::JsonValue^ value)
{
	_value += value->to_string();
	return this;
}

Json::JsonValue^ Json::JsonString::operator=(System::String^ value)
{
	_value = value;
	return this;
}

Json::JsonValue^ Json::JsonString::operator=(Json::JsonValue^ value)
{
	_value = value->to_string();
	return this;
}

cliext::map<System::String^, Json::JsonValue^> Json::JsonValue::get_value()
{
	return cliext::map<System::String^, Json::JsonValue^>();
}

System::Collections::Generic::List<Json::JsonValue^>% Json::JsonValue::get_value_list()
{
	return System::Collections::Generic::List<Json::JsonValue^>();
}

//Json::JsonValue^% Json::JsonValue::get_value(System::String^ key)
//{
//	return Json::JsonValue(Json::JsonTypes::Null);
//}

void Json::JsonValue::add_value(Json::JsonValue^ value){}

void Json::JsonValue::add_value(Microsoft::VisualC::StlClr::GenericPair<System::String^, Json::JsonValue^>^ value){}

void Json::JsonValue::add_value(System::String^ key, Json::JsonValue^ value){}

Json::JsonTypes^ Json::JsonValue::get_type()
{
	return _type;
}