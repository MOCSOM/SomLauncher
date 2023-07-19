#ifndef JSON_H_     // equivalently, #if !defined HEADER_H_
#define JSON_H_

//#include <ctype.h>
//#include <tchar.h> 
//#include <stdio.h>
//#include <strsafe.h>
//#include <sys/stat.h>
//#include <cstdio>
//#include <vcclr.h>

#if defined(__cplusplus_winrt)

#include <iostream>

#elif defined(__cplusplus_cli)

#include <cliext/map>
#include <map>

#endif // cpp

#include "Additionals.h"


#define IS_SKIP_COMMENTS true

//Классы для обработки и парсинга файла json
namespace Json 
{
	public enum struct JsonTypes
	{
		String,
		Number,
		Bool,
		Array,
		Object,
		Null
	};

	ref class JsonValue abstract
	{
	protected:	
		Json::JsonTypes type;

	public:
		JsonValue(Json::JsonTypes type) : type(type) {/* type = JsonTypes::Null; */}
		JsonValue() {}
		~JsonValue() {}

		virtual Json::JsonValue^ operator[](wchar_t*& key);
		virtual Json::JsonValue^ operator[](System::String^ key);
		virtual Json::JsonValue^ operator[](int index) { return nullptr; }
		virtual Json::JsonValue^ operator=(Json::JsonValue^ value);
		virtual Json::JsonValue^ operator=(double^ value) { return nullptr; }
		virtual Json::JsonValue^ operator=(System::String^ value) { return nullptr; }
		virtual Json::JsonValue^ operator=(int^ value) { return nullptr; }
		virtual Json::JsonValue^ operator+(Json::JsonValue^ value) { return nullptr; }

		//virtual cliext::map<System::String^, Json::JsonValue^> get_value();
		virtual System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>^ get_value();

		virtual System::Collections::Generic::List<Json::JsonValue^>^ get_value_list();

		virtual Json::JsonValue^ get_value(System::String^ key) { return this; }

		virtual System::String^ to_string() { return ""; }
		virtual wchar_t* to_stringW() { return nullptr; }
		virtual System::String^ _as_string() { return ""; }

		virtual void Print() {}

		virtual bool HasKey(wchar_t*& key) { return nullptr; }

		virtual int get_count() { return 0; }

		virtual System::Double^ to_double() { return 0.0; }
		virtual int to_int() { return 0; }

		virtual bool is_exist(System::String^ key) { return nullptr; }

		virtual void add_value(Json::JsonValue^ value);
		virtual void add_value(Microsoft::VisualC::StlClr::GenericPair<System::String^, Json::JsonValue^>^ value);
		virtual void add_value(System::String^ key, Json::JsonValue^ value);
		//virtual bool HasKey(const wchar_t*& key) { return nullptr; }

		virtual Json::JsonTypes^ get_type();

		void SaveJsonToFile(System::String^ file_name, int indent);

		System::String^ _JsonValueToString(int indent);
		void _Indent(System::Text::StringBuilder^ builder, int indent);

		virtual void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent);
		

