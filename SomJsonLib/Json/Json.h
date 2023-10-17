#ifndef JSON_H_     // equivalently, #if !defined HEADER_H_
#define JSON_H_

//#ifdef SOMJSONDLL_EXPORTS
//#define JSONPARCER_API __declspec(dllexport)
//#else
//#define JSONPARCER_API __declspec(dllimport)
//#endif

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>

#include "..\..\SomAdditionalsLib\Additionals.h"

#include "JsonTypes.h"

//Классы для обработки и парсинга файла json
namespace Json
{
	class JsonNode;
	using JsonValue = std::shared_ptr<Json::JsonNode>;

	class JsonNode : public std::enable_shared_from_this<Json::JsonNode>
	{
	protected:
		Json::JsonTypes type;

	public:
		JsonNode(const Json::JsonTypes& type);
		//JsonNode(std::nullptr_t values);
		JsonNode();
		virtual ~JsonNode();

		virtual bool operator!=(Json::JsonValue value);
		virtual bool operator==(Json::JsonValue value);

		virtual Json::JsonValue operator[](const std::wstring& key);
		virtual Json::JsonValue operator[](const std::string& key);
		virtual Json::JsonValue operator[](int index);
		virtual Json::JsonValue& operator=(const Json::JsonValue& value);
		virtual Json::JsonValue operator=(double value);
		virtual Json::JsonValue operator=(const std::string& value);
		virtual Json::JsonValue operator=(const std::wstring& value);
		virtual Json::JsonValue operator=(int value);
		virtual Json::JsonValue operator+(Json::JsonValue value);

		virtual std::unordered_map<std::string, Json::JsonValue> get_value();

		virtual std::vector<Json::JsonValue> get_value_list();

		virtual Json::JsonValue get_value(const std::string& key);

		virtual std::string to_string();
		virtual std::wstring to_stringW();
		virtual std::string _as_string();

		virtual bool HasKey(const std::wstring& key);

		virtual int get_count();

		virtual double to_double();
		virtual int to_int();
		virtual bool toBool();

		virtual bool is_exist(const std::string& key);

		virtual void replaceValue(const std::string& key, const std::string& value);
		virtual void add_value(Json::JsonValue value);
		virtual void add_value(std::pair<std::string, Json::JsonValue> value);
		virtual void add_value(const std::string& key, Json::JsonValue value);

		virtual void setValue(Json::JsonValue value);

		virtual Json::JsonTypes get_type();

		void SaveJsonToFile(const std::string& file_name, int indent);
		void SaveJsonToFile(const std::wstring& file_name, int indent);

		std::string _JsonValueToString(int indent);
		void _Indent(std::string& builder, int indent);

		virtual void _JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent);
	};

	class JsonNull : public Json::JsonNode
	{
	public:
		JsonNull();

		std::string to_string() override;
		std::wstring to_stringW() override;
		Json::JsonTypes get_type() override;

		void _JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonArray : public Json::JsonNode
	{
	private:
		std::vector<Json::JsonValue> values;

	public:
		JsonArray();
		~JsonArray();

		int get_count() override;
		void add_value(Json::JsonValue value);
		void add_value_list(Json::JsonArray value);

		Json::JsonValue findValueInJsonValue(Json::JsonValue jsonValue,
			const std::string& key);

		int get_size();

		std::vector<Json::JsonValue> get_value_list() override;
		Json::JsonValue get_value(const std::string& key) override;

		Json::JsonValue operator[](int index) override;
		Json::JsonValue& operator=(const Json::JsonValue& value) override;
		Json::JsonValue operator+(Json::JsonValue value) override;
		/*Json::JsonValue operator[](const std::wstring& key) override;
		Json::JsonValue operator[](const std::string& key) override;*/

		Json::JsonTypes get_type() override;

		std::string to_string() override;
		std::wstring to_stringW() override;

		void _JsonValueToStringHelper(Json::JsonValue json_value,
			std::string& builder, int current_indent, int indent) override;
	};

	class JsonNumber : public Json::JsonNode
	{
	private:
		double value;

	public:
		JsonNumber(double value);

		Json::JsonValue operator=(double value) override;
		Json::JsonValue operator=(int value) override;
		Json::JsonValue operator+(Json::JsonValue value) override;

		std::string to_string() override;
		Json::JsonTypes get_type() override;
		std::wstring to_stringW() override;

		double to_double() override;
		int to_int() override;

		void _JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonObject : public Json::JsonNode
	{
	private:
		std::unordered_map<std::string, Json::JsonValue> values;

	public:
		JsonObject();
		~JsonObject();

		void add_value(const std::string& key, Json::JsonValue value) override;
		int GetSize();
		Json::JsonTypes get_type() override;

		Json::JsonValue operator[](const std::wstring& key);
		Json::JsonValue operator[](const std::string& key);
		Json::JsonValue& operator=(const Json::JsonValue& value) override;

		Json::JsonValue _FindValueInJsonValue(Json::JsonValue jsonValue,
			const std::string& key);
		Json::JsonValue get_value(const std::string& key) override;

		//cliext::map<System::String^, Json::JsonNode^> get_value();
		std::unordered_map<std::string, Json::JsonValue> get_value() override;

		std::string get_pair(const std::string& key);
		bool is_exist(const std::string& key) override;
		void add_value(std::pair<std::string, Json::JsonValue> value) override;

		void replaceValue(const std::string& key, const std::string& value) override;

		//bool HasKey(wchar_t*& key) override { return this->values.count(System::String(key).ToString()) > 0; }
		//bool HasKey(const wchar_t* key) override { return this->values.count(System::String(key).ToString()) > 0; }
		std::string to_string() override;
		std::wstring to_stringW() override;

		int get_count() override;

		void _JsonValueToStringHelper(Json::JsonValue json_value,
			std::string& builder, int current_indent, int indent) override;
	};

	class JsonString : public Json::JsonNode
	{
	private:
		std::string value;
	public:
		JsonString(const std::wstring& value);
		JsonString(const std::string& value);

		std::string _as_string() override;
		std::string to_string() override;
		Json::JsonTypes get_type() override;

		Json::JsonValue operator+(Json::JsonValue value) override;
		Json::JsonValue operator=(const std::string& value) override;
		Json::JsonValue& operator=(const Json::JsonValue& value)override;
		Json::JsonValue operator=(const std::wstring& value) override;

		std::wstring to_stringW() override;

		void _JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent) override;
	};

	class JsonBool : public Json::JsonNode
	{
	private:
		bool value;

	public:
		JsonBool(bool value);

		std::string to_string() override;
		std::wstring to_stringW() override;
		bool toBool() override;

		Json::JsonTypes get_type() override;

		void _JsonValueToStringHelper(Json::JsonValue json_value, std::string& builder, int current_indent, int indent) override;
	};
}

#endif // !JSON_H_