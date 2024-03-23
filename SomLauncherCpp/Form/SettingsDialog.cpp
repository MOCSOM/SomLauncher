#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(nlohmann::json data, MinecraftCpp::option::MinecraftOptions& option, QWidget* parent)
	: QDialog(parent), option(option)
{
	ui.setupUi(this);

	this->account_data = data;

	ui.label_account_name->setText(this->account_data["username"].template get<std::string>().c_str());

	ui.label_modreinstall_notifiy->setStyleSheet("#label_modreinstall_notifiy{color: rgb(255, 0, 0);}");

	QPalette palette = ui.label_modreinstall_notifiy->palette();
	palette.setColor(ui.label_modreinstall_notifiy->backgroundRole(), Qt::red);
	palette.setColor(ui.label_modreinstall_notifiy->foregroundRole(), Qt::red);
	ui.label_modreinstall_notifiy->setPalette(palette);

	ui.label_modreinstall_notifiy->setHidden(true);

	ui.label_launcher_version->setText(getApplicationVersion().c_str());

	QObject::connect(ui.horizontalSlider_memory, &QSlider::valueChanged, this, &SettingsDialog::setMemoryLableValue);

	QObject::connect(ui.okButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);

	QObject::connect(ui.okButton, &QPushButton::clicked, this, &SettingsDialog::acceptButtonClicked);

	QObject::connect(ui.pushButton_toDefault, &QPushButton::clicked, this, &SettingsDialog::setToDefaultButtonClicked);

	QObject::connect(ui.checkBox_reinstall_modpack, &QPushButton::clicked, this, &SettingsDialog::reinstallModPackIsChecked);

	QObject::connect(ui.toolButton_game_path, &QToolButton::clicked, this, &SettingsDialog::onClickToolBotton_getminecraft_core);
	QObject::connect(ui.toolButton_java_path, &QToolButton::clicked, this, &SettingsDialog::onClickToolBotton_getjava_path);

	QObject::connect(ui.pushButton_exit_account, &QToolButton::clicked, this, &SettingsDialog::onClickPushButtonLogoutFromAccount);
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

void SettingsDialog::setStandartJavaPath(const std::filesystem::path& new_path)
{
	ui.lineEdit_java_path->setPlaceholderText(new_path.u8string().c_str());
}

void SettingsDialog::setStandartMinecraftPath(const std::filesystem::path& new_path)
{
	ui.lineEdit_game_path->setPlaceholderText(new_path.u8string().c_str());
}

void SettingsDialog::setJavaPath(const std::string& new_path)
{
	ui.lineEdit_java_path->setText(new_path.c_str());
}

void SettingsDialog::setMinecraftPath(const std::string& new_path)
{
	ui.lineEdit_game_path->setText(new_path.c_str());
}

void SettingsDialog::setConfigPath(const std::filesystem::path& config_path)
{
	this->config_path = config_path;
}

int SettingsDialog::getMemoryValue()
{
	return ui.horizontalSlider_memory->value();
}

std::filesystem::path SettingsDialog::getMinecraftPath()
{
	return ui.lineEdit_game_path->text().toStdWString();
}

void SettingsDialog::setToDefault(const MinecraftCpp::option::MinecraftOptions& option, int memory)
{
	this->option = option;
	setCurretMemory(memory);
	setStandartJavaPath(this->option.executablePath);
	setStandartMinecraftPath(this->option.gameDirectory);
	setJavaPath("");
	setMinecraftPath("");
}

bool SettingsDialog::getReintsallModsState()
{
	return ui.checkBox_reinstall_modpack->isChecked();
}

QLabel* SettingsDialog::getVersionLabel()
{
	return ui.label_launcher_version;
}

std::string SettingsDialog::getApplicationVersion()
{

	// get the filename of the executable containing the version resource
	TCHAR szFilename[MAX_PATH + 1] = { 0 };
	if (GetModuleFileName(NULL, szFilename, MAX_PATH) == 0)
	{
		qWarning() << "GetModuleFileName failed with error" << GetLastError() << std::endl;
		return "";
	}

	// allocate a block of memory for the version info
	DWORD dummy;
	DWORD dwSize = GetFileVersionInfoSize(szFilename, &dummy);
	if (dwSize == 0)
	{
		qWarning() << "GetFileVersionInfoSize failed with error" << GetLastError() << std::endl;
		return "";
	}
	std::vector<BYTE> data(dwSize);

	// load the version info
	if (!GetFileVersionInfo(szFilename, NULL, dwSize, &data[0]))
	{
		qWarning() << "GetFileVersionInfo failed with error" << GetLastError() << std::endl;
		return "";
	}

	// get the name and version strings
	LPVOID pvProductName = NULL;
	unsigned int iProductNameLen = 0;
	LPVOID pvProductVersion = NULL;
	unsigned int iProductVersionLen = 0;

	// replace "040904e4" with the language ID of your resources
	if (!VerQueryValue(&data[0], _T("\\StringFileInfo\\041904b0\\ProductName"), &pvProductName, &iProductNameLen) ||
		!VerQueryValue(&data[0], _T("\\StringFileInfo\\041904b0\\ProductVersion"), &pvProductVersion, &iProductVersionLen))
	{
		qWarning() << "Can't obtain ProductName and ProductVersion from resources" << std::endl;
		return "";
	}
	
	qInfo() << (LPCSTR)pvProductName << iProductNameLen << std::endl;
	qInfo() << (LPCSTR)pvProductVersion << iProductVersionLen << std::endl;

	CStringA strProductName;
	CStringA strProductVersion;

	strProductName.SetString((LPCSTR)pvProductName, iProductNameLen);
	strProductVersion.SetString((LPCSTR)pvProductVersion, iProductVersionLen);
	qInfo() << strProductVersion.GetString() << std::endl;
	return "";
}

std::filesystem::path SettingsDialog::getPathFromWindowSelector(const QFileDialog::FileMode& type,
	const QFileDialog::Option& option, const QList<QString>& file_types_display)
{
	QFileDialog dialog(this);
	dialog.setFileMode(type);
	dialog.setOptions(option);
	dialog.setNameFilters(file_types_display);

	return dialog.getExistingDirectory().toStdWString();
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

void SettingsDialog::reinstallModPackIsChecked()
{
	if (ui.label_modreinstall_notifiy->isHidden())
	{
		ui.label_modreinstall_notifiy->setHidden(false);
		emit reinstallMods(true);
	}
	else
	{
		ui.label_modreinstall_notifiy->setHidden(true);
		emit reinstallMods(false);
	}
}

void SettingsDialog::onClickToolBotton_getminecraft_core()
{
	qInfo() << "onClickToolBotton_getminecraft_core" << std::endl;
	std::filesystem::path path = getPathFromWindowSelector(QFileDialog::Directory, QFileDialog::ShowDirsOnly);
	if (path.empty())
	{
		return;
	}
	ui.lineEdit_game_path->setText(path.u8string().c_str());
	emit changedMinecraftPathSignal(path);
}

void SettingsDialog::onClickToolBotton_getjava_path()
{
	qInfo() << "onClickToolBotton_getjava_path" << std::endl;

	std::filesystem::path path = getPathFromWindowSelector(QFileDialog::FileMode::ExistingFile,
		QFileDialog::Option::ReadOnly, { "Java executeble file (*.exe)" });
	if (path.empty())
	{
		return;
	}

	ui.lineEdit_java_path->setText(path.u8string().c_str());
}

void SettingsDialog::onClickPushButtonLogoutFromAccount()
{
	SJson::JsonValue parced_config = SJson::JsonParcer::ParseFile(this->config_path);
	parced_config["user"]["name"] = "";
	parced_config["user"]["password"] = "";
	parced_config.save_json_to_file(this->config_path.u8string(), 4);
	this->close();
	emit logoutSignal();
}

void SettingsDialog::setMemoryLableValue(int value)
{
	ui.label_memory_count->setText((std::to_string(value) + " Mb").c_str());
}