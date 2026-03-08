#include <Arduino_LSM9DS1.h>   // Library to access the IMU of the Arduino Nano 33 BLE


// ============================================================================
// DATA COLLECTION SETTINGS
// ============================================================================

// Number of measurements captured for one vibration window
// This must stay consistent with the value used during model training
const int WINDOW_SIZE = 100;

// Delay between two sensor readings (in milliseconds)
// 20 ms ≈ 50 Hz sampling rate
const int SAMPLING_INTERVAL = 20;


// ============================================================================
// GLOBAL STATE VARIABLES
// ============================================================================

// Tracks the number of samples already recorded in the current window
int sampleCounter = 0;


// ============================================================================
// INITIALIZATION (runs once at startup)
// ============================================================================
void setup() {

  // Initialize serial communication with the computer
  Serial.begin(9600);

  // Wait until the serial monitor is ready
  while (!Serial);

  // Start the IMU sensor
  if (!IMU.begin()) {
    Serial.println("IMU initialization failed.");
    while (true);   // stop execution if sensor is not detected
  }

  // CSV header used when saving the dataset
  Serial.println("accX,accY,accZ,gyroX,gyroY,gyroZ");
}


// ============================================================================
// MAIN PROGRAM LOOP
// ============================================================================
void loop() {

  // Temporary variables for sensor readings
  float accX, accY, accZ;
  float gyroX, gyroY, gyroZ;

  // Collect a full window of IMU measurements
  while (sampleCounter < WINDOW_SIZE) {

    // Ensure both accelerometer and gyroscope data are available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {

      // Read acceleration data
      IMU.readAcceleration(accX, accY, accZ);

      // Read gyroscope data
      IMU.readGyroscope(gyroX, gyroY, gyroZ);

      // Increment the sample counter
      sampleCounter++;

      // --------------------------------------------------------------
      // Send the values to the computer in CSV format
      // --------------------------------------------------------------

      Serial.print(accX, 3);
      Serial.print(",");

      Serial.print(accY, 3);
      Serial.print(",");

      Serial.print(accZ, 3);
      Serial.print(",");

      Serial.print(gyroX, 3);
      Serial.print(",");

      Serial.print(gyroY, 3);
      Serial.print(",");

      Serial.println(gyroZ, 3);

      // Control the acquisition rate
      delay(SAMPLING_INTERVAL);
    }
  }

  // Empty line to mark the end of one vibration window
  Serial.println();

  // Reset counter to start collecting a new sequence
  sampleCounter = 0;
}


/*
===============================================================================
PROJECT NOTES
===============================================================================

This Arduino sketch is used to build a vibration dataset using the
Arduino Nano 33 BLE IMU sensor.

The program continuously records accelerometer and gyroscope data
and sends it to the computer through the serial port.

Each recording window contains 100 samples.

-------------------------------------------------------------------------------
OUTPUT FORMAT
-------------------------------------------------------------------------------

The serial output follows CSV formatting:

accX,accY,accZ,gyroX,gyroY,gyroZ

Where:

accX, accY, accZ  -> acceleration on the 3 axes
gyroX, gyroY, gyroZ -> angular velocity on the 3 axes


-------------------------------------------------------------------------------
MEASUREMENT UNITS
-------------------------------------------------------------------------------

Acceleration  : expressed in G
Gyroscope     : degrees per second (deg/s)


-------------------------------------------------------------------------------
DATA COLLECTION FOR TRAINING
-------------------------------------------------------------------------------

To create the dataset, the captured sequences should be saved
into separate CSV files according to the vibration level:

idle.csv     -> no vibration
normal.csv   -> normal vibration
high.csv     -> strong vibration

These files will then be used in Python to train a TinyML
classification model (TensorFlow Lite).

Each sequence = 100 rows of measurements.

Example:

accX,accY,accZ,gyroX,gyroY,gyroZ
0.02,0.97,-0.01,0.10,0.04,-0.02
...
(100 rows)

A blank line separates each recorded sequence.

===============================================================================
*/