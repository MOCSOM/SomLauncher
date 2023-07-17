#include "Additionals.h"

wchar_t* Additionals::Convectors::ConvertStringToWcharPtr(System::String^ str)
{
    pin_ptr<const wchar_t> wch_str = PtrToStringChars(str);
    wchar_t* wcharPtr = const_cast<wchar_t*>(wch_str);
    return wcharPtr;
}

wchar_t*& Additionals::String::strdogW(wchar_t* ref_str, wchar_t* str_to_add)
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
    return new_str; ////FIXME утечка памяти
}

wchar_t*& Additionals::String::strdogWA(wchar_t* ref_str, char* str_to_add)
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
    return new_str; //FIXME утечка памяти
}

wchar_t*& Additionals::String::strdogAW(char* ref_str, wchar_t* str_to_add)
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
    return new_str; //FIXME утечка памяти
}

wchar_t*& Additionals::String::strdogA(char* ref_str, char* str_to_add)
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
    return new_str; //FIXME утечка памяти
}

wchar_t*& Additionals::String::strdogW(std::initializer_list<wchar_t*> list)
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

wchar_t*& Additionals::Path::joinW(std::initializer_list<wchar_t*> list)
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

wchar_t*& Additionals::Path::joinA(std::initializer_list<char*> list)
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
