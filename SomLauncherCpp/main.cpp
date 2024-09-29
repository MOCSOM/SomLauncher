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
	application.setApplicationDisplayName("SomLauncher");
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

		QPointer<SomLauncherMainWindow> main_window = new SomLauncherMainWindow();
		qInfo() << "Creating account window...";
		QPointer<LoginAccountForm> account_window = new LoginAccountForm()/*(&main_window)*/;
		account_window->setStyleSheet(main_window->getStyleSheetPath());
		account_window->setModal(false);
		qInfo() << "Configureate account window...";
		account_window->setConfigPath(main_window->getConfigPath());
		account_window->_setPasswordAndLoginInUi();
		account_window->show();
		account_window->setDisabled(true);

		//main_window.setConnectionWithDatabase();
		//qDebug() << main_window.getServersFromServer().to_string();

		QObject::connect(account_window, &LoginAccountForm::accountDataReceivedSignal,
			[&main_window, &account_window](const std::string& json_string_data) -> void
			{
				qInfo() << "accountDataReceivedSignal detected";

				nlohmann::json data = nlohmann::json::parse(json_string_data);
				main_window->setAccountData(data);
				main_window->initMainWindow();

				QObject::connect(main_window->getSettingsDialog().get(), &SettingsDialog::logoutSignal,
					[&main_window, &account_window]() -> void
					{
						main_window->hide();
						account_window->eraseAllData();
						account_window->show();
					}
				);

				main_window->show();
				account_window->hide();
			}
		);

		QObject::connect(main_window, &SomLauncherMainWindow::mainFormInitCompleteSignal,
			[&main_window, &account_window]() -> void
			{
				qInfo() << "mainFormInitCompleteSignal detected";

				main_window->show();
				account_window->hide();
			}
		);


		//QObject::connect(&application, &QApplication::Loop)
		QTimer::singleShot(30, account_window, &LoginAccountForm::checkLoggined);
		returned_id = application.exec();

	}
	catch (const std::exception& exc)
	{
		qFatal() << "Exception:" << exc.what();
		QMessageBox::critical(nullptr, QObject::tr("Error"), exc.what());
	}

	return returned_id;
}