﻿#include "DownloadClasses.h"


//bool DDIC::Download::Files::_CreateDirectoryIfNotExists(const std::wstring& path) 
//{
//    if (!std::filesystem::exists(path)) 
//    {
//        return std::filesystem::create_directory(path);
//    }
//    return true;
//}


std::string DDIC::Download::Files::download_file(const std::string& s_url, const std::string& d_file, CallbackNull* callback, bool lzma_compressed)
{
    //callback = const_cast<CallbackNull>(callback);
    std::string destenation_file;

    if (d_file == "")
    {
        destenation_file = "";
    }
    else
    {
        destenation_file = d_file;
    }
    if (d_file == "")
    {
        std::string url = s_url;
        int count = -1;
        for (auto& var : Additionals::String::split(url, '/'))
        {
            ++count;
        }
        url = Additionals::String::split(url, '/')[count];
        destenation_file = url;
    }


    std::filesystem::path d_file_path(destenation_file);
    d_file_path = d_file_path.parent_path();

    if (d_file_path != "")
    {
        if (!std::filesystem::create_directories(d_file_path))
        {
            // Обработка ошибки создания директории
            int error = GetLastError();
        }
    }
    

    if (d_file != "")
    {
        if (std::filesystem::exists(d_file) && std::filesystem::is_directory(d_file))
        {
            std::string url = s_url;
            int count = -1;
            for (auto& var : Additionals::String::split(url, '/'))
            {
                ++count;
            }
            url = Additionals::String::split(url, '/')[count];

            std::string ff = d_file;
            destenation_file = ff + "\\" + url;
        }
    }
    HRESULT download_result = URLDownloadToFileA(NULL, s_url.c_str(), destenation_file.c_str(), NULL, callback);

    if (S_OK == download_result)
    {
        callback->OnProgress(NULL, NULL, NULL, Additionals::Convectors::ConvertStringToWcharPtr("The file is saved as: " + d_file + "\n"));
        return destenation_file;
    }
    else
    {
        callback->OnProgress(NULL, NULL, NULL, Additionals::Convectors::ConvertStringToWcharPtr("Unable to Download the file: " + s_url + "\nto: " + d_file));
        return "";
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


bool DDIC::Download::Files::download_all_files(const std::string& s_url_dir, CallbackNull callback)
{
    return false;
}

int DDIC::Download::Files::_get_java_exist_ver(const std::string& direct)
{
    std::vector<std::string> dirs = Additionals::Path::get_directories(direct);
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

std::string DDIC::Download::Files::_get_java_path(const std::string& dir)
{
    std::vector<std::string> dirs = Additionals::Path::get_directories(dir);
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

std::string DDIC::Download::Java::install(const std::string& version, const std::string& path, const std::string& operating_system, const std::string& arch, const std::string& impl, bool jre)
{
    std::string url = get_download_url(version, operating_system, arch, impl, jre);

    std::string path2 = path;
    if (path != "") {
        if (jre){
            path2 = _JRE_DIR;
        }
        else{
            path2 = _JDK_DIR;
        }
    }

    std::string path_wch = path2 + "\\.zip";
    std::string path_wch_norm = path2;

    std::string jdk_file2 = "";
    CallbackDict callback;
    

    jdk_file2 = DownloadFile(url, path_wch, &callback);

    std::string jdk_file = jdk_file2;
    
    if (jdk_file == "")
    {
        //return _wcsdup(L"error 105: file not download");
        return "";
    }
    std::string jdk_ext = _get_normalized_compressed_file_ext(jdk_file);
    std::string jdk_dir = _decompress_archive(jdk_file, jdk_ext, path_wch_norm);


    if (jdk_file != "")
    {
        std::string fifa;
        for (size_t i = 0; jdk_file[i] != L'\0'; ++i)
        {
            fifa += jdk_file[i];
        }
        bool del = DeleteFileA(fifa.c_str());


        std::cout << "Deleted archive status: " << del << std::endl;
    }
    /*System::Console::WriteLine("Installation of java completed");*/

    std::cout << "Installation of java completed" << std::endl;


    return jdk_dir;
}

std::string DDIC::Download::Java::get_download_url(/*wchar_t*& url,*/const std::string& version, const std::string& operating_system, const std::string& arch, const std::string& impl, bool jre)
{
    std::string _version = version;
    _version = normalize_version(version);
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

        std::string url = Join({
            "https://api.adoptopenjdk.net/v3/binary/latest/",
            _version,
            "ga",
            operating_system,
            arch,
            "jre",
            impl,
            "normal/adoptopenjdk "});

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

        std::string url = Join({
            "https://api.adoptopenjdk.net/v3/binary/latest/",
            _version,
            "ga",
            operating_system,
            arch,
            "jdk",
            impl,
            "normal/adoptopenjdk "});
        
        return url;
    }
}

std::string DDIC::Download::Java::_decompress_archive(const std::string& repo_root, const std::string& file_ending, const std::string& destination_folder)
{
    //WIN32_FIND_DATA ffd;

    std::string destination_str;
    destination_str = destination_folder;
    std::string destination_str_cstr = destination_str;

    std::string repo_root_str;
    repo_root_str = repo_root;

    if (!std::filesystem::exists(destination_str)) {
        bool out_mkdir = std::filesystem::create_directories(destination_str_cstr);
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
        return repo_root;
    }
}

bool DDIC::Download::Java::check_system_verison_java(const std::string& version)
{
    //TODO Проверка текущей версии java
    return false;
}

bool DDIC::Download::Java::check_downloaded_version_java(const std::string& path)
{
    std::string java_path = DDIC::Download::Files::_get_java_path(path) + "\\" + "bin" + "\\" + "java.exe";
    if (std::filesystem::exists(java_path))
    {
        return true;
    }
    return false;
}


std::string DDIC::Download::Java::_get_normalized_compressed_file_ext(const std::string& file)
{
    std::string file_str;
    file_str = file;
    
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

std::string DDIC::Download::Java::normalize_version(const std::string& version)
{
    if (version == "1.8") {
        return "8";
    } 
    return version;
}

std::string DDIC::Download::Java::expand_user(std::string path)
{
    if (!path.empty() && path[0] == '~') 
    {
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

