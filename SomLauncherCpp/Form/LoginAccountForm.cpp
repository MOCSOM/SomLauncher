#include "LoginAccountForm.h"

LoginAccountForm::LoginAccountForm(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	QObject::connect(ui.pushButton_login, &QPushButton::pressed, this, &LoginAccountForm::onClickPushButtonLogin);
	QObject::connect(ui.pushButton_registration, &QPushButton::pressed, this, &LoginAccountForm::onClickPushButtonRegistrate);

	ui.label_wrong_password->setHidden(true);
}

LoginAccountForm::~LoginAccountForm()
{
}

void LoginAccountForm::_setPasswordAndLoginInUi()
{
	nlohmann::json config = getUserDataFromConfig();
	ui.lineEdit_login->setText(config["user"]["name"].template get<std::string>().c_str());
	ui.lineEdit_password->setText(config["user"]["password"].template get<std::string>().c_str());
	if (!config["user"]["password"].template get<std::string>().empty())
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
	this->config.reopenConfig(config_path);
}

const std::string LoginAccountForm::getUserDataFromServer()
{
	std::stringstream response;

	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		request.setOpt(curlpp::options::Verbose(true));
		request.setOpt(curlpp::options::Url(
			"https://mocsom.site/api/accounts/" + ui.lineEdit_login->text().toStdString()));
		request.setOpt(curlpp::options::WriteStream(&response));

		request.perform();
		long http_code = curlpp::infos::ResponseCode::get(request);

		switch (http_code)
		{
		case 200:
			break;
		case 404:
			//response.str(std::string());
			//response << R"({})" << std::endl;
			break;
		default:
			//response.str(std::string());
			qWarning() << "code not 200" << std::endl;
			QMessageBox::critical(this, tr("Server Connection error"), tr("Unable to connect to mocsom server"));
			QApplication::exit(1);
			break;
		}
	}
	catch (curlpp::LogicError& e)
	{
		qWarning() << e.what() << std::endl;
	}
	catch (curlpp::RuntimeError& e)
	{
		qWarning() << e.what() << std::endl;
	}

	return response.str();
}

bool LoginAccountForm::checkPassword(const nlohmann::json& data)
{
	const std::string server_hash = data["password"];
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

bool LoginAccountForm::checkLogin(const nlohmann::json& data)
{
	return ui.lineEdit_login->text().toStdString() == getUserLogin(data);
}

const std::string LoginAccountForm::getUserLogin(const nlohmann::json& data)
{
	nlohmann::json config = getUserDataFromConfig();
	if (config["user"]["name"].template get<std::string>().empty())
	{
		return data["username"];
	}
	return config["user"]["name"].template get<std::string>();
}

const std::string LoginAccountForm::getUserPassword()
{
	nlohmann::json config = getUserDataFromConfig();
	if (config["user"]["password"].empty())
	{
		return "";
	}
	return config["user"]["password"].template get<std::string>();
}

const nlohmann::json LoginAccountForm::getUserDataFromConfig()
{
	return this->config.json();
}

void LoginAccountForm::eraseAllData()
{
	ui.lineEdit_login->setText("");
	ui.lineEdit_password->setText("");
	this->config.json()["user"]["name"] = "";
	this->config.json()["user"]["password"] = "";
	this->config.saveJsonToFile();
}

void LoginAccountForm::onClickPushButtonLogin()
{
	std::string json_data_string = getUserDataFromServer();
	nlohmann::json json_data = nlohmann::json::parse(json_data_string);

	if (checkPassword(json_data) == true && checkLogin(json_data) == true)
	{
		nlohmann::json& parced_config = this->config.json();;

		if (ui.checkBox_remember_password->isChecked())
		{
			parced_config["user"]["name"] = json_data["username"];
			parced_config["user"]["password"] = json_data["password"];
		}
		else
		{
			parced_config["user"]["name"] = json_data["username"];
		}

		this->config.saveJsonToFile();

		emit accountDataReceivedSignal(json_data_string);
	}
	else
	{
		ui.label_wrong_password->setHidden(false);

		wrongPasswordOrLogin();
	}
}

void LoginAccountForm::onClickPushButtonRegistrate()
{
	QDesktopServices::openUrl(QUrl("https://mocsom.site/accounts/registration/"));
}

void LoginAccountForm::onClickLableForgotPassword()
{
}

void LoginAccountForm::erasePassword()
{
	ui.lineEdit_password->setText("");
	this->config.json()["user"]["password"] = "";
	this->config.saveJsonToFile();
}

void LoginAccountForm::eraseLogin()
{
	ui.lineEdit_login->setText("");
	this->config.json()["user"]["name"] = "";
	this->config.saveJsonToFile();
}

void LoginAccountForm::wrongPasswordOrLogin()
{
	QEventLoop zaloop;


	QTimer timer_white(this);
	QTimer timer_red(this);
	QTimer timer_big(this);

	connect(&timer_white, &QTimer::timeout,
		[&]()
		{
			UIThread::run([&]() {ui.label_wrong_password->setStyleSheet(R"(#label_wrong_password {color: white;})"); });
			timer_white.stop();
			timer_red.start(150);
		}
	);
	connect(&timer_red, &QTimer::timeout,
		[&]()
		{
			UIThread::run([&]() {ui.label_wrong_password->setStyleSheet(R"(#label_wrong_password {color: red;})"); });
			timer_red.stop();
			timer_white.start(150);
		}
	);
	connect(&timer_big, &QTimer::timeout, [&]() {zaloop.exit(); });

	timer_white.start(150);
	timer_big.start(1000);

	zaloop.exec();

	ui.label_wrong_password->setStyleSheet(R"(QLabel {color: white;})");
}
