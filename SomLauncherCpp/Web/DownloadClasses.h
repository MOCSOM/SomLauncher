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
#define OS "windows"
#elif defined(__APPLE__)
#define OS "mac"
#elif defined(__unix__) || defined(__unix)
#define OS "linux"
#else
#error unsupported platform
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
#define ARCH "x64"
#else
#define ARCH "x86"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define _UNPACK200 "unpack200.exe"
#else
#define _UNPACK200 "unpack200"
#endif

#if defined(_WIN32) || defined(_WIN64)
#define _UNPACK200_ARGS R"(-r -v -l "")"
#else
#define _UNPACK200_ARGS ""
#endif

#define _USER_DIR DDIC::Download::Java::expand_user("~")
#define _JRE_DIR _USER_DIR + "\\" + ".jre"
#define _JDK_DIR _USER_DIR + "\\" + ".jdk"

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

			std::string download_file(const std::string& s_url, const std::string& d_file = "", CallbackNull* callback = new CallbackNull(), bool lzma_compressed = false);
			bool download_all_files(const std::string& s_url_dir, CallbackNull callback);
			int _get_java_exist_ver(const std::string& direct);
			std::string _get_java_path(const std::string& dir);
			//bool delete_file();
			//bool delete_all_files();
			//bool delete_repos();

			//bool _check_hash();
			//void set_hash(System::String^ FilePath, int index);
		}
		namespace Java {
			std::string install(
				const std::string& version,
				const std::string& path = "",
				const std::string& operating_system = OS,
				const std::string& arch = ARCH,
				const std::string& impl = "hotspot",
				bool jre = false);

			std::string get_download_url(
				/*wchar_t*& uru,*/
				const std::string& version,
				const std::string& operating_system = OS,
				const std::string& arch = ARCH,
				const std::string& impl = "hotspot",
				bool jre = false);

			std::string _decompress_archive(
				const std::string& repo_root,
				const std::string& file_ending,
				const std::string& destination_folder);

			bool check_system_verison_java(const std::string& version);
			bool check_downloaded_version_java(const std::string& path);

			std::string _get_normalized_compressed_file_ext(const std::string& file);
			std::string normalize_version(const std::string& version);
			std::string expand_user(std::string path);
		}
	}
}


#endif //DWLD_H_

