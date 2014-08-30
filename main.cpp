#include "logwidgetmainwindow.h"
#include <QApplication>
#include <QVariant>
#include <logmodeldata.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogWidgetMainWindow w;
    w.show();


    return a.exec();
}
