
Projet de Fin de Formation
L’objectif de ce projet est de concevoir une Station Météo. Cette Station Météo permettra de fournir certaines informations. Les fonctionnalités demandées seront détaillées par la suite. 

On souhaite afficher sur cette station Météo des informations météorologiques de 2 points géographiques différents : 
      
      - en mer 
      - d'une ville choisie 

Dans un premier temps, nous détaillerons le matériel mis à disposition. Dans un second temps, nous citerons les différentes fonctionnalités attendues. Enfin, vous aurez quelques informations sur la présentation à effectuer le jour de la soutenance.




Cette balise positionnée en plein coeur de la Mer est équipée des éléments suivants : 
 - Raspberry Pi 3 Model B+ : 
 o Marque : U:Create 
 o Processeur : ARM 
 o Vitesse du processeur : 1.40 GHz 
 o Nombre de coeurs : 4 
 o Taille de la mémoire vive : 1GB 
 o Type de technologie sans fil : 802.11bgn, 802.11ac 
 o Nombre de ports USB 2.0 : 4 
 

 - Capteurs d'humidité BME280 : 
 o capteur environnemental intégré développé spécifiquement pour les applications mobiles 
 où la taille et la faible consommation d'énergie sont des contraintes de conception essentielles. 
 o Tension d'alimentation : 1,8 - 5V DC 
 o Interface : I2C (up to 3.4MHz), SPI (up to 10 MHz) 
 o Température : -40 à + 85 ° C 
 o Humidité : 0-100% 
 o Pression : 300-1100 hPa 
 o Température : 0.01 ° C 
 o Humidité : 0.008% 
 o Type de Processeur : ARM710 
 o Pression : 0.18Pa 
 o Température : + -1 ° C 
 o Humidité : + -3% 
 o Pression : + -1Pa 
 o Adresse I2C 
 o SDO LOW : 0x76 
 o SDO HIGH : 0x77 
 

Cette balise Météo est en état de fonctionnement. Pour preuve, un programme python sur la balise renvoie les informations. Ci-dessous, les informations renvoyées par le programme python. 


Afin de disposer de ces données, vous avez la possibilité de vous y connecter via le protocole SSH. Toutes les informations de connexion (adresse IP, login et mot de passe) vous seront communiquées ultérieurement.

De plus, vous proposerez une solution permettant d'afficher les informations météorologiques à partir d'une ville choisie. Vous justifierez la solution pour laquelle vous avez optée. 

Afin de bien définir les éléments attendus au niveau de l'interface graphique de la Station Météo, voici la liste des fonctionnalités requises : 
- Affichage de l'heure et de la date 

- Au niveau de la balise située en Mer : 
 o Température en °C/°F de -40°C à 50°C 
 o Résolution : 0.1°C relevé toutes les minutes 
 o Taux d’humidité 
 o Pression 


- Au niveau de la température de la ville : 
      o Température en °C/°F de -40°C à 50°C 
 o Résolution : 0.1°C relevé toutes les minutes 
 o Gestion de l’affichage de pictogrammes associés 
 o Affichage de la Ville 
 o Graphique prévisionnel pour les 5 jours suivants 
 

Par ailleurs, on disposera d’une interface « Administration » permettant de configurer certains paramètres :
	
> Section Affichage : 
? Format de l’heure 12 ou 24H
? Choix de la Ville
? Unité de Température Fahrenheit ou Celsius
? Possibilité de choisir les styles d’affichage :
- Famille de Police
- Couleur
o Chaque style sera décliné en Mode Jour/Nuit
      ? Choix de la langue :
- Anglais
- Français


Facultatif : 

S'il vous reste du temps, vous enregistrerez toutes les heures les informations de la balise au sein d'une base de données. Le but sera d'afficher la température moyenne des 12 dernières heures et de l'afficher au sein de votre station.



L’ensemble des travaux réalisés devront être mis sur un dépôt afin de centraliser les informations et de faciliter la communication entre les membres du projet. Vous ferez en sorte de bien vous répartir les tâches. 

Vous constituerez une présentation (PowerPoint ou équivalent) qui vous servira de fil conducteur pour le jour de la soutenance. Lors de la soutenance, il va de soi que le temps de parole entre chacun des membres du groupe devra être équilibré.



Informations Techniques : 

Branchements du Capteur BME280 sur le Raspberry :



1


