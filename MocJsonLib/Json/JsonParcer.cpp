#include "pch.h"

#include "JsonParcer.h"

Json::JsonValue Json::JsonParcer::ParseFile(const std::wstring& filename)
{
	std::string file_name_string = Additionals::Convectors::ConvertWStringToString(filename);

	if (!std::filesystem::exists(file_name_string))
	{
		std::cout << "Unable to open file: " << file_name_string << std::endl;
		return nullptr;
	}

	std::fstream file(file_name_string, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "failed to open " << file_name_string << std::endl;

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

Json::JsonValue Json::JsonParcer::ParseFile(const std::string& filename)
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

Json::JsonValue Json::JsonParcer::ParseJson(const std::string& json_str)
{
	Json::JsonParcer parcer;
	parcer._pos = 0;
	return parcer.ParseValue(json_str);
}

Json::JsonValue Json::JsonParcer::ParseUrl(const std::string& url, const std::filesystem::path& destination)
{
	std::string destenation_file = Additionals::TempFile::get_tempdir_SYSTEM();

	if (destination == "")
	{
		destenation_file = destination.u8string();
	}

	{
		std::string replace_url = url;
		replace_url = Additionals::String::split(url, '/')[Additionals::String::split(url, '/').size() - 1];
		destenation_file = destenation_file /*+ "\\"*/ + replace_url;
	}
	std::string normalise_url = url;
	// Замена двойных косых черт на одиночные
	size_t pos = normalise_url.find("//");
	while (pos != std::string::npos)
	{
		normalise_url.replace(pos, 2, "/");
		pos = normalise_url.find("//", pos + 1);
	}

	CURL* curl = nullptr;
	CURLcode res;
	std::ofstream output(destenation_file, std::ios::binary);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, normalise_url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		output.close();
	}
	else
	{
		std::cerr << "Curl failed init" << std::endl;;
		output.close();
	}

	output.close();
	//HRESULT resurl = URLDownloadToFileA(NULL, normalise_url.c_str(), destenation_file.c_str(), NULL, NULL);

	if (res == CURLE_OK)
	{
		Json::JsonValue return_val = ParseFile(destenation_file);
		if (destination == "")
		{
			std::remove(destenation_file.c_str());
		}
		else
		{
			std::filesystem::copy_file(destenation_file, destination, std::filesystem::copy_options::overwrite_existing);
			std::remove(destenation_file.c_str());
		}
		return return_val;
	}
	else
	{
		std::cerr << "Dont download file in json" << std::endl;
	}
	return nullptr;
}

size_t Json::JsonParcer::write_data(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	std::ofstream* out = static_cast<std::ofstream*>(userdata);
	size_t nbytes = size * nmemb;
	out->write(ptr, nbytes);

	return nbytes;
}

void Json::JsonParcer::SkipWhitespace(const std::string& json_str)
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

Json::JsonValue Json::JsonParcer::ParseValue(const std::string& json_str)
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

Json::JsonValue Json::JsonParcer::ParseNull(const std::string& json_str)
{
	std::string expectedValue = "null";
	std::string actualValue = json_str.substr(_pos, expectedValue.size());

	if (actualValue != expectedValue)
	{
		std::cout << "Expected " << expectedValue << " but found: " << actualValue << std::endl;
		return nullptr;
	}

	_pos += expectedValue.size();

	return Json::JsonValue(std::nullptr_t());
}

Json::JsonValue Json::JsonParcer::ParseBool(const std::string& json_str)
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

	return Json::JsonValue(value);
}

Json::JsonValue Json::JsonParcer::ParseNumber(const std::string& json_str)
{
	std::string num_str;

	while (_pos < json_str.size() && (isdigit(json_str[_pos]) || json_str[_pos] == '.' || json_str[_pos] == '-'))
	{
		num_str += json_str[_pos];
		++_pos;
	}

	return Json::JsonValue(::atof(num_str.c_str()));
}

Json::JsonValue Json::JsonParcer::ParseString(const std::string& json_str)
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

	return Json::JsonValue(value_str);
}

std::string Json::JsonParcer::ParseUnicode(const std::string& json_str)
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

Json::JsonValue Json::JsonParcer::ParseArray(const std::string& json_str)
{
	if (json_str[_pos] != '[')
	{
		std::cout << "Expected array but found: " << json_str[_pos] << std::endl;
		return nullptr;
	}

	++_pos;

	Json::JsonValue arr = Json::JsonValue(std::vector<Json::SomJson>());

	SkipWhitespace(json_str);

	if (json_str[_pos] == ']')
	{
		++_pos;
		return arr;
	}

	while (true)
	{
		Json::JsonValue value = ParseValue(json_str);

		if (value == nullptr)
		{
			return nullptr;
		}

		arr.add_value(value);
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

Json::JsonValue Json::JsonParcer::ParseObject(const std::string& json_str)
{
	if (json_str[_pos] != '{')
	{
		std::cout << "Expected object but found : " << json_str[_pos] << std::endl;
		return nullptr;
	}

	Json::JsonValue obj = Json::JsonValue(std::unordered_map<std::string, Json::SomJson>());

	++_pos;
	SkipWhitespace(json_str);

	if (json_str[_pos] == '}')
	{
		++_pos;
		return obj;
	}

	while (true)
	{
		Json::JsonValue key = ParseString(json_str);

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

		Json::JsonValue value = ParseValue(json_str);

		if (value == nullptr)
		{
			return nullptr;
		}

		obj.add_value(key.to_string(), value);

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