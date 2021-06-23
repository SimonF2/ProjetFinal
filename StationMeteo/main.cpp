#include "mainwindow.h"
#include "dialoglangue.h"
#include <QTranslator>
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
    parametres::setVille(maConfig.value("Ville").toString());


    QString policeString = maConfig.value("Police").toString();
    //qDebug() << "Police recue du fichier ini:"<<policeString;
    QFont policeChoisie;
    policeChoisie.fromString(policeString);
    parametres::setPolice(policeChoisie);

    //Traduction

     QTranslator translator;
     a.installTranslator(&translator);

    //Ouverture de la première fenêtre de dialogue

    Dialoglangue l;
    l.exec();




    if (parametres::getLangue()=="English")
    {
        translator.load(":/traduction/StationMeteo_en.qm");
        //qDebug() <<"Speaking English right now. ";
    }
    else // (parametres::getLangue()=="Français")
    {
        translator.load(":/traduction/StationMeteo_fr.qm");
        //qDebug() <<"Ca cause Français là. ";
    }





    //ouverture de la fenêtre principale une fois la première fermée

    MainWindow w(&translator);
    w.show();

    return a.exec();
}
