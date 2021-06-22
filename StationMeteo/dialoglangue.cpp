#include "dialoglangue.h"
#include "ui_dialoglangue.h"


#include <QSettings>

Dialoglangue::Dialoglangue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglangue)
{
    ui->setupUi(this);




    if (parametres::getLangue()=="English")
        ui->comboBoxLangue->setCurrentText("English");



    if (ui->comboBoxLangue->currentText()=="English")
        this->setWindowTitle("Language choice");

    else
        this->setWindowTitle("Choix de la langue");

}

Dialoglangue::~Dialoglangue()
{
    delete ui;

}

void Dialoglangue::on_comboBoxLangue_currentTextChanged(const QString &arg1)
{
    parametres::setLangue(arg1);

    if (ui->comboBoxLangue->currentText()=="English")
        this->setWindowTitle("Language choice");
    else //if (ui->comboBoxLangue->currentText()=="Français")
        this->setWindowTitle("Choix de la langue");


}


void Dialoglangue::on_ValidLangue_clicked()
{

    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    maConfig.setValue("Langue", parametres::getLangue());

    qDebug()<<"Paramètre langue enregistré";

    this->close();
}
