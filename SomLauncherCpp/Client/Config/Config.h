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
	Config() = default;
	~Config() = default;

public:
	void createConfig() const;
	bool isConfigExist() const;
	void checkAndCreateConfig() const;

public:
	static void saveJsonToFile(const nlohmann::json& json, const std::filesystem::path& file_path);
	void saveJsonToFile(const std::filesystem::path& file_path);
	void saveJsonToFile();

public:
	void reopenConfig();
	void reopenConfig(const std::filesystem::path& config_path);
	
public:
	nlohmann::json& json();

private:
	std::filesystem::path config_path;
	nlohmann::json config_json;
};

#endif // !CONFIG_CONFIG_H_