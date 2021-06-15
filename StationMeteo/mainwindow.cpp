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


    qDebug()<<"Langue parametres initiale" << parametres::getLangue();
    qDebug()<<"Unite parametres initiale" << parametres::getUnite();


    if (parametres::getUnite()=="Celsius")
        setUnite("metric");
    else if (parametres::getUnite()=="Fahrenheit")
        setUnite("imperial");
    if (parametres::getLangue()=="Français")
        setLangue("fr");
    else if (parametres::getLangue()=="English")
        setLangue("en");

    qDebug()<<"Langue mainWindow initiale" << getLangue();
    qDebug()<<"Unite mainWindow initiale" << getUnite();

    //affMeteoville(villeSelec,unite,langue);






    //qDebug()<<"Premier test : " + parametres::getPolice().toString();
    //qDebug()<<"Bouton : " + ui->BtnMeteo->font().toString();



}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete FenetreOptions;
}


void MainWindow::setLangue(const QString &value)
{
    langue = value;
}

void MainWindow::setUnite(const QString &value)
{
    unite = value;
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

void MainWindow::affMeteoville(QString villeSelec, QString unite, QString langue)
{

    //qDebug() << "SSL ? " << QSslSocket::supportsSsl();

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
        //qDebug() << "CodeIcon : " << obj["icon"].toString();
        codeIcon= obj["icon"].toString();

    }



    //On se positionne sur l'objet "main"
    QJsonObject infos = jsonObject["main"].toObject();
    //qDebug()<<infos.count();
    //qDebug()<<infos.keys();

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
    //qDebug()<<infosRecap;
    ui->plainTextMeteo->setPlainText(infosRecap);


    //affichage icone
    ui->lbliconmeteo->setScaledContents(true);
    if (codeIcon=="01d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/01d_clear_sky.png").fileName());
    else if (codeIcon=="02d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/02d_few_clouds.png").fileName());
    else if (codeIcon=="03d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/03d_scattered_clouds.png").fileName());
    else if (codeIcon=="04d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/04d_broken_clouds.png").fileName());
    else if (codeIcon=="09d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/09d_shower_rain.png").fileName());
    else if (codeIcon=="10d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/10d_rain.png").fileName());
    else if (codeIcon=="11d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/11d_thunderstorm.png").fileName());
    else if (codeIcon=="13d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/13d_snow.png").fileName());
    else if (codeIcon=="50d")
        ui->lbliconmeteo->setPixmap(QResource(":/icons/icons/50d_mist.png").fileName());



}


void MainWindow::on_BtnMeteo_clicked()
{
    //qDebug()<<ui->lineEditVille->text();

    if (ui->lineEditVille->text()!="")
        villeSelec=ui->lineEditVille->text();

    if (parametres::getUnite()=="Celsius")
        setUnite("metric");
    else if (parametres::getUnite()=="Fahrenheit")
        setUnite("imperial");
    if (parametres::getLangue()=="Français")
        setLangue("fr");
    else if (parametres::getLangue()=="English")
        setLangue("en");

    qDebug()<<"langue au moment de cliquer:"<<getLangue();
    qDebug()<<"unite au moment de cliquer:"<<getUnite();

    //affMeteoville(villeSelec, unite, langue);

}

void MainWindow::on_BtnPrevisions_clicked()
{
    QDateTime DateTime = QDateTime::currentDateTime();
    QString Date=DateTime.toString("yyyy-MM-dd");
    qDebug()<<Date;

    qDebug() << "SSL ? " << QSslSocket::supportsSsl();

    QString villeSelec="Paris";
    //en fonction de ce qui est rentré ou séléctionné
    QString unite="metric";
    //imperial
    QString langue="fr";
    //en

    QNetworkRequest request(QUrl("http://api.openweathermap.org/data/2.5/forecast?appid=fe47ec6aff6db6e77d8d9fbe73db9f10&cnt=40&q="+villeSelec+"&units="+unite+"&lang="+langue));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager nam;

    QNetworkReply *reply = nam.get(request);

    while(!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();

    QByteArray response_data = reply->readAll();


    //Conversion du ByteArryay en Json
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);

    //On se positionne sur l'objet principal
    QJsonObject jsonObject = jsonResponse.object();


    int cnt =jsonObject["cnt"].toInt();
    qDebug()<<QString::number(cnt);




    //On se positionne sur le tableau "List"
    QJsonArray Liste = jsonObject["list"].toArray();
    qDebug()<<"Nb : "<<Liste.count();

    QString dt_txt;
    QString temperature;
    QString tempressentie;
    QString pression;
    QString humidite;
    QString description;
    QString codeIcon [5];
    int indiceresult=0;

    foreach(const QJsonValue &value, Liste)
    {
        QJsonObject obj = value.toObject();

        dt_txt= obj["dt_txt"].toString();

        if (dt_txt.contains(" 12:00:00")&&!dt_txt.contains(Date))
        {
            qDebug()<< "dt texte: "<<dt_txt;

            //on se positionne sur l'objet main
            QJsonObject main=obj["main"].toObject();
            //qDebug()<<"main count"<<main.count();
            //qDebug()<<"main keys"<<main.keys();
            temperature=QString::number(main["temp"].toDouble());
            tempressentie=QString::number(main["feels_like"].toDouble());
            pression=QString::number(main["pressure"].toDouble());
            humidite=QString::number(main["humidity"].toDouble());


            QJsonArray weather = obj["weather"].toArray();
            foreach(const QJsonValue &value, weather)
            {
                QJsonObject newobj = value.toObject();
                //qDebug() << "description : " << newobj["description"].toString();
                description=newobj["description"].toString();
                qDebug() << "CodeIcon : " << newobj["icon"].toString();


                codeIcon[indiceresult]= newobj["icon"].toString();
                indiceresult=indiceresult+1;
            }


            QString infosRecap = QString("%1 \n\nConditions Météo :     %2 "
        "\nTempérature :     %3 \nTempérature Ressentie :     %4 \n\n-------------------------------------------------------------").
                    arg(dt_txt).arg(description).
                    arg(temperature).arg(tempressentie);
            //qDebug()<<infosRecap;

            ui->plainTextPrevisions->appendPlainText(infosRecap);

        }
    }
    //affichage icone

    QLabel* ListeIcones[5]={ui->iconeJ1,ui->iconeJ2,ui->iconeJ3,ui->iconeJ4,ui->iconeJ5};

    for (int i=0;i<5;i++)
    {
        qDebug()<<"element "<<i<<" : "<<codeIcon[i];


            if (codeIcon[i]=="01d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/01d_clear_sky.png").fileName());
            else if (codeIcon[i]=="02d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/02d_few_clouds.png").fileName());
            else if (codeIcon[i]=="03d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/03d_scattered_clouds.png").fileName());
            else if (codeIcon[i]=="04d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/04d_broken_clouds.png").fileName());
            else if (codeIcon[i]=="09d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/09d_shower_rain.png").fileName());
            else if (codeIcon[i]=="10d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/10d_rain.png").fileName());
            else if (codeIcon[i]=="11d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/11d_thunderstorm.png").fileName());
            else if (codeIcon[i]=="13d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/13d_snow.png").fileName());
            else if (codeIcon[i]=="50d")
                ListeIcones[i]->setPixmap(QResource(":/icons/icons/50d_mist.png").fileName());

    }

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




