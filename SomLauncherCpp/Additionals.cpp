#include "Additionals.h"

wchar_t* Additionals::Convectors::ConvertStringToWcharPtr(const std::string& str)
{
    wchar_t* wch_str = new wchar_t[str.size() + 1];
    const char* str_c_str = str.c_str();

    for (size_t i = 0; i < str.size(); ++i)
    {
        wch_str[i] = str_c_str[i];
    }

    return wch_str;
}

std::string Additionals::Convectors::ConvertWcharPtrToString(const wchar_t* str)
{
    std::wstring ws(str);
    std::string url(ws.begin(), ws.end());
    return url;
}

std::string Additionals::Convectors::ConvertWStringToString(const std::wstring& str)
{
    std::string url(str.begin(), str.end());
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
    size_t ref_size = wcslen(ref_str);
    size_t to_add_size = strlen(str_to_add);
    wchar_t* new_str_temp = nullptr;

    if (ref_str == nullptr || ref_str[0] == L'\0')
    {
        new_str_temp = new wchar_t[to_add_size + 1];
        for (size_t j = 0; j < to_add_size; j++)
        {
            new_str_temp[j] = static_cast<wchar_t>(str_to_add[j]);
        }
        new_str_temp[to_add_size] = L'\0';
        return new_str_temp;
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

wchar_t* Additionals::Path::joinA(std::initializer_list<const char*> list)
{
    std::wstring path;
    int i = 0;

    for (const char* elem : list)
    {
        if (i == 0)
        {
            path = std::wstring(elem, elem + strlen(elem));
            ++i;
            continue;
        }

        path += L'\\';
        path += std::wstring(elem, elem + strlen(elem));
        ++i;
    }

    wchar_t* return_path = const_cast<wchar_t*>(path.c_str());

    return return_path;
}

std::vector<std::string> Additionals::Path::get_directories(const std::string& directory)
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::recursive_directory_iterator(directory))
        if (p.is_directory())
            r.push_back(p.path().string());
    return r;
}

wchar_t* Additionals::TempFile::get_tempdir()
{
    /*
    Private accessor for tempfile.tempdir.
    */


    return Additionals::TempFile::_get_default_tempdir();
}

