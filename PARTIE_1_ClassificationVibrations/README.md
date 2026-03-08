# TinyML Project – Classification des Vibrations

##  Présentation du projet

Ce projet a pour objectif de développer un système intelligent de **classification des vibrations** en utilisant les techniques de **TinyML**.

Le système utilise un **Arduino Nano 33 BLE** équipé d’un capteur IMU intégré pour collecter les données d’accélération et de gyroscope.

Un modèle de réseau de neurones léger est entraîné avec **TensorFlow** puis converti au format **TensorFlow Lite** afin d’être déployé sur microcontrôleur.

---

##  Objectif principal

Le projet permet de :

- Collecter des données de vibrations via Arduino
- Prétraiter et analyser les signaux capteurs
- Entraîner un modèle de classification
- Déployer le modèle sur Arduino pour l’inférence en temps réel

Les vibrations sont classées en trois catégories :

| Classe | Description |
|--------|-------------|
| idle | Pas de vibration |
| normal | Vibration normale |
| high | Vibration forte |

---

---

##  Technologies utilisées

- Arduino Nano 33 BLE  
- Capteur IMU intégré (Accéléromètre + Gyroscope)  
- Python  
  - NumPy  
  - Pandas  
  - Matplotlib  
  - Scikit-learn  
  - TensorFlow  
- TensorFlow Lite (TinyML)

---

##  Pipeline du projet

1. Collecte des données vibration
2. Visualisation des signaux capteurs
3. Extraction des caractéristiques statistiques
4. Entraînement du modèle de classification
5. Conversion du modèle en TensorFlow Lite
6. Déploiement sur Arduino

---

##  Résultats du modèle

Les performances du modèle sont évaluées à l’aide de :

- Accuracy
- Matrice de confusion
- Classification report


---

##  Fichiers principaux

- `data_generation.ino` → collecte des données IMU  
- `training_vibrations.ipynb` → entraînement du modèle  
- `inference_vibrations.ino` → classification en temps réel  
- `model_data.h` → modèle TinyML embarqué  

---

##  Auteur

HAFSI Nadim / 3ème Instrumentation
Projet académique TinyML – Classification des vibrations.

Ce projet est développé dans un cadre académique et vise à démontrer l’utilisation de l’intelligence artificielle embarquée sur microcontrôleur.




