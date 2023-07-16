#include "MainForm.h"

void SomLauncherMainWin::MainForm::start_minecraft_params()
{
	System::Console::WriteLine("Config loaded");

	Json::JsonParcer json_config;
	Json::JsonValue^ config_parce = json_config.ParseFile(System::String(this->config_path).ToString());
	Json::JsonValue^ servers_parce = json_config.ParseFile(System::String(this->servers_json).ToString());

	System::Console::WriteLine(config_parce["user"]["name"]->to_string());
	System::Console::WriteLine(config_parce["user"]["memory"]->to_string());
	System::Console::WriteLine(config_parce["user"]["mcdir"]->to_string());
	System::Console::WriteLine(config_parce["user"]["online"]->to_string());
	System::Console::WriteLine(config_parce["user"]["server"]->to_string());

	System::String^ java = "";
	System::String^ core = "";
	System::String^ version = "";
	pin_ptr<const wchar_t> path_wch_java = PtrToStringChars(DDIC::Download::Files::_get_java_path(JoinA({ getenv("APPDATA"), ".SomSomSom" })) + "\\" + "bin" + "\\" + "java.exe");

	MCCL::Option::MinecraftOptions options;
	options.customResolution = false;
	options.gameDirectory = this->minecraft_core_dir_path;
	options.launcherName = this->launcher_name;
	options.launcherVersion = this->launcher_version;
	options.username = this->username;
	options.jvmArguments = StrDogW(L"-Xms1024M -Xmx", StrDogW(L"8000", L"M"));
	options.executablePath = const_cast<wchar_t*>(path_wch_java);
	options.uuid = L"uuu";
	options.token = L"uuu";

	switch (config_parce["user"]["server"]->to_int())
	{
	case 0:
		java = servers_parce["java"][0]->to_string();
		core = servers_parce["core"][0]->to_string();
		version = servers_parce["version"][0]->to_string();
		install_run_minecraft(version, core, servers_parce["loaderVersion"][0]->to_string(), java, config_parce["user"]["mcdir"]->to_string(), options);
	case 1:
		java = servers_parce["java"][1]->to_string();
		core = servers_parce["core"][1]->to_string();
		version = servers_parce["version"][0]->to_string();
		//install_run_Aeronautics(java, core, config_parce["user"]["mcdir"]->to_string());
	case 2:
		java = servers_parce["java"][2]->to_string();
		core = servers_parce["core"][2]->to_string();
		version = servers_parce["version"][0]->to_string();
		//install_run_Vanilla(java, core, config_parce["user"]["mcdir"]->to_string());
	/*case 3:
		java = servers_parce["java"][3]->to_stringW();
		core = servers_parce["core"][3]->to_stringW();
		version = servers_parce["version"][0]->to_stringW();
		install_run_Olds(java, core, config_parce["user"]["mcdir"]->to_string());*/
	default:
		break;
	}
}

void SomLauncherMainWin::MainForm::install_run_minecraft(System::String^ version, System::String^ loader_mame, System::String^ loader_version, System::String^ java, System::String^ mcdir, MCCL::Option::MinecraftOptions options)
{
	wchar_t* java_dir = NULL;
	if (/*!DDIC::Download::Java::check_system_verison_java(java) ||*/ !DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path))
	{
		pin_ptr<const wchar_t> wch_java = PtrToStringChars(java);
		java_dir = DDIC::Download::Java::install(const_cast<wchar_t*>(wch_java), this->minecraft_core_dir_path);
		options.executablePath = java_dir;
	}
	else
	{
		java_dir = options.executablePath;
	}

	Json::JsonParcer parecer_modpack;
	Json::JsonValue^ data_modpack = parecer_modpack.ParseFile(this->minecraft_core_dir_path);


	/* minecraft_version = 1.12.2 + "-" + forge_version = 14.23.5.2860 */
	//wchar_t* launch_varsion = L"1.12.2-forge-14.23.5.2860";

	System::String^ launch_version;
	System::String^ install_version;

	if (loader_mame == "forge" || loader_mame == "Forge")
	{
		launch_version = version + '-' + loader_mame + '-' + loader_version;
		install_version = version + '-' + loader_version;
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{

	}

	pin_ptr<const wchar_t> wch_launch_version = PtrToStringChars(launch_version);
	pin_ptr<const wchar_t> wch_install_version = PtrToStringChars(install_version);

	MCCL::Forge::install_forge_version(const_cast<wchar_t*>(wch_install_version), this->minecraft_core_dir_path, CallbackNull(), options.executablePath);
	wchar_t* command = MCCL::get_minecraft_command__(const_cast<wchar_t*>(wch_launch_version), this->minecraft_core_dir_path, options);
	System::Console::WriteLine(System::String(command).ToString());

	MCCL::start_minecraft(L"", command);
}