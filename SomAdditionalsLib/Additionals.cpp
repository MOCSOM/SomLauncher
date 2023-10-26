#include "pch.h"

#include "Additionals.h"

wchar_t* Additionals::Convectors::ConvertStringToWcharPtr(const std::string& str)
{
	/*std::wstring_convert<std::codecvt<wchar_t, char, wchar_t>, wchar_t> converter;
	std::wstring wstr = converter.from_bytes(str);

	wchar_t* wch_str = new wchar_t[wstr.size() + 1];
	wcscpy(wch_str, wstr.c_str());*/

	UINT CodePage = CP_ACP;
	DWORD const BuffSize = MultiByteToWideChar(CodePage, 0, str.c_str(), -1, NULL, 0);
	if (!BuffSize) return NULL;
	std::vector<wchar_t> Buffer;
	Buffer.resize(BuffSize);
	if (!MultiByteToWideChar(CodePage, 0, str.c_str(), -1, &Buffer[0], BuffSize)) return NULL;
	return (&Buffer[0]);
}

std::unique_ptr<wchar_t[]> Additionals::Convectors::ConvertStringToWcharUniqPtr(const std::string& str)
{
	UINT CodePage = CP_ACP;
	DWORD const BuffSize = MultiByteToWideChar(CodePage, 0, str.c_str(), -1, NULL, 0);
	if (!BuffSize) return NULL;
	std::unique_ptr<wchar_t[]> Buffer = std::make_unique<wchar_t[]>(BuffSize);
	if (!MultiByteToWideChar(CodePage, 0, str.c_str(), -1, &Buffer[0], BuffSize)) return NULL;
	return Buffer;
}

std::string Additionals::Convectors::ConvertWcharPtrToString(const wchar_t* str)
{
	std::wstring ws(str);
	std::string url(ws.begin(), ws.end()); //FIXME: выполняется компиляция ссылки на экземпляр шаблон функции "std::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string<std::_String_iterator<std::_String_val<std::_Simple_types<_Elem>>>,0>(_Iter,_Iter,const _Alloc &)"

	return url;
}

std::string Additionals::Convectors::ConvertWStringToString(const std::wstring& str)
{
	std::string url(str.begin(), str.end()); //FIXME: выполняется компиляция ссылки на экземпляр шаблон функции "std::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string<std::_String_iterator<std::_String_val<std::_Simple_types<_Elem>>>,0>(_Iter,_Iter,const _Alloc &)"
	return url;
}

std::wstring Additionals::Convectors::ConvertStringToWString(const std::string& str)
{
	std::wstring_convert<std::codecvt<wchar_t, char, wchar_t>, wchar_t> converter;

	std::wstring wideStr = converter.from_bytes(str);
	return wideStr;
}

std::wstring Additionals::Convectors::ConvertWcharPtrToWstring(const wchar_t* str)
{
	if (str)
		return std::wstring(str);
	return L"";
}

std::unique_ptr<wchar_t[]> Additionals::Convectors::ConvertWstringToWcharPtr(const std::wstring& str)
{
	std::unique_ptr<wchar_t[]> buffer(new wchar_t[str.size() + 1]);
	wcscpy_s(buffer.get(), str.size() + 1, str.c_str());
	return buffer;
}

std::string Additionals::Convectors::ConvertLPCWSTRToString(LPCWSTR lpcwszStr)
{
	// Determine the length of the converted string
	int strLength = WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1,
		nullptr, 0, nullptr, nullptr);

	// Create a std::string with the determined length
	std::string str(strLength, 0);

	// Perform the conversion from LPCWSTR to std::string
	WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, &str[0],
		strLength, nullptr, nullptr);

	// Return the converted std::string
	return str;
}

LPCWSTR Additionals::Convectors::ConvertTringToLPCWSTR(std::string string)
{
	int bufferSize = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, NULL, 0);
	std::unique_ptr<wchar_t[]> wideStr = std::make_unique<wchar_t[]>(bufferSize);

	MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, wideStr.get(), bufferSize);

	LPCWSTR lpcwstr = wideStr.get();

	return lpcwstr;
}

