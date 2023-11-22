#ifndef JSON_H_
#define JSON_H_

#include "../pch.h"
#include "../framework.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "JsonTypes.h"
#include "../../SomAdditionalsLib/Additionals.h"

namespace Json
{
	class SomJson
	{
	private:
		struct StandartNode
		{
			Json::JsonTypes type = Json::JsonTypes::NotImplemented;
		};

		struct Node : public StandartNode
		{
			bool bool_value = NULL;
			long double number_value = NULL;
			std::string string_value = "";
			std::nullptr_t null_value = NULL;
			std::unordered_map<std::string, Json::SomJson> object_value = {};
			std::vector<Json::SomJson> array_value = {};

			Node();
			Node(Json::JsonTypes type);
			Node(long double number_value);
			Node(double number_value);
			Node(int number_value);
			Node(long long number_value);
			Node(bool bool_value);
			Node(std::string string_value);
			Node(const char* string_value);
			Node(std::nullptr_t null_value);
			Node(std::unordered_map<std::string, Json::SomJson> object_value);
			Node(std::vector<Json::SomJson> array_value);

			bool operator==(const Node& value) const;
			bool operator!=(const Node& value) const;
		};

	private:
		template <typename ITERATOR>
		class SomIterator
		{
			friend class Json::SomJson;
			friend struct Json::SomJson::Node;

		public:
			typedef ITERATOR iterator_type;
			typedef std::forward_iterator_tag iterator_category; //категория итератора может быть иной, но должна соответствовать стандарту
			typedef iterator_type value_type;
			typedef iterator_type& reference;
			typedef iterator_type* pointer;
			typedef ptrdiff_t difference_type;

			iterator_type* value;

		private:
			SomIterator(ITERATOR* pointer);

		public:
			SomIterator(const SomIterator& other);

			bool operator!=(const SomIterator& other) const noexcept;
			bool operator==(const SomIterator& other) const noexcept;

			typename SomIterator::reference operator*() noexcept;
			typename SomIterator::pointer operator->() noexcept;

			SomIterator& operator++() noexcept;

			SomIterator operator++(int) noexcept;

			SomIterator& operator[](const size_t index) noexcept;
		};

	private:
		std::shared_ptr<Node> value;

	public:
		typedef SomIterator<Node> iterator;
		typedef SomIterator<const Node> const_iterator;

		iterator begin() noexcept;
		iterator end() noexcept;

		const_iterator begin() const noexcept;

		const_iterator end() const noexcept;

	public:
		SomJson();
		SomJson(Node json);
		SomJson(const Json::SomJson& json);
		SomJson(std::nullptr_t null);
		~SomJson();

		void add_value(const std::string& key, const Node& value);
		void add_value(const std::string& key, const Json::SomJson& value);
		void add_value(const std::pair<std::string, Json::SomJson>& pair);
		void add_value(const Node& value);
		void add_value(const Json::SomJson& value);

		void replace_value(const size_t& index, const Node& value);
		void replace_value(const std::string& key, const Node& value);

		long double& get_number();
		bool& get_bool();
		std::string& get_string();
		std::nullptr_t& get_null();
		std::unordered_map<std::string, Json::SomJson>& get_object();
		std::vector<Json::SomJson>& get_array();

		size_t get_count();
		Json::JsonTypes get_type();

		std::string to_string();
		std::wstring to_stringW();
		int to_int();

		bool is_exist(const std::string& key);

		Json::SomJson& operator[](const std::string& key);
		Json::SomJson& operator[](const size_t& index);

		Json::SomJson& operator=(const Json::SomJson& value);
		Json::SomJson& operator=(const Node& value);
		Json::SomJson& operator+=(const Json::SomJson& value);
		Json::SomJson operator+(const Json::SomJson& value);

		bool operator==(const std::nullptr_t& null);
		bool operator!=(const std::nullptr_t& null);

		bool operator==(const Json::SomJson& value) const;
		bool operator!=(const Json::SomJson& value) const;

		void save_json_to_file(const std::string& file_name, int indent);
		std::string _json_value_to_string(int indent);
		void _json_value_to_string_helper(Json::SomJson json_value, std::string& builder, int current_indent, int indent);
		void _indent(std::string& builder, int indent);
	};

	using JsonValue = Json::SomJson;

	template<typename ITERATOR>
	inline SomJson::SomIterator<ITERATOR>::SomIterator(ITERATOR* pointer)
		: value(pointer)
	{
	}
	template<typename ITERATOR>
	inline SomJson::SomIterator<ITERATOR>::SomIterator(const SomIterator& other)
		: value(other.value)
	{
	}
	template<typename ITERATOR>
	inline bool SomJson::SomIterator<ITERATOR>::operator!=(const SomIterator& other) const noexcept
	{
		return this->value != other.value;
	}
	template<typename ITERATOR>
	inline bool SomJson::SomIterator<ITERATOR>::operator==(const SomIterator& other) const noexcept
	{
		return this->value == other.value;
	}
	template<typename ITERATOR>
	inline typename SomJson::SomIterator<ITERATOR>::reference SomJson::SomIterator<ITERATOR>::operator*() noexcept
	{
		return *this->value;
	}
	template<typename ITERATOR>
	inline typename SomJson::SomIterator<ITERATOR>::pointer SomJson::SomIterator<ITERATOR>::operator->() noexcept
	{
		return this->value;
	}
	template<typename ITERATOR>
	inline SomJson::SomIterator<ITERATOR>& SomJson::SomIterator<ITERATOR>::operator++() noexcept
	{
		//++this->value;
		//if (this->value->type == Json::JsonTypes::Object)
		//{
		//	for (auto& i = this->value->object_value.begin();
		//		i <= this->value->object_value.find((*i).first->string_value); ++i)
		//	{
		//		this->value = (*(++i)).second;
		//	}
		//}
		//else if (this->value->type == Json::JsonTypes::Array)
		//{
		//	//this->value = this->value->array_value[++this->value->array_value.size()];
		//}
		return *this;
	}
	template<typename ITERATOR>
	inline SomJson::SomIterator<ITERATOR> SomJson::SomIterator<ITERATOR>::operator++(int) noexcept
	{
		++(*this);
		SomIterator<ITERATOR> temp = *this;
		return temp;
	}
	template<typename ITERATOR>
	inline SomJson::SomIterator<ITERATOR>& SomJson::SomIterator<ITERATOR>::operator[](const size_t index) noexcept
	{
		return (*this)[index];
	}
}

#endif // !JSON_H_