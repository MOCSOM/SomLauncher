#include "DownloadClasses.h"


//bool DDIC::Download::Files::_CreateDirectoryIfNotExists(const std::wstring& path) 
//{
//    if (!std::filesystem::exists(path)) 
//    {
//        return std::filesystem::create_directory(path);
//    }
//    return true;
//}


std::wstring DDIC::Download::Files::download_file(const wchar_t* s_url, const wchar_t* d_file, CallbackNull callback, bool lzma_compressed)
{
    std::wstring destenation_file;

    if (d_file == nullptr || d_file == NULL)
    {
        destenation_file = L"";
    }
    else
    {
        destenation_file = d_file;
    }
    if (d_file == nullptr || d_file == NULL)
    {
        std::string url = Additionals::Convectors::ConvertWStringToString(s_url);
        int count = -1;
        for (auto& var : Additionals::String::split(url, '/'))
        {
            ++count;
        }
        url = Additionals::String::split(url, '/')[count];
        destenation_file = Additionals::Convectors::ConvertStringToWcharPtr(url);
    }


    std::filesystem::path d_file_path(destenation_file);
    d_file_path = d_file_path.parent_path();

    DWORD attrib = GetFileAttributesW(d_file_path.wstring().c_str());
    if (d_file_path != "" && attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (!CreateDirectoryW(d_file_path.wstring().c_str(), NULL))
        {
            // Обработка ошибки создания директории
            int error = GetLastError();
            //System::Console::WriteLine(System::String(().ToString());
            //System::Console::WriteLine(error);
        }
    }

    if (d_file != nullptr || d_file != NULL)
    {
        if (std::filesystem::exists(d_file) && std::filesystem::is_directory(d_file))
        {
            std::string url = Additionals::Convectors::ConvertWStringToString(s_url);
            int count = -1;
            for (auto& var : Additionals::String::split(url, '/'))
            {
                ++count;
            }
            url = Additionals::String::split(url, '/')[count];

            std::wstring ff = d_file;
            destenation_file = ff + L"\\" + Additionals::Convectors::ConvertStringToWcharPtr(url);
        }
    }
    HRESULT download_result = URLDownloadToFileW(NULL, s_url, destenation_file.c_str(), NULL, &callback);

    if (S_OK == download_result)
    {
        callback.OnProgress(NULL, NULL, NULL, StrDogW({ L"The file is saved as: ",  d_file, L"\n" }));
        return destenation_file;
    }
    else
    {
        if (s_url == NULL)
        {
            s_url = L" ";
        }
        if (d_file == NULL)
        {
            d_file = L" ";
        }
        callback.OnProgress(NULL, NULL, NULL, StrDogW({ L"Unable to Download the file: ", s_url, L"\nto: ", d_file }));
        return L"";
    }
    if (lzma_compressed)
    {
        /*System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(System::String(d_file).ToString());
        System::IO::Compression::ZipFileExtensions::ExtractToDirectory(zArchive, System::String(d_file).ToString());*/
    }
}

//wchar_t* DDIC::DownloadDeleteClass::download_file(wchar_t* s_url, CallbackDict callback)
//{
//    wchar_t* d_file = NULL;
//
//    if (S_OK == URLDownloadToFileW(NULL, s_url, d_file, NULL, &callback)) {
//        System::Console::Write("The file is saved as: ");
//        System::Console::WriteLine(System::String(d_file).ToString());
//        return d_file;
//    }
//    else {
//        System::Console::Write("Unable to Download the file: ");
//        System::Console::WriteLine(System::String(s_url).ToString());
//        return d_file;
//    }
//}


bool DDIC::Download::Files::download_all_files(wchar_t* s_url_dir, CallbackNull callback)
{
    return false;
}

int DDIC::Download::Files::_get_java_exist_ver(wchar_t* direct)
{
    std::vector<std::string> dirs = Additionals::Path::get_directories(Additionals::Convectors::ConvertWcharPtrToString(direct));
    for (std::string var : dirs)
    {
        int count = -1;
        for (auto& var2 : Additionals::String::split(var, '\\'))
        {
            ++count;
        }
        if (Additionals::String::split(var, '\\')[count]._Starts_with("jdk"))
        {
            if (Additionals::String::split(var, '\\')[count]._Starts_with("jdk8"))
            {
                return 8;
            }
            return 1;
        }
    }
    return 0;
}

