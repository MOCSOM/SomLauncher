#include "Additionals.h"

wchar_t* Additionals::Convectors::ConvertStringToWcharPtr(const std::string& str)
{
    std::wstring_convert<std::codecvt<wchar_t, char, wchar_t>, wchar_t> converter;
    std::wstring wstr = converter.from_bytes(str);

    wchar_t* wch_str = new wchar_t[wstr.size() + 1];
    wcscpy(wch_str, wstr.c_str());

    return wch_str;
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
    std::wstring_convert<std::codecvt<wchar_t, char, wchar_t>, wchar_t> converter;

    for (const char* elem : list)
    {
        if (!path.empty())
            path += L'\\';

        path += converter.from_bytes(elem);
    }


    return path;
}

std::vector<std::string> Additionals::Path::get_directories(const std::string& directory)
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::recursive_directory_iterator(directory))
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

std::wstring Additionals::TempFile::get_tempdir_SYSTEM()
{
    auto temp_path = std::filesystem::temp_directory_path();
    return temp_path.wstring();
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

    for(std::string dir : dirlist)
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

Additionals::file::File::File(const std::string& file_name)
    : _file_name(file_name) {}

std::string Additionals::file::File::getFileName() const
{
    return _file_name;
}

void Additionals::file::File::readContent()
{
    std::ifstream file_stream(_file_name, std::ios::binary);
    if (!file_stream) {
        std::cerr << "Error opening file: " << _file_name << std::endl;
        return;
    }

    file_stream.seekg(0, std::ios::end);
    std::streampos file_size = file_stream.tellg();
    _content.resize(static_cast<size_t>(file_size));

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(reinterpret_cast<char*>(_content.data()), file_size);

    file_stream.close();
}

void Additionals::file::File::writeContent() const
{
    std::ofstream file_stream(_file_name, std::ios::binary);
    if (!file_stream) {
        std::cerr << "Error opening file: " << _file_name << std::endl;
        return;
    }

    file_stream.write(reinterpret_cast<const char*>(_content.data()), _content.size());

    file_stream.close();
}

std::vector<uint8_t>& Additionals::file::File::getContent()
{
    return _content;
}

std::string Additionals::file::File::getFullPath() const
{
    return std::filesystem::absolute(_file_name).string();
}

Additionals::archives::Archive::Archive(const std::string& archive_name)
    : _file_name(archive_name) 
{
    readArchive();
}

Additionals::archives::Archive::Archive(const std::wstring& archive_name)
{
    this->_file_name = Additionals::Convectors::ConvertWStringToString(archive_name);
    readArchive();
}

Additionals::archives::Archive::Archive()
{
}

void Additionals::archives::Archive::Open(const std::string& archive_name)
{
    this->_file_name = archive_name;
    readArchive();
}

void Additionals::archives::Archive::Open(const std::wstring& archive_name)
{
    this->_file_name = Additionals::Convectors::ConvertWStringToString(archive_name);
    readArchive();
}

void Additionals::archives::Archive::addFile(Additionals::file::File& file)
{
    _entries.push_back(file);
}

void Additionals::archives::Archive::packArchive()
{
    std::ofstream archive_stream(_file_name, std::ios::binary);
    if (!archive_stream) 
    {
        std::cerr << "Error creating archive: " << _file_name << std::endl;
        return;
    }

    for (Additionals::file::File& file : _entries) 
    {
        size_t file_name_size = file.getFileName().size();
        archive_stream.write(reinterpret_cast<const char*>(&file_name_size), sizeof(size_t));
        archive_stream.write(file.getFileName().c_str(), file_name_size);

        size_t file_content_size = file.getContent().size();
        archive_stream.write(reinterpret_cast<const char*>(&file_content_size), sizeof(size_t));
        archive_stream.write(reinterpret_cast<const char*>(file.getContent().data()), file_content_size);
    }

    archive_stream.close();
}

void Additionals::archives::Archive::readArchive()
{
    std::ifstream archive_stream(_file_name, std::ifstream::binary);
    if (!archive_stream) 
    {
        std::cerr << "Error opening archive: " << _file_name << std::endl;
        return;
    }

    _entries.clear();

    while (true) 
    {
        //// get length of file:
        //archive_stream.seekg(0, archive_stream.end);
        //int length = archive_stream.tellg();
        //archive_stream.seekg(0, archive_stream.beg);

        //if (archive_stream.eof()) 
        //{
        //    break;
        //}

        //std::string file_name(length, ' ');
        //archive_stream.read(&file_name[0], length);

        //size_t file_content_size;
        //archive_stream.read(reinterpret_cast<char*>(&file_content_size), sizeof(size_t));

        //std::vector<uint8_t> file_content(length);
        //archive_stream.read(reinterpret_cast<char*>(file_content.data()), length);

        archive_stream.seekg(0, archive_stream.end);
        int length = archive_stream.tellg();
        archive_stream.seekg(0, archive_stream.beg);

        char* buffer = new char[length];

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        archive_stream.read(buffer, length);

        if (archive_stream)
            std::cout << "all characters read successfully.";
        else
            std::cout << "error: only " << archive_stream.gcount() << " could be read";
        archive_stream.close();

        // ...buffer contains the entire file...

        delete[] buffer;

        /*Additionals::file::File file(file_name);
        file.getContent() = file_content;
        _entries.push_back(file);*/
    }

    archive_stream.close();
}

void Additionals::archives::Archive::extractFile(Additionals::file::File& file, const std::string& destination_path)
{
    std::ofstream file_stream(destination_path, std::ios::binary);
    if (!file_stream) 
    {
        std::cerr << "Error creating file: " << destination_path << std::endl;
        return;
    }

    file_stream.write(reinterpret_cast<const char*>(file.getContent().data()), file.getContent().size());

    file_stream.close();
}

std::vector<Additionals::file::File> Additionals::archives::Archive::_getEntries()
{
    return this->_entries;
}

void Additionals::archives::compressFile(std::string zipfile, std::string directory)
{
    QZipWriter c_zip(zipfile.c_str());
    c_zip.addDirectory(directory.c_str());
    c_zip.close();
}

void Additionals::archives::decompressFile(const QZipReader& zip, const QZipReader::FileInfo& file, const std::string& directory)
{
    std::filesystem::path d_file_path(directory);
    d_file_path = d_file_path.parent_path();

    DWORD attrib = GetFileAttributesW(d_file_path.wstring().c_str());
    if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (!std::filesystem::create_directories(d_file_path))
        {
            // Обработка ошибки создания директории
            int error = GetLastError();
        }
    }


    QFile new_file(directory.c_str());

    new_file.open(QIODevice::WriteOnly);

    new_file.write(zip.fileData(file.filePath));

    new_file.close();
}
