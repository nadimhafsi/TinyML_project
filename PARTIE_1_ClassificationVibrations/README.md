# PARTIE 1 – Classification des Vibrations

## 1. Objectif

Cette partie du projet consiste à créer un système capable de **classer différents niveaux de vibration** à partir des données d'un **IMU (accéléromètre + gyroscope)** sur Arduino Nano 33 BLE.  

Les classes de vibration :

| Classe | Description |
|-------|-------------|
| idle  | Pas de vibration |
| normal | Vibration normale |
| high  | Vibration forte |

---

## 2. Collecte des données

Le fichier Arduino utilisé pour la collecte des données :  
`1-DataGeneration_Arduino/data_generation.ino`  

Le programme lit les données IMU et les envoie au PC au format CSV :  
![Architecture projet](https://drive.google.com/uc?export=download&id=1mlT16ec7p0rEYS0jFpizkr3lV9C3n5o6)
