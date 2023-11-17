#include "Form/SomLauncherMainWindow.h"
#include "Form/LoginAccountForm.h"
#include <QtWidgets/QApplication>

#include "Web/DownloadClasses.h"
#include "Databases/SQLBased.h"

#include "Encryption/PBKDF2SHA256.h"

#include <qexception.h>
#include <qmessagebox.h>
#include <exception>
#include <filesystem>

int main(int argc, char* argv[])
{
	//QApplication application(argc, argv);

	try
	{
		sql::Connection* con = nullptr;
		con = sqlbase::mysql::sqlconnector::connect(
			"79.174.93.203", "sombd", "somuser", "Vblyfqn_jqk23");

		/*sql::ResultSet* res = nullptr;
		res = sqlbase::mysql::sqlconnector::sendQuerry(con, "SELECT JSON_OBJECTAGG(JSON_OBJECT('id',id)) FROM users_customuser");

		while (res->next())
		{
			std::cout << res->getString(1) << std::endl;
		}*/
		//std::cout << sqlbase::mysql::sqlconnector::sqlResultToJson(res);
	}
	catch (sql::SQLException& eSQL) {
		std::cerr << "Failed with exception: " << eSQL.what() << std::endl;
	}

	//return application.exec();

	//unsigned char salt[] = { '3','7','5','0','c','5','9','2','f','8','2','5','4','5','2','a','a','4','d','8','5','7','1','5','7','d','0','7','8','4','5','5','\0' };
	/*QByteArray arr = PBKDF2_SHA256_DJANGO("ShoSha2004",
		"3750c592f825452aa4d857157d078455", 390000, 32);
	QByteArray out = arr.toBase64();
	std::cout << arr.toBase64().data() << std::endl;

	if (std::string("5mgQxlrdtHwtk0izq5Mq8JvY7nXufdQiPxrC+KbnI/0=") == std::string(arr.toBase64().data()))
	{
		std::cout << "aaaaaaaaaaaaaaaa" << std::endl;
	}*/

	int returned_id = -1;
	QApplication application(argc, argv);
	sqlbase::mysql::sqlconnector::connect("79.174.93.203", "sombd", "somuser", "Vblyfqn_jqk23");

	qInstallMessageHandler(customHandler);
	try
	{
		if (!std::filesystem::exists("somlogs"))
		{
			std::filesystem::create_directories("somlogs");
		}

		std::ofstream ofs;
		ofs.open("somlogs\\last_log.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		SomLauncherMainWindow main_window;
		LoginAccountForm account_window(&main_window);

		QObject::connect(&main_window, &SomLauncherMainWindow::updateSignal,
			[=]() -> int
			{
				qInfo() << "updateSignal detected" << std::endl;
				return system(DownloadFile("https://mocsom.site/setups/SomSetup.msi").c_str());
			}
		);

		QObject::connect(&account_window, &LoginAccountForm::accountDataReceivedSignal,
			[&main_window](const std::string& json_string_data) -> void
			{
				qInfo() << "accountDataReceivedSignal detected" << std::endl;
				Json::JsonValue data = Json::JsonParcer::ParseJson(json_string_data);
				main_window.setAccountData(data);
				main_window.show();
			}
		);

		//main_window.show();
		account_window.show();
		returned_id = application.exec();
	}
	catch (const QException& exc)
	{
		qWarning() << "qexception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Qt Error", exc.what());
		messageBox.setFixedSize(500, 200);
	}
	catch (const std::exception& exc)
	{
		qWarning() << "exception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Std Error", exc.what());
		messageBox.setFixedSize(500, 200);
	}

	return returned_id;
}