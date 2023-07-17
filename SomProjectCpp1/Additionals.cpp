#include "Additionals.h"

wchar_t* Additionals::Convectors::ConvertStringToWcharPtr(System::String^ str)
{
    pin_ptr<const wchar_t> wch_str = PtrToStringChars(str);
    wchar_t* wcharPtr = const_cast<wchar_t*>(wch_str);
    return wcharPtr;
}

wchar_t* Additionals::String::strdogW(wchar_t* ref_str, wchar_t* str_to_add)
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

wchar_t* Additionals::String::strdogW(const wchar_t* ref_str, wchar_t* str_to_add)
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

wchar_t* Additionals::String::strdogW(wchar_t* ref_str, const wchar_t* str_to_add)
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

wchar_t* Additionals::String::strdogWA(wchar_t* ref_str, char* str_to_add)
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

wchar_t* Additionals::String::strdogAW(char* ref_str, wchar_t* str_to_add)
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

wchar_t* Additionals::String::strdogA(char* ref_str, char* str_to_add)
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

wchar_t* Additionals::String::strdogW(std::initializer_list<wchar_t*> list)
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

wchar_t* Additionals::Path::joinW(std::initializer_list<wchar_t*> list)
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

wchar_t* Additionals::Path::joinA(std::initializer_list<char*> list)
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

wchar_t* Additionals::TempFile::get_tempdir()
{
    /*
    Private accessor for tempfile.tempdir.
    */


    return Additionals::TempFile::_get_default_tempdir();
}

wchar_t* Additionals::TempFile::get_tempdir_SYSTEM()
{
    System::String^ temp_path = System::IO::Path::GetTempPath();
    pin_ptr<const wchar_t> wch_path = PtrToStringChars(temp_path);
    return const_cast<wchar_t*>(wch_path);
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

    //wchar_t* namer;// = DDIC::TempFile::_RandomNameSequence();
    System::Collections::Generic::List<System::String^>^ dirlist = nullptr;// = DDIC::TempFile::_candidate_tempdir_list();

    for each (System::String^ dir in dirlist)
    {
        if (dir != System::String(".").ToString())
        {
            dir = System::IO::Path::GetFullPath(dir);
        }
    }

    return nullptr;
}
