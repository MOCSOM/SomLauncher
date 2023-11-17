#ifndef LOGGINACCOUNTFORM_H_
#define LOGGINACCOUNTFORM_H_

#include <qdialog.h>

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
	sql::ResultSet* result = nullptr;

	Json::JsonValue data;

public:
	explicit LoginAccountForm(QWidget* parent = nullptr);
	~LoginAccountForm();

	void setConnectionWithDataBase();
	const std::string getPasswordHashFromServer();
	const std::string getLoginFromServer();
	bool checkPassword();
	bool checkLogin();

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