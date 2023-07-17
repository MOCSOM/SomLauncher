#ifndef ADDITIONALS_H_
#define ADDITIONALS_H_

#include <vcclr.h>
#include <initializer_list>

#define StrDogWA Additionals::String::strdogWA
#define StrDogW Additionals::String::strdogW
#define StrDogAW Additionals::String::strdogAW
#define StrDogA Additionals::String::strdogA
#define JoinW Additionals::Path::joinW
#define JoinA Additionals::Path::joinA

namespace Additionals {
	namespace Convectors {
		wchar_t* ConvertStringToWcharPtr(System::String^ str);

	}

	namespace String {
		wchar_t*& strdogW(wchar_t* ref_str, wchar_t* str_to_add);
		wchar_t*& strdogWA(wchar_t* ref_str, char* str_to_add);
		wchar_t*& strdogAW(char* ref_str, wchar_t* str_to_add);
		wchar_t*& strdogA(char* ref_str, char* str_to_add);

		wchar_t*& strdogW(std::initializer_list<wchar_t*> list);
	}

	namespace Path {
		wchar_t*& joinW(std::initializer_list<wchar_t*> list);
		wchar_t*& joinA(std::initializer_list<char*> list);
	}

	namespace TempFile {
		wchar_t* get_tempdir();
		wchar_t* get_tempdir_SYSTEM();
		wchar_t* _get_default_tempdir();
	}
}


#endif // !ADDITIONALS_H_

