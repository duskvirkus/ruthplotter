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

void setup() {
  Serial.begin(9600);
  
  pinMode(LIMIT_1, INPUT);
  pinMode(LIMIT_1, INPUT);

  penServo.attach(10);
  
  ms.begin();

  goHome();

  int arr[ARR_SIZE];
  arr[0] = 80;
  arr[1] = 90;
  arr[2] = 100;
  arr[3] = 110;
  arr[4] = 120;

  for (int i = 0; i < ARR_SIZE; ++i) {
    for (int j = 0; j < arr[i]; ++j) {
      right();
      delay(20);
    }
    for (int j = 0; j < arr[i]; ++j) {
      down();
      delay(20);
    }
  }
  
}

void loop() {

}
