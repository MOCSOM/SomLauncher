#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(Json::JsonValue* data, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	account_data = data;

	

	QObject::connect(ui.horizontalSlider_memory, &QSlider::valueChanged, this, &SettingsDialog::setMemoryLableValue);

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

void SettingsDialog::setStandartJavaPath(const std::string& new_path)
{
	ui.lineEdit_java_path->setPlaceholderText(new_path.c_str());
}

void SettingsDialog::setStandartMinecraftPath(const std::string& new_path)
{
	ui.lineEdit_game_path->setPlaceholderText(new_path.c_str());
}

void SettingsDialog::updateMinecraftPath()
{
	QString newData = ui.lineEdit_game_path->text();
	emit minecraftPathChanged(newData);
}

void SettingsDialog::updateJavaPath()
{
	QString newData = ui.lineEdit_java_path->text();
	emit javaPathChanged(newData);
}

void SettingsDialog::setMemoryLableValue(int value)
{
	ui.label_memory_count->setText((std::to_string(value) + " Mb").c_str());
}

