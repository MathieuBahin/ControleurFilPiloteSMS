# Controleur radiateur avec fil pilote par SMS

Bonjour à tous je vous propose aujourd'hui un projet pour contrôler un radiateur par SMS. Le radiateur doit posséder l'option "Fil pilote".

Mon besoin est de pouvoir piloter la mise en marche d'un radiateur situé dans une résidence secondaire à distance. L'idée est de pouvoir envoyer un ordre à une unité réceptrice qui va allumer le radiateur et me permettre d'arriver 1/2 jours plus tard avec une température correcte dans la résidence.

Des produits similaires existent mais la plupart proposent une communication par Internet, non compatible avec la configuration de la résidence secondaire.

Attention vous allez manipuler des courants mortels je vous conseille une grande vigilance lors des manipulations.

## Electronique





### La communication par fil pilote
On retrouve ci-dessous les commandes pour piloter le radiateur :

<img src="https://github.com/MathieuBahin/ControleurFilPiloteSMS/blob/main/Image/Commande.jpg" width="600" >

[Source](https://www.planete-domotique.com/blog/2012/01/05/piloter-un-radiateur-grace-a-son-fil-pilote/)

Le radiateur est donc piloté grâce à la sinusoïde 230V.

Pour créer les demi-alternances positives et négatives on utilise les optocoupleurs et les diodes.

En effet une diode dans le sens passant du 230V créer une demi-alternance positive et une diode dans le sens non passant crée une demi-alternance négative. Les optocoupleurs permettent de choisir si le chemin positif, négatif ou les deux sont utilisés.

### Composants utilisés
Pour le projet voici les composants utilisés : 

| Nom                  |  Coût |
| --------------------- |:-----:|
| Arduino Nano x1          |   2€  |
| [SIM800L](https://www.amazon.fr/Sim800l-Quadribande-Embarqu%C3%A9e-Antenne-Arduino/dp/B01FQPLG9W) x1     | 6€ |
| [DS18B20](https://www.amazon.fr/ANGEEK-capteurs-temp%C3%A9rature-num%C3%A9riques-TO92-55%C2%B0C/dp/B07VB25GS5/) x1        |  8€ pour 5 |
| [IRM-10-5](https://fr.rs-online.com/web/p/alimentations-a-decoupage/1358929/)    x1        |  10€   |
| [ZFKDS gauche](https://fr.rs-online.com/web/p/borniers-pour-circuits-imprimes/8045105/)  x1    | 0.50€ |
| [ZFKDS droit](https://fr.rs-online.com/web/p/borniers-pour-circuits-imprimes/8045102/)   x1  | 16.70€ pour 50 |
| [MOC3023M](https://fr.rs-online.com/web/p/optocoupleurs/6711422/) x2    | 2.59€ pour 5 |
| Résistance 4.7k x1    | |
| Résistance 1.8k x1    | |
| Résistance 1k x1    | |
| Résistance 680 x2    | |
| Résistance 330 x2    | |
| Diode 1N4007 x3    | |
| Condensateur 100uF    | |
| LED (optionnel) x3    | |

Les LED, le capteur de température et les résistances associées sont optionnels.
Les connecteurs ZFKDS peuvent être remplacés par des borniers etc.
Le condensateur n'est pas optionnel.

## Projet KiCad
Les fichiers KiCad sont situés dans le dossier KiCad. Les PCB sont gravés chez [JLCPCB](https://jlcpcb.com/).

Attention pour le module SIM800L a la tension d'alimentation qui est spéciale. J'utilise la tension de chute de la diode pour l'alimenter selon la datasheet. Un pont diviseur est également nécessaire pour la communication UART (5V → 3.3V).

Une fois le PCB reçu je vous conseille de souder le transformateur en dernier.

Si vous souhaitez faire une vérification sur le 230V à la sortie du fil pilote noté que votre multimètre ne vous indiquera pas 230/2V et si vous souhaitez vérifier avec un oscilloscope faite attention à utiliser une sonde différentielle !

<img src="https://github.com/MathieuBahin/ControleurFilPiloteSMS/blob/main/Image/PCB.jpg" width="600" >

<img src="https://github.com/MathieuBahin/ControleurFilPiloteSMS/blob/main/Image/PCBa.jpg" width="600" >

## Développement Arduino
Vous pouvez utiliser l'IDE de votre choix j'utilise personnellement l'IDE Arduino.

Ajoutez les librairies dans votre dossier Arduino (généralement Documents\Arduino\libraries) sinon depuis l'IDE "Croquis → Inclure une bibliothèque"

Dans Outil choisissez votre carte : Arduino Nano et le processeur qui correspond à votre carte.

Puis connectez votre Arduino et flashez le programme.

Vous pouvez ouvrir le moniteur série à 9600 pour voir l'initialisation des composants.

Le projet est en pause le temps de recevoir la carte SIM et de terminer la programmation.

## Imprimante 3D

Les modèles ne sont pas encore figés ils sont à l'étude.


## Installation derrière le radiateur

A faire + documenter.
