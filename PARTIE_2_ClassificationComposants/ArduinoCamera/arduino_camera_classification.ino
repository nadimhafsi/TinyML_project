/*
========================================================
TinyML - Electronic Component Recognition
Board : Arduino Nano 33 BLE
Camera : OV7670
Model : Edge Impulse

Fonction :
- Capture une image avec la caméra
- Lance l'inférence Edge Impulse
- Affiche les probabilités des classes
- Affiche la classe prédite dans le Serial Monitor
========================================================
*/

#include <electronic-components-detector_inferencing.h>
#include <Arduino_OV767X.h>

/* Résolution caméra */
#define CAMERA_WIDTH 160
#define CAMERA_HEIGHT 120

bool camera_ready = false;
uint8_t *image_buffer;

/* Initialisation caméra */
bool init_camera() {

    if (camera_ready) return true;

    Serial.println("Initialisation de la camera...");

    if (!Camera.begin(QQVGA, RGB565, 1)) {
        Serial.println("Erreur : camera non detectee");
        return false;
    }

    Serial.println("Camera prete !");
    camera_ready = true;
    return true;
}

/* Capture image */
bool capture_image(uint8_t *buffer) {

    if (!camera_ready) {
        Serial.println("Camera non initialisee");
        return false;
    }

    Camera.readFrame(buffer);

    return true;
}

/* Conversion image vers format Edge Impulse */
int get_image_data(size_t offset, size_t length, float *out_ptr) {

    size_t pixel_index = offset * 2;
    size_t out_index = 0;

    while (length--) {

        uint16_t pixel = (image_buffer[pixel_index] << 8) | image_buffer[pixel_index + 1];

        uint8_t r = ((pixel >> 11) & 0x1F) << 3;
        uint8_t g = ((pixel >> 5) & 0x3F) << 2;
        uint8_t b = (pixel & 0x1F) << 3;

        out_ptr[out_index] = (r << 16) + (g << 8) + b;

        pixel_index += 2;
        out_index++;
    }

    return 0;
}

/* Setup */
void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println("\n===============================");
    Serial.println("TinyML Component Classification");
    Serial.println("===============================");

    if (!init_camera()) {
        Serial.println("Echec initialisation camera");
        while (1);
    }

    image_buffer = (uint8_t*)malloc(CAMERA_WIDTH * CAMERA_HEIGHT * 2);

    if (!image_buffer) {
        Serial.println("Erreur allocation memoire");
        while (1);
    }
}

/* Loop principal */
void loop() {

    Serial.println("\nCapture d'image...");

    if (!capture_image(image_buffer)) {
        Serial.println("Erreur capture image");
        delay(2000);
        return;
    }

    ei::signal_t signal;

    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &get_image_data;

    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR err = run_classifier(&signal, &result, false);

    if (err != EI_IMPULSE_OK) {
        Serial.println("Erreur inference");
        delay(2000);
        return;
    }

    Serial.println("\nResultats classification :");

    float best_score = 0;
    int best_index = 0;

    for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        Serial.print(ei_classifier_inferencing_categories[i]);
        Serial.print(" : ");
        Serial.println(result.classification[i].value, 4);

        if (result.classification[i].value > best_score) {
            best_score = result.classification[i].value;
            best_index = i;
        }
    }

    Serial.println("-----------------------------");

    Serial.print("Prediction finale : ");
    Serial.print(ei_classifier_inferencing_categories[best_index]);
    Serial.print("  (score = ");
    Serial.print(best_score, 3);
    Serial.println(")");

    // -----------------------------
    // Envoi vers Node-RED Dashboard
    // -----------------------------
    if(best_score > 0.6){
        Serial.print("CLASS:");
        Serial.println(ei_classifier_inferencing_categories[best_index]);
    } else {
        Serial.println("CLASS:Unknown");
    }

    delay(3000); // Attente avant prochaine capture
}