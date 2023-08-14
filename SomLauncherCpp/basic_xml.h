#ifndef BASIC_XML_H_
#define BASIC_XML_H_

#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <urlmon.h>

#pragma comment(lib, "Urlmon.lib")

#define IS_SKIP_COMMENTS true

namespace Xml
{
	enum struct XmlTypes
	{
		String,
		Number,
		Bool,
		Array,
		Object,
		Null,
		NotImplemented
	};

	template <Xml::XmlTypes Type = Xml::XmlTypes::NotImplemented, class Alloc = std::allocator<Xml::XmlTypes>>
	class basic_xml
	{
	public:
		std::string a;
	};

	class XmlParcer
	{
	public:
		XmlParcer();
		~XmlParcer();

		basic_xml<> ParseFile(const std::string& filename);
		basic_xml<> ParseJson(const std::string& json_str);
		//basic_xml<> ParseUrl(const std::string& url);

	private:
		void SkipWhitespace(const std::string& json_str);

		basic_xml<> ParseValue(const std::string& json_str);
		//basic_xml<> ParseNull(const std::string& json_str);
		//basic_xml<> ParseBool(const std::string& json_str);
		//basic_xml<> ParseNumber(const std::string& json_str);
		basic_xml<Xml::XmlTypes::String> ParseString(const std::string& json_str);
		//basic_xml<> ParseArray(const std::string& json_str);
		basic_xml<Xml::XmlTypes::Object> ParseObject(const std::string& json_str);

		//std::string ParseUnicode(const std::string& json_str);

	private:
		int _position = 0;
	};

	using XmlValue = Xml::basic_xml<Xml::XmlTypes::NotImplemented, std::allocator<Xml::XmlTypes>>;
}



#endif /*BASIC_XML_H_*/