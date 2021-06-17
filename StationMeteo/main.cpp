#include "mainwindow.h"
#include "dialoglangue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialoglangue l;
    l.show();

    //MainWindow w;
    //w.show();

    return a.exec();
}
