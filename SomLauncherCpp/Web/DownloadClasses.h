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
#include <fstream>

#include <curl/curl.h>
#include <lzma.h>

//#include <vcclr.h>

//#include <atlstr.h>

#include "../Callbacks/CallbackDict.h"
#include "../Additionals/Additionals.h"
#include "../Archives/Archives.h"
#include "../Encryption/Hashes/sha1.h"
#include "../Encryption/LZMA/LzmaDecompress.h"
#include "Download/Download.h"

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

/* read/write buffer sizes */
#define IN_BUF_MAX  409600
#define OUT_BUF_MAX 409600
/* analogous to xz CLI options: -0 to -9 */
#define COMPRESSION_LEVEL 7

/* boolean setting, analogous to xz CLI option: -e */
#define COMPRESSION_EXTREME true

//#define DownloadFile DDIC::Download::Files::download_file
#define DownloadFile web::download::downloadFile

namespace DDIC
{
	namespace Download
	{
		namespace Files
		{
			//bool _CreateDirectoryIfNotExists(const std::wstring& path);

			//inline std::string download_file(const std::string& s_url, const std::string& d_file = "", CallbackNull* callback = new CallbackNull(), const std::string& sha1 = "", bool lzma_compressed = false);
			std::string download_file(const std::string& s_url, const std::string& d_file = "", CallbackNull* callback = new CallbackNull(), const std::string& sha1 = "", bool lzma_compressed = false);
			int _get_java_exist_ver(const std::string& direct);
			std::vector<std::pair<std::filesystem::path, std::string>> _get_java_path(const std::filesystem::path& dir);
			std::filesystem::path getInstalledJavaInDirectory(std::filesystem::path directory_path = "", int version = 0);
			//bool delete_file();
			//bool delete_all_files();
			//bool delete_repos();

			//bool _check_hash();
			//void set_hash(System::String^ FilePath, int index);

			CURLcode download(CURL* curl, const std::string& s_url, const std::string& d_file = "", CallbackNull* callback = new CallbackNull());
			size_t write_data(char* ptr, size_t size, size_t nmemb, void* userdata);
			int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
		}
		namespace Java
		{
			std::filesystem::path install(
				const std::string& version,
				const std::filesystem::path& path = "",
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

			std::filesystem::path _decompress_archive(
				const std::filesystem::path& repo_root,
				const std::string& file_ending,
				const std::filesystem::path& destination_folder);

			bool check_system_verison_java(const std::string& java);
			bool check_downloaded_version_java(const std::filesystem::path& path, const std::string& java);

			std::string _get_normalized_compressed_file_ext(const std::filesystem::path& file);
			std::string normalize_version(const std::string& version);
			std::string expand_user(std::string path);
		}
	}
}

#endif //DWLD_H_