//wchar_t* Additionals::String::strdogW(wchar_t* ref_str, wchar_t* str_to_add)
//{
//	if (ref_str == NULL || ref_str[0] == L'\0')
//    {
//        wchar_t* new_str_temp = _wcsdup(str_to_add);
//        return new_str_temp;
//    }
//
//    if (str_to_add == NULL || str_to_add[0] == L'\0')
//    {
//		wchar_t* new_str_temp = _wcsdup(ref_str);
//        return new_str_temp;
//    }
//
//    size_t ref_size = wcslen(ref_str);
//    size_t to_add_size = wcslen(str_to_add);
//
//    wchar_t* new_str = new wchar_t[ref_size + to_add_size + 1];
//
//    wcscpy_s(new_str, ref_size + to_add_size + 1, ref_str);
//    wcscat_s(new_str, ref_size + to_add_size + 1, str_to_add);
//
//    return new_str;
//}
//
//wchar_t* Additionals::String::strdogW(const wchar_t* ref_str, wchar_t* str_to_add)
//{
//	if (ref_str == NULL || ref_str[0] == L'\0')
//    {
//        wchar_t* new_str_temp = _wcsdup(str_to_add);
//        return new_str_temp;
//    }
//
//	if (str_to_add == NULL || str_to_add[0] == L'\0')
//    {
//		wchar_t* new_str_temp = _wcsdup(ref_str);
//        return new_str_temp;
//    }
//
//    size_t ref_size = wcslen(ref_str);
//    size_t to_add_size = wcslen(str_to_add);
//
//    wchar_t* new_str = new wchar_t[ref_size + to_add_size + 1];
//
//    wcscpy_s(new_str, ref_size + to_add_size + 1, ref_str);
//    wcscat_s(new_str, ref_size + to_add_size + 1, str_to_add);
//
//    return new_str;
//}
//
//wchar_t* Additionals::String::strdogW(wchar_t* ref_str, const wchar_t* str_to_add)
//{
//	if (ref_str == NULL || ref_str[0] == L'\0')
//    {
//        wchar_t* new_str_temp = _wcsdup(str_to_add);
//        return new_str_temp;
//    }
//
//	if (str_to_add == NULL || str_to_add[0] == L'\0')
//    {
//		wchar_t* new_str_temp = _wcsdup(ref_str);
//        return new_str_temp;
//    }
//
//    size_t ref_size = wcslen(ref_str);
//    size_t to_add_size = wcslen(str_to_add);
//
//    wchar_t* new_str = new wchar_t[ref_size + to_add_size + 1];
//
//    wcscpy_s(new_str, ref_size + to_add_size + 1, ref_str);
//    wcscat_s(new_str, ref_size + to_add_size + 1, str_to_add);
//
//    return new_str;
//}

wchar_t* Additionals::String::strdogW(const wchar_t* ref_str, const wchar_t* str_to_add)
{
	if (ref_str == NULL || ref_str[0] == L'\0')
	{
		wchar_t* new_str_temp = _wcsdup(str_to_add);
		return new_str_temp;
	}

	if (str_to_add == NULL || str_to_add[0] == L'\0')
	{
		wchar_t* new_str_temp = _wcsdup(ref_str);
		return new_str_temp;
	}

	size_t ref_size = wcslen(ref_str);
	size_t to_add_size = wcslen(str_to_add);

	wchar_t* new_str = new wchar_t[ref_size + to_add_size + 1];

	wcscpy_s(new_str, ref_size + to_add_size + 1, ref_str);
	wcscat_s(new_str, ref_size + to_add_size + 1, str_to_add);

	return new_str;
}

wchar_t* Additionals::String::strdogWA(const wchar_t* ref_str, const char* str_to_add)
{
	size_t ref_size;
	size_t to_add_size = strlen(str_to_add);
	wchar_t* new_str_temp = nullptr;

	if (ref_str == nullptr || ref_str[0] == L'\0')
	{
		ref_size = 0;
		new_str_temp = new wchar_t[to_add_size + 1];
		for (size_t j = 0; j < to_add_size; j++)
		{
			new_str_temp[j] = static_cast<wchar_t>(str_to_add[j]);
		}
		new_str_temp[to_add_size] = L'\0';
		return new_str_temp;
	}
	else
	{
		ref_size = wcslen(ref_str);
	}

	size_t total_size = ref_size + to_add_size;
	wchar_t* new_str = new wchar_t[total_size + 1];

	wcscpy_s(new_str, total_size + 1, ref_str);
	for (size_t j = 0; j < to_add_size; j++)
	{
		new_str[ref_size + j] = static_cast<wchar_t>(str_to_add[j]);
	}
	new_str[total_size] = L'\0';

	return new_str;
}

wchar_t* Additionals::String::strdogAW(const char* ref_str, const wchar_t* str_to_add)
{
	if (ref_str == nullptr || ref_str[0] == '\0')
	{
		size_t to_add_size = wcslen(str_to_add);
		wchar_t* new_str = new wchar_t[to_add_size + 1];
		for (size_t j = 0; j < to_add_size; j++)
		{
			new_str[j] = str_to_add[j];
		}
		new_str[to_add_size] = L'\0';
		return new_str;
	}

	size_t ref_size = strlen(ref_str);
	size_t to_add_size = wcslen(str_to_add);
	wchar_t* new_str = new wchar_t[ref_size + to_add_size + 1];

	wcscpy_s(new_str, ref_size + to_add_size + 1, reinterpret_cast<const wchar_t*>(ref_str));
	wcscat_s(new_str, ref_size + to_add_size + 1, str_to_add);

	return new_str;
}

