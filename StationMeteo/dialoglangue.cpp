#include "dialoglangue.h"
#include "ui_dialoglangue.h"


#include <QSettings>

Dialoglangue::Dialoglangue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglangue)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Choix de la langue"));

    if (parametres::getLangue()=="English")
        ui->comboBoxLangue->setCurrentText("English");

}

Dialoglangue::~Dialoglangue()
{
    delete ui;

}

void Dialoglangue::on_comboBoxLangue_currentTextChanged(const QString &arg1)
{
    parametres::setLangue(arg1);
}


void Dialoglangue::on_ValidLangue_clicked()
{

    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    maConfig.setValue("Langue", parametres::getLangue());

    qDebug()<<"Paramètre langue enregistré";

    this->close();
}
