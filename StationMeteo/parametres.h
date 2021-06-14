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
    static void setLangue(const QString &value);

    static QFont getPolice();
    static void setPolice(const QFont &value);

private:
    static bool format24Heure;
    static QString langue;
    static QFont police;
};

#endif // PARAMETRES_H
