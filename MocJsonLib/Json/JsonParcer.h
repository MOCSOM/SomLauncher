#ifndef JSONPARCER_H_
#define JSONPARCER_H_

#ifdef SOMJSONDLL_EXPORTS
#define JSONPARCER_API __declspec(dllexport)
#else
#define JSONPARCER_API __declspec(dllimport)
#endif

#include <urlmon.h>
#include <filesystem>
#include <curl/curl.h>

#include "Json.h"

#include "../../SomAdditionalsLib/Additionals.h"

#pragma comment(lib, "Urlmon.lib")

#define IS_SKIP_COMMENTS 1

namespace Json
{
	class JsonParcer
	{
	private:
		size_t _pos = 0;
	public:
		JsonParcer() {}

		static Json::JsonValue ParseFile(const std::wstring& filename);
		static Json::JsonValue ParseFile(const std::string& filename);
		static Json::JsonValue ParseJson(const std::string& json_str);
		static Json::JsonValue ParseUrl(const std::string& url, const std::filesystem::path& destination = "");

	private:
		static size_t write_data(char* ptr, size_t size, size_t nmemb, void* userdata);
		void SkipWhitespace(const std::string& json_str);

		Json::JsonValue ParseValue(const std::string& json_str);
		Json::JsonValue ParseNull(const std::string& json_str);
		Json::JsonValue ParseBool(const std::string& json_str);
		Json::JsonValue ParseNumber(const std::string& json_str);
		Json::JsonValue ParseString(const std::string& json_str);
		Json::JsonValue ParseArray(const std::string& json_str);
		Json::JsonValue ParseObject(const std::string& json_str);

		std::string ParseUnicode(const std::string& json_str);
	};
}

#endif /*JSONPARCER_H_*/