#include "parametres.h"
#include "QDateTime"

#include <QFont>


bool parametres::format24Heure = true;
QString parametres::langue = "Français";
QFont parametres::police("MS Shell Dlg 2",8,-1, false);

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
}

QString parametres::getLangue()
{
    return langue;
}

void parametres::setLangue(const QString &value)
{
    if (value == "Français" || value == "English")
        langue = value;
    qDebug()<<value;
}

QFont parametres::getPolice()
{
    return police;
}

void parametres::setPolice(const QFont &value)
{
    police = value;
    qDebug()<<value.toString();
}
