#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include "parametres.h"
#include <QDialog>
#include <QTimer>


namespace Ui {
class DialogOptions;
}

class DialogOptions : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOptions(QString,QWidget *parent);
    ~DialogOptions();

signals:
    void modifparam();
    void modifmode();

private slots:
    void affHeure();

    void on_rdBtn12_clicked();

    void on_rdBtn24_clicked();

    void on_comboBoxLangue_currentTextChanged(const QString &arg1);

    void on_BtnPolice_clicked();

    void on_rdBtnC_clicked();

    void on_rdBtnFar_clicked();

    void on_buttonBox_accepted();

    void on_rdBtnJour_clicked();

    void on_rdBtnNuit_clicked();

private:
    Ui::DialogOptions *ui;
    QTimer* timer;
};

#endif // DIALOGOPTIONS_H