std::string DDIC::Download::Files::_get_java_path(const wchar_t* dir)
{
    std::vector<std::string> dirs = Additionals::Path::get_directories(Additionals::Convectors::ConvertWcharPtrToString(dir));
    for (std::string var : dirs)
    {
        int count = -1;
        for (auto& var2 : Additionals::String::split(var, '\\'))
        {
            ++count;
        }
        if (Additionals::String::split(var, '\\')[count]._Starts_with("jdk"))
        {
            return var;
        }
    }
    return "";
}

wchar_t* DDIC::Download::Java::install(wchar_t* version, wchar_t* path, wchar_t* operating_system, wchar_t* arch, wchar_t* impl, bool jre)
{
    wchar_t* url = get_download_url(version, operating_system, arch, impl, jre);

    std::string path2 = Additionals::Convectors::ConvertWcharPtrToString(path);
    if (!path) {
        if (jre){
            path2 = _JRE_DIR;
        }
        else{
            path2 = _JDK_DIR;
        }
    }

    wchar_t* path_wch = Additionals::Convectors::ConvertStringToWcharPtr(path2 + "\\.zip");
    wchar_t* path_wch_norm = Additionals::Convectors::ConvertStringToWcharPtr(path2);

    std::wstring jdk_file2 = nullptr;
    CallbackDict callback;
    

    jdk_file2 = DownloadFile(url, path_wch, callback);

    const wchar_t* jdk_file = jdk_file2.c_str();
    
    if (jdk_file == nullptr)
    {
        return _wcsdup(L"error 105: file not download");
    }
    wchar_t* jdk_ext = Additionals::Convectors::ConvertStringToWcharPtr(_get_normalized_compressed_file_ext(jdk_file));
    wchar_t* jdk_dir = _decompress_archive(jdk_file, jdk_ext, path_wch_norm);


    if (jdk_file != nullptr)
    {
        std::string fifa;
        for (size_t i = 0; jdk_file[i] != L'\0'; ++i)
        {
            fifa += jdk_file[i];
        }
        bool del = DeleteFileW(Additionals::Convectors::ConvertStringToWcharPtr(fifa));
        /*System::Console::Write("Deleted archive status: ");
        System::Console::WriteLine(del);*/

        std::cout << "Deleted archive status: " << del << std::endl;
    }
    /*System::Console::WriteLine("Installation of java completed");*/

    std::cout << "Installation of java completed" << std::endl;


    return jdk_dir;
}

wchar_t* DDIC::Download::Java::get_download_url(/*wchar_t*& url,*/wchar_t* version, wchar_t* operating_system, wchar_t* arch, wchar_t* impl, bool jre)
{
    version = normalize_version(version);
    if(jre) {
        //L"https://api.adoptopenjdk.net/v3/binary/latest/"

        /*wchar_t* url = L"https://api.adoptopenjdk.net/v3/binary/latest/";

        url = strdogW(url, version);
        url = strdogW(url, L"/ga/");
        url = strdogW(url, operating_system);
        url = strdogW(url, L"/");
        url = strdogW(url, arch);
        url = strdogW(url, L"/jre/");
        url = strdogW(url, impl);
        url = strdogW(url, L"/normal/adoptopenjdk");*/

        wchar_t* url = JoinW({ 
            L"https://api.adoptopenjdk.net/v3/binary/latest/",
            version,
            L"ga",
            operating_system,
            arch,
            L"jre",
            impl,
            L"normal/adoptopenjdk "});

        return url; 
        //L"https://api.adoptopenjdk.net/v3/binary/latest/%s/ga/%s/%s/jre/%s/normal/adoptopenjdk", version, operating_system, arch, impl;
    }
    else {
        /*wchar_t* url = L"https://api.adoptopenjdk.net/v3/binary/latest/";
        
        url = strdogW(url, version);
        url = strdogW(url, L"/ga/");
        url = strdogW(url, operating_system);
        url = strdogW(url, L"/");
        url = strdogW(url, arch);
        url = strdogW(url, L"/jdk/");
        url = strdogW(url, impl);
        url = strdogW(url, L"/normal/adoptopenjdk");*/

		wchar_t* url = JoinW({ 
            L"https://api.adoptopenjdk.net/v3/binary/latest/",
            version,
            L"ga",
            operating_system,
            arch,
            L"jdk",
            impl,
            L"normal/adoptopenjdk "});
        
        return url;
    }
}

