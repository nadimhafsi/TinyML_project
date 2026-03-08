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

Chaque type de vibration est enregistré dans un fichier :  
idle.csv
normal.csv
high.csv


---

## 3. Entraînement du modèle

Le notebook pour l’entraînement :  
`2-Training/notebooks/training_vibrations.ipynb`  

### Étapes principales :

1. Chargement du dataset depuis Google Drive
2. Visualisation des signaux IMU  
   - **Accélération**  
     ![acceleration_signals](https://drive.google.com/uc?export=download&id=1hSjkbLmdytaqDIyQJFInKn2PKx7jYoQZ)
   - **Gyroscope**  
     ![gyroscope_signals](images/gyroscope_signals.png)
3. Découpage en **fenêtres temporelles** (sliding window)  
   - `WINDOW_SIZE = 100`  
   - `STRIDE = 30`
4. Extraction des **caractéristiques statistiques**  
   - Accélération : moyenne, écart type, amplitude  
   - Gyroscope : moyenne, écart type, amplitude  
   - Résultat : **6 features par fenêtre**
5. Séparation du dataset : **train (60%)**, **val (20%)**, **test (20%)**
6. Normalisation des features  
   - Moyenne et écart-type sauvegardés (`mean.npy`, `std.npy`)

---

## 4. Modèle

- **Architecture** : réseau léger adapté TinyML  
  - Input : 6 features  
  - Dense 24 ReLU → Dense 12 ReLU → Output 3 Softmax  
- **Optimiseur** : Adam  
- **Perte** : Sparse Categorical Crossentropy  
- **Époques** : 60, **batch** : 8

### Courbes d'entraînement

- Accuracy :  
  ![training_accuracy](images/training_accuracy.png)  
- Loss :  
  ![training_loss](images/training_loss.png)

### Évaluation

- Test accuracy et matrice de confusion  
  ![confusion_matrix](images/confusion_matrix.png)

---

## 5. Export du modèle

Les fichiers générés pour Arduino :

| Fichier | Description |
|---------|-------------|
| vibration_idle_normal_high.tflite | modèle TensorFlow Lite |
| model_data.h | modèle converti en tableau C pour Arduino |
| labels.txt | noms des classes |
| mean.npy / std.npy | paramètres de normalisation |

---

## 6. Déploiement sur Arduino

Le modèle est utilisé dans le fichier :  
`3-Inference_Arduino/inference_vibrations.ino`  

- Lit les données IMU en temps réel  
- Normalise et applique le modèle  
- Affiche la classe prédite dans le **Serial Monitor**

---

## 7. Organisation des images

