#ifndef JSON_H_     // equivalently, #if !defined HEADER_H_
#define JSON_H_


#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <urlmon.h>

#pragma comment(lib, "Urlmon.lib")

//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QUrl>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>

#include "../Additionals/Additionals.h"

#define IS_SKIP_COMMENTS true

//Классы для обработки и парсинга файла json
namespace Json
{
	enum struct JsonTypes
	{
		String,
		Number,
		Bool,
		Array,
		Object,
		Null,
		NotImplemented
	};

	class JsonValue
	{
	protected:	
		Json::JsonTypes type;

	public:
		JsonValue(const Json::JsonTypes& type);
		JsonValue(std::nullptr_t values);
		JsonValue();
		virtual ~JsonValue();

		virtual bool operator!=(Json::JsonValue* value);
		virtual bool operator==(Json::JsonValue* value);

		virtual Json::JsonValue* operator[](const wchar_t* key);
		virtual Json::JsonValue* operator[](const std::string& key);
		virtual Json::JsonValue* operator[](int index);
		virtual Json::JsonValue* operator=(Json::JsonValue* value);
		virtual Json::JsonValue* operator=(double value);
		virtual Json::JsonValue* operator=(std::string value);
		virtual Json::JsonValue* operator=(std::wstring value);
		virtual Json::JsonValue* operator=(int value);
		virtual Json::JsonValue* operator+(Json::JsonValue* value);

		virtual std::unordered_map<std::string, Json::JsonValue*> get_value();

		virtual std::vector<Json::JsonValue*> get_value_list();

		virtual Json::JsonValue* get_value(std::string key);

		virtual std::string to_string();
		virtual wchar_t* to_stringW();
		virtual std::string _as_string();

		virtual bool HasKey(wchar_t*& key);

		virtual int get_count();

		virtual double to_double();
		virtual int to_int();

		virtual bool is_exist(std::string key);

		virtual void replaceValue(const std::string& key, const std::string& value);
		virtual void add_value(Json::JsonValue* value);
		virtual void add_value(std::pair<std::string, Json::JsonValue*> value);
		virtual void add_value(std::string key, Json::JsonValue* value);
		//virtual bool HasKey(const wchar_t*& key) { return nullptr; }

		virtual Json::JsonTypes get_type();

		void SaveJsonToFile(std::string file_name, int indent);
		void SaveJsonToFile(std::wstring file_name, int indent);

		std::string _JsonValueToString(int indent);
		void _Indent(std::string& builder, int indent);

		virtual void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent);
		

		//property System::String^ PropertyString;
		//property wchar_t* PropertyWch;
	};

	class JsonString : public JsonValue
	{
	private:
		std::string value;
	public:
		JsonString(std::string& value);
		JsonString(const std::wstring& value);
		JsonString(const std::string& value);

		std::string _as_string() override;
		std::string to_string() override;
		Json::JsonTypes get_type() override;

		Json::JsonValue* operator+(Json::JsonValue* value) override;
		Json::JsonValue* operator=(std::string value) override;
		Json::JsonValue* operator=(Json::JsonValue* value) override;
		Json::JsonValue* operator=(std::wstring value) override;

		wchar_t* to_stringW() override;

		void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonNumber : public JsonValue
	{
	private:
		double value;

	public:
		JsonNumber(double value);

		Json::JsonValue* operator=(double value) override;
		Json::JsonValue* operator=(int value) override;
		Json::JsonValue* operator+(Json::JsonValue* value) override;

		std::string to_string() override;
		Json::JsonTypes get_type() override;
		wchar_t* to_stringW() override;

		double to_double() override;
		int to_int() override;

		void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonBool : public JsonValue
	{
	private:
		bool value;

	public:
		JsonBool(bool value);

		std::string to_string() override;
		wchar_t* to_stringW() override;

		Json::JsonTypes get_type() override;

		void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonNull : public JsonValue
	{
	public:
		JsonNull();

		std::string to_string() override;
		wchar_t* to_stringW() override;
		Json::JsonTypes get_type() override;

		void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonArray : public JsonValue
	{
	private:
		std::vector<Json::JsonValue*> values;
		
	public:
		JsonArray();
		~JsonArray();

		int get_count() override;
		void add_value(Json::JsonValue* value) override;
		void add_value_list(Json::JsonArray value);

		Json::JsonValue* FindValueInJsonValue(Json::JsonValue* jsonValue, std::string key);

		int get_size();

		std::vector<Json::JsonValue*> get_value_list() override;
		Json::JsonValue* get_value(std::string key) override;


		Json::JsonValue* operator[](int index) override;
		Json::JsonValue* operator=(Json::JsonValue* value) override;
		Json::JsonValue* operator+(Json::JsonValue* value) override;
		/*Json::JsonValue* operator[](const wchar_t* key) override;
		Json::JsonValue* operator[](const std::string& key) override;*/

		Json::JsonTypes get_type() override;

		std::string to_string() override;
		wchar_t* to_stringW() override;

		void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonObject : public JsonValue
	{
	private:
		std::unordered_map<std::string, Json::JsonValue*> values;

	public:
		JsonObject();
		~JsonObject();

		void add_value(std::string key, Json::JsonValue* value) override;
		int GetSize();
		Json::JsonTypes get_type() override;

		Json::JsonValue* operator[](const wchar_t* key) override;
		Json::JsonValue* operator[](const std::string& key) override;
		//cliext::map<System::String^, Json::JsonValue^> operator=(cliext::map<System::String^, Json::JsonValue^> value) override;


		Json::JsonValue* _FindValueInJsonValue(Json::JsonValue* jsonValue, std::string key);
		Json::JsonValue* get_value(std::string key) override;

		//cliext::map<System::String^, Json::JsonValue^> get_value() override;
		std::unordered_map<std::string, Json::JsonValue*> get_value() override;

		std::string get_pair(std::string key);
		bool is_exist(std::string key) override;
		void add_value(std::pair<std::string, Json::JsonValue*> value) override;

		void replaceValue(const std::string& key, const std::string& value) override;

		//bool HasKey(wchar_t*& key) override { return this->values.count(System::String(key).ToString()) > 0; }
		//bool HasKey(const wchar_t* key) override { return this->values.count(System::String(key).ToString()) > 0; }
		std::string to_string() override;
		wchar_t* to_stringW() override;

		int get_count() override;

		void _JsonValueToStringHelper(Json::JsonValue* json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonParcer
	{
	private:
		int _pos = 0;
	public:
		JsonParcer() {}

		Json::JsonValue* ParseFile(const wchar_t* filename);
		Json::JsonValue* ParseFile(std::string filename);
		Json::JsonValue* ParseJson(std::string json_str);
		Json::JsonValue* ParseUrl(const std::string& url);

	private:
		void SkipWhitespace(std::string json_str);

		Json::JsonValue* ParseValue(std::string json_str);
		Json::JsonValue* ParseNull(std::string json_str);
		Json::JsonValue* ParseBool(std::string json_str);
		Json::JsonValue* ParseNumber(std::string json_str);
		Json::JsonValue* ParseString(std::string json_str);
		Json::JsonValue* ParseArray(std::string json_str);
		Json::JsonValue* ParseObject(std::string json_str);

		std::string ParseUnicode(std::string json_str);

		
	};
}

#endif // !JSON_H_