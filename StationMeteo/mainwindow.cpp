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
#include <QResource>


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

    parametres Options;
    qDebug()<<"Premier test : " + Options.getPolice().toString();
    qDebug()<<"Bouton : " + ui->BtnMeteo->font().toString();



}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete FenetreOptions;
}

void MainWindow::affHeure()
{
   ui->lblHeure->setText(parametres::getHeure());
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
    QString codeIcon;
    foreach(const QJsonValue &value, weather)
    {
        QJsonObject obj = value.toObject();
        //qDebug() << "description : " << obj["description"].toString();
        description=obj["description"].toString();
        qDebug() << "CodeIcon : " << obj["icon"].toString();
        codeIcon= obj["icon"].toString();

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


    //affichage icone
    ui->lbliconmeteo->setScaledContents(true);
    if (codeIcon=="01d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/01d_soleil.png").fileName());
    else if (codeIcon=="02d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/02d_nuageux.png").fileName());
    else if (codeIcon=="03d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/03d_couvert.png").fileName());
    else if (codeIcon=="04d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/04d_pluvieux.png").fileName());
    else if (codeIcon=="09d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/09d_fortes_pluies.png").fileName());
    else if (codeIcon=="10d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/10d_soleil_pluies.png").fileName());
    else if (codeIcon=="11d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/11d_orages.png").fileName());
    else if (codeIcon=="13d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/13d_neige.png").fileName());
    else if (codeIcon=="50d")
    ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/50d_Brouillard.png").fileName());

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


