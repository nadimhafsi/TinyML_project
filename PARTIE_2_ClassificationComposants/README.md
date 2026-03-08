# PARTIE 2 – Classification et comptage de composants électroniques

## 1. Objectif

L'objectif de cette partie est de créer un système capable de **reconnaître différents composants électroniques** (LED, résistances, condensateurs, diodes, etc.) à partir d'une caméra OV7670 connectée à l'Arduino Nano 33 BLE, et de **transmettre les résultats à Node-RED** pour le comptage et l'affichage en temps réel.

---

## 2. Étapes principales

### 2.1 Projet Edge Impulse

- Le modèle de classification est entraîné sur **Edge Impulse**.  
- Le dataset contient plusieurs classes de composants ainsi qu’un fond (**background**).  
- Chaque image du dataset a été importée et étiquetée dans Edge Impulse.  
- L’Impulse (pipeline) d’Edge Impulse est configuré pour :  
  - Prétraitement des images  
  - Extraction des features  
  - Entraînement du modèle de classification  
- Après l’entraînement, le modèle est exporté pour Arduino en **bibliothèque Edge Impulse**.

Fichiers dans le dossier `1-EdgeImpulse/` :

| Fichier | Description |
|---------|-------------|
| link_to_edge_impulse.md | Contient le lien vers le projet Edge Impulse |
| instructions.md | Instructions détaillées pour l’import du dataset et l’entraînement sur Edge Impulse |

---

### 2.2 Inférence sur Arduino avec la caméra OV7670

- Sketch principal : `ArduinoCamera/arduino_camera_classification.ino`  
- Fonctionnalités :  
  - Initialisation de la caméra OV7670  
  - Capture des images  
  - Prétraitement des images pour Edge Impulse  
  - Inference du modèle pour identifier la classe du composant  
  - Affichage du résultat dans le **Serial Monitor**

---

### 2.3 Transmission des résultats à Node-RED

- Les prédictions sont envoyées via **Serial** (format : `CLASS:<label>`)  
- Node-RED reçoit la classe détectée et incrémente le compteur correspondant  
- Le dashboard Node-RED affiche le nombre de composants détectés pour chaque classe en temps réel  

Fichiers dans le dossier `3-NodeRED/` :

| Fichier | Description |
|---------|-------------|
| flows.json | Flow Node-RED pour le comptage et le dashboard |

---

## 3. Fichiers importants

- `arduino_camera_classification.ino` : capture et inférence des composants  
- `flows.json` : flow Node-RED pour le comptage et affichage  
- `link_to_edge_impulse.md` : lien vers le projet Edge Impulse  
- `instructions.md` : guide pour la configuration et l’entraînement sur Edge Impulse  
- `README.md` : ce fichier d’explications  
- `documentation.md` : documentation détaillée de la partie 2
