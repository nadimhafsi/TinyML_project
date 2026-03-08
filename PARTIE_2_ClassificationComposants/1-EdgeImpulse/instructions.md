# Instructions pour reproduire le projet Edge Impulse

Ce fichier décrit les étapes pour configurer, entraîner et tester le modèle de classification des composants électroniques sur **Edge Impulse**.

---

## 1. Créer un projet Edge Impulse

1. Connectez-vous sur [Edge Impulse](https://www.edgeimpulse.com/).
2. Cliquez sur **“Create new project”**.
3. Donnez un nom à votre projet, par exemple : `TinyML_Component_Classification`.
4. Choisissez le type de projet **Image Classification**.

---

## 2. Importer les données (Dataset)

1. Dans l’onglet **Data acquisition**, cliquez sur **Upload files**.
2. Importez les dossiers suivants depuis votre dataset local :
   - `background` → pour les images de fond (sans composants)
   - `led` → images de LED
   - `diode` → images de diodes
   - `resistor` → images de résistances
   - `capacitor` → images de condensateurs
3. Chaque image sera automatiquement étiquetée selon le dossier d’origine.  
4. Vérifiez que chaque classe contient un nombre suffisant d’images (idéalement > 50 par classe).

---

## 3. Créer l’Impulse

1. Allez dans l’onglet **Impulse design**.
2. Ajoutez un **Image processing block** (Block DSP) :
   - Type : `Image`  
   - Redimensionnement recommandé : 160x120 (compatible avec OV7670)
3. Ajoutez un **Learning block** :
   - Type : `Image Classification`
4. Cliquez sur **Save Impulse**.

---

## 4. Entraîner le modèle

1. Allez dans l’onglet **Training**.
2. Sélectionnez le modèle par défaut ou un modèle léger (pour TinyML).
3. Cliquez sur **Start Training**.
4. Une fois l’entraînement terminé, vérifiez :
   - Accuracy sur validation
   - Confusion matrix
   - Précision pour chaque classe

---

## 5. Tester le modèle

1. Allez dans l’onglet **Model testing**.
2. Testez le modèle sur des images de votre dataset ou nouvelles images pour vérifier la précision.

---

## 6. Exporter le modèle pour Arduino

1. Allez dans **Deployment → Arduino Library**.
2. Cliquez sur **Build Arduino library**.
3. Téléchargez la bibliothèque générée (`.zip`) et importez-la dans l’IDE Arduino.
4. Utilisez les fonctions fournies pour faire l’inférence en temps réel avec l’Arduino Nano 33 BLE et la caméra OV7670.

---

## 7. Notes

- Le dataset local n’est pas nécessaire pour l’inférence Arduino, mais peut être conservé pour référence ou amélioration du modèle.  
- Assurez-vous que l’orientation et la luminosité des images sont similaires à ce que la caméra Arduino verra pendant l’utilisation réelle.  
- Pour le déploiement, connectez la carte Arduino via USB et utilisez le sketch `arduino_camera_classification.ino` pour capturer les images et afficher les résultats dans le Serial Monitor.
