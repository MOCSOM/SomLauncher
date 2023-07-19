#include "Json.h"

//#include <cliext/vector>
#include <cliext/map>
#include <ctype.h>

Json::JsonArray::JsonArray(): Json::JsonValue(JsonTypes::Array) 
{
	this->values = gcnew System::Collections::Generic::List<Json::JsonValue^>;
}

Json::JsonArray::~JsonArray()
{
	for each (auto value in this->values)
	{
		delete value;
	}
	this->values->Clear();
}

void Json::JsonArray::add_value(Json::JsonValue^ value)
{
	if (value->get_type() == Json::JsonTypes::Array)
	{
		for each (auto var in value->get_value_list())
		{
			this->values->Add(var);
		}
	}
	else
	{
		this->values->Add(value);
	}
}

void Json::JsonArray::add_value_list(Json::JsonArray^ value)
{
	for each (auto var in value->get_value_list())
	{
		this->values->Add(var);
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

System::Collections::Generic::List<Json::JsonValue^>^ Json::JsonArray::get_value_list()
{
	return this->values;
}

Json::JsonValue^ Json::JsonArray::get_value(System::String^ key)
{
	for each (auto value in this->values)
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
	this->values->Clear();
	this->values->Add(value);

	return this;
}

Json::JsonValue^ Json::JsonArray::operator+(Json::JsonValue^ value)
{
	this->Json::JsonArray::add_value(value);

	return this;
}

Json::JsonValue^ Json::JsonArray::operator[](wchar_t*& key)
{
	for each (auto value in this->values)
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
	for each (auto value in this->values)
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
	for (int i = 0; i < this->values->Count; ++i)
	{
		this->values[i]->Print();

		if (i != this->values->Count - 1)
		{
			System::Console::Write(", ");
		}
	}
	System::Console::Write("]");
}

System::String^ Json::JsonArray::to_string()
{
	System::String^ result = "[";

	for (int i = 0; i < this->values->Count; ++i)
	{
		if (i > 0) 
			result += ",";

		result += this->values[i]->ToString();
	}

	result += "]";

	return result;
}

wchar_t* Json::JsonArray::to_stringW()
{
	wchar_t* result = L"[";
	//wchar_t* val_wcr;
	for (int i = 0; i < this->values->Count; ++i)
	{
		if (i > 0) 
			result = StrDogW(result, L",");

		pin_ptr<const wchar_t> val_wcr = PtrToStringChars(this->values[i]->ToString());
		result = StrDogW(result, const_cast<wchar_t*>(val_wcr));
	}

	result = StrDogW(result, L"]");

	return result;
}

void Json::JsonArray::_JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent)
{
	builder->Append("[\n");
	for (int i = 0; i < json_value->get_count(); i++)
	{
		_Indent(builder, current_indent + indent);
		_JsonValueToStringHelper(json_value[i], builder, current_indent + indent, indent);
		if (i != json_value->get_count() - 1)
		{
			builder->Append(",");
		}
		builder->Append("\n");
	}
	_Indent(builder, current_indent);
	builder->Append("]");
}

//cliext::map<System::String^, Json::JsonValue^> Json::JsonObject::operator=(cliext::map<System::String^, Json::JsonValue^> value)
//{
//    return this->values = value;
//}

Json::JsonObject::JsonObject() : Json::JsonValue(Json::JsonTypes::Object)
{
	this->values = gcnew System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>;
}

Json::JsonObject::~JsonObject()
{
	for each (auto var in this->values)
	{
		delete var;
	}
	this->values->Clear();
}

Json::JsonValue^ Json::JsonObject::operator[](wchar_t*& key)
{
	if (!this->values[System::String(key).ToString()])
	{
		for each (auto value in this->values)
		{
			Json::JsonValue^ result = _FindValueInJsonValue(value.Value, System::String(key).ToString());

			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return this->values[System::String(key).ToString()];
	//return values[System::String(key).ToString()];
}

Json::JsonValue^ Json::JsonObject::operator[](System::String^ key)
{
	if (!this->values[key])
	{
		for each (auto value in this->values)
		{
			Json::JsonValue^ result = _FindValueInJsonValue(value.Value, key);

			if (result != this) 
			{
				return result;
			}
		}
		return this;
	}
	return this->values[key];
	//return values[key];
}

void Json::JsonObject::Print()
{
	System::Console::Write("{");
	int i = 0;
	for each (auto kv in this->values)
	{
		System::Console::Write("\"");
		System::Console::Write(kv.Key);
		System::Console::Write("\": ");

		kv.Value->Print();

		if (i != this->values->Count - 1)
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
	if (!this->values[key])
	{
		for each (auto value in this->values)
		{
			Json::JsonValue^ result = _FindValueInJsonValue(value.Value, key);
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

System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>^ Json::JsonObject::get_value()
{
	auto value_return = gcnew System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>;

	for each (auto var in this->values)
	{
		value_return->Add(var.Key, var.Value);
	}

	return value_return;
}

System::String^ Json::JsonObject::get_pair(System::String^ key)
{
	throw gcnew System::NotImplementedException();
	// TODO: вставьте здесь оператор return
}

bool Json::JsonObject::is_exist(System::String^ key)
{
	if (this->values[key])
	{
		return true;
	}
	return false;
}

void Json::JsonObject::add_value(Microsoft::VisualC::StlClr::GenericPair<System::String^, Json::JsonValue^>^ value)
{
	//this->values.Add(value);
}


System::String^ Json::JsonObject::to_string()
{
	System::Text::StringBuilder^ builder = gcnew System::Text::StringBuilder();
	builder->Append("{");

	bool first = true;

	for each (auto var in this->values)
	{
		if (!first)
			builder->Append(",");

		System::String^ key = var.Key->ToString();
		System::String^ value;

		if (var.Value->get_type() == Json::JsonTypes::String)
		{
			value = "\"" + key + "\":" + var.Value->_as_string();
		}
		else
		{
			value = "\"" + key + "\":" + var.Value->to_string();
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

	for each(auto it in this->values)
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

int Json::JsonObject::get_count()
{
	return this->GetSize();
}

void Json::JsonObject::_JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent)
{
	builder->Append("{\n");
	int i = 0;

	for each (auto kvp in json_value->get_value())
	{
		_Indent(builder, current_indent + indent);

		builder->Append("\"" + kvp.Key + "\": ");

		kvp.Value->_JsonValueToStringHelper(kvp.Value, builder, current_indent + indent, indent);

		if (i != json_value->get_count() - 1)
		{
			builder->Append(",");
		}
		builder->Append("\n");
		++i;
	}
	_Indent(builder, current_indent);
	builder->Append("}");
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

void Json::JsonValue::SaveJsonToFile(System::String^ file_name, int indent)
{
	System::IO::StreamWriter^ file = System::IO::File::CreateText(file_name);
	file->WriteLine(_JsonValueToString(indent));
	file->Close();
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


Json::JsonValue^ Json::JsonNumber::operator=(double^ value)
{
	this->value = value;
	return this;
}

Json::JsonValue^ Json::JsonNumber::operator=(int^ value)
{
	this->value = System::Convert::ToDouble(value);
	return this;
}

Json::JsonValue^ Json::JsonNumber::operator+(Json::JsonValue^ value)
{
	//value += value->to_double();
	return this;
}

System::Double^ Json::JsonNumber::to_double()
{
	return this->value;
}

int Json::JsonNumber::to_int()
{
	return System::Convert::ToInt32(this->value);
}

void Json::JsonNumber::_JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent)
{
	builder->Append(json_value->to_string());
}

System::String^ Json::JsonString::_as_string()
{
	return "\"" + this->value + "\"";
}

System::String^ Json::JsonString::to_string()
{
	return  this->value;
}

Json::JsonTypes^ Json::JsonString::get_type()
{
	return this->type;
}

Json::JsonValue^ Json::JsonString::operator+(Json::JsonValue^ value)
{
	this->value += value->to_string();
	return this;
}

Json::JsonValue^ Json::JsonString::operator=(System::String^ value)
{
	this->value = value;
	return this;
}

Json::JsonValue^ Json::JsonString::operator=(Json::JsonValue^ value)
{
	this->value = value->to_string();
	return this;
}

wchar_t* Json::JsonString::to_stringW()
{
	pin_ptr<const wchar_t> first = PtrToStringChars(this->value);
	wchar_t* returned_value = const_cast<wchar_t*>(first);
	//wchar_t* full_str;
	/*full_str = StrDogW(L"\"", const_cast<wchar_t*>(first));
	full_str = StrDogW(full_str, L"\"");*/
	return returned_value;
}

void Json::JsonString::Print()
{
#if defined(__cplusplus_winrt)

	std::cout << "\"" << this->value << "\"";

#elif defined(__cplusplus_cli)

	System::Console::Write("\"");
	System::Console::Write(this->value);
	System::Console::Write("\"");

#endif // cpp
}

void Json::JsonString::_JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent)
{
	builder->Append("\"" + json_value->to_string() + "\"");
}

//cliext::map<System::String^, Json::JsonValue^> Json::JsonValue::get_value()
//{
//	return cliext::map<System::String^, Json::JsonValue^>();
//}

Json::JsonValue^ Json::JsonValue::operator[](wchar_t*& key)
{
	return nullptr;
}

Json::JsonValue^ Json::JsonValue::operator[](System::String^ key)
{
	return nullptr;
}

Json::JsonValue^ Json::JsonValue::operator=(Json::JsonValue^ value)
{
	//this->get_value() = value->get_value();
	this->get_value()->Clear();
	for each (auto var in value->get_value())
	{
		this->get_value()->Add(var.Key, var.Value);
	}
	return this;
}

System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>^ Json::JsonValue::get_value()
{
	return gcnew System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>;
}

System::Collections::Generic::List<Json::JsonValue^>^ Json::JsonValue::get_value_list()
{
	return gcnew System::Collections::Generic::List<Json::JsonValue^>;
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
	return type;
}

System::String^ Json::JsonValue::_JsonValueToString(int indent)
{
	System::Text::StringBuilder^ builder = gcnew System::Text::StringBuilder();
	_JsonValueToStringHelper(this, builder, 0, indent);
	return builder->ToString();
}

void Json::JsonValue::_JsonValueToStringHelper(Json::JsonValue^ jsonValue, System::Text::StringBuilder^ builder, int current_indent, int indent){}

void Json::JsonValue::_Indent(System::Text::StringBuilder^ builder, int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		builder->Append(" ");
	}
}

void Json::JsonNull::_JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent)
{
	builder->Append(json_value->to_string());
}

void Json::JsonBool::_JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent)
{
	builder->Append(json_value->to_string());
}
