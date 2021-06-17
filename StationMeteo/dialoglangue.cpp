#include "dialoglangue.h"
#include "ui_dialoglangue.h"
#include "mainwindow.h"

#include <QSettings>

Dialoglangue::Dialoglangue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglangue)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Choix de la langue"));
}

Dialoglangue::~Dialoglangue()
{
    delete ui;
    delete FenetrePrincipale;
}

void Dialoglangue::on_ValidLangue_clicked()
{
    FenetrePrincipale = new MainWindow;
    FenetrePrincipale->show();
    this->close();

    /*
    if (bouton checked)
    parametres::setLangue(bouton->text());
    else if (bouton2 checked)
    parametres::setLangue(bouton2->text());

    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    maConfig.setValue("Langue", parametres::getLangue());

    */
}
