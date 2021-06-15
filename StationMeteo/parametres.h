#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QObject>
#include <QDebug>


class parametres
{
public:
    parametres();

    static QString getHeure();
    static void setFormatHeure(bool value);

    static QString getLangue();
    static void setLangue(QString value);

    static QFont getPolice();
    static void setPolice(QFont value);

    static QString getUnite();
    static void setUnite(QString value);

private:
    static bool format24Heure;
    static QString langue;
    static QFont police;
    static QString unite;
};

#endif // PARAMETRES_H
