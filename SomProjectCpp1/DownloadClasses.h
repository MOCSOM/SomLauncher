#ifndef DWLD_H_     // equivalently, #if !defined HEADER_H_
#define DWLD_H_

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <sys/stat.h>
#include <cstdio>
#include <initializer_list>

#include <vcclr.h>

//#include <atlstr.h>

#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "User32.lib")

#include "CallbackDict.h"
//#include "Additionals.h"

#if defined(_WIN32) || defined(_WIN64)
#define OS L"windows"
#elif defined(__APPLE__)
#define OS L"mac"
#elif defined(__unix__) || defined(__unix)
#define OS L"linux"
#else
#error unsupported platform
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
#define ARCH L"x64"
#else
#define ARCH L"x86"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define _UNPACK200 L"unpack200.exe"
#else
#define _UNPACK200 L"unpack200"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define _UNPACK200_ARGS LR"(-r -v -l "")"
#else
#define _UNPACK200_ARGS L""
#endif

#define _USER_DIR DDIC::Download::Java::expand_user("~")
#define _JRE_DIR _USER_DIR + System::String(L"\\").ToString() + System::String(L".jre").ToString();
#define _JDK_DIR _USER_DIR + System::String(L"\\").ToString() + System::String(L".jdk").ToString();

#define _TAR L".tar"
#define _TAR_GZ L".tar.gz"
#define _ZIP L".zip"
#define _SEVEN_ZIP L".7z"

#define StrDogWA DDIC::strdogWA
#define StrDogW DDIC::strdogW
#define StrDogAW DDIC::strdogAW
#define StrDogA DDIC::strdogA
#define JoinW DDIC::Path::joinW
#define JoinA DDIC::Path::joinA

#define GetTempPath System::IO::Path::GetTempPath

#define DownloadFile DDIC::Download::Files::download_file

namespace DDIC {
	wchar_t*& strdogW(wchar_t* ref_str, wchar_t* str_to_add);
	wchar_t*& strdogWA(wchar_t* ref_str, char* str_to_add);
	wchar_t*& strdogAW(char* ref_str, wchar_t* str_to_add);
	wchar_t*& strdogA(char* ref_str, char* str_to_add);

	wchar_t*& strdogW(std::initializer_list<wchar_t*> list);

	namespace Path {
		wchar_t*& joinW(std::initializer_list<wchar_t*> list);
		wchar_t*& joinA(std::initializer_list<char*> list);
	}

	namespace TempFile {
		wchar_t* get_tempdir();
		wchar_t* get_tempdir_SYSTEM();
		wchar_t* _get_default_tempdir();
	}

	namespace Download {
		namespace Files {
			wchar_t* download_file(wchar_t* s_url, wchar_t* d_file = NULL, CallbackNull &callback = CallbackNull(), bool lzma_compressed = false);
			bool download_all_files(wchar_t* s_url_dir, CallbackNull callback);
			int _get_java_exist_ver(wchar_t* direct);
			System::String^ _get_java_path(wchar_t* dir);
			//bool delete_file();
			//bool delete_all_files();
			//bool delete_repos();

			//bool _check_hash();
			//void set_hash(System::String^ FilePath, int index);
		}
		namespace Java {
			wchar_t* install(
				wchar_t* version,
				wchar_t* path = NULL,
				wchar_t* operating_system = OS,
				wchar_t* arch = ARCH,
				wchar_t* impl = L"hotspot",
				bool jre = false);

			wchar_t*& get_download_url(
				/*wchar_t*& uru,*/
				wchar_t* version,
				wchar_t* operating_system = OS,
				wchar_t* arch = ARCH,
				wchar_t* impl = L"hotspot",
				bool jre = false);

			wchar_t* _decompress_archive(
				wchar_t* repo_root,
				wchar_t* file_ending,
				wchar_t* destination_folder);

			bool check_system_verison_java(wchar_t* version);
			bool check_downloaded_version_java(wchar_t* path);

			wchar_t* _get_normalized_compressed_file_ext(wchar_t* file);
			wchar_t* normalize_version(wchar_t* version);
			System::String^ expand_user(System::String^ path);
		}
	}
}


#endif //DWLD_H_

