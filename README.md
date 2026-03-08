# Projet TinyML – Présentation générale

Ce projet TinyML comporte deux parties principales :

---

## Partie 1 – Classification de vibrations

Objectif : Créer un système capable de détecter et classer différents niveaux de vibrations (idle, normal, high) à l’aide de l’IMU intégré sur une carte Arduino Nano 33 BLE.

- Collecte des données via Arduino
- Entraînement d’un modèle TensorFlow Lite
- Inférence temps réel sur Arduino
- Documentation et visualisation des résultats

---

## Partie 2 – Classification et comptage de composants électroniques

Objectif : Créer un système basé sur la caméra OV7670 capable de reconnaître différents composants électroniques et de compter les occurrences via Node-RED.

- Entraînement du modèle sur Edge Impulse
- Inférence temps réel sur Arduino
- Transmission des résultats vers Node-RED
- Visualisation et comptage des composants sur un dashboard

---

## Organisation du dépôt

![Architecture](https://drive.google.com/uc?export=download&id=13V5NzGzNzfxNDsH6FBPrvt4gAOAaBGMI)

Ce fichier sert de **présentation générale** du projet et guide l’utilisateur vers les différentes parties pour plus de détails.