wchar_t* Additionals::String::strdogA(const char* ref_str, const char* str_to_add)
{
	if (ref_str == nullptr || ref_str[0] == '\0')
	{
		size_t to_add_size = strlen(str_to_add);
		wchar_t* new_str = new wchar_t[to_add_size + 1];
		for (size_t j = 0; j < to_add_size; ++j)
		{
			new_str[j] = static_cast<wchar_t>(str_to_add[j]);
		}
		new_str[to_add_size] = L'\0';
		return new_str;
	}

	size_t ref_size = strlen(ref_str);
	size_t to_add_size = strlen(str_to_add);
	wchar_t* new_str = new wchar_t[ref_size + to_add_size + 1];

	for (size_t i = 0; i < ref_size; ++i)
	{
		new_str[i] = static_cast<wchar_t>(ref_str[i]);
	}

	for (size_t j = 0; j < to_add_size; ++j)
	{
		new_str[ref_size + j] = static_cast<wchar_t>(str_to_add[j]);
	}
	new_str[ref_size + to_add_size] = L'\0';

	return new_str;
}

char* Additionals::String::strdogA(std::initializer_list<const char*> list)
{
	char* path = nullptr;
	bool isFirst = true;

	for (auto& elem : list)
	{
		if (isFirst)
		{
			path = const_cast<char*>(elem);
			isFirst = false;
		}
		else
		{
			//wchar_t* temp = StrDogW(path, elem);
			//delete[] path;
			path = Additionals::String::Char::strdogA(path, elem);
		}
	}

	return path;
}

wchar_t* Additionals::String::strdogW(std::initializer_list<const wchar_t*> list)
{
	wchar_t* path = nullptr;
	bool isFirst = true;

	for (const wchar_t* elem : list)
	{
		if (isFirst)
		{
			path = const_cast<wchar_t*>(elem);
			isFirst = false;
		}
		else
		{
			//wchar_t* temp = StrDogW(path, elem);
			//delete[] path;
			path = StrDogW(path, elem);
		}
	}

	return path;
}

std::vector<std::string> Additionals::String::split(const std::string& s, const char& seperator, const int& count)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			if ((pos = s.find(seperator, pos)) != std::string::npos)
			{
				std::string substring(s.substr(prev_pos, pos - prev_pos));

				output.push_back(substring);

				prev_pos = ++pos;
			}
		}
	}
	else if (count == 0)
	{
		while ((pos = s.find(seperator, pos)) != std::string::npos)
		{
			std::string substring(s.substr(prev_pos, pos - prev_pos));

			output.push_back(substring);

			prev_pos = ++pos;
		}
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

	return output;
}

std::vector<std::wstring> Additionals::String::split(const std::wstring& s, const char& seperator, const int& count)
{
	std::vector<std::wstring> output;

	std::wstring::size_type prev_pos = 0, pos = 0;

	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			if (!s.find(seperator))
			{
			}
			if ((pos = s.find(seperator, pos)) != std::wstring::npos)
			{
				std::wstring substring(s.substr(prev_pos, pos - prev_pos));

				output.push_back(substring);

				prev_pos = ++pos;
			}
		}
	}
	else if (count == 0)
	{
		while ((pos = s.find(seperator, pos)) != std::wstring::npos)
		{
			std::wstring substring(s.substr(prev_pos, pos - prev_pos));

			output.push_back(substring);

			prev_pos = ++pos;
		}
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

	return output;
}

bool Additionals::String::replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

bool Additionals::String::replace(std::wstring& str, const std::wstring& from, const std::wstring& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

bool Additionals::String::EndsWith(const std::string& str, const std::string& suffix)
{
	if (str.length() < suffix.length())
	{
		return false;
	}
	return str.rfind(suffix) == str.size() - suffix.size();
}

bool Additionals::String::EndsWith(const std::wstring& str, const std::wstring& suffix)
{
	if (str.length() < suffix.length())
	{
		return false;
	}
	return str.rfind(suffix) == str.size() - suffix.size();
}

void Additionals::String::ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

void Additionals::String::ltrim(std::string& s, const char& symbol)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&symbol](char ch) {
		return ch != symbol;
		}));
}

void Additionals::String::rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

static inline void Additionals::String::rtrim(std::string& s, const char& symbol)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [&symbol](char ch) {
		return ch != symbol;
		}).base(), s.end());
}

void Additionals::String::trim(std::string& s)
{
	rtrim(s);
	ltrim(s);
}

void Additionals::String::trim(std::string& s, const char& symbol)
{
	rtrim(s, symbol);
	ltrim(s, symbol);
}

