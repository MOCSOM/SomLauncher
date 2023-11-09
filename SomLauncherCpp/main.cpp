#include "Form/SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>

#include "Web/DownloadClasses.h"
#include "Databases/SQLBased.h"

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

		QObject::connect(&window, &SomLauncherMainWindow::updateSignal,
			[=]() -> int
			{
				qInfo() << "connect updateSignal" << std::endl;
				return system(DownloadFile("https://mocsom.site/setups/SomSetup.msi").c_str());
			});

		window.show();
		returned_id = application.exec();
	}
	catch (const QException& exc)
	{
		qWarning() << "qexception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(0, "Error in qt", exc.what());
		messageBox.setFixedSize(500, 200);
	}
	catch (const std::exception& exc)
	{
		qWarning() << "exception " << exc.what();
		QMessageBox messageBox;
		messageBox.critical(0, "Error in std", exc.what());
		messageBox.setFixedSize(500, 200);
	}

	return returned_id;
}