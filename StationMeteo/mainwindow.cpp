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




MainWindow::MainWindow(QTranslator* pttranslator, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    if (parametres::getLangue()=="English")
        this->setWindowTitle("Weather Station");
    else
        this->setWindowTitle("Station Météo");


    this->traducteur=pttranslator;



    //--------------------------------------------------------------------
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
    //--------------------------------------------------------------------

    //Affichage en fonction du mode choisi
    modeaffichage();

    //Affichage Date en continue
    affDate();

    //Affichage Heure avec maj toutes les secondes
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
    timerRasp->setInterval(300000); //5min=300000 msec
    timerRasp->start();
    connect(timerRasp, SIGNAL(timeout()), this, SLOT(affMeteoMer()));
    connect(timerRasp, SIGNAL(timeout()), this, SLOT(affMeteoVille()));
    connect(timerRasp, SIGNAL(timeout()), this, SLOT(affPrevisions()));



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

void MainWindow::traduction()
{
    ui->retranslateUi(this);

    if (parametres::getLangue()=="English")
        this->setWindowTitle("Weather Station");
    else
        this->setWindowTitle("Station Météo");


    //ajout car n'apparait pas sinon
    affDate();
    affMeteoMer();


}

void MainWindow::modeaffichage()
{
    //MAJ de la police de la fenêtre principale

    QFont font = parametres::getPolice();
    font.setPointSize(10);

    ui->labelVille->setFont(font);
    ui->BtnMeteo->setFont(font);



    if (parametres::getMode()=="Jour")
    {
        qDebug()<< "Mode Jour";

        ui->centralwidget->setStyleSheet("background-color: rgb(225,211,200); color: black");
        ui->lineEditVille->setStyleSheet("background-color: white; color: black");
        ui->labelVille->setStyleSheet("color: black");

        //éléments oranges
        ui->BtnMeteo->setStyleSheet("background-color: #07575B; color: #DFF0D8; border-radius: 15px");
        ui->plainTextMeteo->setStyleSheet("background-color: #07575B; color: #DFF0D8");
        ui->lbliconmeteo->setStyleSheet("background-color: #07575B; color: #DFF0D8");
        ui->plainTextDate->setStyleSheet("background-color: #07575B; color: #DFF0D8");
        ui->lblDate->setStyleSheet("background-color: #07575B; color: #DFF0D8");
        ui->lcdNumber->setStyleSheet("background-color: #07575B; color: #DFF0D8");

        //éléments verts
        ui->plainTextPrevisions1->setStyleSheet("background-color: #66A5AD; color: white");
        ui->plainTextPrevisions2->setStyleSheet("background-color: #66A5AD; color: white");
        ui->plainTextPrevisions3->setStyleSheet("background-color: #66A5AD; color: white");
        ui->plainTextPrevisions4->setStyleSheet("background-color: #66A5AD; color: white");
        ui->plainTextPrevisions5->setStyleSheet("background-color: #66A5AD; color: white");
        ui->iconeJ1->setStyleSheet("background-color: rgb(102,165,173,0); color: white");
        ui->iconeJ2->setStyleSheet("background-color: rgb(102,165,173,0); color: white");
        ui->iconeJ3->setStyleSheet("background-color: rgb(102,165,173,0); color: white");
        ui->iconeJ4->setStyleSheet("background-color: rgb(102,165,173,0); color: white");
        ui->iconeJ5->setStyleSheet("background-color: rgb(102,165,173,0); color: white");

        //éléments bleus
        ui->label->setPixmap(QResource(":/pictures/pictures/mer.png").fileName());

        ui->labelMer->setStyleSheet("background-color: rgb(255,255,255,50); color: black; border-radius: 5px;");
        ui->labelTitreMer->setStyleSheet("background-color: rgb(255,255,255,50); color: black; border-radius: 5px;");
        ui->plainTextMer->setStyleSheet("background-color: #C4DFE6; color: black");


    }
    else if (parametres::getMode()=="Nuit")
    {
        qDebug()<< "Mode Nuit";

        ui->centralwidget->setStyleSheet("background-color: rgb(0,0,0)");
        ui->lineEditVille->setStyleSheet("background-color: black; color: white");
        ui->labelVille->setStyleSheet("color: #C4DFE6");

        //éléments oranges
        ui->BtnMeteo->setStyleSheet("background-color: rgb(50,50,50); color: rgb(255, 170, 0); border-radius: 15px");
        ui->plainTextDate->setStyleSheet("background-color: rgb(50,50,50); color: rgb(255, 170, 0)");
        ui->lblDate->setStyleSheet("background-color: rgb(50,50,50); color: rgb(255, 170, 0)");
        ui->lcdNumber->setStyleSheet("background-color: rgb(50,50,50); color: rgb(255, 170, 0)");
        ui->plainTextMeteo->setStyleSheet("background-color: rgb(50,50,50); color: rgb(255, 170, 0)");
        ui->lbliconmeteo->setStyleSheet("background-color: rgb(50,50,50); color: rgb(255, 170, 0)");

        //éléments verts
        ui->plainTextPrevisions1->setStyleSheet("background-color: rgb(25,25,25); color: rgb(89,255,117)");
        ui->plainTextPrevisions2->setStyleSheet("background-color: rgb(25,25,25); color: rgb(89,255,117)");
        ui->plainTextPrevisions3->setStyleSheet("background-color: rgb(25,25,25); color: rgb(89,255,117)");
        ui->plainTextPrevisions4->setStyleSheet("background-color: rgb(25,25,25); color: rgb(89,255,117)");
        ui->plainTextPrevisions5->setStyleSheet("background-color: rgb(25,25,25); color: rgb(89,255,117)");
        ui->iconeJ1->setStyleSheet("background-color: rgb(25,25,25,0); color: rgb(89,255,117)");
        ui->iconeJ2->setStyleSheet("background-color: rgb(25,25,25,0); color: rgb(89,255,117)");
        ui->iconeJ3->setStyleSheet("background-color: rgb(25,25,25,0); color: rgb(89,255,117)");
        ui->iconeJ4->setStyleSheet("background-color: rgb(25,25,25,0); color: rgb(89,255,117)");
        ui->iconeJ5->setStyleSheet("background-color: rgb(25,25,25,0); color: rgb(89,255,117)");

        //éléments bleus
        ui->label->setPixmap(QResource(":/pictures/pictures/mer_nuit_m.png").fileName());
        ui->labelMer->setStyleSheet("background-color: rgb(0,0,0,25);color: #C4DFE6; border-radius: 5px;");
        ui->labelTitreMer->setStyleSheet("background-color: rgb(0,0,0,25);color: #C4DFE6; border-radius: 5px;");
        ui->plainTextMer->setStyleSheet("background-color: rgb(75,75,75)");

    }
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

    qDebug() << "MAJ Date";


    QDateTime Date = QDateTime::currentDateTime();
    QLocale locale;
    QString dateaff;
    if (parametres::getLangue()=="Français")
    {
        locale=QLocale(QLocale::French, QLocale::Country::France);
        QLocale::setDefault(locale);
        dateaff=locale.toString(Date,"dddd dd MMMM");
    }
    else if (parametres::getLangue()=="English")
    {
        locale=QLocale(QLocale::English, QLocale::Country::UnitedKingdom);
        QLocale::setDefault(locale);
        dateaff=locale.toString(Date,"dddd, dd MMMM");
    }

    dateaff[0]=dateaff[0].toUpper();

    /**************************************/
    //MAJ de la police de la Date
    QFont font = parametres::getPolice();
    font.setPointSize(13);
    font.setBold(true);
    ui->lblDate->setFont(font);

    /**************************************/
    ui->lblDate->setText(dateaff);

}

void MainWindow::affMeteoville()
{
    qDebug() <<"MAJ MeteoVille";

    /**************************************/

    //MAJ de la police de affMeteoville
    ui->plainTextMeteo->setFont(parametres::getPolice());


    /**************************************/

    if (parametres::getUnite()=="Celsius")
        setUnite("metric");
    else if (parametres::getUnite()=="Fahrenheit")
        setUnite("imperial");
    if (parametres::getLangue()=="Français")
        setLangue("fr");
    else if (parametres::getLangue()=="English")
        setLangue("en");



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

    QString unit;
    if (parametres::getUnite()=="Celsius")
    {
        unit= "°C";
    }
    if (parametres::getUnite()=="Fahrenheit")
    {
        unit= "°F";
    }


    foreach(const QJsonValue &value, weather)
    {
        QJsonObject obj = value.toObject();
        //qDebug() << "description : " << obj["description"].toString();
        description=obj["description"].toString();
        //qDebug() << "CodeIcon : " << obj["icon"].toString();
        codeIcon= obj["icon"].toString();
        description[0]=description[0].toUpper();
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

    QString infosRecap = tr("%1 \n\nConditions Météo :   \n    %2 "
"\nTempérature :   \n    %3  %4\nTempérature Ressentie :   \n    %5  %6"
"\nPression atmosphérique :   \n    %7  hPa \nTaux d'Humidité :   \n    %8  %")
            .arg(ville).arg(description).
            arg(temperature).arg(unit).arg(tempressentie).arg(unit).arg(pression).arg(humidite);

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

    if (ui->lineEditVille->text()!="")
        villeSelec=ui->lineEditVille->text();

    affMeteoville();
    affPrevisions();

}

void MainWindow::affPrevisions()
{
    qDebug()<<"MAJ Prévisions";

    /**************************************/
    //MAJ de la police de affMeteoPrevisions
    ui->plainTextPrevisions1->setFont(parametres::getPolice());
    ui->plainTextPrevisions2->setFont(parametres::getPolice());
    ui->plainTextPrevisions3->setFont(parametres::getPolice());
    ui->plainTextPrevisions4->setFont(parametres::getPolice());
    ui->plainTextPrevisions5->setFont(parametres::getPolice());


    /**************************************/

    if (parametres::getUnite()=="Celsius")
        setUnite("metric");
    else if (parametres::getUnite()=="Fahrenheit")
        setUnite("imperial");
    if (parametres::getLangue()=="Français")
        setLangue("fr");
    else if (parametres::getLangue()=="English")
        setLangue("en");



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

    QString infosRecaptab [5];


    QString unit;
    if (parametres::getUnite()=="Celsius")
    {
        unit= " °C ";
    }
    if (parametres::getUnite()=="Fahrenheit")
    {
        unit= " °F ";
    }


    int indiceresult=0;

    foreach(const QJsonValue &value, Liste)
    {
        QJsonObject obj = value.toObject();

        dt_txt= obj["dt_txt"].toString();
        QDateTime dateconv =QDateTime::fromString(dt_txt,"yyyy-MM-dd hh:mm:ss");
        QLocale locale;
        QString dateaff;


        //qDebug()<<dateconv.toString("dddd dd MMMM '15H'");


        QDateTime Date = QDateTime::currentDateTime();
        QString date=Date.toString("yyyy-MM-dd");

        if (dt_txt.contains(" 15:00:00"))//&&!dt_txt.contains(date))

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

            if (parametres::getLangue()=="Français")
            {
                locale=QLocale(QLocale::French, QLocale::Country::France);
                QLocale::setDefault(locale);
                dateaff=locale.toString(dateconv,"dddd dd MMMM '15h'");
            }
            else if (parametres::getLangue()=="English")
            {
                locale=QLocale(QLocale::English, QLocale::Country::UnitedKingdom);
                QLocale::setDefault(locale);
                dateaff=locale.toString(dateconv,"dddd, dd MMMM '3pm'");
            }

            dateaff[0]=dateaff[0].toUpper();
            description[0]=description[0].toUpper();




        //Préaparation du tableau pour affichage dans plusieurs plaintext

            infosRecaptab[indiceresult]=tr("%1 \n\nConditions Météo :     \n    %2 "
        "\nTempérature :     %3 %4 \nTempérature Ressentie :     %5 %6  ").
                    arg(dateaff).arg(description).
                    arg(temperature).arg(unit).arg(tempressentie).arg(unit);

            indiceresult=indiceresult+1;

        }
    }


    //affichage icone et infosRecap

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

    qDebug() << "MAJ Meteo en Mer";

    /**************************************/
    //MAJ de la police de affMeteoville
    QFont font = parametres::getPolice();
    font.setPointSize(10);
    font.setBold(true);
    ui->labelTitreMer->setFont(font);
    ui->BtnMeteo->setFont(font);
    ui->labelVille->setFont(font);

    ui->labelMer->setFont(parametres::getPolice());



    /**************************************/


    if (parametres::getUnite()=="Celsius")
        setUnite("metric");
    else if (parametres::getUnite()=="Fahrenheit")
        setUnite("imperial");
    if (parametres::getLangue()=="Français")
        setLangue("fr");
    else if (parametres::getLangue()=="English")
        setLangue("en");

    //qDebug() << "SSL ? " << QSslSocket::supportsSsl();

    QNetworkRequest request(QUrl("http://78.199.78.207:48010/Releve_meteo.json"));
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
    qDebug() <<"responsedata"<< QString::fromStdString(response_data.toStdString());

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

    QString unit;
    if (parametres::getUnite()=="Celsius")
    {
        unit= "°C";
    }
    if (parametres::getUnite()=="Fahrenheit")
    {
        unit= "°F";
    }

    QString temperature=QString::number(temp);
    QString pression=QString::number(jsonObject["pressure"].toDouble());
    QString humidite=QString::number(jsonObject["humidity"].toDouble());


    //concaténation et affichage des infos

    ui->labelTitreMer->setText(tr("Conditions Météo en Mer :"));


    QString infosRecap = tr("Température :   \n    %1  %2"
"\n\nPression atmosphérique :   \n    %3  hPa\n\nTaux d'Humidité :   \n    %4  %")
            .arg(temperature).arg(unit).arg(pression).arg(humidite);
    //qDebug()<<infosRecap;
    ui->labelMer->setText(infosRecap);


}

void MainWindow::on_action_Administration_triggered()
{
    FenetreOptions = new DialogOptions(traducteur,tr("Paramètres"),this);
    FenetreOptions->show();
    connect(FenetreOptions, SIGNAL(modifmode()), this, SLOT(modeaffichage()));
    connect(FenetreOptions, SIGNAL(modifparam()), this, SLOT(affDate()));
    connect(FenetreOptions, SIGNAL(modifparam()), this, SLOT(affPrevisions()));
    connect(FenetreOptions, SIGNAL(modifparam()), this, SLOT(affMeteoville()));
    connect(FenetreOptions, SIGNAL(modifparam()), this, SLOT(affMeteoMer()));
    connect(FenetreOptions, SIGNAL(modifparam()), this, SLOT(traduction()));
}

void MainWindow::on_action_Quitter_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Quitter"));
    msgBox.setText(tr("Vous allez quitter le programme."));
    msgBox.setInformativeText(tr("Êtes-vous sûr?"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.button(QMessageBox::Yes)->setText(tr("Oui"));
    msgBox.button(QMessageBox::No)->setText(tr("Non"));

    int reponse = msgBox.exec();

    if (reponse == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}