std::string Additionals::String::ltrim_copy(std::string s)
{
	ltrim(s);
	return s;
}

std::string Additionals::String::ltrim_copy(std::string s, const char& symbol)
{
	ltrim(s, symbol);
	return s;
}

std::string Additionals::String::rtrim_copy(std::string s)
{
	rtrim(s);
	return s;
}

std::string Additionals::String::rtrim_copy(std::string s, const char& symbol)
{
	rtrim(s, symbol);
	return s;
}

std::string Additionals::String::trim_copy(std::string s)
{
	trim(s);
	return s;
}

std::string Additionals::String::trim_copy(std::string s, const char& symbol)
{
	trim(s, symbol);
	return s;
}

wchar_t* Additionals::Path::joinW(std::initializer_list<const wchar_t*> list)
{
	std::wstring path;

	for (const wchar_t* elem : list)
	{
		if (!path.empty())
		{
			path += L"\\";
		}
		path += elem;
	}

	// If the list was empty, we should return nullptr, so handle that case explicitly
	if (path.empty())
	{
		return nullptr;
	}

	// Allocate memory for the resulting wchar_t* and copy the path content into it
	wchar_t* result = new wchar_t[path.size() + 1];
	wcscpy_s(result, path.size() + 1, path.c_str());

	return result;
}

std::wstring Additionals::Path::joinA(std::initializer_list<const char*> list)
{
	std::wstring path;

	for (const char* elem : list)
	{
		if (!path.empty())
			path += L'\\';

		path += Additionals::Convectors::ConvertStringToWcharPtr(elem);
	}

	return path;
}

std::string Additionals::Path::joinString(std::initializer_list<const std::string> list)
{
	std::string path;

	for (const std::string& elem : list)
	{
		if (!path.empty())
			path += L'\\';

		path += elem;
	}

	return path;
}

std::vector<std::string> Additionals::Path::get_directories(const std::string& directory)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::directory_iterator(directory))
		if (p.is_directory())
			r.push_back(p.path().string());
	return r;
}

std::string Additionals::Path::getFileNameFromPath(const std::string& path)
{
	// Находим последний разделитель пути (для Windows '\' и для Linux '/')
	size_t lastSeparatorPos = path.find_last_of("\\/");
	if (lastSeparatorPos != std::string::npos) {
		// Извлекаем имя файла из строки пути
		return path.substr(lastSeparatorPos + 1);
	}
	else {
		// Если разделитель не найден, значит весь путь является именем файла
		return path;
	}
}

wchar_t* Additionals::TempFile::get_tempdir()
{
	/*
	Private accessor for tempfile.tempdir.
	*/

	return Additionals::TempFile::_get_default_tempdir();
}

std::string Additionals::TempFile::get_tempdir_SYSTEM()
{
	std::filesystem::path temp_path = std::filesystem::temp_directory_path();
	return temp_path.string();
}

wchar_t* Additionals::TempFile::_get_default_tempdir()
{
	/*
	Calculate the default directory to use for temporary files.
	This routine should be called exactly once.

	We determine whether or not a candidate temp dir is usable by
	trying to create and write to a file in that directory.  If this
	is successful, the test file is deleted.  To prevent denial of
	service, the name of the test file must be randomized.
	*/
	// TODO: доделать это говно из описание сверху^

	//wchar_t* namer;// = DDIC::TempFile::_RandomNameSequence();
	//System::Collections::Generic::List<System::String^>^ dirlist = nullptr;// = DDIC::TempFile::_candidate_tempdir_list();
	std::list<std::string> dirlist;

	for (std::string dir : dirlist)
	{
		if (dir != std::string("."))
		{
			std::filesystem::path path;
			path = std::filesystem::absolute(dir);

			dir = path.string();
		}
	}

	return nullptr;
}

char* Additionals::String::Char::strdogA(const char* ref_str, const char* str_to_add)
{
	if (ref_str == nullptr || ref_str[0] == '\0')
	{
		size_t to_add_size = strlen(str_to_add);
		char* new_str = new char[to_add_size + 1];
		for (size_t j = 0; j < to_add_size; ++j)
		{
			new_str[j] = static_cast<wchar_t>(str_to_add[j]);
		}
		new_str[to_add_size] = L'\0';
		return new_str;
	}

	size_t ref_size = strlen(ref_str);
	size_t to_add_size = strlen(str_to_add);
	char* new_str = new char[ref_size + to_add_size + 1];

	for (size_t i = 0; i < ref_size; ++i)
	{
		new_str[i] = static_cast<char>(ref_str[i]);
	}

	for (size_t j = 0; j < to_add_size; ++j)
	{
		new_str[ref_size + j] = static_cast<char>(str_to_add[j]);
	}
	new_str[ref_size + to_add_size] = L'\0';

	return new_str;
}