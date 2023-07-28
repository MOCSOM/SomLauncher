#include "SomLauncherMainWindow.h"
#include <QtWidgets/QApplication>


#include "Json.h"

int main(int argc, char *argv[])
{

    /*Json::JsonParcer parcer;
    auto& js = *parcer.ParseFile("DATA.json");*/


    QApplication application(argc, argv);
    SomLauncherMainWindow window;
    window.show();
    return application.exec();
}
