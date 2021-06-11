#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include <QDialog>

namespace Ui {
class DialogOptions;
}

class DialogOptions : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOptions(QString,QWidget *parent);
    ~DialogOptions();

private:
    Ui::DialogOptions *ui;
};

#endif // DIALOGOPTIONS_H
