#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include <filesystem>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

class Config
{
public:
	Config(const std::filesystem::path& config_path);
	~Config() = default;

public:
	void createConfig() const;
	bool isConfigExist() const;
	void checkAndCreateConfig() const;
	
public:
	nlohmann::json getConfigJson();

private:
	std::filesystem::path config_path;
	nlohmann::json config_json;
};

#endif // !CONFIG_CONFIG_H_