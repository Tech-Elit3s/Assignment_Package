#include <Arduino.h>
#include <Servo.h>

const double driveSpeed = 45;
const double turnSpeed = 45;

int position1;
Servo servo1;

Servo topLeftESC;
Servo topRightESC;
Servo bottomLeftESC;
Servo bottomRightESC;

void setup() {
  // declares radio receiver channel pins
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  // Attaches the servo mounted to the lid to pin and
  // positions it at the start up position.
  servo1.attach(3);
  position1 = 90;
  servo1.write(position1);
  delay(15);

  Serial.begin(9600);
}

// TODO: set correct pins
// Attaches pin and set to middle
void setupCar() {
  topLeftESC.attach(10);
  topRightESC.attach(11);
  bottomLeftESC.attach(12);
  bottomRightESC.attach(13);

  topLeftESC.write(90);
  topRightESC.write(90);
  bottomLeftESC.write(90);
  bottomRightESC.write(90);
}

void loop() {
  // Reads radio input signals assigns values
  // to variable
  double* values = readValues();

  // Prints out radio signals to terminal
  //       Serial.print(values[0]);
  //   Serial.print(" - ");
  //   Serial.print(values[1]);
  //   Serial.print(" - ");
  //   Serial.print(values[2]);
  //   Serial.print(" - ");
  //   Serial.print(values[3]);
  //   Serial.print(" - ");
  //   Serial.println(values[4]);

  // If the channel 5 switch is activated
  // the robot arm is being robot arm
  // functionality is turned on.
  if (values[4] > 1500) {
    controlArm(values);
  }
  // Else the robot car functionality
  // is turned on
  //   else{
  // controlCar(values);
  //   }

  delete[] values;
}

// Robot Arm functionality
void controlArm(double* values) {
  // If the channel 2 joystick is moved backwards
  // move the servo motor.
  if (values[1] < 1700) {
    position1 += 5;

    // Servo end point reached.
    if (position1 > 120) {
      position1 = 120;
    }

    servo1.write(position1);
    delay(15);
  }

  // If the channel 2 joystick is moved fowards
  // move the servo motor.
  if (values[1] > 1200) {
    position1 -= 5;
    // Servo end point reached.
    if (position1 < 20) {
      position1 = 20;
    }
    servo1.write(position1);
    delay(15);
  }
}

// TODO: Handle range of values correctly for input
// Select correct values
void controlCar(double* values) {
  double turnValue = values[0];
  double forwardValue = values[1];

  double leftSideSpeed = 0;
  double rightSideSpeed = 0;

  // Base speed for both sides is just the drive speed multiplied by forward
  // value
  leftSideSpeed = forwardValue * driveSpeed;
  rightSideSpeed = forwardValue * driveSpeed;

  leftSideSpeed += turnValue * turnSpeed;
  rightSideSpeed -= turnValue * turnSpeed;

  // Write the speed values to the ESCs. 90 is added as this is the 'center'
  // point
  topLeftESC.write(90 + leftSideSpeed);
  bottomLeftESC.write(90 + leftSideSpeed);
  topRightESC.write(90 + rightSideSpeed);
  bottomRightESC.write(90 + rightSideSpeed);
}

double* readValues() {
  double* channelValues = new double[5];

  for (int i = 0; i < 5; i++) {
    channelValues[i] = readValue(9 + i);
  }

  return channelValues;
}

double readValue(int pin) { return pulseIn(pin, HIGH); }