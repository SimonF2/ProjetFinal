#include "parametres.h"
#include "QDateTime"

#include <QFont>


bool parametres::format24Heure = true;
QString parametres::langue = "Français";
QFont parametres::police("MS Shell Dlg 2",8,-1, false);
QString parametres::unite = "Celsius";

parametres::parametres()
{
 //pas besoin de constructeur si uniquement des données static
}

QString parametres::getHeure()
{
   QDateTime Heure =  QDateTime::currentDateTime();
    if (format24Heure == true)
    {
        return Heure.toString("hh:mm:ss");
    }
    else
        return Heure.toString("h:m:s ap");
}

void parametres::setFormatHeure(bool value)
{
    if (value == true || value == false)
        format24Heure = value;

    qDebug()<<"Changement Format heure parametres:"<<getHeure();
}

QString parametres::getLangue()
{
    return langue;
}

void parametres::setLangue(QString value)
{
    if (value == "Français" || value == "English")
        langue = value;


    qDebug()<<"Changement Langue parametres:"<<getLangue();
}

QFont parametres::getPolice()
{
    return police;
}

void parametres::setPolice(QFont value)
{
    police = value;

    qDebug()<<value.toString();
}

QString parametres::getUnite()
{
    return unite;
}

void parametres::setUnite(QString value)
{
    if (value == "Celsius" || value == "Fahrenheit")
        unite = value;


    qDebug()<<"Changement Unite parametres:"<<getUnite();
}

bool parametres::getFormat24Heure()
{
    return format24Heure;
}
