#include "Config.h"

Config::Config(const std::filesystem::path& config_path)
	: config_path(config_path)
{
	std::ifstream ifstr(config_path);
	this->config_json = nlohmann::json::parse(ifstr);
	ifstr.close();
}

void Config::createConfig() const
{
	//{"user":{"name":"","password":"","memory":7168,"wight":854,"hight":480,"mcdir":"","isInstallMods":false,"server":0},"launcher":{"verison":""},"modpack":{}}
	//std::filesystem::copy(this->template_config_path, this->config_path, std::filesystem::copy_options::overwrite_existing);
	
	nlohmann::json template_config = nlohmann::json::parse(
		R"({"user":{"name":"","password":"","memory":7168,"wight":854,"hight":480,"mcdir":"","isInstallMods":false,"server":0},"launcher":{"verison":""},"modpack":{}})"
	);

	std::ofstream ofstr(this->config_path);
	ofstr << template_config.dump(4) << std::endl;
	ofstr.close();
}

bool Config::isConfigExist() const
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

void Config::checkAndCreateConfig() const
{
	if (!isConfigExist())
	{
		createConfig();
	}
}

nlohmann::json Config::getConfigJson()
{
	return this->config_json;
}
