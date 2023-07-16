#ifndef MINECRAFTUS_H_     // equivalently, #if !defined HEADER_H_
#define MINECRAFTUS_H_


#include "DownloadClasses.h"
#include "CallbackDict.h"
#include "Json.h"
#include <initializer_list>
//#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#define OS L"Windows"
#elif defined(__APPLE__)
#define OS L"Darwin"
#elif defined(__unix__) || defined(__unix)
#define OS L"Linux"
#else
#error unsupported platform
#endif

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
#define ARCH L"x64"
#else
#define ARCH L"x86"
#endif

namespace MCCL {

	namespace Option {
		struct MinecraftOptions
		{
			MinecraftOptions() {}
			~MinecraftOptions() {}

			wchar_t* username            = NULL;
			wchar_t* uuid                = NULL;
			wchar_t* token               = NULL;
			wchar_t* executablePath      = NULL;
			wchar_t* jvmArguments        = NULL;
			wchar_t* launcherName        = NULL;
			wchar_t* launcherVersion     = NULL;
			wchar_t* gameDirectory       = NULL;
			bool	 demo                = NULL;
			bool	 customResolution    = NULL;
			wchar_t* resolutionWidth     = NULL;
			wchar_t* resolutionHeight    = NULL;
			wchar_t* server              = NULL;
			wchar_t* port                = NULL;
			wchar_t* nativesDirectory    = NULL;
			bool	 enableLoggingConfig = NULL;
			wchar_t* classpath           = NULL;
			wchar_t* NULLES              = NULL;
			
			// get (поле, стандарт)
			wchar_t*& get(wchar_t* param, wchar_t* writ = NULL);
			bool get(wchar_t* param, bool writ = NULL, int a = 7);
			bool is_exist(wchar_t* param);
		};
	}


	wchar_t* get_minecraft_command__(
		wchar_t* version,
		wchar_t* minecraft_directory,
		MCCL::Option::MinecraftOptions options);

	bool start_minecraft(wchar_t* java_path = NULL, wchar_t* args = NULL);
	wchar_t* get_classpath_separator();
	bool parse_single_rule(Json::JsonValue^ rule, MCCL::Option::MinecraftOptions options);
	bool parse_rule_list(Json::JsonValue^ data, wchar_t* rule_string, MCCL::Option::MinecraftOptions options);
	wchar_t* get_library_path(wchar_t* name, wchar_t* path);
	wchar_t* get_natives(Json::JsonValue^ data);
	wchar_t* _get_jvm_platform_string();
	wchar_t* replace_arguments(System::String^ argstr, Json::JsonValue^ versionData, wchar_t* path, MCCL::Option::MinecraftOptions options);
	wchar_t* get_executable_path(wchar_t* jvm_version, wchar_t* minecraft_directory);
	bool install_libraries(Json::JsonValue^ data, wchar_t* path, CallbackNull callback);
	bool extract_natives_file(wchar_t* filename, wchar_t* extract_path, Json::JsonValue^ extract_data);
	bool install_assets(Json::JsonValue^ data, wchar_t* path, CallbackNull callback);
	bool install_jvm_runtime(wchar_t* jvm_version, wchar_t* minecraft_directory, CallbackNull callback = CallbackNull());
	namespace Forge {
		bool install_forge_version(wchar_t* versionid, wchar_t* path, CallbackNull callback = CallbackNull(), wchar_t* java = NULL);
		bool extract_file(System::IO::Compression::ZipArchive^ handler, wchar_t* zip_path, wchar_t* extract_path);
		System::String^ get_data_library_path(wchar_t* libname, wchar_t* path);
		wchar_t* get_jar_mainclass(wchar_t* path);
		
		bool forge_processors(
			Json::JsonValue^ data,
			wchar_t* minecraft_directory,
			wchar_t* lzma_path,
			wchar_t* installer_path,
			CallbackNull callback,
			wchar_t* java = NULL);
	}

	wchar_t* get_arguments(
		Json::JsonValue^ data,
		Json::JsonValue^ versionData,
		wchar_t* path,
		MCCL::Option::MinecraftOptions options);

	wchar_t* get_arguments_string(
		Json::JsonValue^ versionData,
		wchar_t* path,
		MCCL::Option::MinecraftOptions options);

	bool install_minecraft_version(
		wchar_t* versionid,
		wchar_t* minecraft_directory,
		CallbackNull callback = CallbackNull());

	bool do_version_install(
		wchar_t* versionid,
		wchar_t* path,
		CallbackNull callback,
		wchar_t* url = NULL);

	Json::JsonValue^ inherit_json(
		Json::JsonValue^ original_data,
		wchar_t* path);

	wchar_t* get_libraries(
		Json::JsonValue^ data,
		wchar_t* path);

	namespace ModPacks {
		bool install_mod_pack(wchar_t* versionid, wchar_t* path, CallbackNull callback = CallbackNull());

	}

	
}




#endif  /*MINECRAFTUS_H_*/