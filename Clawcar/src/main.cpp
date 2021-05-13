#include <Arduino.h>
#include <Servo.h>

#define ESC_ARM_SIGNAL 1000
#define ESC_ARM_TIME 2000

const double driveSpeed = 0.2;
const double turnSpeed = 0.2;
const int servoSpeed = 5;
int baseServoPosition;
int elbowPosition;
int clawPosition;
Servo baseServo;
Servo elbowServo;
Servo clawServo;

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

  setupArm();
  setupCar();

  delay(ESC_ARM_TIME);
}

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
// Attaches pins and sets arm starting position
void setupArm(){
  elbowServo.attach(2);
  baseServo.attach(3);
  clawServo.attach(4);

  elbowPosition = 180;
  baseServoPosition = 120;
  clawPosition = 180;

  baseServo.write(baseServoPosition);
  elbowServo.write(elbowPosition);
  clawServo.write(clawPosition);
  delay(15);
}

void loop() {
  // Reads radio input signals assigns values
  // to variable
  int* values = readValues();

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
  // baseServo 
  // If the channel 2 joystick is moved move baseServo motor.
  if (values[1] < 40) {
    baseServoPosition += servoSpeed;
  }
  if (values[1] > 60) {
    baseServoPosition -= servoSpeed;
  }

      //Servo end point reached.
    if (baseServoPosition > 120) {
      baseServoPosition = 120;
    }
    if (baseServoPosition < 25) {
      baseServoPosition = 25;
    }
 
  baseServo.write(baseServoPosition);

  // elbowServo 
  // If the channel 0 joystick is moved, move elbow servo motor.
  if (values[0] < 40) {
    elbowPosition += servoSpeed;
  }
  if (values[0] > 60) {
    elbowPosition -= servoSpeed;
  }
        //Servo end point reached.
    if (elbowPosition  > 180) {
      elbowPosition  = 180;
    }
    if (elbowPosition  < 0) {
      elbowPosition  = 0;
    }

  
  elbowServo.write(elbowPosition);

    // clawServo 
  // If the channel 2 joystick is move, move elbow servo motor.
  if (values[3] < 40) {
    clawPosition += servoSpeed;
  }
  if (values[3] > 60) {
    clawPosition -= servoSpeed;
  }
        //Servo end point reached.
    if (clawPosition  > 180) {
      clawPosition  = 180;
    }
    if (clawPosition  < 100) {
      clawPosition  = 100;
    }

  
  clawServo.write(clawPosition);

  
  
}


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