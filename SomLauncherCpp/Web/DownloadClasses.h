﻿#ifndef DWLD_H_     // equivalently, #if !defined HEADER_H_
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
#include "../../SomAdditionalsLib/Additionals.h"
#include "../Archives.h"

#if defined(_WIN32) || defined(_WIN64)
const std::string OS = "windows";
#elif defined(__APPLE__)
const std::string OS "mac"
#elif defined(__unix__) || defined(__unix)
const std::string OS "linux"
#else
#error unsupported platform
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
const std::string ARCH = "x64";
#else
const std::string ARCH "x86"
#endif

#if defined(_WIN32) || defined(_WIN64)
const std::string _UNPACK200 = "unpack200.exe";
#else
const std::string _UNPACK200 "unpack200"
#endif

#if defined(_WIN32) || defined(_WIN64)
const std::string _UNPACK200_ARGS = R"(-r -v -l "")";
#else
const std::string _UNPACK200_ARGS ""
#endif

#define _USER_DIR DDIC::Download::Java::expand_user("~")
#define _JRE_DIR _USER_DIR + "\\" + ".jre"
#define _JDK_DIR _USER_DIR + "\\" + ".jdk"

const std::string _TAR = ".tar";
const std::string _TAR_GZ = ".tar.gz";
const std::string _ZIP = ".zip";
const std::string _SEVEN_ZIP = ".7z";

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
			std::vector<std::pair<std::string, std::string>> _get_java_path(const std::string& dir);
			std::string getInstalledJavaInDirectory(std::string directory_path = "", int version = 0);
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
				CallbackNull* callback = new CallbackNull(),
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

			bool check_system_verison_java(const std::string& java);
			bool check_downloaded_version_java(const std::string& path, const std::string& java);

			std::string _get_normalized_compressed_file_ext(const std::string& file);
			std::string normalize_version(const std::string& version);
			std::string expand_user(std::string path);
		}
	}
}

#endif //DWLD_H_
