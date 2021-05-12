#include <Arduino.h>
#include <Servo.h>

<<<<<<< HEAD
#define ESC_ARM_SIGNAL 1000
#define ESC_ARM_TIME 2000

const double driveSpeed = 1;
const double turnSpeed = 1;
=======
const double driveSpeed = 45;
const double turnSpeed = 45;
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3

int position1;
Servo servo1;

Servo topLeftESC;
Servo topRightESC;
Servo bottomLeftESC;
Servo bottomRightESC;
<<<<<<< HEAD

int channelMin[5] = {990, 985, 1000, 1020, 990};

int channelMax[5] = {1975, 1965, 1990, 1990, 2000};

void setup() {
=======

void setup() {
  // declares radio receiver channel pins
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3
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

  setupCar();

<<<<<<< HEAD
  delay(ESC_ARM_TIME);

=======
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3
  Serial.begin(9600);
}

// TODO: set correct pins
// Attaches pin and set to middle
void setupCar() {
<<<<<<< HEAD
  topLeftESC.attach(7);
  topRightESC.attach(8);
  bottomLeftESC.attach(6);
  bottomRightESC.attach(5);

  topLeftESC.writeMicroseconds(ESC_ARM_SIGNAL);
  topRightESC.writeMicroseconds(ESC_ARM_SIGNAL);
  bottomLeftESC.writeMicroseconds(ESC_ARM_SIGNAL);
  bottomRightESC.writeMicroseconds(ESC_ARM_SIGNAL);
=======
  topLeftESC.attach(10);
  topRightESC.attach(11);
  bottomLeftESC.attach(12);
  bottomRightESC.attach(13);

  topLeftESC.write(90);
  topRightESC.write(90);
  bottomLeftESC.write(90);
  bottomRightESC.write(90);
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3
}

void loop() {
  // Reads radio input signals assigns values
  // to variable
<<<<<<< HEAD
  int* values = readValues();

  // Prints out radio signals to terminal
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
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3

  // If the channel 5 switch is activated
  // the robot arm is being robot arm
  // functionality is turned on.
<<<<<<< HEAD
  if (values[4] > 50) {
=======
  if (values[4] > 1500) {
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3
    controlArm(values);
  } else {
    controlCar(values);
  }

  delete[] values;
}

// Robot Arm functionality
<<<<<<< HEAD
void controlArm(int* values) {
=======
void controlArm(double* values) {
>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3
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
<<<<<<< HEAD

    servo1.write(position1);
    delay(15);
  }
}

// TODO: Handle range of values correctly for input
// Select correct values
void controlCar(int* values) {
  int turnValue = values[0] - 50;
  int forwardValue = values[1] - 50;

  int leftSideSpeed = 0;
  int rightSideSpeed = 0;

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

int* readValues() {
  int* channelValues = new int[5];

  for (int i = 0; i < 5; i++) {
    double value = readValue(9 + i);
    channelValues[i] =
        (int)round(map(value, channelMin[i], channelMax[i], 0, 100));
  }

=======
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

>>>>>>> 797e4bc6d2a7d4d5bf90f2cfb4b12a15e7b785a3
  return channelValues;
}

double readValue(int pin) { return pulseIn(pin, HIGH); }