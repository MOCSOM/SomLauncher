#include "Form/SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>
#include <qexception.h>
#include <qmessagebox.h>
#include <exception>

int main(int argc, char* argv[])
{
	int returned_id = -1;
	try
	{
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

	return returned_id;
}