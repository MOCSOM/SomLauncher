#ifndef LOGGINACCOUNTFORM_H_
#define LOGGINACCOUNTFORM_H_

#include <qdialog.h>
#include <qmessagebox.h>

#include <string>
#include <optional>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include <nlohmann/json.hpp>

#include "../Databases/SQLBased.h"
#include "../Json/SomJson.h"
#include "../Moc/Logger/MocIOStream.h"
#include "../Encryption/PBKDF2SHA256.h"

#include "../../../QObjects/ClickableLabel.h"

#include "ui_LoginAccountForm.h"

class LoginAccountForm : public QDialog
{
	Q_OBJECT

private:
	std::filesystem::path config_path;

	std::string username;
	std::string password_hash;

public:
	explicit LoginAccountForm(QWidget* parent = nullptr);
	~LoginAccountForm();

	void _setPasswordAndLoginInUi();

	void setStyleSheet(const std::filesystem::path& path);
	void setConfigPath(const std::filesystem::path& config_path);
	const std::string getUserDataFromServer();
	bool checkPassword(const nlohmann::json& data);
	bool checkLogin(const nlohmann::json& data);

	const std::string getUserLogin(const nlohmann::json& data);
	const std::string getUserPassword();
	const nlohmann::json getUserDataFromConfig();

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