#ifndef LANG_H_
#define LANG_H_

#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_set>
#include <utility>
#include <vector>

#undef max
#undef min

namespace Lang
{
	/*template <typename T>
	T requireNonNullElse(T value, T defaultValue)
	{
		return value != nullptr ? value : defaultValue;
	}

	template <typename T>
	T requireNonNullElseGet(T value, const std::function<T()>& defaultValue)
	{
		return value != nullptr ? value : defaultValue();
	}

	template <typename T, typename U>
	U requireNonNullElseGet(T value, const std::function<U(T)>& mapper, const std::function<U()>& defaultValue)
	{
		return value != nullptr ? mapper(value) : defaultValue();
	}

	template <typename... K, typename... V>
	std::map<K..., V...> mapOf(std::pair<K, V>... pairs)
	{
		std::vector<std::pair<K, V>> pairVector(pairs...);
		return mapOf(pairVector);
	}

	template <typename K, typename V>
	std::map<K, V> mapOf(const std::vector<std::pair<K, V>>& pairs)
	{
		std::map<K, V> map;
		for (const auto& pair : pairs)
		{
			map.insert(pair);
		}
		return map;
	}

	template <typename... T>
	std::vector<T...> immutableListOf(T... elements)
	{
		return { elements... };
	}

	template <typename T>
	T clamp(T min, T val, T max)
	{
		if (val < min) return min;
		else if (val > max) return max;
		else return val;
	}

	double clamp(double min, double val, double max)
	{
		return std::max(min, std::min(val, max));
	}

	int clamp(int min, int val, int max)
	{
		return std::max(min, std::min(val, max));
	}

	bool test(const std::function<void()>& r)
	{
		try
		{
			r();
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	template <typename E>
	bool test(const std::function<bool()>& r)
	{
		try
		{
			return r();
		}
		catch (const E&)
		{
			return false;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	template <typename T>
	T ignoringException(const std::function<T()>& supplier)
	{
		try
		{
			return supplier();
		}
		catch (const std::exception&)
		{
			return T();
		}
	}

	template <typename T>
	T ignoringException(const std::function<T()>& supplier, T defaultValue)
	{
		try
		{
			return supplier();
		}
		catch (const std::exception&)
		{
			return defaultValue;
		}
	}

	template <typename V>
	std::unique_ptr<V> tryCast(const std::shared_ptr<void>& obj)
	{
		auto casted = std::dynamic_pointer_cast<V>(obj);
		if (casted)
		{
			return std::make_unique<V>(*casted);
		}
		return nullptr;
	}

	template <typename T>
	T getOrDefault(const std::vector<T>& a, int index, T defaultValue)
	{
		if (index < 0 || index >= a.size())
		{
			return defaultValue;
		}
		return a[index];
	}*/

	template <typename T>
	T merge(const T& a, const T& b, const std::function<T>& operator_function);
	template <typename T>
	std::vector<T> merge(const std::vector<T>& a, const std::vector<T>& b);

	/*template <typename T>
	std::vector<T> removingDuplicates(const std::vector<T>& list)
	{
		std::unordered_set<T> set;
		std::vector<T> result;
		for (const T& item : list)
		{
			if (set.insert(item).second)
			{
				result.push_back(item);
			}
		}
		return result;
	}

	template <typename T>
	std::vector<T> copyList(const std::vector<T>& list)
	{
		if (list.empty())
		{
			return {};
		}
		return list;
	}

	void executeDelayed(const std::function<void()>& runnable, std::chrono::milliseconds timeout, bool isDaemon)
	{
		std::thread([runnable, timeout]
			{
				std::this_thread::sleep_for(timeout);
				runnable();
			}).detach();
	}

	std::thread thread(const std::function<void()>& runnable, const std::string& name = "", bool isDaemon = false)
	{
		std::thread thread(runnable);
		if (!name.empty())
		{
			thread = std::thread(runnable);
		}
		if (isDaemon)
		{
			thread.detach();
		}
		return thread;
	}

	std::vector<std::string> splitString(const std::string& str, char delimiter)
	{
		std::vector<std::string> tokens;
		std::istringstream tokenStream(str);
		std::string token;
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	int parseInt(const std::string& str, int defaultValue)
	{
		try
		{
			return std::stoi(str);
		}
		catch (const std::invalid_argument&)
		{
			return defaultValue;
		}
		catch (const std::out_of_range&)
		{
			return defaultValue;
		}
	}

	double parseDouble(const std::string& str, double defaultValue)
	{
		try
		{
			return std::stod(str);
		}
		catch (const std::invalid_argument&)
		{
			return defaultValue;
		}
		catch (const std::out_of_range&)
		{
			return defaultValue;
		}
	}

	std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vec)
	{
		os << '[';
		for (size_t i = 0; i < vec.size(); ++i)
		{
			os << vec[i];
			if (i < vec.size() - 1) {
				os << ", ";
			}
		}
		os << ']';
		return os;
	}*/
}

template<typename T>
T Lang::merge(const T& a, const T& b, const std::function<T>& operator_function)
{
	if (a == nullptr)
		return b;
	if (b == nullptr)
		return a;
	return operator_function(a, b);
}

template<typename T>
std::vector<T> Lang::merge(const std::vector<T>& a, const std::vector<T>& b)
{
	std::vector<T> result = a;
	result.insert(result.end(), b.begin(), b.end());
	return result;
}

#endif // !LANG_H_