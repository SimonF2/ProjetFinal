#include "dialogoptions.h"
#include "ui_dialogoptions.h"
#include "mainwindow.h"
#include "parametres.h"



#include <QDateTime>
#include <QDebug>
#include <QFontDialog>
#include <QSettings>

DialogOptions::DialogOptions(QTranslator* pttranslator,QString texte,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    if (!texte.isEmpty())
    {
        this->setWindowTitle(texte);
    }

    this->trad=pttranslator;


    //--------------------------------------------------------------------
    //Mise à jour affichage Dialogoptions en fonction de la classe parametres

    if (parametres::getMode()=="Nuit")
        ui->rdBtnNuit->setChecked(true);
    if (parametres::getFormat24Heure()==false)
        ui->rdBtn12->setChecked(true);
    if (parametres::getUnite()=="Fahrenheit")
        ui->rdBtnFar->setChecked(true);
    if (parametres::getLangue()=="English")
        ui->comboBoxLangue->setCurrentText("English");

    if (ui->comboBoxLangue->currentText()=="English")
        this->setWindowTitle("Settings");
    else
        this->setWindowTitle("Paramètres");

    //ajout suite à erreur dans la traduction
    ui->rdBtnFar->setText("Fahrenheit");

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
    emit modifparam();

}


void DialogOptions::on_rdBtn24_clicked()
{
     parametres::setFormatHeure(true);
     emit modifparam();
}

void DialogOptions::on_comboBoxLangue_currentTextChanged(const QString &arg1)
{
    parametres::setLangue(arg1);



    if (parametres::getLangue()=="English")
    {
        trad->load(":/traduction/StationMeteo_en.qm");
    }
    else // (parametres::getLangue()=="Français")
    {
        trad->load(":/traduction/StationMeteo_fr.qm");
    }


    ui->retranslateUi(this);

    // Eléments liés à des erreurs ou des oublis dans la traduction
    ui->rdBtnFar->setText("Fahrenheit");

    if (ui->comboBoxLangue->currentText()=="English")
        this->setWindowTitle("Settings");
    else
        this->setWindowTitle("Paramètres");

    emit modifparam();

}


void DialogOptions::on_BtnPolice_clicked()
{
    bool ok = false;
    QFont policechoisie = QFontDialog::getFont(&ok, ui->BtnPolice->font(), this, "Choisissez une police");
    //policechoisie.fromString("Arial Narrow,60,-1,5,75,1,1,0,0,0,Gras Italique");

    if (ok)
    {
        //on enregistre la police choisie dans la classe parametres
        parametres::setPolice(policechoisie);
        emit modifparam();
        //on modifie la police de tous les éléments de la fenêtre
        //this->setFont(parametres::getPolice());

    }


}

void DialogOptions::on_rdBtnC_clicked()
{
    parametres::setUnite("Celsius");
    emit modifparam();

}

void DialogOptions::on_rdBtnFar_clicked()
{
    parametres::setUnite("Fahrenheit");
    emit modifparam();

}


void DialogOptions::on_rdBtnJour_clicked()
{
    parametres::setMode("Jour");
    emit modifmode();
}

void DialogOptions::on_rdBtnNuit_clicked()
{
    parametres::setMode("Nuit");
    emit modifmode();
}


void DialogOptions::on_buttonBox_accepted()
{
    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    maConfig.setValue("Langue", parametres::getLangue());
    maConfig.setValue("Unite", parametres::getUnite());
    maConfig.setValue("FormatHeure", parametres::getFormat24Heure());
    maConfig.setValue("Police", parametres::getPolice());
    maConfig.setValue("Mode", parametres::getMode());

    qDebug()<<"Paramètres enregistrés";


}


