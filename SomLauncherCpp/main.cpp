#include <QtWidgets/QApplication>

#include <qexception.h>
#include <qmessagebox.h>
#include <exception>
#include <filesystem>

#include "Form/SomLauncherMainWindow.h"
#include "Form/LoginAccountForm.h"

#include "Web/DownloadClasses.h"

int main(int argc, char* argv[])
{
	int returned_id = -1;
	QApplication application(argc, argv);
	application.setApplicationName("SomLauncher");
	//application.setApplicationDisplayName("SomLauncher");

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
		qInfo() << "Creating account window..." << std::endl;
		LoginAccountForm account_window/*(&main_window)*/;
		account_window.setStyleSheet(main_window.getStyleSheetPath());
		account_window.setModal(false);
		qInfo() << "Configureate account window..." << std::endl;
		account_window.setConfigPath(main_window.getConfigPath());
		account_window._setPasswordAndLoginInUi();

		//main_window.setConnectionWithDatabase();
		//std::cout << main_window.getServersFromServer().to_string() << std::endl;

		QObject::connect(&main_window, &SomLauncherMainWindow::updateSignal,
			[=](const std::string& url) -> void
			{
				qInfo() << "updateSignal detected" << std::endl;
				std::string download_url = "https://mocsom.site/media" + std::string("/") + url;
				UIThread::run([&]() {system(DownloadFile(download_url, Additionals::TempFile::get_tempdir_SYSTEM()).u8string().c_str()); });
				QApplication::exit(0);
			}
		);

		QObject::connect(&account_window, &LoginAccountForm::accountDataReceivedSignal,
			[&main_window, &account_window](const std::string& json_string_data) -> void
			{
				qInfo() << "accountDataReceivedSignal detected" << std::endl;
				nlohmann::json data = nlohmann::json::parse(json_string_data);
				main_window.setAccountData(data);
				main_window.setUuidFromAccount();
				main_window._settingAccountDataInUi();
				main_window.createSettingsForm();
				//main_window.setConnectionWithDatabase();
				main_window._parcingServers();
				main_window._settingServersWidgets();
				main_window._settingServerType();
				main_window._settingModsCount();
				main_window._settingCurrentServerName();

				QObject::connect(main_window.getSettingsDialog().get(), &SettingsDialog::logoutSignal,
					[&main_window, &account_window]() -> void
					{
						main_window.close();
						account_window.eraseAllData();
						account_window.show();
					}
				);

				main_window.show();
				account_window.close();
			}
		);

		qInfo() << "Checking user data" << std::endl;
		std::string json_data_string = account_window.getUserDataFromServer();
		nlohmann::json json_data = nlohmann::json::parse(json_data_string);

		if (!json_data.contains("id"))
		{
			account_window.eraseAllData();
			account_window.show();
		}
		else
		{
			if (account_window.getUserPassword().empty())
			{
				account_window.show();
			}
			else
			{
				if (account_window.checkPassword(json_data) == true && account_window.checkLogin(json_data) == true)
				{
					emit account_window.accountDataReceivedSignal(json_data_string);
				}
				else
				{
					account_window.show();
				}
			}
		}

		//main_window.show();
		
		returned_id = application.exec();
	}
	catch (const std::exception& exc)
	{
		QMessageBox::critical(nullptr, QObject::tr("Error"), exc.what());
		qFatal() << "Exception:" << exc.what();
		/*QMessageBox messageBox;
		messageBox.critical(nullptr, "Error", exc.what());
		messageBox.setFixedSize(500, 200);*/
	}

	return returned_id;
}