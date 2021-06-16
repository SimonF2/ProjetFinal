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
    void affMeteoville();
    void affPrevisions();


    void setUnite(const QString &value);
    void setLangue(const QString &value);

    QString getUnite() const {return unite;}
    QString getLangue() const {return langue;}
    QString getVilleSelec() const {return villeSelec;}

protected:
    void closeEvent(QCloseEvent *event);



private slots:
    void affHeure();
    void affMeteoMer();
    void on_action_Administration_triggered();
    void on_action_Quitter_triggered();
    void on_BtnMeteo_clicked(); //équivalent set ville



private:
    Ui::MainWindow *ui;
    DialogOptions* FenetreOptions;
    QString villeSelec = "Paris";
    QString unite;
    QString langue;
    QTimer* timer; //Declenche un traitement à intervalle régulier
    QTimer* timerRasp;

};
#endif // MAINWINDOW_H
