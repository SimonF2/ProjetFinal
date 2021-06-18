#include "mainwindow.h"
#include "dialoglangue.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //
    //a.installTranslator(&translator);

    //récupération des données du fichier ini;

    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    parametres::setFormatHeure(maConfig.value("FormatHeure").toBool());
    parametres::setUnite(maConfig.value("Unite").toString());
    parametres::setLangue(maConfig.value("Langue").toString());

    QString policeString = maConfig.value("Police").toString();
    qDebug() << "Police recue du fichier ini:"<<policeString;
    QFont policeChoisie;
    policeChoisie.fromString(policeString);
    parametres::setPolice(policeChoisie);

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
