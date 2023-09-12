#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#include "ui_SettingsDialog.h"

#include "../../SomJsonLib/SomJson.h"
#include "../Minecraft/Minecraftus.h"

#include <string>

class SettingsDialog : public QDialog
{
	Q_OBJECT

private:
	Json::JsonValue account_data;

	MinecraftCpp::option::MinecraftOptions& option;

public:
	SettingsDialog(Json::JsonValue data, MinecraftCpp::option::MinecraftOptions& option, QWidget* parent = nullptr);
	~SettingsDialog();

	void setMemoryData(int min, int max, int recomended_value);
	void setCurretMemory(int value);

	void setStandartJavaPath(const std::string& new_path);
	void setStandartMinecraftPath(const std::string& new_path);

	void setJavaPath(const std::string& new_path);
	void setMinecraftPath(const std::string& new_path);

	int getMemoryValue();
	std::string getMinecraftPath();
	std::string getJavaPath();

	void setToDefault(const MinecraftCpp::option::MinecraftOptions& option, int memory);

	bool getReintsallModsState();

signals:
	void acceptButtonClicked();
signals:
	void setToDefaultButtonClicked();

private slots:
	void setMemoryLableValue(int value);

	void saveSettings();

	void reinstallModPackIsChecked();

private:
	Ui::SettingsDialog ui;
};

#endif /*SETTINGSDIALOG_H_*/