# PARTIE 1 – Classification des Vibrations avec TinyML

## 1. Objectif du projet

L'objectif de cette partie du projet est de concevoir un système capable de **détecter et classifier différents niveaux de vibration** à l’aide d’un modèle de **TinyML exécuté sur une carte Arduino Nano 33 BLE**.

Le système complet comprend trois étapes principales :

1. **Collecte des données** à partir du capteur IMU (accéléromètre et gyroscope).
2. **Entraînement d’un modèle de classification** avec TensorFlow.
3. **Déploiement du modèle sur Arduino** pour effectuer l'inférence en temps réel.

Les vibrations sont classées en **trois catégories** :

| Classe | Description |
|------|-------------|
| idle | absence de vibration |
| normal | vibration normale |
| high | vibration forte |

---

# 2. Architecture générale du projet

Cette partie est organisé selon la structure suivante :

## Structure du projet
PARTIE_1_ClassificationVibrations/
├── README.md
├── 1-DataGeneration_Arduino/
│ └── data_generation.ino
├── 2-Training/
│ ├── dataset/
│ ├── notebooks/
│ │ └── training_vibrations.ipynb
├── 3-Inference_Arduino/
│ └── inference_vibrations.ino
└── doc/
└── documentation.md