wchar_t* DDIC::Download::Java::_decompress_archive(const wchar_t* repo_root, wchar_t* file_ending, wchar_t* destination_folder)
{
    //WIN32_FIND_DATA ffd;

    std::string destination_str;
    destination_str = Additionals::Convectors::ConvertWcharPtrToString(destination_folder);
    wchar_t* destination_str_cstr = Additionals::Convectors::ConvertStringToWcharPtr(destination_str);

    std::string repo_root_str;
    repo_root_str = Additionals::Convectors::ConvertWcharPtrToString(repo_root);

    if (!std::filesystem::exists(destination_str)) {
        int out_mkdir = _wmkdir(destination_str_cstr);
        /*System::Console::Write("java dir is maked with status: ");
        System::Console::WriteLine(out_mkdir);*/

        std::cout << "java dir is maked with status: " << out_mkdir << std::endl;
    }

    std::string jdk_file = repo_root_str;

    if (std::filesystem::is_directory(jdk_file))
    {
        if (std::filesystem::exists(destination_str))
        {
            return destination_folder; //TODO переписывание архива
        }

        /*System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(repo_root_str);
        System::IO::Compression::ZipFileExtensions::ExtractToDirectory(zArchive, destination_str);*/


        /*jdk_directory = _extract_files(jdk_file, file_ending, destination_folder);
        jdk_bin = path.join(jdk_directory, "bin");
        _unpack_jars(jdk_directory, jdk_bin);*/

        return destination_folder;
    }
    else 
    {
        return (wchar_t*)repo_root;
    }
}

bool DDIC::Download::Java::check_system_verison_java(wchar_t* version)
{
    //TODO Проверка текущей версии java
    return false;
}

bool DDIC::Download::Java::check_downloaded_version_java(wchar_t* path)
{
    std::string java_path = DDIC::Download::Files::_get_java_path(path) + "\\" + "bin" + "\\" + "java.exe";
    if (std::filesystem::exists(java_path))
    {
        return true;
    }
    return false;
}


std::string DDIC::Download::Java::_get_normalized_compressed_file_ext(const wchar_t* file)
{
    std::string file_str;
    file_str = Additionals::Convectors::ConvertWcharPtrToString(file);
    
    if (file_str.find(_TAR)) {
        return _TAR;
    }
    else if (file_str.find(_TAR_GZ)) {
        return _TAR_GZ;
    }
    else if (file_str.find(_ZIP)) {
        return _ZIP;
    }
    else {
        return _SEVEN_ZIP;
    }
}

wchar_t* DDIC::Download::Java::normalize_version(wchar_t* version)
{
    if (version == L"1.8") {
        return const_cast<wchar_t*>(L"8");
    } 
    return version;
}

std::string DDIC::Download::Java::expand_user(std::string path)
{
    if (!path.empty() && path[0] == '~') {
        //assert(path.size() == 1 || path[1] == '/');  // or other error handling
        //_dupenv_s(,"HOME")

		char* home = nullptr;
        size_t home_sz = 0;

        _dupenv_s(&home, &home_sz, "HOME");

		//home.compare(profile)
        if (home || (_dupenv_s(&home, &home_sz, "USERPROFILE")) && home != 0) 
        {
            path = Additionals::String::replace(path, path, std::string(home));
        }
        else 
        {
			size_t hdrive_sz = 0;
			size_t hpath_sz = 0;
            char* hdrive;
            char* hpath;

            _dupenv_s(&hdrive, &hdrive_sz, "HOMEDRIVE");
			_dupenv_s(&hpath, &hpath_sz, "HOMEPATH");

            //assert(hdrive);  // or other error handling
            //assert(hpath);

            path = Additionals::String::replace(path, path, (hdrive == 0 ? "" : std::string(hdrive)) + (hpath == 0 ? "" : std::string(hpath)));
        }
    }
    return path;
}

//std::string DDIC::JavaDownload::expand_user(std::string path) {
//    if (! path.empty() && path[0] == '~') {
//        //assert(path.size() == 1 || path[1] == '/');  // or other error handling
//        char const* home = getenv("HOME");
//        if (home || ((home = getenv("USERPROFILE")))) {
//            path.replace(0, 1, home);
//        }
//        else {
//            char const* hdrive = getenv("HOMEDRIVE"),
//                * hpath = getenv("HOMEPATH");
//            //assert(hdrive);  // or other error handling
//            //assert(hpath);
//            path.replace(0, 1, std::string(hdrive) + hpath);
//        }
//    }
//    return path;
//}

