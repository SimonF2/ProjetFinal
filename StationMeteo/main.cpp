#include "mainwindow.h"
#include "dialoglangue.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //Récupération des données du fichier ini;

    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    parametres::setMode(maConfig.value("Mode").toString());
    parametres::setFormatHeure(maConfig.value("FormatHeure").toBool());
    parametres::setUnite(maConfig.value("Unite").toString());
    parametres::setLangue(maConfig.value("Langue").toString());

    QString policeString = maConfig.value("Police").toString();
    //qDebug() << "Police recue du fichier ini:"<<policeString;
    QFont policeChoisie;
    policeChoisie.fromString(policeString);
    parametres::setPolice(policeChoisie);

    //Traduction

    /*
    QTranslator translator;

    a.installTranslator(&translator);
    if (parametres::getLangue()=="English")
    {
        translator.load("/traduction/StationMeteo_en.qm");
    }
    else
    {

    }
    */

    //Ouverture de la première fenêtre de dialogue

    Dialoglangue l;
    l.exec();


    //ouverture de la fenêtre principale une fois la première fermée

    MainWindow w;
    w.show();

    return a.exec();
}
