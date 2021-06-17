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
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Station Météo de Mehdi et Simon");
    //this->setStyleSheet("border-radius: 5px;");
    //this->setStyleSheet("background-color: black; border-radius: 5px;");

    QSettings maConfig("parametres.ini", QSettings::IniFormat);
    parametres::setFormatHeure(maConfig.value("FormatHeure").toBool());
    parametres::setUnite(maConfig.value("Unite").toString());
    parametres::setLangue(maConfig.value("Langue").toString());


    //qDebug()<<"langue Mainwindow au démarrage:"<<getLangue();
    //qDebug()<<"unite Mainwindow au démarrage:"<<getUnite();

    //Mise à jour des parametres de MainWindow en fonction de la classe parametres
    if (parametres::getUnite()=="Celsius")
        setUnite("metric");
    else if (parametres::getUnite()=="Fahrenheit")
        setUnite("imperial");
    if (parametres::getLangue()=="Français")
        setLangue("fr");
    else if (parametres::getLangue()=="English")
        setLangue("en");

    qDebug()<<"langue Mainwindow suite MAJ via parametres:"<<getLangue();
    qDebug()<<"unite Mainwindow suite MAJ via parametres:"<<getUnite();


    //Affichage Date en continue
    affDate();

    //AFfichage Heure avec maj toutes les secondes
    affHeure(); // Affiche l'heure dès la première seconde
    timer = new QTimer();
    timer->setInterval(1000); //1000ms = 1 sec
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(affHeure())); // Affiche l'heure toutes les secondes

    //Affichage des 3 Météos avec maj toutes les 5min
    affMeteoville();
    affPrevisions();
    affMeteoMer();
    timerRasp = new QTimer();
    timerRasp->setInterval(60000); //5min=300000 msec
    timerRasp->start();
    connect(timerRasp, SIGNAL(timeout()), this, SLOT(affMeteoMer()));
    connect(timerRasp, SIGNAL(timeout()), this, SLOT(affMeteoVille()));
    connect(timerRasp, SIGNAL(timeout()), this, SLOT(affPrevisions()));







    //qDebug()<<"Premier test : " + parametres::getPolice().toString();
    //qDebug()<<"Bouton : " + ui->BtnMeteo->font().toString();



}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete FenetreOptions;
    delete timerRasp;
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
   if (parametres::getFormat24Heure()==true)
   {
       ui->lcdNumber->setDigitCount(8);
       ui->lcdNumber->display(parametres::getHeure());
   }
   if (parametres::getFormat24Heure()==false)
   {
       ui->lcdNumber->setDigitCount(11);
       ui->lcdNumber->display(parametres::getHeure());
   }
}

void MainWindow::affDate()
{
    QDateTime Date = QDateTime::currentDateTime();
    QString dateaff=Date.toString("dddd dd MMMM");
    dateaff[0]=dateaff[0].toUpper();
    ui->lblDate->setText(dateaff);
}

void MainWindow::affMeteoville()
{
    qDebug() <<"MAJ MeteoVille";
    //qDebug() << "SSL ? " << QSslSocket::supportsSsl();
    QString villeSelec = getVilleSelec();
    QString unite = getUnite();
    QString langue = getLangue();

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

    qDebug()<<"langue Mainwindow au moment de cliquer:"<<getLangue();
    qDebug()<<"unite Mainwindow au moment de cliquer:"<<getUnite();

    affMeteoville();
    //ui->plainTextPrevisions->clear();
    affPrevisions();

}

