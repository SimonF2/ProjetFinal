#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QObject>
#include <QDebug>


class parametres : public QObject
{


public:
    parametres();

    static bool getFormat24Heure();
    static QString getHeure();
    static void setFormatHeure(bool value);

    static QString getLangue();
    static void setLangue(QString value);

    static QFont getPolice();
    static void setPolice(QFont value);

    static QString getUnite();
    static void setUnite(QString value);

    static QString getMode();
    static void setMode(const QString &value);

private:
    static bool format24Heure;
    static QString langue;
    static QFont police;
    static QString unite;
    static QString mode;
};

#endif // PARAMETRES_H
