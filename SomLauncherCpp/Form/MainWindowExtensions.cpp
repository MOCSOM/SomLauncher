#include "SomLauncherMainWindow.h"

void SomLauncherMainWindow::start_minecraft_params()
{
	Json::JsonParcer json_config;
	Json::JsonValue* servers_parce = json_config.ParseFile(this->servers_json);
	Json::JsonValue* config_parce = json_config.ParseFile(this->config_path);

	std::cout << "Config loaded" << std::endl;
	std::cout << (*(*config_parce)["user"])["name"]->to_string() << std::endl;
	std::cout << (*(*config_parce)["user"])["memory"]->to_string() << std::endl;
	std::cout << (*(*config_parce)["user"])["mcdir"]->to_string() << std::endl;
	std::cout << (*(*config_parce)["user"])["online"]->to_string() << std::endl;
	std::cout << (*(*config_parce)["user"])["server"]->to_string() << std::endl;

	std::string java = "";
	std::string core = "";
	std::string version = "";

	char* appdata = nullptr;
	size_t appdata_sz = 0;

	_dupenv_s(&appdata, &appdata_sz, "APPDATA");

	std::string path_wch_java = DDIC::Download::Files::_get_java_path(JoinA({ appdata, ".SomSomSom" }).c_str()) + "\\" + "bin" + "\\" + "java.exe";


	MinecraftCpp::option::MinecraftOptions options;
	options.customResolution = false;
	options.gameDirectory = Additionals::Convectors::ConvertStringToWcharPtr(this->minecraft_core_dir_path);
	options.launcherName = Additionals::Convectors::ConvertStringToWcharPtr(this->launcher_name);
	options.launcherVersion = Additionals::Convectors::ConvertStringToWcharPtr(this->launcher_version);
	options.username = Additionals::Convectors::ConvertStringToWcharPtr(this->username);
	options.jvmArguments = StrDogW(L"-Xms1024M -Xmx", StrDogW(L"8000", L"M"));
	options.executablePath = Additionals::Convectors::ConvertStringToWcharPtr(path_wch_java);
	options.uuid = Additionals::Convectors::ConvertStringToWcharPtr("uuu");
	options.token = Additionals::Convectors::ConvertStringToWcharPtr("uuu");

	switch ((*(*config_parce)["user"])["server"]->to_int())
	{
	case 0:
	{
		java = (*(*(*servers_parce)["servers"])[0])["java"]->to_string();
		core = (*(*(*servers_parce)["servers"])[0])["core"]->to_string();
		version = (*(*(*servers_parce)["servers"])[0])["version"]->to_string();
		install_run_minecraft(version, core, (*(*(*servers_parce)["servers"])[0])["loaderVersion"]->to_string(), java, (*(*config_parce)["user"])["mcdir"]->to_string(), options);
	}
	//case 1:
	//{
	//	java = (*(*servers_parce)["java"])[1]->to_string();
	//	core = (*(*servers_parce)["core"])[1]->to_string();
	//	version = (*(*servers_parce)["version"])[0]->to_string();
	//	//install_run_Aeronautics(java, core, config_parce["user"]["mcdir"]->to_string());
	//}
	//case 2:
	//{
	//	java = (*(*servers_parce)["java"])[2]->to_string();
	//	core = (*(*servers_parce)["core"])[2]->to_string();
	//	version = (*(*servers_parce)["version"])[0]->to_string();
	//	//install_run_Vanilla(java, core, config_parce["user"]["mcdir"]->to_string());
	//}
	/*case 3:
		java = servers_parce["java"][3]->to_stringW();
		core = servers_parce["core"][3]->to_stringW();
		version = servers_parce["version"][0]->to_stringW();
		install_run_Olds(java, core, config_parce["user"]["mcdir"]->to_string());*/
	default:
	{
		break;
	}
	}
}

void SomLauncherMainWindow::install_run_minecraft(
	std::string version,
	std::string loader_mame,
	std::string loader_version,
	std::string java,
	std::string mcdir,
	MinecraftCpp::option::MinecraftOptions options)
{
	wchar_t* java_dir = NULL;
	if (/*!DDIC::Download::Java::check_system_verison_java(java) ||*/ !DDIC::Download::Java::check_downloaded_version_java(Additionals::Convectors::ConvertStringToWcharPtr(this->minecraft_core_dir_path)))
	{
		java_dir = DDIC::Download::Java::install(Additionals::Convectors::ConvertStringToWcharPtr(java), Additionals::Convectors::ConvertStringToWcharPtr(this->minecraft_core_dir_path));
		options.executablePath = java_dir;
	}
	else
	{
		java_dir = options.executablePath;
	}

	Json::JsonParcer parecer_modpack;
	Json::JsonValue* data_modpack = parecer_modpack.ParseFile(this->minecraft_core_dir_path);


	/* minecraft_version = 1.12.2 + "-" + forge_version = 14.23.5.2860 */
	//wchar_t* launch_varsion = L"1.12.2-forge-14.23.5.2860";

	std::string launch_version;
	std::string install_version;

	if (loader_mame == "forge" || loader_mame == "Forge")
	{
		launch_version = version + "-" + loader_mame + "-" + loader_version;
		install_version = version + "-" + loader_version;
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{

	}


	MinecraftCpp::forge::install_forge_version(Additionals::Convectors::ConvertStringToWcharPtr(install_version), Additionals::Convectors::ConvertStringToWcharPtr(this->minecraft_core_dir_path), CallbackNull(), options.executablePath);
	wchar_t* command = MinecraftCpp::get_minecraft_command__(Additionals::Convectors::ConvertStringToWcharPtr(launch_version), Additionals::Convectors::ConvertStringToWcharPtr(this->minecraft_core_dir_path), options);

	std::cout << command << std::endl;

	MinecraftCpp::start_minecraft(L"", command);
}

bool SomLauncherMainWindow::IsConfigExist()
{
	if (std::filesystem::exists(this->config_path))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SomLauncherMainWindow::CreateConfig()
{
	std::filesystem::copy("SOMCONFIG.json", this->config_path);
}


