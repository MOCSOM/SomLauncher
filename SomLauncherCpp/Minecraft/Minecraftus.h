#ifndef MINECRAFTUS_H_     // equivalently, #if !defined HEADER_H_
#define MINECRAFTUS_H_

#include "../Web/DownloadClasses.h"
#include "../Callbacks/CallbackDict.h"
#include "../Json/Json.h"
#include "../Additionals/Additionals.h"
#include <initializer_list>
//#include <stdio.h>

#include <filesystem>

#include "../qzipreader_p.h"
#include "../qzipwriter_p.h" 

#include <qdir.h>


namespace MinecraftCpp 
{
	namespace option 
	{
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
			wchar_t* get(const wchar_t* param, const wchar_t* writ = NULL);
			bool get(const wchar_t* param, bool writ = NULL);
			bool is_exist(wchar_t* param);
		};
	}


	std::wstring get_minecraft_command__(
		wchar_t* version,
		wchar_t* minecraft_directory,
		MinecraftCpp::option::MinecraftOptions options);

	bool start_minecraft(const wchar_t* java_path = NULL, const wchar_t* args = NULL);
	wchar_t* get_classpath_separator();
	bool parse_single_rule(Json::JsonValue* rule, MinecraftCpp::option::MinecraftOptions options);
	bool parse_rule_list(Json::JsonValue* data, const wchar_t* rule_string, MinecraftCpp::option::MinecraftOptions options);
	wchar_t* get_library_path(wchar_t* name, wchar_t* path);
	wchar_t* get_natives(Json::JsonValue* data);
	wchar_t* _get_jvm_platform_string();
	std::string replace_arguments(std::string argstr, Json::JsonValue* versionData, wchar_t* path, MinecraftCpp::option::MinecraftOptions options);
	wchar_t* get_executable_path(wchar_t* jvm_version, wchar_t* minecraft_directory);
	bool install_libraries(Json::JsonValue* data, wchar_t* path, CallbackNull* callback);
	bool extract_natives_file(wchar_t* filename, wchar_t* extract_path, Json::JsonValue* extract_data);
	bool install_assets(Json::JsonValue* data, wchar_t* path, CallbackNull* callback);
	bool install_jvm_runtime(wchar_t* jvm_version, wchar_t* minecraft_directory, CallbackNull* callback = new CallbackNull());

	namespace forge 
	{
		bool install_forge_version(wchar_t* versionid, wchar_t* path, CallbackNull* callback = new CallbackNull(), wchar_t* java = NULL);
		bool extract_file(const QZipReader& handler, const wchar_t* zip_path, const wchar_t* extract_path);
		std::string get_data_library_path(wchar_t* libname, wchar_t* path);
		wchar_t* get_jar_mainclass(wchar_t* path);
		
		bool forge_processors(
			Json::JsonValue* data,
			wchar_t* minecraft_directory,
			wchar_t* lzma_path,
			wchar_t* installer_path,
			CallbackNull* callback,
			wchar_t* java);
	}

	wchar_t* get_arguments(
		Json::JsonValue* data,
		Json::JsonValue* versionData,
		wchar_t* path,
		MinecraftCpp::option::MinecraftOptions options);

	std::string get_arguments_string(
		Json::JsonValue* versionData,
		wchar_t* path,
		MinecraftCpp::option::MinecraftOptions options);

	bool install_minecraft_version(
		wchar_t* versionid,
		wchar_t* minecraft_directory,
		CallbackNull* callback = new CallbackNull());

	bool do_version_install(
		wchar_t* versionid,
		wchar_t* path,
		CallbackNull* callback,
		wchar_t* url = NULL);

	Json::JsonValue* inherit_json(
		Json::JsonValue* original_data,
		wchar_t* path);

	wchar_t* get_libraries(
		Json::JsonValue* data,
		wchar_t* path);




}




#endif  /*MINECRAFTUS_H_*/