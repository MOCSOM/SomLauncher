#ifndef LOGGINACCOUNTFORM_H_
#define LOGGINACCOUNTFORM_H_

#include <qdialog.h>
#include <qmessagebox.h>

#include <string>

#include "../Databases/SQLBased.h"
#include "../../MocJsonLib/SomJson.h"
#include "../Moc/Logger/MocIOStream.h"
#include "../Encryption/PBKDF2SHA256.h"

#include "../../../QObjects/ClickableLabel.h"

#include "ui_LoginAccountForm.h"

class LoginAccountForm : public QDialog
{
	Q_OBJECT

private:
	sql::Connection* connection = nullptr;

	std::filesystem::path config_path;

public:
	explicit LoginAccountForm(QWidget* parent = nullptr);
	~LoginAccountForm();

	void _setPasswordAndLoginInUi();

	void setConfigPath(const std::filesystem::path& config_path);
	void setConnectionWithDataBase();
	const std::string getPasswordHashFromServer();
	const std::string getLoginFromServer();
	const std::string getUserDataFromServer();
	bool checkPassword();
	bool checkLogin();

	const std::string getUserLogin();
	const std::string getUserPassword();
	const Json::JsonValue getUserDataFromConfig();

	void earseAllData();

private slots:
	void onClickPushButtonLogin();
	void onClickPushButtonRegistrate();
	void onClickLableForgotPassword();

signals:
	void accountDataReceivedSignal(const std::string& json_string_data);

private:
	Ui::LoginAccountForm ui;
};

#endif // !LOGGINACCOUNTFORM_H_