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

	

	switch ((*(*this->config_parce)["user"])["server"]->to_int())
	{
	case 0:
	{
		java = (*(*(*servers_parce)["servers"])[0])["java"]->to_string();
		core = (*(*(*servers_parce)["servers"])[0])["core"]->to_string();
		version = (*(*(*servers_parce)["servers"])[0])["version"]->to_string();
		install_run_minecraft(version, core, (*(*(*this->servers_parce)["servers"])[0])["loaderVersion"]->to_string(), java, (*(*this->config_parce)["user"])["mcdir"]->to_string(), this->options);
		break;
	}
	case 1:
	{
		java = (*(*(*servers_parce)["servers"])[1])["java"]->to_string();
		core = (*(*(*servers_parce)["servers"])[1])["core"]->to_string();
		version = (*(*(*servers_parce)["servers"])[1])["version"]->to_string();
		install_run_minecraft(version, core, (*(*(*this->servers_parce)["servers"])[1])["loaderVersion"]->to_string(), java, (*(*this->config_parce)["user"])["mcdir"]->to_string(), this->options);
		break;
	}
	//case 2:
	//{
	//	java = (*(*servers_parce)["java"])[2]->to_string();
	//	core = (*(*servers_parce)["core"])[2]->to_string();
	//	version = (*(*servers_parce)["version"])[0]->to_string();
	//	//install_run_Vanilla(java, core, config_parce["user"]["mcdir"]->to_string());
	//	break;
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
	if (!DDIC::Download::Java::check_system_verison_java(java))
	{
		if (!DDIC::Download::Java::check_downloaded_version_java(this->minecraft_core_dir_path, java))
		{
			java_dir = DDIC::Download::Java::install(java, this->minecraft_core_dir_path);
			options.executablePath = java_dir + "\\" + "bin" + "\\" + "java.exe";
		}
		else
		{
			for (auto& var : DDIC::Download::Files::_get_java_path(this->minecraft_core_dir_path))
			{
				if (var.second == java)
				{
					options.executablePath = var.first + "\\" + "bin" + "\\" + "java.exe";
				}
			}

		}
	}
	else
	{
		char* program_files = nullptr;
		size_t program_files_sz = 0;
		_dupenv_s(&program_files, &program_files_sz, "ProgramFiles");

		for (auto& var : DDIC::Download::Files::_get_java_path(std::string(program_files == nullptr ? "" : program_files) + '\\' + "java"))
		{
			if (var.second == java)
			{
				options.executablePath = var.first + "\\" + "bin" + "\\" + "java.exe";
			}
		}
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
		MinecraftCpp::forge::install_forge_version(install_version, this->minecraft_core_dir_path, new CallbackDict(), options.executablePath);
	}
	else if (loader_mame == "fabric" || loader_mame == "Fabric")
	{
		launch_version = std::string("fabric") + "-" + "loader" + "-" + loader_version + "-" + version;
		MinecraftCpp::fabric::install_fabric_version(version, this->minecraft_core_dir_path, loader_version, new CallbackDict(), options.executablePath);
	}


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

void SomLauncherMainWindow::configureOptions()
{
	char* appdata = nullptr;
	size_t appdata_sz = 0;

	_dupenv_s(&appdata, &appdata_sz, "APPDATA");

	//std::string path_wch_java = DDIC::Download::Files::_get_java_path(Join({ appdata == nullptr ? "" : appdata, ".SomSomSom" })).first + "\\" + "bin" + "\\" + "java.exe";

	this->options.customResolution = false;
	this->options.gameDirectory = this->minecraft_core_dir_path;
	this->options.launcherName = this->launcher_name;
	this->options.launcherVersion = this->launcher_version;
	this->options.username = this->username;
	this->options.jvmArguments = "-Xms1024M -Xmx" + std::to_string(8000) + "M";
	this->options.executablePath = "";
	this->options.uuid = "uuu";
	this->options.token = "uuu";
}


