#include <Arduino.h>

void setup() {
<<<<<<< HEAD
  pinMode(9, INPUT);  // radio receiver channel 1 
  pinMode(10, INPUT); // radio receiver channel 2
  pinMode(11, INPUT); // radio receiver channel 3 
  pinMode(12, INPUT); // radio receiver channel 4
  pinMode(13, INPUT); // radio receiver channel 5
 Serial.begin(9600);  // put your setup code here, to run once:
}

void loop() {
   
    double* values = readValues();

      Serial.print(values[0]);
  Serial.print(" - ");
  Serial.print(values[1]);
  Serial.print(" - ");
  Serial.print(values[2]);
  Serial.print(" - ");
  Serial.print(values[3]);
  Serial.print(" - ");
  Serial.println(values[4]);
=======
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
    double* values = readValues();
>>>>>>> 6df842452b822c5a341244223c9d5424ed62c84a
}

void controlArm(double* values) {}
void controlCar(double* values) {}

double* readValues() {
    double channelValues[5];

    for (int i = 0; i < 5; i++) {
        channelValues[i] = readValue(9 + i);
    }

    double finalValues[5];

    // map value and filter deadzone
    for (int i = 0; i < 5; i++) {
        finalValues[i] = channelValues[i];
    }

    return finalValues;
}

double readValue(int pin) { return analogRead(pin); }