void MainWindow::affPrevisions()
{
    qDebug()<<"MAJ Prévisions";
    QString villeSelec = getVilleSelec();
    QString unite = getUnite();
    QString langue = getLangue();

    //qDebug() << "SSL ? " << QSslSocket::supportsSsl();

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


    //On se positionne sur le tableau "List"
    QJsonArray Liste = jsonObject["list"].toArray();
    //qDebug()<<"Nb : "<<Liste.count();

    QString dt_txt;
    QString temperature;
    QString tempressentie;
    QString pression;
    QString humidite;
    QString description;

    QString codeIcon [5];
    //QString infosRecap;
    QString infosRecaptab [5];


    int indiceresult=0;

    foreach(const QJsonValue &value, Liste)
    {
        QJsonObject obj = value.toObject();

        dt_txt= obj["dt_txt"].toString();
        //dt_txttab[indiceresult]=obj["dt_txt"].toString();

        if (dt_txt.contains(" 15:00:00"))

        {

            //on se positionne sur l'objet main
            QJsonObject main=obj["main"].toObject();
            //qDebug()<<"main count"<<main.count();
            //qDebug()<<"main keys"<<main.keys();
            temperature=QString::number(main["temp"].toDouble());

            tempressentie=QString::number(main["feels_like"].toDouble());

            pression=QString::number(main["pressure"].toDouble());

            humidite=QString::number(main["humidity"].toDouble());

            //on se positionne sur le tableau weather
            QJsonArray weather = obj["weather"].toArray();
            foreach(const QJsonValue &value, weather)
            {
                QJsonObject newobj = value.toObject();
                //qDebug() << "description : " << newobj["description"].toString();
                description=newobj["description"].toString();
                codeIcon[indiceresult]= newobj["icon"].toString();
            }
/*
        //Affichage dans un seul plaintext

            infosRecap = QString("%1 \n\nConditions Météo :     %2 "
        "\nTempérature :     %3 \nTempérature Ressentie :     %4 \n\n-------------------------------------------------------------").
                    arg(dt_txt).arg(description).
                    arg(temperature).arg(tempressentie);
            //qDebug()<<infosRecap;

            ui->plainTextPrevisions->appendPlainText(infosRecap);
*/
        //Préaparation du tableau pour affichage dans plusieurs plaintext

            infosRecaptab[indiceresult]=QString("%1 \n\nConditions Météo :     %2 "
        "\nTempérature :     %3 \nTempérature Ressentie :     %4  ").
                    arg(dt_txt).arg(description).
                    arg(temperature).arg(tempressentie);

            indiceresult=indiceresult+1;

        }
    }


    //affichage icone


    QLabel* ListeIcones[5]={ui->iconeJ1,ui->iconeJ2,ui->iconeJ3,ui->iconeJ4,ui->iconeJ5};
    QPlainTextEdit* ListePlaintext[5]={ui->plainTextPrevisions1,ui->plainTextPrevisions2,ui->plainTextPrevisions3,ui->plainTextPrevisions4,ui->plainTextPrevisions5};

    for (int i=0;i<5;i++)
    {
        //qDebug()<<"element "<<i<<" : "<<codeIcon[i];
        //qDebug() <<"element "<<i<<" : "<<infosRecaptab[i];

        ListePlaintext[i]->setPlainText(infosRecaptab[i]);



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

void MainWindow::affMeteoMer()
{
    //qDebug() << "SSL ? " << QSslSocket::supportsSsl();
    qDebug() << "Mise à jour Meteo en Mer";

    QNetworkRequest request(QUrl("http://82.65.244.166:48010/Releve_meteo.json"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager nam;

    QNetworkReply *reply = nam.get(request);

    while(!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();

    QByteArray response_data = reply->readAll();

    //qDebug() << "Size: " << response_data.size();
    //qDebug() <<"responsedata"<< QString::fromStdString(response_data.toStdString());

    //Conversion du ByteArray en Json
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);

    //On se positionne sur l'objet principal
    QJsonObject jsonObject = jsonResponse.object();

    //qDebug() << jsonObject.value("sensor").toString();
    //qDebug() << jsonObject["sensor"].toString();
    //qDebug() << jsonObject.keys();

    double temp=0;
    if (parametres::getUnite()=="Celsius")
    {
        temp=jsonObject["temperature"].toDouble();
    }
    else if (parametres::getUnite()=="Fahrenheit")
    {
        temp=(jsonObject["temperature"].toDouble()*9/5) + 32;
    }

    QString temperature=QString::number(temp);
    QString pression=QString::number(jsonObject["pressure"].toDouble());
    QString humidite=QString::number(jsonObject["humidity"].toDouble());


    //concaténation et affichage des infos

    QString infosRecap = QString("Température :   \n  %1 "
"\n\nPression atmosphérique (hPa) :   \n  %2 \n\nTaux d'Humidité (%) :   \n  %3").
            arg(temperature).arg(pression).arg(humidite);
    //qDebug()<<infosRecap;
    ui->labelMer->setText(infosRecap);


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




