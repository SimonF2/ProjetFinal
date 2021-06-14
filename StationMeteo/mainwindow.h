#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QLabel>

#include "dialogoptions.h"
#include "parametres.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void affDate();


protected:
    void closeEvent(QCloseEvent *event);



private slots:
    void affHeure();
    void on_action_Administration_triggered();
    void on_action_Quitter_triggered();
    void on_BtnMeteo_clicked();


private:
    Ui::MainWindow *ui;
    DialogOptions* FenetreOptions;
    QTimer* timer; //Declenche un traitement à intervalle régulier


};
#endif // MAINWINDOW_H
