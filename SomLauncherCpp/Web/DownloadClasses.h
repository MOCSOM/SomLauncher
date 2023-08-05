#ifndef DWLD_H_     // equivalently, #if !defined HEADER_H_
#define DWLD_H_

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <sys/stat.h>
#include <cstdio>
#include <initializer_list>

#include <filesystem>
#include <string>
#include <memory>
#include <urlmon.h>


//#include <vcclr.h>

//#include <atlstr.h>

#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "User32.lib")

#include "../Callbacks/CallbackDict.h"
#include "../Additionals/Additionals.h"

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
#define _JRE_DIR _USER_DIR + std::string("\\") + std::string(".jre")
#define _JDK_DIR _USER_DIR + std::string("\\") + std::string(".jdk")

#define _TAR ".tar"
#define _TAR_GZ ".tar.gz"
#define _ZIP ".zip"
#define _SEVEN_ZIP ".7z"

#define DownloadFile DDIC::Download::Files::download_file

namespace DDIC 
{
	namespace Download 
	{
		namespace Files 
		{
			//bool _CreateDirectoryIfNotExists(const std::wstring& path);

			std::wstring download_file(const wchar_t* s_url, const wchar_t* d_file = nullptr, CallbackNull* callback = new CallbackNull(), bool lzma_compressed = false);
			bool download_all_files(wchar_t* s_url_dir, CallbackNull callback);
			int _get_java_exist_ver(wchar_t* direct);
			std::string _get_java_path(const wchar_t* dir);
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
				wchar_t* operating_system = const_cast<wchar_t*>(OS),
				wchar_t* arch = const_cast<wchar_t*>(ARCH),
				wchar_t* impl = const_cast<wchar_t*>(L"hotspot"),
				bool jre = false);

			wchar_t* get_download_url(
				/*wchar_t*& uru,*/
				wchar_t* version,
				wchar_t* operating_system = const_cast<wchar_t*>(OS),
				wchar_t* arch = const_cast<wchar_t*>(ARCH),
				wchar_t* impl = const_cast<wchar_t*>(L"hotspot"),
				bool jre = false);

			wchar_t* _decompress_archive(
				const wchar_t* repo_root,
				wchar_t* file_ending,
				wchar_t* destination_folder);

			bool check_system_verison_java(wchar_t* version);
			bool check_downloaded_version_java(wchar_t* path);

			std::string _get_normalized_compressed_file_ext(const wchar_t* file);
			wchar_t* normalize_version(wchar_t* version);
			std::string expand_user(std::string path);
		}
	}
}


#endif //DWLD_H_

