#include "LoginAccountForm.h"

LoginAccountForm::LoginAccountForm(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.pushButton_login, &QPushButton::pressed, this, &LoginAccountForm::onClickPushButtonLogin);

	ui.label_wrong_password->setHidden(true);
}

LoginAccountForm::~LoginAccountForm()
{
}

void LoginAccountForm::_setPasswordAndLoginInUi()
{
	Json::JsonValue config = getUserDataFromConfig();
	ui.lineEdit_login->setText(config["user"]["name"].to_string().c_str());
	ui.lineEdit_password->setText(config["user"]["password"].to_string().c_str());
	if (!config["user"]["password"].to_string().empty())
	{
		ui.checkBox_remember_password->setChecked(true);
	}
}

void LoginAccountForm::setStyleSheet(const std::filesystem::path& path)
{
	QFile styleFile(path);
	styleFile.open(QFile::ReadOnly);
	// Apply the loaded stylesheet
	QString style(styleFile.readAll());
	QDialog::setStyleSheet(style);
}

void LoginAccountForm::setConfigPath(const std::filesystem::path& config_path)
{
	this->config_path = config_path;
}

void LoginAccountForm::setConnectionWithDataBase()
{
	try
	{
		this->connection = sqlbase::mysql::sqlconnector::connect(
			"79.174.93.203", "sombd", "somuser", "Vblyfqn_jqk23");
	}
	catch (sql::SQLException& exc)
	{
		qWarning() << "exception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Connection Error", exc.what());
		messageBox.setFixedSize(500, 200);
		//qFatal() << "Failed with exception: " << eSQL.what();
	}
}

const std::string LoginAccountForm::getPasswordHashFromServer()
{
	sql::ResultSet* res = nullptr;
	QString querry = "SELECT password FROM users_customuser WHERE username LIKE " + QString("'%") + ui.lineEdit_login->text() + "%'";
	try
	{
		res = sqlbase::mysql::sqlconnector::sendQuerry(this->connection, querry.toStdString());
	}
	catch (sql::SQLException& eSQL)
	{
		qFatal() << "Failed with exception: " << eSQL.what();
	}
	while (res->next())
		return res->getString(1);

	return "";
}

const std::string LoginAccountForm::getLoginFromServer()
{
	sql::ResultSet* res = nullptr;
	QString querry = "SELECT username FROM users_customuser WHERE username LIKE " + QString("'%") + ui.lineEdit_login->text() + "%'";
	try
	{
		//std::string querry = "SELECT username FROM users_customuser WHERE username LIKE " + '%' + ui.label_login->text().toStdString() + "%";
		res = sqlbase::mysql::sqlconnector::sendQuerry(this->connection, querry.toStdString());
	}
	catch (sql::SQLException& eSQL)
	{
		qInfo() << "Failed with exception: " << eSQL.what();
		return "";
	}
	while (res->next())
		return res->getString(1);

	return "";
}

const std::string LoginAccountForm::getUserDataFromServer()
{
	sql::ResultSet* res = nullptr;
	QString querry = "SELECT JSON_ARRAYAGG(JSON_OBJECT('id',id, 'email',email, 'username',username, 'password',password, 'is_staff',is_staff, 'is_active',is_active, 'is_superuser',is_superuser, 'date_joined',date_joined, 'last_login',last_login)) FROM users_customuser WHERE username LIKE " + QString("'%") + ui.lineEdit_login->text() + "%'";
	try
	{
		res = sqlbase::mysql::sqlconnector::sendQuerry(this->connection, querry.toStdString());
	}
	catch (sql::SQLException& eSQL)
	{
		qInfo() << "Failed with exception: " << eSQL.what();
		return "";
	}
	while (res->next())
		return res->getString(1);

	return "";
}

bool LoginAccountForm::checkPassword()
{
	const std::string server_hash = getPasswordHashFromServer();
	const std::string config_hash = getUserPassword();

	if (server_hash == config_hash)
	{
		return true;
	}

	std::vector<std::string> split_hash = Additionals::String::split(server_hash, '$');

	std::string method = split_hash[0];
	size_t iterators = std::stoi(split_hash[1]);
	std::string salt = split_hash[2];
	std::string server_hash_password = split_hash[3];

	QByteArray client_user_password_byte_array =
		PBKDF2_SHA256_DJANGO(ui.lineEdit_password->text().toStdString(), salt, iterators);
	std::string client_hash_password = client_user_password_byte_array.toBase64().data();

	if (client_hash_password == server_hash_password)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool LoginAccountForm::checkLogin()
{
	return ui.lineEdit_login->text().toStdString() == getUserLogin();
}

const std::string LoginAccountForm::getUserLogin()
{
	Json::JsonValue config = getUserDataFromConfig();
	if (config["user"]["name"].to_string().empty())
	{
		return getLoginFromServer();
	}
	return config["user"]["name"].to_string();
}

const std::string LoginAccountForm::getUserPassword()
{
	Json::JsonValue config = getUserDataFromConfig();
	if (config["user"]["password"].to_string().empty())
	{
		return "";
	}
	return config["user"]["password"].to_string();
}

const Json::JsonValue LoginAccountForm::getUserDataFromConfig()
{
	const Json::JsonValue parced_config = Json::JsonParcer::ParseFile(this->config_path);
	return parced_config;
}

void LoginAccountForm::earseAllData()
{
	ui.lineEdit_login->setText("");
	ui.lineEdit_password->setText("");
}

void LoginAccountForm::onClickPushButtonLogin()
{
	setConnectionWithDataBase();

	if (checkPassword() == true && checkLogin() == true)
	{
		std::string json_data_string = getUserDataFromServer();

		if (ui.checkBox_remember_password->isChecked())
		{
			Json::JsonValue data_to_save = Json::JsonParcer::ParseJson(json_data_string);
			Json::JsonValue parced_config = Json::JsonParcer::ParseFile(this->config_path);
			for (auto& elem : data_to_save.get_array())
			{
				if (elem.is_exist("username"))
				{
					parced_config["user"]["name"] = elem["username"];
				}
				if (elem.is_exist("password"))
				{
					parced_config["user"]["password"] = elem["password"];
				}
			}
			parced_config.save_json_to_file(this->config_path.u8string(), 4);
		}
		else
		{
			Json::JsonValue data_to_save = Json::JsonParcer::ParseJson(json_data_string);
			Json::JsonValue parced_config = Json::JsonParcer::ParseFile(this->config_path);
			for (auto& elem : data_to_save.get_array())
			{
				if (elem.is_exist("username"))
				{
					parced_config["user"]["name"] = elem["username"];
				}
			}
			parced_config.save_json_to_file(this->config_path.u8string(), 4);
		}

		this->connection->close();
		emit accountDataReceivedSignal(json_data_string);
	}
	else
	{
		ui.label_wrong_password->setHidden(false);
	}
}

void LoginAccountForm::onClickPushButtonRegistrate()
{
}

void LoginAccountForm::onClickLableForgotPassword()
{
}