		//property System::String^ PropertyString;
		//property wchar_t* PropertyWch;
	};

	ref class JsonString : public JsonValue
	{
	private:
		System::String^ value;
	public:
		JsonString(System::String^% value): JsonValue(JsonTypes::String), value(value) {}

		System::String^ _as_string() override;
		System::String^ to_string() override;
		Json::JsonTypes^ get_type() override;

		Json::JsonValue^ operator+(Json::JsonValue^ value) override;
		Json::JsonValue^ operator=(System::String^ value) override;
		Json::JsonValue^ operator=(Json::JsonValue^ value) override;

		wchar_t* to_stringW() override;
		void Print() override;

		void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent) override;
	};

	ref class JsonNumber : public JsonValue
	{
	private:
		double^ value;

	public:
		JsonNumber(double^ value) : JsonValue(JsonTypes::Number), value(value) {}

		Json::JsonValue^ operator=(double^ value) override;
		Json::JsonValue^ operator=(int^ value) override;
		Json::JsonValue^ operator+(Json::JsonValue^ value) override;

		System::String^ to_string() override { return this->value->ToString(); }
		Json::JsonTypes^ get_type() override { return type; }
		wchar_t* to_stringW() override 
		{
			pin_ptr<const wchar_t> first = PtrToStringChars(this->value->ToString());
			return const_cast<wchar_t*>(first);
		}
		void Print() override { System::Console::Write(this->value); }
		System::Double^ to_double() override;
		int to_int() override;

		void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent) override;
	};

	ref class JsonBool : public JsonValue
	{
	private:
		bool value;

	public:
		JsonBool(bool value): JsonValue(JsonTypes::Bool), value(value){}

		System::String^ to_string() override { return this->value ? "true" : "false"; }
		wchar_t* to_stringW() override { return this->value ? L"true" : L"false"; }
		void Print() override { System::Console::Write(this->value ? "true" : "false"); }
		Json::JsonTypes^ get_type() override { return type; }

		void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent) override;
	};

	ref class JsonNull : public JsonValue
	{
	public:
		JsonNull(): JsonValue(JsonTypes::Null){}

		System::String^ to_string() override { return "null"; }
		wchar_t* to_stringW() override { return L"null"; }
		void Print() override { System::Console::Write("null"); }
		Json::JsonTypes^ get_type() override { return type; }

		void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent) override;
	};

	ref class JsonArray : public JsonValue
	{
	private:
		System::Collections::Generic::List<Json::JsonValue^>^ values;
		
	public:
		JsonArray();
		~JsonArray();

		int get_count() override { return this->values->Count; }
		void add_value(Json::JsonValue^ value) override;
		void add_value_list(Json::JsonArray^ value);

		Json::JsonValue^ FindValueInJsonValue(Json::JsonValue^ jsonValue, System::String^ key);

		int get_size() { return this->values->Count; }

		System::Collections::Generic::List<Json::JsonValue^>^ get_value_list() override;
		Json::JsonValue^ get_value(System::String^ key) override;


		JsonValue^ operator[](int index) override { return this->values[index]; }
		Json::JsonValue^ operator=(Json::JsonValue^ value) override;
		Json::JsonValue^ operator+(Json::JsonValue^ value) override;
		Json::JsonValue^ operator[](wchar_t*& key) override;
		Json::JsonValue^ operator[](System::String^ key) override;

		void Print() override;
		Json::JsonTypes^ get_type() override { return this->type; }

		System::String^ to_string() override;
		wchar_t* to_stringW() override;

		void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent) override;
	};

	ref class JsonObject : public JsonValue
	{
	private:
		//cliext::map<System::String^, Json::JsonValue^> values;
		System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>^ values;

	public:
		JsonObject();
		~JsonObject();

		void add_value(System::String^ key, Json::JsonValue^ value) override { this->values->Add(key, value); }
		int GetSize() { return this->values->Count; /*values.size();*/ }
		Json::JsonTypes^ get_type() override { return this->type; }

		Json::JsonValue^ operator[](wchar_t*& key) override;
		Json::JsonValue^ operator[](System::String^ key) override;
		//cliext::map<System::String^, Json::JsonValue^> operator=(cliext::map<System::String^, Json::JsonValue^> value) override;

		void Print() override;

		Json::JsonValue^ _FindValueInJsonValue(Json::JsonValue^ jsonValue, System::String^ key);
		Json::JsonValue^ get_value(System::String^ key) override;

		//cliext::map<System::String^, Json::JsonValue^> get_value() override;
		System::Collections::Generic::Dictionary<System::String^, Json::JsonValue^>^ get_value() override;

		System::String^ get_pair(System::String^ key);
		bool is_exist(System::String^ key) override;
		void add_value(Microsoft::VisualC::StlClr::GenericPair<System::String^, Json::JsonValue^>^ value) override;

		//bool HasKey(wchar_t*& key) override { return this->values.count(System::String(key).ToString()) > 0; }
		//bool HasKey(const wchar_t* key) override { return this->values.count(System::String(key).ToString()) > 0; }
		System::String^ to_string() override;
		wchar_t* to_stringW() override;

		int get_count() override;

		void _JsonValueToStringHelper(Json::JsonValue^ json_value, System::Text::StringBuilder^ builder, int current_indent, int indent) override;
	};

	ref class JsonParcer
	{
	private:
		int _pos;
	public:
		JsonParcer() {}

		Json::JsonValue^ ParseFile(wchar_t* filename);
		Json::JsonValue^ ParseFile(System::String^ filename);
		Json::JsonValue^ ParseJson(System::String^ json_str);

	private:
		void SkipWhitespace(System::String^ json_str);

		Json::JsonValue^ ParseValue(System::String^ json_str);
		Json::JsonValue^ ParseNull(System::String^ json_str);
		Json::JsonValue^ ParseBool(System::String^ json_str);
		Json::JsonValue^ ParseNumber(System::String^ json_str);
		Json::JsonValue^ ParseString(System::String^ json_str);
		Json::JsonValue^ ParseArray(System::String^ json_str);
		Json::JsonValue^ ParseObject(System::String^ json_str);

		System::String^ ParseUnicode(System::String^ json_str);

		
	};
}

#endif // !JSON_H_