wchar_t* Additionals::TempFile::get_tempdir_SYSTEM()
{
    size_t path_size = 0;
    wchar_t* temp_path = nullptr;
    GetTempPathW(path_size, temp_path);

    return temp_path;
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

Additionals::ziparchives::ZipArchive::ZipArchive(const std::string& file_name)
{
    this->file_name = QString(file_name.c_str());

    
}

Additionals::ziparchives::ZipArchive::ZipArchive(const std::wstring& file_name)
{
    this->file_name = QString(Additionals::Convectors::ConvertWStringToString(file_name).c_str());
}

Additionals::ziparchives::ZipArchive::ZipArchive(const ZipArchive& for_copy)
{
    file_name = for_copy.file_name;

    data = for_copy.data;

    source_file.setFileName(for_copy.source_file.fileName());
    source_file.setCurrentReadChannel(for_copy.source_file.currentReadChannel());
    source_file.setCurrentWriteChannel(for_copy.source_file.currentWriteChannel());
    //source_file.setFileTime(for_copy.source_file.fileTime());
    source_file.setObjectName(for_copy.source_file.objectName());
    source_file.setParent(for_copy.source_file.parent());
    source_file.setPermissions(for_copy.source_file.permissions());
    //source_file.setProperty(for_copy.source_file.property());
    source_file.setTextModeEnabled(for_copy.source_file.isTextModeEnabled());

    data_stream.setByteOrder(for_copy.data_stream.byteOrder());
    data_stream.setStatus(for_copy.data_stream.status());
    data_stream.setDevice(for_copy.data_stream.device());
    data_stream.setFloatingPointPrecision(for_copy.data_stream.floatingPointPrecision());
    data_stream.setVersion(for_copy.data_stream.version());

    _entires = for_copy._entires;
}

Additionals::ziparchives::ZipArchive::~ZipArchive()
{
}

void Additionals::ziparchives::ZipArchive::ArchiveStream(const QString& sourceFilePath, QDataStream& data_stream)
{
    QFile sourceFile(sourceFilePath);

    if (sourceFile.open(QIODevice::ReadOnly))
    {
        QByteArray data = sourceFile.readAll();
        QString fileName = sourceFile.fileName().split('/').last(); // Получаем имя файла без пути.

        // Записываем размер файла и его имя.
        data_stream << qint64(data.size());
        data_stream << fileName;

        // Записываем содержимое файла.
        data_stream.writeRawData(data.data(), data.size());

        sourceFile.close();
        std::cout << "Файл добавлен в архив: " << fileName.toStdString();
    }
    else 
    {
        std::cout << "Ошибка чтения файла: " << this->file_name.toStdString();
    }
}

void Additionals::ziparchives::ZipArchive::ExtractFile(QDataStream& inStream, const QString& outputDir)
{
    qint64 fileSize;
    QString fileName;

    // Читаем размер файла и его имя.
    inStream >> fileSize;
    inStream >> fileName;

    QString filePath = outputDir + "/" + fileName;
    QFile outFile(filePath);
    if (outFile.open(QIODevice::WriteOnly)) {
        char* buffer = new char[fileSize];

        // Читаем содержимое файла.
        inStream.readRawData(buffer, fileSize);

        // Записываем содержимое в файл.
        outFile.write(buffer, fileSize);

        outFile.close();
        delete[] buffer;
        qDebug() << "Файл извлечен: " << fileName;
    }
    else 
    {
        qDebug() << "Ошибка создания файла: " << filePath;
    }
}

void Additionals::ziparchives::ZipArchive::Open(const std::string& file_name)
{
    QFile archiveFile(file_name.c_str());

    if (archiveFile.open(QIODevice::ReadOnly)) 
    {
        data_stream.setDevice(&archiveFile);
        data_stream.setVersion(QDataStream::Qt_6_5);

    }
    else 
    {
        qDebug() << "Ошибка открытия архива.";
    }
}

void Additionals::ziparchives::ZipArchive::Open(const std::wstring& file_name)
{
    QFile archiveFile(Additionals::Convectors::ConvertWStringToString(file_name).c_str());

    if (archiveFile.open(QIODevice::ReadOnly))
    {
        data_stream.setDevice(&archiveFile);
        data_stream.setVersion(QDataStream::Qt_6_5);

    }
    else
    {
        qDebug() << "Ошибка открытия архива.";
    }
}

void Additionals::ziparchives::ZipArchive::Close()
{
    this->~ZipArchive();
}

void Additionals::ziparchives::ZipArchive::ExtractFile(QFile& file_name, const std::string& outputDir)
{
    if (file_name.open(QIODevice::ReadOnly)) 
    {
        QDataStream inStream(&file_name);
        inStream.setVersion(QDataStream::Qt_6_5);

        // Убедитесь, что директория для извлечения существует.
        QDir().mkpath(QString(outputDir.c_str()));

        while (!inStream.atEnd()) 
        {
            qint64 fileSize;
            QString fileName;

            // Читаем размер файла и его имя.
            inStream >> fileSize;
            inStream >> fileName;

            QString filePath = (outputDir + "/" + fileName.toStdString()).c_str();
            QFile outFile(filePath);
            if (outFile.open(QIODevice::WriteOnly)) 
            {
                char* buffer = new char[fileSize];

                // Читаем содержимое файла.
                inStream.readRawData(buffer, fileSize);

                // Записываем содержимое в файл.
                outFile.write(buffer, fileSize);

                outFile.close();
                delete[] buffer;
                std::cout << "Файл извлечен: " << fileName.toStdString() << std::endl;
            }
            else 
            {
                std::cout << "Ошибка создания файла: " << filePath.toStdString() << std::endl;
            }
        }

        file_name.close();
        std::cout << "Разархивация успешно завершена." << std::endl;
    }
    else 
    {
        std::cout << "Ошибка открытия архива." << std::endl;
    }

    
}

QList<Additionals::file::File> Additionals::ziparchives::ZipArchive::_GetEntries()
{
    return this->_entires;
}

Additionals::file::File::File(QObject* parent)
{
}

Additionals::file::File::File(const std::string& filename) 
    : QTemporaryFile{ filename.c_str() } {}

Additionals::file::File::File(const QString& filename)
    : QTemporaryFile{ filename } {}

Additionals::file::File::File(const Additionals::file::File& for_copy)
{
}

void Additionals::file::File::Open()
{
    this->open(QFile::ReadWrite);
    if (!this->open()) // если файл не существует, то
    {      // формирмируем сообщение
    
    }

}

void Additionals::file::File::Close()
{
    if (this->isOpen())
    {
        this->close();
    }// закрываем файл
}