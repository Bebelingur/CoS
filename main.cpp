//bla
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    data d;
    d.connectionToDatabase();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
