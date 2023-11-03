#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class StringUtils
{
private:
	StringUtils() {}

public:
	static std::string getStackTrace(std::exception& ex) {
		try {
			throw;
		}
		catch (const std::exception& e) {
			return e.what();
		}
	}

	static std::string getStackTrace(const std::vector<std::string>& elements) {
		std::string stackTrace;
		for (const std::string& element : elements) {
			stackTrace += "\tat " + element + "\n";
		}
		return stackTrace;
	}

	static bool isBlank(const std::string& str) {
		return str.empty() || str.find_first_not_of(' ') == std::string::npos;
	}

	static bool isNotBlank(const std::string& str) {
		return !isBlank(str);
	}

	static std::string substringBeforeLast(const std::string& str, char delimiter) {
		size_t index = str.find_last_of(delimiter);
		if (index != std::string::npos) {
			return str.substr(0, index);
		}
		else {
			return str;
		}
	}

	static std::string substringBeforeLast(const std::string& str, char delimiter, const std::string& missingDelimiterValue) {
		size_t index = str.find_last_of(delimiter);
		if (index != std::string::npos) {
			return str.substr(0, index);
		}
		else {
			return missingDelimiterValue;
		}
	}

	static std::string substringBefore(const std::string& str, char delimiter) {
		size_t index = str.find(delimiter);
		if (index != std::string::npos) {
			return str.substr(0, index);
		}
		else {
			return str;
		}
	}

	static std::string substringAfterLast(const std::string& str, char delimiter) {
		size_t index = str.find_last_of(delimiter);
		if (index != std::string::npos) {
			return str.substr(index + 1);
		}
		else {
			return "";
		}
	}

	static std::string removeSurrounding(const std::string& str, const std::string& delimiter) {
		if (str.size() >= 2 * delimiter.size() && str.find(delimiter) == 0 && str.rfind(delimiter) == str.size() - delimiter.size()) {
			return str.substr(delimiter.size(), str.size() - 2 * delimiter.size());
		}
		else {
			return str;
		}
	}

	static std::string addPrefix(const std::string& str, const std::string& prefix) {
		if (str.find(prefix) != 0) {
			return prefix + str;
		}
		else {
			return str;
		}
	}

	static std::string addSuffix(const std::string& str, const std::string& suffix) {
		if (str.rfind(suffix) != str.size() - suffix.size()) {
			return str + suffix;
		}
		else {
			return str;
		}
	}

	static std::string removePrefix(const std::string& str, const std::string& prefix) {
		if (str.find(prefix) == 0) {
			return str.substr(prefix.size());
		}
		else {
			return str;
		}
	}

	static std::string removeSuffix(const std::string& str, const std::string& suffix) {
		if (str.rfind(suffix) == str.size() - suffix.size()) {
			return str.substr(0, str.size() - suffix.size());
		}
		else {
			return str;
		}
	}

	static std::vector<std::string> tokenize(const std::string& str) {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);
		while (std::getline(tokenStream, token, ' ')) {
			tokens.push_back(token);
		}
		return tokens;
	}

	static bool containsOne(const std::vector<std::string>& patterns, const std::vector<std::string>& targets) {
		for (const std::string& pattern : patterns) {
			for (const std::string& target : targets) {
				if (pattern.find(target) != std::string::npos) {
					return true;
				}
			}
		}
		return false;
	}

	static bool containsOne(const std::string& pattern, const std::vector<std::string>& targets) {
		for (const std::string& target : targets) {
			if (pattern.find(target) != std::string::npos) {
				return true;
			}
		}
		return false;
	}

	static bool containsChinese(const std::string& str) {
		for (char ch : str) {
			if (ch >= 0x4E00 && ch <= 0x9FA5) {
				return true;
			}
		}
		return false;
	}

	static std::string parseColorEscapes(const std::string& original) {
		std::string result = original;
		size_t pos = 0;
		while ((pos = result.find('\u00A7', pos)) != std::string::npos) {
			if (pos + 1 < result.size() && (result[pos + 1] >= '0' && result[pos + 1] <= '9') || (result[pos + 1] >= 'a' && result[pos + 1] <= 'r')) {
				result.erase(pos, 2);
			}
			else {
				pos++;
			}
		}
		return result;
	}

	static std::string parseEscapeSequence(const std::string& str) {
		std::string result;
		bool inEscape = false;
		for (char ch : str) {
			if (ch == '\033') {
				inEscape = true;
			}
			if (!inEscape) {
				result += ch;
			}
			if (inEscape && ch == 'm') {
				inEscape = false;
			}
		}
		return result;
	}

	static std::string repeats(char ch, int repeat) {
		std::string result;
		for (int i = 0; i < repeat; i++) {
			result += ch;
		}
		return result;
	}

	static const int MAX_SHORT_STRING_LENGTH = 77;

	static std::string truncate(const std::string& str) {
		if (str.length() > MAX_SHORT_STRING_LENGTH) {
			int halfLength = (MAX_SHORT_STRING_LENGTH - 5) / 2;
			return str.substr(0, halfLength) + " ... " + str.substr(str.length() - halfLength);
		}
		else {
			return str;
		}
	}

	static bool isASCII(const std::string& str) {
		for (char ch : str) {
			if (ch >= 128) {
				return false;
			}
		}
		return true;
	}

	static bool isAlphabeticOrNumber(const std::string& str) {
		for (char ch : str) {
			if (!((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
				return false;
			}
		}
		return true;
	}
};

#endif /*STRINGUTILS_H_*/