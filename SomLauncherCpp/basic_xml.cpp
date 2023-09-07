#include "basic_xml.h"

Xml::XmlParcer::XmlParcer()
{
}

Xml::XmlParcer::~XmlParcer()
{
}

Xml::basic_xml<> Xml::XmlParcer::ParseFile(const std::string& filename)
{
	return Xml::basic_xml<>();
}

Xml::basic_xml<> Xml::XmlParcer::ParseJson(const std::string& json_str)
{
	return Xml::basic_xml<>();
}

void Xml::XmlParcer::SkipWhitespace(const std::string& json_str)
{
	while (this->_position < json_str.size())
	{
#ifdef IS_SKIP_COMMENTS

		// Пропустить однострочные комментарии
		if (json_str[this->_position] == '/' && json_str[this->_position + 1] == '/')
		{
			this->_position += 2;
			while (this->_position < json_str.size() && json_str[this->_position] != '\n')
			{
				++this->_position;
			}
			continue;
		}

		// Пропустить многострочные комментарии
		if (json_str[this->_position] == '/' && json_str[this->_position + 1] == '*')
		{
			this->_position += 2;
			while (this->_position < json_str.size() && (json_str[this->_position] != '*' || json_str[this->_position + 1] != '/'))
			{
				++this->_position;
			}
			if (this->_position < json_str.size())
			{
				this->_position += 2;
			}
			continue;
		}

#endif /*IS_SKIP_COMMENTS*/

		if (!isspace(json_str[this->_position]))
		{
			break;
		}

		++this->_position;
	}
}

Xml::basic_xml<> Xml::XmlParcer::ParseValue(const std::string& json_str)
{
	SkipWhitespace(json_str);

	if (this->_position >= json_str.size())
	{
		std::cout << "Unexpected end of JSON string" << std::endl;
		return Xml::basic_xml<>();
	}

	switch (json_str[this->_position])
	{
	case 'n':
		//return ParseNull(json_str);
	case 't':
	case 'f':
		//return ParseBool(json_str);
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
		//return ParseNumber(json_str);
	case '"':
		//return ParseString(json_str);
	case '[':
		//return ParseArray(json_str);
	case '{':
		//return ParseObject(json_str);
	default:
		std::cout << "Unexpected character: " << json_str[this->_position] << std::endl;
		return Xml::basic_xml<>();
	}
}

Xml::basic_xml<Xml::XmlTypes::String> Xml::XmlParcer::ParseString(const std::string& json_str)
{
	return basic_xml<Xml::XmlTypes::String>();
}

Xml::basic_xml<Xml::XmlTypes::Object> Xml::XmlParcer::ParseObject(const std::string& json_str)
{
	if (json_str[this->_position] != '{')
	{
		std::cout << "Expected object but found : " << json_str[this->_position] << std::endl;
		return Xml::basic_xml<Xml::XmlTypes::Object>();
	}

	Xml::basic_xml<Xml::XmlTypes::Object> obj;

	++this->_position;
	SkipWhitespace(json_str);

	if (json_str[this->_position] == '}')
	{
		++this->_position;
		return obj;
	}

	while (true)
	{
		Xml::basic_xml<Xml::XmlTypes::String> key = ParseString(json_str);

		/*if (key == Xml::basic_xml<Xml::XmlTypes::NotImplemented>())
		{
			std::cout << "Expected string as object key" << std::endl;
			return Xml::basic_xml<Xml::XmlTypes::Object>();
		}*/

		SkipWhitespace(json_str);

		if (json_str[this->_position] != ':')
		{
			std::cout << "Expected ':' after object key but found: " << json_str[this->_position] << std::endl;
			return Xml::basic_xml<Xml::XmlTypes::Object>();
		}

		++this->_position;
		SkipWhitespace(json_str);

		//Json::JsonValue* value = ParseValue(json_str);

		/*if (value == Xml::basic_xml<>())
		{
			return Xml::basic_xml<Xml::XmlTypes::Object>();
		}*/

		//obj->add_value(key->to_string(), value);

		SkipWhitespace(json_str);

		if (json_str[this->_position] == '}')
		{
			++this->_position;
			return obj;
		}

		if (json_str[this->_position] != ',')
		{
			std::cout << "Expected ',' or '}' but found: " << json_str[this->_position] << std::endl;
			return Xml::basic_xml<Xml::XmlTypes::Object>();
		}

		++this->_position;
		SkipWhitespace(json_str);
	}
}