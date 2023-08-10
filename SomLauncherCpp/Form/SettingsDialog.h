#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#include "ui_SettingsDialog.h"

#include "../Json/Json.h"

#include <string>

class SettingsDialog : public QDialog
{
	Q_OBJECT
		
private:
	Json::JsonValue* account_data;

public:
	SettingsDialog(Json::JsonValue* data, QWidget* parent = nullptr);
	~SettingsDialog();

	void setMemoryData(int min, int max, int recomended_value);

	void setStandartJavaPath(const std::string& new_path);
	void setStandartMinecraftPath(const std::string& new_path);

	void updateMinecraftPath();
	void updateJavaPath();

private slots:
	void setMemoryLableValue(int value);

signals:
	void minecraftPathChanged(const QString& data);
signals:
	void javaPathChanged(const QString& data);

private:
	Ui::SettingsDialog ui;
};

#endif /*SETTINGSDIALOG_H_*/