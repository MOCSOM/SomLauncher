#include "Form/SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>

#include "Exceptions/TerminateProgrammException.h"

#include <qexception.h>
#include <qmessagebox.h>
#include <exception>
#include <filesystem>

int main(int argc, char* argv[])
{
	int returned_id = -1;
	try
	{
		if (!std::filesystem::exists("somlogs"))
		{
			std::filesystem::create_directories("somlogs");
		}

		std::ofstream ofs;
		ofs.open("somlogs\\last_log.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		QApplication application(argc, argv);
		SomLauncherMainWindow window;

		window.show();
		returned_id = application.exec();
	}
	catch (const QException& exc)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "QError", exc.what());
		messageBox.setFixedSize(500, 200);
	}
	catch (const std::exception& exc)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", exc.what());
		messageBox.setFixedSize(500, 200);
	}
	catch (const TerminateProgrammException& exc)
	{
		return exc.getReturnedId();
	}

	return returned_id;
}