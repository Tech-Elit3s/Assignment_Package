#include <Arduino.h>
#include <Servo.h>

#define ESC_ARM_SIGNAL 1000
#define ESC_ARM_TIME 2000

const double driveSpeed = 0.2;
const double turnSpeed = 0.2;

int position1;
Servo servo1;

Servo topLeftESC;
Servo topRightESC;
Servo bottomLeftESC;
Servo bottomRightESC;

int channelMin[5] = {990, 985, 1000, 1020, 990};

int channelMax[5] = {1975, 1965, 1990, 1990, 2000};

void setup() {
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

  delay(ESC_ARM_TIME);

  Serial.begin(9600);
}

// TODO: set correct pins
// Attaches pin and set to middle
void setupCar() {
  topLeftESC.attach(7);
  topRightESC.attach(8);
  bottomLeftESC.attach(6);
  bottomRightESC.attach(5);

  topLeftESC.writeMicroseconds(ESC_ARM_SIGNAL);
  topRightESC.writeMicroseconds(ESC_ARM_SIGNAL);
  bottomLeftESC.writeMicroseconds(ESC_ARM_SIGNAL);
  bottomRightESC.writeMicroseconds(ESC_ARM_SIGNAL);
}

void loop() {
  // Reads radio input signals assigns values
  // to variable
  int* values = readValues();

  // Prints out radio signals to terminal
    //      Serial.print(values[0]);
    //  Serial.print(" - ");
    //  Serial.print(values[1]);
    //  Serial.print(" - ");
    //  Serial.print(values[2]);
    //  Serial.print(" - ");
    //  Serial.print(values[3]);
    //  Serial.print(" - ");
    //  Serial.println(values[4]);

  // If the channel 5 switch is activated
  // the robot arm is being robot arm
  // functionality is turned on.
  if (values[4] > 50) {
    controlArm(values);
  } else {
    controlCar(values);
  }

  delete[] values;
}

// Robot Arm functionality
void controlArm(int* values) {
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

  // Increases controller joystick dead zone (neutral point) 
  // to allow for receiver value variance or flicker
  if ((90 + leftSideSpeed)<98 && (90 + leftSideSpeed)>82)
  {
  leftSideSpeed = 0;
  }
  if ((90 + rightSideSpeed)<98 && (90 + rightSideSpeed)>82)
  {
  rightSideSpeed = 0;
  }

  // Lowers top speed  
//     if ((90 + leftSideSpeed)>100)
//   {
//   leftSideSpeed = 10;
//   }
//       if ((90 + rightSideSpeed ) > 100)
//   {
//   rightSideSpeed = 10;
//   }
//   if ((90 + rightSideSpeed) < 80)
//   {
//   rightSideSpeed = -10;
//   }
//     if ((90 + leftSideSpeed) <80)
//   {
//   leftSideSpeed = -10;
//   }
// Serial.println(leftSideSpeed);

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

  return channelValues;
}

double readValue(int pin) { return pulseIn(pin, HIGH); }