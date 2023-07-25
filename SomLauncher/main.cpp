#include "SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SomLauncherMainWindow w;
    w.show();
    return a.exec();
}
