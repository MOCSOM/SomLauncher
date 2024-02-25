#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#include "ui_SettingsDialog.h"

#include <string>

#include <nlohmann/json.hpp>

#include "../Minecraft/Minecraftus.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT

private:
	nlohmann::json account_data;
	std::filesystem::path config_path;

	MinecraftCpp::option::MinecraftOptions& option;

public:
	explicit SettingsDialog(nlohmann::json data, MinecraftCpp::option::MinecraftOptions& option, QWidget* parent = nullptr);
	~SettingsDialog();

	void setMemoryData(int min, int max, int recomended_value);
	void setCurretMemory(int value);

	void setStandartJavaPath(const std::filesystem::path& new_path);
	void setStandartMinecraftPath(const std::filesystem::path& new_path);

	void setJavaPath(const std::string& new_path);
	void setMinecraftPath(const std::string& new_path);

	void setConfigPath(const std::filesystem::path& config_path);

	int getMemoryValue();
	std::filesystem::path getMinecraftPath();
	std::string getJavaPath();

	void setToDefault(const MinecraftCpp::option::MinecraftOptions& option, int memory);

	bool getReintsallModsState();

	std::filesystem::path getPathFromWindowSelector(
		const QFileDialog::FileMode& type = QFileDialog::FileMode::AnyFile,
		const QFileDialog::Option& option = QFileDialog::Option::DontConfirmOverwrite,
		const QList<QString>& file_types_display = {});

signals:
	void acceptButtonClicked();
signals:
	void setToDefaultButtonClicked();
signals:
	void reinstallMods(bool state);
signals:
	void logoutSignal();
signals:
	void changedMinecraftPathSignal(const std::filesystem::path& path);

private slots:
	void setMemoryLableValue(int value);

	void saveSettings();

	void reinstallModPackIsChecked();

	void onClickToolBotton_getminecraft_core();
	void onClickToolBotton_getjava_path();
	void onClickPushButtonLogoutFromAccount();

private:
	Ui::SettingsDialog ui;
};

#endif /*SETTINGSDIALOG_H_*/