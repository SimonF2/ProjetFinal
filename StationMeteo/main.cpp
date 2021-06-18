#include "mainwindow.h"
#include "dialoglangue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //
    //a.installTranslator(&translator);

    Dialoglangue l;
    l.exec();

    /*
    if (parametres::getLangue()=="English")
    {
        //translator.load
    }
    else
    {

    }
    */

    MainWindow w;
    w.show();

    return a.exec();
}
