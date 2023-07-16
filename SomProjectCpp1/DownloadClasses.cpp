#include "DownloadClasses.h"




wchar_t* DDIC::Download::Files::download_file(wchar_t* s_url, wchar_t* d_file, CallbackNull &callback, bool lzma_compressed)
{
    if (d_file == NULL)
    {
        System::String^ url = System::String(s_url).ToString();
        int count = -1;
        for each (auto var in url->Split('/'))
        {
            ++count;
        }
        url = url->Split('/')[count];
        pin_ptr<const wchar_t> wch_url = PtrToStringChars(url);
        d_file = const_cast<wchar_t*>(wch_url);
    }


    pin_ptr<const wchar_t> wch = PtrToStringChars(System::IO::Path::GetDirectoryName(System::String(d_file).ToString()));
    DWORD attrib = GetFileAttributesW(wch);
    if (attrib == INVALID_FILE_ATTRIBUTES || !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (!CreateDirectoryW(wch, NULL))
        {
            // ќбработка ошибки создани€ директории
            int error = GetLastError();
            //System::Console::WriteLine(System::String(().ToString());
            //System::Console::WriteLine(error);
        }
    }

    if (System::IO::Directory::Exists(System::String(d_file).ToString()) && System::IO::File::GetAttributes(System::String(d_file).ToString()) == System::IO::FileAttributes::Directory)
    {
        System::String^ url = System::String(s_url).ToString();
        int count = -1;
        for each (auto var in url->Split('/'))
        {
            ++count;
        }
        url = url->Split('/')[count];
        pin_ptr<const wchar_t> wch_url = PtrToStringChars(System::String(d_file).ToString() + "\\" + url);
        d_file = const_cast<wchar_t*>(wch_url);
    }
	if (S_OK == URLDownloadToFileW(NULL, s_url, d_file, NULL, &callback)) 
    {
        callback.OnProgress(NULL, NULL, NULL, StrDogW({L"The file is saved as: ",  d_file, L"\n"}));
		return d_file;
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
        callback.OnProgress(NULL, NULL, NULL, StrDogW({L"Unable to Download the file: ", s_url, L"\nto: ", d_file}));
		return nullptr;
	}
    if (lzma_compressed)
    {
        System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(System::String(d_file).ToString());
        System::IO::Compression::ZipFileExtensions::ExtractToDirectory(zArchive, System::String(d_file).ToString());
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
    array<System::String^>^ dirs = System::IO::Directory::GetDirectories(System::String(direct).ToString());
    for each (System::String ^ var in dirs)
    {
        int count = -1;
        for each (auto var2 in var->Split('\\'))
        {
            ++count;
        }
        if (var->Split('\\')[count]->StartsWith("jdk"))
        {
            if (var->Split('\\')[count]->StartsWith("jdk8"))
            {
                return 8;
            }
            return 1;
        }
    }
    return 0;
}

System::String^ DDIC::Download::Files::_get_java_path(wchar_t* dir)
{
    array<System::String^>^ dirs = System::IO::Directory::GetDirectories(System::String(dir).ToString());
    for each (System::String ^ var in dirs)
    {
        int count = -1;
        for each (auto var2 in var->Split('\\'))
        {
            ++count;
        }
        if (var->Split('\\')[count]->StartsWith("jdk"))
        {
            return var;
        }
    }
    return nullptr;
}

wchar_t* DDIC::Download::Java::install(wchar_t* version, wchar_t* path, wchar_t* operating_system, wchar_t* arch, wchar_t* impl, bool jre)
{
    wchar_t* url = get_download_url(version, operating_system, arch, impl, jre);

    System::String^ path2 = System::String(path).ToString();
    if (!path) {
        if (jre){
            path2 = _JRE_DIR;
        }
        else{
            path2 = _JDK_DIR;
        }
    }

    pin_ptr<const wchar_t> path_wch = PtrToStringChars(path2 + L"\\.zip");
    pin_ptr<const wchar_t> path_wch_norm = PtrToStringChars(path2);

    wchar_t* jdk_file = NULL;
    CallbackDict callback;
    
    try
    {
        jdk_file = DownloadFile(url, const_cast<wchar_t*>(path_wch), callback);
        if (jdk_file == NULL)
        {
            return L"error 105: file not download";
        }
        wchar_t* jdk_ext = _get_normalized_compressed_file_ext(jdk_file);
        wchar_t* jdk_dir = _decompress_archive(jdk_file, jdk_ext, const_cast<wchar_t*>(path_wch_norm));

        return jdk_dir;
    }
    finally
    {
        if (jdk_file != NULL)
        {
            char fifa[100];
            int size_fifa = 0;
            for (int i = 0; jdk_file[i] != L'\0'; i++)
            {
                fifa[i] = jdk_file[i];
                size_fifa = i;
            }
            fifa[size_fifa + 1] = '\0';
            bool del = DeleteFileW(jdk_file); //FIXME не удал€ет файл
            //int del = 0;
            //del = std::remove(fifa);
            System::Console::Write("Deleted archive status: ");
            System::Console::WriteLine(del);
        }
        System::Console::WriteLine("Installation of java completed");
    }
}

wchar_t*& DDIC::Download::Java::get_download_url(/*wchar_t*& url,*/wchar_t* version, wchar_t* operating_system, wchar_t* arch, wchar_t* impl, bool jre)
{
    version = normalize_version(version);
    if(jre) {
        wchar_t* url = L"https://api.adoptopenjdk.net/v3/binary/latest/";

        url = strdogW(url, version);
        url = strdogW(url, L"/ga/");
        url = strdogW(url, operating_system);
        url = strdogW(url, L"/");
        url = strdogW(url, arch);
        url = strdogW(url, L"/jre/");
        url = strdogW(url, impl);
        url = strdogW(url, L"/normal/adoptopenjdk");

        return url; 
        //L"https://api.adoptopenjdk.net/v3/binary/latest/%s/ga/%s/%s/jre/%s/normal/adoptopenjdk", version, operating_system, arch, impl;
    }
    else {
        wchar_t* url = L"https://api.adoptopenjdk.net/v3/binary/latest/";
        
        url = strdogW(url, version);
        url = strdogW(url, L"/ga/");
        url = strdogW(url, operating_system);
        url = strdogW(url, L"/");
        url = strdogW(url, arch);
        url = strdogW(url, L"/jdk/");
        url = strdogW(url, impl);
        url = strdogW(url, L"/normal/adoptopenjdk");
        
        return url;
    }
}

wchar_t* DDIC::Download::Java::_decompress_archive(wchar_t* repo_root, wchar_t* file_ending, wchar_t* destination_folder)
{
    //WIN32_FIND_DATA ffd;

    System::String^ destination_str;
    destination_str = System::String(destination_folder).ToString();
    pin_ptr<const wchar_t> destination_str_cstr = PtrToStringChars(destination_str);

    System::String^ repo_root_str;
    repo_root_str = System::String(repo_root).ToString();

    if (!System::IO::File::Exists(destination_str)) {
        int out_mkdir = _wmkdir(destination_str_cstr);
        System::Console::Write("java dir is maked with status: ");
        System::Console::WriteLine(out_mkdir);
    }

    auto jdk_file = repo_root_str;

    if (System::IO::File::GetAttributes(jdk_file) != System::IO::FileAttributes::Directory) 
    {
        if (System::IO::Directory::Exists(destination_str))
        {
            return destination_folder; //TODO переписывание архива
        }

        System::IO::Compression::ZipArchive^ zArchive = System::IO::Compression::ZipFile::OpenRead(repo_root_str);
        System::IO::Compression::ZipFileExtensions::ExtractToDirectory(zArchive, destination_str);


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

bool DDIC::Download::Java::check_system_verison_java(wchar_t* version)
{
    //TODO ѕроверка текущей версии java
    return false;
}

bool DDIC::Download::Java::check_downloaded_version_java(wchar_t* path)
{
    System::String^ java_path = DDIC::Download::Files::_get_java_path(path) + "\\" + "bin" + "\\" + "java.exe";
    if (System::IO::File::Exists(java_path))
    {
        return true;
    }
    return false;
}

wchar_t*& DDIC::strdogW(wchar_t* ref_str, wchar_t* str_to_add)
{
    int ref_size = 0, to_add_size = 0;


    if (ref_str == NULL)
    {
        for (int i = 0; str_to_add[i] != '\0'; i++)
        {
            to_add_size = i + 1;
        }
        goto skipcount;
    }
    for (int i = 0; ref_str[i] != '\0'; i++)
    {
        ref_size = i + 1;
    }
    for (int i = 0; str_to_add[i] != '\0'; i++)
    {
        to_add_size = i + 1;
    }

    skipcount:
    wchar_t* new_str_temp = new wchar_t[ref_size + to_add_size + 4];
    if (ref_str == NULL || ref_str[0] == '\0' )
    {
        for (int j = 0; str_to_add[j] != '\0'; j++)
        {
            new_str_temp[j] = str_to_add[j];
        }
    }
    if (ref_str == NULL)
    {
        goto skip;
    }
    for (int i = 0; ref_str[i] != '\0'; i++)
    {
        if (ref_str[i+1] == '\0')
        {
            ref_size = i + 1;
            for (int l = 0; ref_str[l] != '\0'; l++)
            {
                new_str_temp[l] = ref_str[l];
            }
            for (int j = 0; str_to_add[j] != '\0'; j++)
            {
                new_str_temp[i+1+j] = str_to_add[j];
            }
            
        }
    }
    skip:
    /*if (ref_size == 0 || to_add_size == 0)
    {
        return ref_str;
    }*/
    wchar_t* new_str = new wchar_t[ref_size + to_add_size];
    for (int i = 0; i < ref_size + to_add_size; i++)
    {
        new_str[i] = new_str_temp[i];
    }
    new_str[ref_size + to_add_size] = '\0';
    
    delete[]new_str_temp;
    return new_str; ////FIXME утечка пам€ти
}

wchar_t*& DDIC::strdogWA(wchar_t* ref_str, char* str_to_add)
{
    int ref_size = 0, to_add_size = 0;
    wchar_t* new_str_temp = new wchar_t[100];
    if (ref_str == NULL || ref_str[0] == '\0')
    {
        for (int j = 0; str_to_add[j] != '\0'; j++)
        {
            new_str_temp[j] = str_to_add[j];
            if (str_to_add[j + 1] == '\0')
            {
                to_add_size = j + 1;
            }
        }
    }
    if (ref_str == NULL)
    {
        goto skip;
    }
    for (int i = 0; ref_str[i] != '\0'; i++)
    {
        if (ref_str[i + 1] == '\0')
        {
            ref_size = i + 1;
            for (int l = 0; ref_str[l] != '\0'; l++)
            {
                new_str_temp[l] = ref_str[l];
            }
            for (int j = 0; str_to_add[j] != '\0'; j++)
            {
                new_str_temp[i + 1 + j] = str_to_add[j];
                if (str_to_add[j + 1] == '\0')
                {
                    to_add_size = j + 1;
                }
            }

        }
    }
    skip:
    /*if (ref_size == 1 || to_add_size == 1)
    {
        return ref_str;
    }*/
    wchar_t* new_str = new wchar_t[ref_size + to_add_size];
    for (int i = 0; i < ref_size + to_add_size; i++)
    {
        new_str[i] = new_str_temp[i];
    }
    new_str[ref_size + to_add_size] = '\0';

    delete[]new_str_temp;
    return new_str; //FIXME утечка пам€ти
}

wchar_t*& DDIC::strdogAW(char* ref_str, wchar_t* str_to_add)
{
    int ref_size = 0, to_add_size = 0;
    wchar_t* new_str_temp = new wchar_t[100];
    if (ref_str == NULL || ref_str[0] == '\0')
    {
        for (int j = 0; str_to_add[j] != '\0'; j++)
        {
            new_str_temp[j] = str_to_add[j];
            if (str_to_add[j + 1] == '\0')
            {
                to_add_size = j + 1;
            }
        }
    }
    if (ref_str == NULL)
    {
        goto skip;
    }
    for (int i = 0; ref_str[i] != '\0'; i++)
    {
        if (ref_str[i + 1] == '\0')
        {
            ref_size = i + 1;
            for (int l = 0; ref_str[l] != '\0'; l++)
            {
                new_str_temp[l] = ref_str[l];
            }
            for (int j = 0; str_to_add[j] != '\0'; j++)
            {
                new_str_temp[i + 1 + j] = str_to_add[j];
                if (str_to_add[j + 1] == '\0')
                {
                    to_add_size = j + 1;
                }
            }

        }
    }
    skip:
    /*if (ref_size == 0 || to_add_size == 0)
    {
        return ref_str;
    }*/
    wchar_t* new_str = new wchar_t[ref_size + to_add_size];
    for (int i = 0; i < ref_size + to_add_size; i++)
    {
        new_str[i] = new_str_temp[i];
    }
    new_str[ref_size + to_add_size] = '\0';

    delete[]new_str_temp;
    return new_str; //FIXME утечка пам€ти
}

wchar_t*& DDIC::strdogA(char* ref_str, char* str_to_add)
{
    int ref_size = 0, to_add_size = 0;
    wchar_t* new_str_temp = new wchar_t[100];
    if (ref_str == NULL || ref_str[0] == '\0')
    {
        for (int j = 0; str_to_add[j] != '\0'; j++)
        {
            new_str_temp[j] = str_to_add[j];
            if (str_to_add[j + 1] == '\0')
            {
                to_add_size = j + 1;
            }
        }
    }
    if (ref_str == NULL)
    {
        goto skip;
    }
    for (int i = 0; ref_str[i] != '\0'; ++i)
    {
        if (ref_str[i + 1] == '\0')
        {
            ref_size = i + 1;
            for (int l = 0; ref_str[l] != '\0'; ++l)
            {
                new_str_temp[l] = ref_str[l];
            }
            for (int j = 0; str_to_add[j] != '\0'; ++j)
            {
                new_str_temp[i + 1 + j] = str_to_add[j];
                if (str_to_add[j + 1] == '\0')
                {
                    to_add_size = j + 1;
                }
            }

        }
    }
    skip:
    /*if (ref_size == 0 || to_add_size == 0)
    {
        return ref_str;
    }*/
    wchar_t* new_str = new wchar_t[ref_size + to_add_size];
    for (int i = 0; i < ref_size + to_add_size; ++i)
    {
        new_str[i] = new_str_temp[i];
    }
    new_str[ref_size + to_add_size] = '\0';

    delete[]new_str_temp;
    return new_str; //FIXME утечка пам€ти
}

wchar_t*& DDIC::strdogW(std::initializer_list<wchar_t*> list)
{
    wchar_t* path = NULL;
    int i = 0;
    for (wchar_t* elem : list)
    {
        /*if (path == NULL)
        {
            path = elem;
        }*/
        if (i == 0)
        {
            path = elem;
            ++i;
            continue;
        }
        path = StrDogW(path, elem);
        ++i;
    }
    return path;
}

wchar_t* DDIC::Download::Java::_get_normalized_compressed_file_ext(wchar_t* file)
{
    System::String^ file_str;
    file_str = System::String(file).ToString();
    
    if (file_str->Contains(_TAR)) {
        return _TAR;
    }
    else if (file_str->Contains(_TAR_GZ)) {
        return _TAR_GZ;
    }
    else if (file_str->Contains(_ZIP)) {
        return _ZIP;
    }
    else {
        return _SEVEN_ZIP;
    }
}

wchar_t* DDIC::Download::Java::normalize_version(wchar_t* version)
{
    if (version == L"1.8") {
        return L"8";
    } 
    return version;
}

System::String^ DDIC::Download::Java::expand_user(System::String^ path)
{
    if (! path->IsNullOrEmpty(path) && path[0] == '~') {
        //assert(path.size() == 1 || path[1] == '/');  // or other error handling
        //_dupenv_s(,"HOME")
        char const* home = getenv("HOME");
        if (home || ((home = getenv("USERPROFILE")))) {
            path = path->Replace(path, System::String(home).ToString());
        }
        else {
            char const* hdrive = getenv("HOMEDRIVE"), 
                *hpath = getenv("HOMEPATH");
            //assert(hdrive);  // or other error handling
            //assert(hpath);

            path = path->Replace(path, System::String(hdrive).ToString() + System::String(hpath).ToString());
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

wchar_t*& DDIC::Path::joinW(std::initializer_list<wchar_t*> list)
{
    wchar_t* path = NULL;
    int i = 0;
    for (wchar_t* elem : list)
    {
        /*if (path == NULL)
        {
            path = elem;
        }*/
        if (i == 0)
        {
            path = elem;
            ++i;
            continue;
        }
        path = StrDogW(path, L"\\");
        path = StrDogW(path, elem);
        ++i;
    }
    return path;
}

wchar_t*& DDIC::Path::joinA(std::initializer_list<char*> list)
{
    wchar_t* path = NULL;
    int i = 0;
    for (char* elem : list)
    {
        if (i == 0)
        {
            path = L"";
            path = StrDogWA(L"", elem);
            ++i;
            continue;
        }
        path = StrDogWA(path, "\\");
        path = StrDogWA(path, elem);
        ++i;
    }
    return path;
}

wchar_t* DDIC::TempFile::get_tempdir()
{
    /*
    Private accessor for tempfile.tempdir.
    */


    return DDIC::TempFile::_get_default_tempdir();
}

wchar_t* DDIC::TempFile::get_tempdir_SYSTEM()
{
    System::String^ temp_path = GetTempPath();
    pin_ptr<const wchar_t> wch_path = PtrToStringChars(temp_path);
    return const_cast<wchar_t*>(wch_path);
}

wchar_t* DDIC::TempFile::_get_default_tempdir()
{
    /*
    Calculate the default directory to use for temporary files.
    This routine should be called exactly once.

    We determine whether or not a candidate temp dir is usable by
    trying to create and write to a file in that directory.  If this
    is successful, the test file is deleted.  To prevent denial of
    service, the name of the test file must be randomized.
    */
    //wchar_t* namer;// = DDIC::TempFile::_RandomNameSequence();
    System::Collections::Generic::List<System::String^>^ dirlist;// = DDIC::TempFile::_candidate_tempdir_list();

    for each (System::String^ dir in dirlist)
    {
        if (dir != System::String(".").ToString())
        {
            dir = System::IO::Path::GetFullPath(dir);
        }
    }

    return nullptr;
}
