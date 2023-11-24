#include "Form/SomLauncherMainWindow.h"
#include "Form/LoginAccountForm.h"
#include <QtWidgets/QApplication>

#include "Web/DownloadClasses.h"
#include "Databases/SQLBased.h"

#include <qexception.h>
#include <qmessagebox.h>
#include <exception>
#include <filesystem>

int main(int argc, char* argv[])
{
	//QApplication application(argc, argv);

//	try
//	{
//		sql::Connection* con = nullptr;
//		con = sqlbase::mysql::sqlconnector::connect(
//			"79.174.93.203", "sombd", "somuser", "Vblyfqn_jqk23");
//
//		sql::ResultSet* res = nullptr;
//		res = sqlbase::mysql::sqlconnector::sendQuerry(con,
//			R"(SELECT mods_mod.mod_link FROM servers_server
//INNER JOIN mods_modmodpack ON servers_server.modpack_id_id = mods_modmodpack.modpack_id_id
//INNER JOIN mods_mod ON mods_modmodpack.mod_id_id = mods_mod.mod_id)");
//
//		while (res->next())
//		{
//			std::cout << res->getString(1) << std::endl;
//		}
//		//std::cout << sqlbase::mysql::sqlconnector::sqlResultToJson(res);
//	}
//	catch (sql::SQLException& eSQL) {
//		std::cerr << "Failed with exception: " << eSQL.what() << std::endl;
//	}
	//return application.exec();

	int returned_id = -1;
	QApplication application(argc, argv);

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
		account_window.setConfigPath(main_window.getConfigPath());
		account_window._setPasswordAndLoginInUi();

		//main_window.setConnectionWithDatabase();
		//std::cout << main_window.getServersFromDatabase().to_string() << std::endl;

		QObject::connect(&main_window, &SomLauncherMainWindow::updateSignal,
			[=](const std::string& url) -> int
			{
				qInfo() << "updateSignal detected" << std::endl;
				std::string download_url = "https://mocsom.site/media" + std::string("/") + url;
				QApplication::exit(0);
				return system(DownloadFile(download_url, Additionals::TempFile::get_tempdir_SYSTEM()).c_str());
			}
		);

		QObject::connect(&account_window, &LoginAccountForm::accountDataReceivedSignal,
			[&main_window, &account_window](const std::string& json_string_data) -> void
			{
				qInfo() << "accountDataReceivedSignal detected" << std::endl;
				Json::JsonValue data = Json::JsonParcer::ParseJson(json_string_data);
				main_window.setAccountData(data);
				main_window._settingAccountDataInUi();
				main_window.createSettingsForm();
				main_window.setConnectionWithDatabase();
				main_window._parcingServers();
				main_window._settingServersWidgets();
				main_window._settingModsCount();
				main_window._settingCurrentServerName();

				QObject::connect(main_window.getSettingsDialog().get(), &SettingsDialog::logoutSignal,
					[&main_window, &account_window]() -> void
					{
						main_window.close();
						account_window.earseAllData();
						account_window.show();
					}
				);

				main_window.show();
				account_window.close();
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