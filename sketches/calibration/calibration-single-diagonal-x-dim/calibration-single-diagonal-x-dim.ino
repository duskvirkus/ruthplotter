
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

#define LIMIT_1 7
#define LIMIT_2 6

#define PEN_DOWN 75
#define PEN_UP 20

#define LINE_SIZE 12
#define COMMAND_SIZE 4
#define UINT16_SIZE 2
#define FLOAT32_SIZE 4

#define ARR_SIZE 5

Adafruit_MotorShield ms = Adafruit_MotorShield();

Adafruit_StepperMotor *step1 = ms.getStepper(200, 1);
Adafruit_StepperMotor *step2 = ms.getStepper(200, 2);

Servo penServo;

void goHome() {
  while (digitalRead(LIMIT_1) == HIGH || digitalRead(LIMIT_2) == HIGH) {
    step1->onestep(FORWARD, INTERLEAVE);
  }
  step1->release();
}

void penUp() {
  penServo.write(PEN_UP);
}

void penDown() {
  penServo.write(PEN_DOWN);
}

void right() {
  step1->onestep(BACKWARD, SINGLE);
//  step1->release();
  step2->onestep(BACKWARD, SINGLE);
//  step2->release();
}

void down() {
  step1->onestep(BACKWARD, SINGLE);
//  step1->release();
  step2->onestep(FORWARD, SINGLE);
//  step2->release();
}

void up() {
  step1->onestep(FORWARD, SINGLE);
//  step1->release();
  step2->onestep(BACKWARD, SINGLE);
//  step2->release();
}


void left() {
  step1->onestep(FORWARD, SINGLE);
//  step1->release();
  step2->onestep(FORWARD, SINGLE);
//  step2->release();
}

void rightUp() {
  step2->onestep(BACKWARD, SINGLE);
}

void rightDown() {
  step1->onestep(BACKWARD, SINGLE);
}

void leftUp() {
  step1->onestep(FORWARD, SINGLE);
}

void leftDown() {
  step2->onestep(FORWARD, SINGLE);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LIMIT_1, INPUT);
  pinMode(LIMIT_1, INPUT);

  penServo.attach(10);
  
  ms.begin();

  goHome();

  penDown();

  for (int i = 0; i < 217; ++i) {
    for (int j = 0; j < 10; ++j) {
      rightDown();
      delay(5);
    }
    int a = 10;
    if (i % 10 == 0) {
      a = 20;
    }
    for (int j = 0; j < a; ++j) {
      rightUp();
      delay(5);
    }
    for (int j = 0; j < a; ++j) {
      leftDown();
      delay(5);
    }
  }

  for (int i = 0; i < 200; ++i) {
    for (int j = 0; j < 10; ++j) {
      rightUp();
      delay(5);
    }
    int a = 10;
    if (i % 10 == 0) {
      a = 20;
    }
    for (int j = 0; j < a; ++j) {
      leftUp();
      delay(5);
    }
    for (int j = 0; j < a; ++j) {
      rightDown();
      delay(5);
    }
  }
  
  
}

void loop() {

}
