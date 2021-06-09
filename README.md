
Projet de Fin de Formation
L�objectif de ce projet est de concevoir une Station M�t�o. Cette Station M�t�o permettra de fournir certaines informations. Les fonctionnalit�s demand�es seront d�taill�es par la suite. 

On souhaite afficher sur cette station M�t�o des informations m�t�orologiques de 2 points g�ographiques diff�rents : 
      
      - en mer 
      - d'une ville choisie 

Dans un premier temps, nous d�taillerons le mat�riel mis � disposition. Dans un second temps, nous citerons les diff�rentes fonctionnalit�s attendues. Enfin, vous aurez quelques informations sur la pr�sentation � effectuer le jour de la soutenance.




Cette balise positionn�e en plein coeur de la Mer est �quip�e des �l�ments suivants : 
 - Raspberry Pi 3 Model B+ : 
 o Marque : U:Create 
 o Processeur : ARM 
 o Vitesse du processeur : 1.40 GHz 
 o Nombre de coeurs : 4 
 o Taille de la m�moire vive : 1GB 
 o Type de technologie sans fil : 802.11bgn, 802.11ac 
 o Nombre de ports USB 2.0 : 4 
 

 - Capteurs d'humidit� BME280 : 
 o capteur environnemental int�gr� d�velopp� sp�cifiquement pour les applications mobiles 
 o� la taille et la faible consommation d'�nergie sont des contraintes de conception essentielles. 
 o Tension d'alimentation : 1,8 - 5V DC 
 o Interface : I2C (up to 3.4MHz), SPI (up to 10 MHz) 
 o Temp�rature : -40 � + 85 � C 
 o Humidit� : 0-100% 
 o Pression : 300-1100 hPa 
 o Temp�rature : 0.01 � C 
 o Humidit� : 0.008% 
 o Type de Processeur : ARM710 
 o Pression : 0.18Pa 
 o Temp�rature : + -1 � C 
 o Humidit� : + -3% 
 o Pression : + -1Pa 
 o Adresse I2C 
 o SDO LOW : 0x76 
 o SDO HIGH : 0x77 
 

Cette balise M�t�o est en �tat de fonctionnement. Pour preuve, un programme python sur la balise renvoie les informations. Ci-dessous, les informations renvoy�es par le programme python. 


Afin de disposer de ces donn�es, vous avez la possibilit� de vous y connecter via le protocole SSH. Toutes les informations de connexion (adresse IP, login et mot de passe) vous seront communiqu�es ult�rieurement.

De plus, vous proposerez une solution permettant d'afficher les informations m�t�orologiques � partir d'une ville choisie. Vous justifierez la solution pour laquelle vous avez opt�e. 

Afin de bien d�finir les �l�ments attendus au niveau de l'interface graphique de la Station M�t�o, voici la liste des fonctionnalit�s requises : 
- Affichage de l'heure et de la date 

- Au niveau de la balise situ�e en Mer : 
 o Temp�rature en �C/�F de -40�C � 50�C 
 o R�solution : 0.1�C relev� toutes les minutes 
 o Taux d�humidit� 
 o Pression 


- Au niveau de la temp�rature de la ville : 
      o Temp�rature en �C/�F de -40�C � 50�C 
 o R�solution : 0.1�C relev� toutes les minutes 
 o Gestion de l�affichage de pictogrammes associ�s 
 o Affichage de la Ville 
 o Graphique pr�visionnel pour les 5 jours suivants 
 

Par ailleurs, on disposera d�une interface � Administration � permettant de configurer certains param�tres :
	
> Section Affichage : 
? Format de l�heure 12 ou 24H
? Choix de la Ville
? Unit� de Temp�rature Fahrenheit ou Celsius
? Possibilit� de choisir les styles d�affichage :
- Famille de Police
- Couleur
o Chaque style sera d�clin� en Mode Jour/Nuit
      ? Choix de la langue :
- Anglais
- Fran�ais


Facultatif : 

S'il vous reste du temps, vous enregistrerez toutes les heures les informations de la balise au sein d'une base de donn�es. Le but sera d'afficher la temp�rature moyenne des 12 derni�res heures et de l'afficher au sein de votre station.



L�ensemble des travaux r�alis�s devront �tre mis sur un d�p�t afin de centraliser les informations et de faciliter la communication entre les membres du projet. Vous ferez en sorte de bien vous r�partir les t�ches. 

Vous constituerez une pr�sentation (PowerPoint ou �quivalent) qui vous servira de fil conducteur pour le jour de la soutenance. Lors de la soutenance, il va de soi que le temps de parole entre chacun des membres du groupe devra �tre �quilibr�.



Informations Techniques : 

Branchements du Capteur BME280 sur le Raspberry :



1


