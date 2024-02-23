#ifndef JSONPARCER_H_
#define JSONPARCER_H_

#include <urlmon.h>
#include <filesystem>
#include <curl/curl.h>

#include <qdebug.h>

#include "Json.h"

#include "../../Additionals/Additionals.h"

#pragma comment(lib, "Urlmon.lib")

#define IS_SKIP_COMMENTS 1

namespace SJson
{
	class JsonParcer
	{
	private:
		size_t _pos = 0;
	public:
		JsonParcer() {}

		static SJson::JsonValue ParseFile(const std::wstring& filename);
		static SJson::JsonValue ParseFile(const std::string& filename);
		static SJson::JsonValue ParseJson(const std::string& json_str);
		static SJson::JsonValue ParseUrl(const std::string& url, const std::filesystem::path& destination = "");

	private:
		static size_t write_data(char* ptr, size_t size, size_t nmemb, void* userdata);
		void SkipWhitespace(const std::string& json_str);

		SJson::JsonValue ParseValue(const std::string& json_str);
		SJson::JsonValue ParseNull(const std::string& json_str);
		SJson::JsonValue ParseBool(const std::string& json_str);
		SJson::JsonValue ParseNumber(const std::string& json_str);
		SJson::JsonValue ParseString(const std::string& json_str);
		SJson::JsonValue ParseArray(const std::string& json_str);
		SJson::JsonValue ParseObject(const std::string& json_str);

		std::string ParseUnicode(const std::string& json_str);
	};
}

#endif /*JSONPARCER_H_*/