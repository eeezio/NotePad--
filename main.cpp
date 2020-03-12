#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
class Dialog;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    MainWindow w;
    w.show();
    a.exec();
}
