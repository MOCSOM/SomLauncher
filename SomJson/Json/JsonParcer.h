#include <urlmon.h>

#include "Json.h"

#include "../../SomLauncherCpp/Additionals/Additionals.h"

#pragma comment(lib, "Urlmon.lib")

namespace Json
{
	class JsonParcer
	{
	private:
		int _pos = 0;
	public:
		JsonParcer() {}

		Json::JsonValue ParseFile(const std::wstring& filename);
		Json::JsonValue ParseFile(const std::string& filename);
		Json::JsonValue ParseJson(const std::string& json_str);
		Json::JsonValue ParseUrl(const std::string& url);

	private:
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