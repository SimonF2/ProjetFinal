#include "dialogoptions.h"
#include "ui_dialogoptions.h"
#include "mainwindow.h"
#include "parametres.h"



#include <QDateTime>
#include <QDebug>
#include <QFontDialog>

DialogOptions::DialogOptions(QString texte,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    if (!texte.isEmpty())
    {
        this->setWindowTitle(texte);
    }

    affHeure();
    timer = new QTimer();
    timer->setInterval(1000); //1000ms = 1 sec
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(affHeure())); // Affiche l'heure toutes les secondes

}

DialogOptions::~DialogOptions()
{
    delete ui;
    delete timer;
}


void DialogOptions::affHeure()
{
    ui->lblHeure->setText(parametres::getHeure());
}


void DialogOptions::on_rdBtn12_clicked()
{
    parametres::setFormatHeure(false);
}


void DialogOptions::on_rdBtn24_clicked()
{
    parametres::setFormatHeure(true);
}

void DialogOptions::on_comboBoxLangue_currentTextChanged(const QString &arg1)
{
    parametres::setLangue(arg1);
}


void DialogOptions::on_BtnPolice_clicked()
{
    bool ok = false;
    QFont policechoisi = QFontDialog::getFont(&ok, ui->BtnPolice->font(), this, "Choisissez une police");

    if (ok)
    {
        ui->BtnPolice->setFont(policechoisi);
    }

    parametres::setPolice(policechoisi);
}
