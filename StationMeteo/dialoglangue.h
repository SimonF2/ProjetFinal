#ifndef DIALOGLANGUE_H
#define DIALOGLANGUE_H
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class Dialoglangue;
}

class Dialoglangue : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoglangue(QWidget *parent = nullptr);
    ~Dialoglangue();


private slots:
    void on_ValidLangue_clicked();
    void on_comboBoxLangue_currentTextChanged(const QString &arg1);

private:
    Ui::Dialoglangue *ui;


};

#endif // DIALOGLANGUE_H
