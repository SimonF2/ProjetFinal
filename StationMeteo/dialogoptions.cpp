#include "dialogoptions.h"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QString texte,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);

    if (!texte.isEmpty())
    {
        this->setWindowTitle(texte);
    }
}

DialogOptions::~DialogOptions()
{
    delete ui;
}
