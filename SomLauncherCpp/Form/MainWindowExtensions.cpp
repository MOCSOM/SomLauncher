#include "SomLauncherMainWindow.h"

void SomLauncherMainWindow::start_minecraft_params()
{

	std::cout << "Config loaded" << std::endl;
	std::cout << (*(*this->config_parce)["user"])["name"]->to_string() << std::endl;
	std::cout << (*(*this->config_parce)["user"])["memory"]->to_string() << std::endl;
	std::cout << (*(*this->config_parce)["user"])["mcdir"]->to_string() << std::endl;
	std::cout << (*(*this->config_parce)["user"])["online"]->to_string() << std::endl;
	std::cout << (*(*this->config_parce)["user"])["server"]->to_string() << std::endl;

	std::string java = "";
	std::string core = "";
	std::string version = "";

	char* appdata = nullptr;
	size_t appdata_sz = 0;

	_dupenv_s(&appdata, &appdata_sz, "APPDATA");

	std::string path_wch_java = DDIC::Download::Files::_get_java_path(Join({ appdata, ".SomSomSom" })) + "\\" + "bin" + "\\" + "java.exe";


	MinecraftCpp::option::MinecraftOptions options;
	options.customResolution = false;
	options.gameDirectory = this->minecraft_core_dir_path;
	options.launcherName = this->launcher_name;
	options.launcherVersion = this->launcher_version;
	options.username = this->username;
	options.jvmArguments = "-Xms1024M -Xmx" + std::to_string(8000) + "M";
	options.executablePath = path_wch_java;
	options.uuid = "uuu";
	options.token = "uuu";

	switch ((*(*this->config_parce)["user"])["server"]->to_int())
	{
	case 0:
	{
		java = (*(*(*servers_parce)["servers"])[0])["java"]->to_string();
		core = (*(*(*servers_parce)["servers"])[0])["core"]->to_string();
		version = (*(*(*servers_parce)["servers"])[0])["version"]->to_string();
		install_run_minecraft(version, core, (*(*(*this->servers_parce)["servers"])[0])["loaderVersion"]->to_string(), java, (*(*this->config_parce)["user"])["mcdir"]->to_string(), options);
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
	std::string java_dir = "";
	if (/*!DDIC::Download::Java::check_system_verison_java(java) ||*/ !DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path))
	{
		java_dir = DDIC::Download::Java::install(java, this->minecraft_core_dir_path);
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


	MinecraftCpp::forge::install_forge_version(install_version, this->minecraft_core_dir_path, new CallbackDict(), options.executablePath);
	std::string command = MinecraftCpp::get_minecraft_command__(launch_version, this->minecraft_core_dir_path, options);

	std::cout << command << std::endl;

	MinecraftCpp::start_minecraft("", command);
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


