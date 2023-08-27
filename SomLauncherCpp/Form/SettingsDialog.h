#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#include "ui_SettingsDialog.h"

#include "../Json/Json.h"
#include "../Minecraft/Minecraftus.h"

#include <string>

class SettingsDialog : public QDialog
{
	Q_OBJECT
		
private:
	Json::JsonValue* account_data;

	MinecraftCpp::option::MinecraftOptions& option;

public:
	SettingsDialog(Json::JsonValue* data, MinecraftCpp::option::MinecraftOptions& option, QWidget* parent = nullptr);
	~SettingsDialog();

	void setMemoryData(int min, int max, int recomended_value);
	void setCurretMemory(int value);

	void setStandartJavaPath(const std::string& new_path);
	void setStandartMinecraftPath(const std::string& new_path);

	int getMemoryValue();
	std::string getMinecraftPath();
	std::string getJavaPath();

signals:
	void acceptButtonClicked();

private slots:
	void setMemoryLableValue(int value);

	void saveSettings();

private:
	Ui::SettingsDialog ui;
};

#endif /*SETTINGSDIALOG_H_*/