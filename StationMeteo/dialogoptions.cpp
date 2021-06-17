#include "dialogoptions.h"
#include "ui_dialogoptions.h"
#include "mainwindow.h"
#include "parametres.h"



#include <QDateTime>
#include <QDebug>
#include <QFontDialog>
#include <QSettings>

DialogOptions::DialogOptions(QString texte,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    if (!texte.isEmpty())
    {
        this->setWindowTitle(texte);
    }

    if (parametres::getFormat24Heure()==false)
        ui->rdBtn12->setChecked(true);
    if (parametres::getUnite()=="Fahrenheit")
        ui->rdBtnFar->setChecked(true);
    if (parametres::getLangue()=="English")
        ui->comboBoxLangue->setCurrentText("English");

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
        parametres::setPolice(policechoisi);
        ui->BtnPolice->setFont(parametres::getPolice());
        //on peut modifier ici la police de tout ce qu'on veut dans dialogoptions


    }


}

void DialogOptions::on_rdBtnC_clicked()
{
    parametres::setUnite("Celsius");
}

void DialogOptions::on_rdBtnFar_clicked()
{
    parametres::setUnite("Fahrenheit");
}

void DialogOptions::on_buttonBox_accepted()
{
    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    maConfig.setValue("Langue", parametres::getLangue());
    maConfig.setValue("Unite", parametres::getUnite());
    maConfig.setValue("FormatHeure", parametres::getFormat24Heure());
    qDebug()<<"Paramètres enregistrés";
}
