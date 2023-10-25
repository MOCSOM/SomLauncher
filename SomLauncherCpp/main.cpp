#include "Form/SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>

#include "Exceptions/TerminateProgrammException.h"
#include "Web/DownloadClasses.h"

#include <qexception.h>
#include <qmessagebox.h>
#include <exception>
#include <filesystem>

int main(int argc, char* argv[])
{
	int returned_id = -1;
	QApplication application(argc, argv);
	try
	{
		if (!std::filesystem::exists("somlogs"))
		{
			std::filesystem::create_directories("somlogs");
		}

		std::ofstream ofs;
		ofs.open("somlogs\\last_log.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		SomLauncherMainWindow window;

		window.show();
		returned_id = application.exec();
	}
	catch (const TerminateProgrammException& exc)
	{
		if (exc.getReturnedId() != 47)
		{
			return exc.getReturnedId();
		}
		else
		{
			return system(DownloadFile("https://mocsom.site/setups/SomSetup.msi").c_str());
		}
	}
	catch (const QException& exc)
	{
		qWarning() << "qexception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(0, "QError", exc.what());
		messageBox.setFixedSize(500, 200);
	}
	catch (const std::exception& exc)
	{
		qWarning() << "exception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(0, "Error", exc.what());
		messageBox.setFixedSize(500, 200);
	}

	return returned_id;
}