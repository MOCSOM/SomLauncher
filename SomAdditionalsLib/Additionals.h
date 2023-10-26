#ifndef ADDITIONALS_H_
#define ADDITIONALS_H_

#include <initializer_list>
#include <cwchar>
#include <stdlib.h>     // for _countof
#include <errno.h>  // for return values
#include <cstring>

#include <list>
#include <string>

#include <filesystem>

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>

#define StrDogWA Additionals::String::strdogWA
#define StrDogW Additionals::String::strdogW
#define StrDogAW Additionals::String::strdogAW
#define StrDogA Additionals::String::strdogA
#define JoinW Additionals::Path::joinW
#define JoinA Additionals::Path::joinA
#define Join Additionals::Path::joinString

namespace Additionals
{
	namespace Convectors
	{
		wchar_t* ConvertStringToWcharPtr(const std::string& str);
		std::unique_ptr<wchar_t[]> ConvertStringToWcharUniqPtr(const std::string& str);
		std::string ConvertWcharPtrToString(const wchar_t* str);
		std::string ConvertWStringToString(const std::wstring& str);
		std::wstring ConvertStringToWString(const std::string& str);
		std::wstring ConvertWcharPtrToWstring(const wchar_t* str);
		std::unique_ptr<wchar_t[]> ConvertWstringToWcharPtr(const std::wstring& str);
		std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr);
		LPCWSTR ConvertTringToLPCWSTR(std::string string);
	}

	namespace String
	{
		namespace Char
		{
			char* strdogA(const char* ref_str, const char* str_to_add);
		}
		wchar_t* strdogW(const wchar_t* ref_str, const wchar_t* str_to_add);

		wchar_t* strdogWA(const wchar_t* ref_str, const char* str_to_add);
		wchar_t* strdogAW(const char* ref_str, const wchar_t* str_to_add);
		wchar_t* strdogA(const char* ref_str, const char* str_to_add);

		char* strdogA(std::initializer_list<const char*> list);
		wchar_t* strdogW(std::initializer_list<const wchar_t*> list);

		std::vector<std::string> split(const std::string& s, const char& seperator, const int& count = 0);
		std::vector<std::wstring> split(const std::wstring& s, const char& seperator, const int& count = 0);

		bool replace(std::string& str, const std::string& from, const std::string& to);
		bool replace(std::wstring& str, const std::wstring& from, const std::wstring& to);

		bool EndsWith(const std::string& str, const std::string& suffix);
		bool EndsWith(const std::wstring& str, const std::wstring& suffix);

		// trim from start (in place)
		static inline void ltrim(std::string& s);
		static inline void ltrim(std::string& s, const char& symbol);

		// trim from end (in place)
		static inline void rtrim(std::string& s);
		static inline void rtrim(std::string& s, const char& symbol);

		// trim from both ends (in place)
		static inline void trim(std::string& s);
		static inline void trim(std::string& s, const char& symbol);

		// trim from start (copying)
		static inline std::string ltrim_copy(std::string s);
		static inline std::string ltrim_copy(std::string s, const char& symbol);

		// trim from end (copying)
		static inline std::string rtrim_copy(std::string s);
		std::string rtrim_copy(std::string s, const char& symbol);

		// trim from both ends (copying)
		static inline std::string trim_copy(std::string s);
		static inline std::string trim_copy(std::string s, const char& symbol);

		template<typename T, typename P>
		T remove_if(T beg, T end, P pred)
		{
			T dest = beg;
			for (T itr = beg; itr != end; ++itr)
				if (!pred(*itr))
					*(dest++) = *itr;
			return dest;
		}
	}

	namespace Path
	{
		wchar_t* joinW(std::initializer_list<const wchar_t*> list);
		std::wstring joinA(std::initializer_list<const char*> list);
		std::string joinString(std::initializer_list<const std::string> list);
		std::vector<std::string> get_directories(const std::string& directory);

		std::string getFileNameFromPath(const std::string& path);
	}

	namespace TempFile
	{
		wchar_t* get_tempdir();
		std::string get_tempdir_SYSTEM();
		wchar_t* _get_default_tempdir();
	}
}

#endif // !ADDITIONALS_H_
