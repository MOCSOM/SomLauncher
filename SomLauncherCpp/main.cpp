#include "Form/SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>

#include "Callbacks/CallbackDict.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	SomLauncherMainWindow window;
	window.show();
	return application.exec();
}