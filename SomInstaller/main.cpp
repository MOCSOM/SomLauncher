#include <QtCore/QCoreApplication>
#include "SomInstallerMainWindow.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	SomInstallerMainWindow window;
	window.show();
	return application.exec();
}