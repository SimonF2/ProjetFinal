#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Station Météo de Mehdi et Simon");



    affDate();
    affHeure(); // Affiche l'heure dès la première seconde
    timer = new QTimer();
    timer->setInterval(1000); //1000ms = 1 sec
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(affHeure())); // Affiche l'heure toutes les secondes

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete FenetreOptions;
}

void MainWindow::affHeure()
{
    QDateTime Heure =  QDateTime::currentDateTime();

    ui->lblHeure->setText(Heure.toString("hh:mm:ss"));
    if (ui->rdBtn24->isChecked())
    {
        ui->lblHeure->setText(Heure.toString("hh:mm:ss"));
    }
    else if (ui->rdBtn12->isChecked())
    {
        ui->lblHeure->setText(Heure.toString("h:m:s ap"));
    }
}


void MainWindow::affDate()
{
    QDateTime Date = QDateTime::currentDateTime();
    ui->lblDate->setText(Date.toString("dddd dd MMMM yyyy"));
}



void MainWindow::on_BtnMeteo_clicked()
{
    qDebug() << "SSL ? " << QSslSocket::supportsSsl();

    QString villeSelec="Paris";
    //en fonction de ce qui est rentré ou séléctionné
    QString unite="metric";
    //imperial
    QString langue="fr";
    //en


    QNetworkRequest request(QUrl("http://api.openweathermap.org/data/2.5/weather?appid=fe47ec6aff6db6e77d8d9fbe73db9f10&q="+villeSelec+"&units="+unite+"&lang="+langue));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager nam;

    QNetworkReply *reply = nam.get(request);

    while(!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();

    QByteArray response_data = reply->readAll();

    //qDebug() << "SizeResponse: " << response_data.size();

    //Conversion du ByteArryay en Json
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);

    //On se positionne sur l'objet principal
    QJsonObject jsonObject = jsonResponse.object();

    QString ville=jsonObject["name"].toString().toUpper();



    //On se positionne sur le tableau "weather"
    QJsonArray weather = jsonObject["weather"].toArray();

    QString description;
    foreach(const QJsonValue &value, weather)
    {
        QJsonObject obj = value.toObject();
        //qDebug() << "description : " << obj["description"].toString();
        description=obj["description"].toString();
        qDebug() << "Code icône : " << obj["icon"].toString();
    }



    //On se positionne sur l'objet "main"
    QJsonObject infos = jsonObject["main"].toObject();
    qDebug()<<infos.count();
    qDebug()<<infos.keys();

    double temp=infos["temp"].toDouble();
    QString temperature=QString::number(temp);
    double tempres=infos["feels_like"].toDouble();
    QString tempressentie=QString::number(tempres);
    double pres=infos["pressure"].toDouble();
    QString pression=QString::number(pres);
    double hum=infos["humidity"].toDouble();
    QString humidite=QString::number(hum);


    //concaténation et affichage des infos

    QString infosRecap = QString("%1 \nConditions Météo :   \n  %2 "
"\nTempérature :   \n  %3 \nTempérature Ressentie :   \n  %4 "
"\nPression atmosphérique (hPa) :   \n  %5 \nTaux d'Humidité (%) :   \n  %6").
            arg(ville).arg(description).
            arg(temperature).arg(tempressentie).arg(pression).arg(humidite);
    qDebug()<<infosRecap;
    ui->plainTextMeteo->setPlainText(infosRecap);

}

void MainWindow::on_action_Administration_triggered()
{
    FenetreOptions = new DialogOptions("Paramètres",this);
    FenetreOptions->show();
}

void MainWindow::on_action_Quitter_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Quitter");
    msgBox.setText("Vous allez quitter le programme.");
    msgBox.setInformativeText("Êtes-vous sûr?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);


    int reponse = msgBox.exec();

    if (reponse == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}


