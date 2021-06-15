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
    void affMeteoville(QString ville, QString unite, QString langue);


    void setUnite(const QString &value);
    void setLangue(const QString &value);

    QString getUnite() const {return unite;}
    QString getLangue() const {return langue;}

protected:
    void closeEvent(QCloseEvent *event);



private slots:
    void affHeure();
    void on_action_Administration_triggered();
    void on_action_Quitter_triggered();
    void on_BtnMeteo_clicked(); //équivalent set ville


    void on_BtnPrevisions_clicked();

private:
    Ui::MainWindow *ui;
    DialogOptions* FenetreOptions;
    QTimer* timer; //Declenche un traitement à intervalle régulier
    QString villeSelec = "Paris";
    QString unite;
    QString langue;

};
#endif // MAINWINDOW_H
