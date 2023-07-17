#ifndef JSON_H_     // equivalently, #if !defined HEADER_H_
#define JSON_H_

#include <cliext/map>
#include <ctype.h>

#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <sys/stat.h>
#include <cstdio>

#include <vcclr.h>

#include "DownloadClasses.h"

//Классы для обработки и парсинга файла json
namespace Json {
	public enum struct JsonTypes
	{
		STRING,
		NUMBER,
		BOOL,
		ARRAY,
		OBJECT,
		Null
	};
	ref class JsonValue abstract
	{
	protected:	
		Json::JsonTypes _type;

	public:
		JsonValue(Json::JsonTypes type) : _type(type) {/* type = JsonTypes::Null; */}
		JsonValue() {}
		virtual ~JsonValue() {}

		virtual Json::JsonValue^ operator[](wchar_t*& key) { return nullptr; }
		virtual Json::JsonValue^ operator[](System::String^ key) { return nullptr; }
		virtual Json::JsonValue^ operator[](int index) { return nullptr; }
		virtual Json::JsonValue^ operator=(Json::JsonValue^ value) { this->get_value() = value->get_value(); return this; }
		virtual Json::JsonValue^ operator=(double^ value) { return nullptr; }
		virtual Json::JsonValue^ operator=(System::String^ value) { return nullptr; }
		virtual Json::JsonValue^ operator=(int^ value) { return nullptr; }
		virtual Json::JsonValue^ operator+(Json::JsonValue^ value) { return nullptr; }

		virtual cliext::map<System::String^, Json::JsonValue^> get_value();
		virtual System::Collections::Generic::List<Json::JsonValue^>% get_value_list();
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

		//property System::String^ PropertyString;
		//property wchar_t* PropertyWch;
	};

	ref class JsonString : public JsonValue
	{
	private:
		System::String^ _value;
	public:
		JsonString(System::String^% value): JsonValue(JsonTypes::STRING), _value(value) {}

		System::String^ _as_string() override { return "\"" + _value + "\""; }
		System::String^ to_string() override { return  _value; }
		Json::JsonTypes^ get_type() override { return _type; }

		Json::JsonValue^ operator+(Json::JsonValue^ value) override;
		Json::JsonValue^ operator=(System::String^ value) override;
		Json::JsonValue^ operator=(Json::JsonValue^ value) override;

		wchar_t* to_stringW() override
		{
			pin_ptr<const wchar_t> first = PtrToStringChars(_value);
			//wchar_t* full_str;
			/*full_str = StrDogW(L"\"", const_cast<wchar_t*>(first));
			full_str = StrDogW(full_str, L"\"");*/
			return const_cast<wchar_t*>(first);
		}
		void Print() override 
		{ 
			System::Console::Write("\""); 
			System::Console::Write(_value); 
			System::Console::Write("\"");
		}
	};
	ref class JsonNumber : public JsonValue
	{
	private:
		double^ _value;

	public:
		JsonNumber(double^ value) : JsonValue(JsonTypes::NUMBER), _value(value) {}

		Json::JsonValue^ operator=(double^ value) override;
		Json::JsonValue^ operator=(int^ value) override;
		Json::JsonValue^ operator+(Json::JsonValue^ value) override;

		System::String^ to_string() override { return _value->ToString(); }
		Json::JsonTypes^ get_type() override { return _type; }
		wchar_t* to_stringW() override 
		{
			pin_ptr<const wchar_t> first = PtrToStringChars(_value->ToString());
			return const_cast<wchar_t*>(first);
		}
		void Print() override { System::Console::Write(_value); }
		System::Double^ to_double() override;
		int to_int() override;
	};
	ref class JsonBool : public JsonValue
	{
	private:
		bool _value;

	public:
		JsonBool(bool value): JsonValue(JsonTypes::BOOL), _value(value){}

		System::String^ to_string() override { return _value ? "true" : "false"; }
		wchar_t* to_stringW() override { return _value ? L"true" : L"false"; }
		void Print() override { System::Console::Write(_value ? "true" : "false"); }
		Json::JsonTypes^ get_type() override { return _type; }
	};
	ref class JsonNull : public JsonValue
	{
	public:
		JsonNull(): JsonValue(JsonTypes::Null){}

		System::String^ to_string() override { return "null"; }
		wchar_t* to_stringW() override { return L"null"; }
		void Print() override { System::Console::Write("null"); }
		Json::JsonTypes^ get_type() override { return _type; }
	};
	ref class JsonArray : public JsonValue
	{
	private:
		System::Collections::Generic::List<Json::JsonValue^> _values;
		
	public:
		JsonArray(): Json::JsonValue(JsonTypes::ARRAY) {}
		~JsonArray();

		int get_count() override { return _values.Count; }
		void add_value(Json::JsonValue^ value) override;
		void add_value_list(Json::JsonArray^ value);

		Json::JsonValue^ FindValueInJsonValue(Json::JsonValue^ jsonValue, System::String^ key);

		int get_size() { return _values.Count; }

		System::Collections::Generic::List<Json::JsonValue^>% get_value_list() override;
		Json::JsonValue^ get_value(System::String^ key) override;


		JsonValue^ operator[](int index) override { return _values[index]; }
		Json::JsonValue^ operator=(Json::JsonValue^ value) override;
		Json::JsonValue^ operator+(Json::JsonValue^ value) override;
		Json::JsonValue^ operator[](wchar_t*& key) override;
		Json::JsonValue^ operator[](System::String^ key) override;

		void Print() override;
		Json::JsonTypes^ get_type() override { return _type; }

		System::String^ to_string() override;
		wchar_t* to_stringW() override;
	};
	ref class JsonObject : public JsonValue
	{
	private:
		cliext::map<System::String^, Json::JsonValue^> _values;

	public:
		JsonObject() : Json::JsonValue(Json::JsonTypes::OBJECT) {}
		void add_value(System::String^ key, Json::JsonValue^ value) override { _values[key] = value; }
		int GetSize() { return _values.size(); }
		Json::JsonTypes^ get_type() override { return _type; }

		Json::JsonValue^ operator[](wchar_t*& key) override;
		Json::JsonValue^ operator[](System::String^ key) override;
		//cliext::map<System::String^, Json::JsonValue^> operator=(cliext::map<System::String^, Json::JsonValue^> value) override;

		void Print() override;

		Json::JsonValue^ _FindValueInJsonValue(Json::JsonValue^ jsonValue, System::String^ key);
		Json::JsonValue^ get_value(System::String^ key) override;
		cliext::map<System::String^, Json::JsonValue^> get_value() override;
		System::String^ get_pair(System::String^ key);
		bool is_exist(System::String^ key) override;
		void add_value(Microsoft::VisualC::StlClr::GenericPair<System::String^, Json::JsonValue^>^ value) override;

		bool HasKey(wchar_t*& key) override { return _values.count(System::String(key).ToString()) > 0; }
		//bool HasKey(const wchar_t* key) override { return _values.count(System::String(key).ToString()) > 0; }
		System::String^ to_string() override;
		wchar_t* to_stringW() override;
	};

	ref class JsonParcer
	{
	private:
		int _pos = 0;
	public:
		JsonParcer() : _pos(0) {}

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
		System::String^ ParseUnicode(System::String^ json_str);
		Json::JsonValue^ ParseArray(System::String^ json_str);
		Json::JsonValue^ ParseObject(System::String^ json_str);

	public:
		Json::JsonValue^ Parse(System::String^ json_str);
	};
}

#endif // JSON_H_