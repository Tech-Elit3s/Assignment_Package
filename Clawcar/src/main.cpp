#include <Arduino.h>

void setup() {
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
  delete[] values;
}

void controlArm(double* values) {}
void controlCar(double* values) {}

double* readValues() {
    double *channelValues = new double[5];
 
    for (int i = 0; i < 5; i++) {
        channelValues[i] = readValue(9 + i);
    }
 
    return channelValues;
}

double readValue(int pin) { 
    return pulseIn(pin, HIGH);
}
    // return analogRead(pin); }