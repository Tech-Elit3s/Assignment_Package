#include <Arduino.h>

void setup() {
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
    double* values = readValues();
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