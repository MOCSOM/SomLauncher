#include "LoginAccountForm.h"

LoginAccountForm::LoginAccountForm(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.pushButton_login, &QPushButton::pressed, this, &LoginAccountForm::onClickPushButtonLogin);

	ui.label_wrong_password->setHidden(true);
}

LoginAccountForm::~LoginAccountForm()
{}

void LoginAccountForm::setConnectionWithDataBase()
{
}

const std::string LoginAccountForm::getPasswordHashFromServer()
{
	return std::string();
}

const std::string LoginAccountForm::getLoginFromServer()
{
	return std::string();
}

bool LoginAccountForm::checkPassword()
{
	const std::string server_hash = getPasswordHashFromServer();
	std::vector<std::string> split_hash = Additionals::String::split(server_hash, '$');

	std::string method = split_hash[0];
	std::string salt = split_hash[1];
	size_t iterators = std::stoi(split_hash[2]);
	std::string server_hash_password = split_hash[3];

	QByteArray client_user_password_byte_array = PBKDF2_SHA256_DJANGO(ui.lineEdit_password->text().toStdString(), salt, iterators);
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
	return ui.lineEdit_login->text().toStdString() == getLoginFromServer();
}

void LoginAccountForm::onClickPushButtonLogin()
{
	if (checkPassword() == true && checkLogin() == true)
	{
		emit accountDataReceivedSignal(data.to_string());
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