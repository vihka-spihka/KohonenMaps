#include "controllermaps.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    controllerMaps controller;
    controller.show();

    return a.exec();
}
