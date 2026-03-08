# Documentation – Partie 2 : Classification et comptage de composants électroniques

Cette partie du projet présente le développement d’un système capable de **classer des composants électroniques** (LED, diode, résistance, condensateur) à l’aide d’une caméra OV7670 et d’une carte Arduino Nano 33 BLE, avec visualisation et comptage via Node-RED.

---

## 1. Objectif du système

L’objectif est de créer un système capable de :

- Capturer une image avec la caméra OV7670
- Identifier le composant électronique présent dans l'image
- Envoyer la classe détectée à Node-RED
- Mettre à jour un compteur pour chaque type de composant détecté

---

## 2. Matériel utilisé

- Arduino Nano 33 BLE  
- Caméra OV7670  
- Ordinateur pour l’entraînement du modèle Edge Impulse  
- Node-RED pour la visualisation et le comptage

---

## 3. Entraînement du modèle avec Edge Impulse

Le modèle est entraîné sur la plateforme Edge Impulse via les étapes suivantes :

### 3.1 Création du projet

Un projet Edge Impulse a été créé pour la classification des composants électroniques.  

### 3.2 Import des images

Les images sont importées dans Edge Impulse et étiquetées avec leur classe correspondante :  

- LED  
- Resistance  
- Capacitor  
- Diode  

### 3.3 Création de l’impulse

L’impulse définit le pipeline de traitement des images :

- Image preprocessing  
- Feature extraction  
- Classification  

### 3.4 Entraînement du modèle

Le modèle est entraîné sur le dataset. La capture ci-dessous montre **l’accuracy et la perte** obtenues :  

![Accuracy Edge Impulse](https://drive.google.com/uc?export=download&id=124Ram3KNg-cDL2SqVXJnq1PGRuLgJ_5M)

---

## 4. Export du modèle pour Arduino

- Export en bibliothèque Arduino via Edge Impulse  
- Contient le modèle TensorFlow Lite et les fonctions pour l’inférence  
- Intégration dans le projet Arduino pour exécuter l’inférence en temps réel  

---

## 5. Inférence sur Arduino

Le sketch principal : `arduino_camera_classification.ino`  

Étapes réalisées par le programme :

1. Initialisation de la caméra OV7670  
2. Capture d’une image  
3. Prétraitement de l’image  
4. Exécution du modèle Edge Impulse  
5. Obtention de la classe prédite  

### Exemple de sortie dans le Serial Monitor :

![Serial Monitor Arduino](images/serial_monitor_results.png)

- Affiche la classe détectée et le score de confiance  
- Permet de vérifier que le modèle fonctionne avant de transmettre les données à Node-RED  

---

## 6. Envoi des résultats à Node-RED

- Les prédictions Arduino sont envoyées via la communication série au format :  
