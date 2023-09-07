#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(Json::JsonValue data, MinecraftCpp::option::MinecraftOptions& option, QWidget* parent)
	: QDialog(parent), option(option)
{
	ui.setupUi(this);

	account_data = data;

	QObject::connect(ui.horizontalSlider_memory, &QSlider::valueChanged, this, &SettingsDialog::setMemoryLableValue);

	QObject::connect(ui.okButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);

	QObject::connect(ui.okButton, &QPushButton::clicked, this, &SettingsDialog::acceptButtonClicked);
}

SettingsDialog::~SettingsDialog()
{
	//delete account_data;
}

void SettingsDialog::setMemoryData(int min, int max, int recomended_value)
{
	ui.label_min_memory->setText((std::to_string(min) + " Mb").c_str());
	ui.label_max_memory->setText((std::to_string(max) + " Mb").c_str());

	ui.horizontalSlider_memory->setMinimum(min);
	ui.horizontalSlider_memory->setMaximum(max);
	ui.horizontalSlider_memory->setValue(recomended_value);
	ui.horizontalSlider_memory->setPivotalValue(recomended_value);
}

void SettingsDialog::setCurretMemory(int value)
{
	ui.horizontalSlider_memory->setValue(value);
}

void SettingsDialog::setStandartJavaPath(const std::string& new_path)
{
	ui.lineEdit_java_path->setPlaceholderText(new_path.c_str());
}

void SettingsDialog::setStandartMinecraftPath(const std::string& new_path)
{
	ui.lineEdit_game_path->setPlaceholderText(new_path.c_str());
}

int SettingsDialog::getMemoryValue()
{
	return ui.horizontalSlider_memory->value();
}

std::string SettingsDialog::getMinecraftPath()
{
	return ui.lineEdit_game_path->text().toStdString();
}

std::string SettingsDialog::getJavaPath()
{
	return ui.lineEdit_java_path->text().toStdString();
}

void SettingsDialog::saveSettings()
{
	if (ui.lineEdit_game_path->text().toStdString() != "")
	{
		this->option.gameDirectory = ui.lineEdit_game_path->text().toStdString();
	}
	if (ui.lineEdit_java_path->text().toStdString() != "")
	{
		this->option.executablePath = ui.lineEdit_java_path->text().toStdString();
	}
}

void SettingsDialog::setMemoryLableValue(int value)
{
	ui.label_memory_count->setText((std::to_string(value) + " Mb").c_str());
}