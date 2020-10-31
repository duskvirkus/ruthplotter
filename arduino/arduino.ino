#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

#define LIMIT_1 7
#define LIMIT_2 6

Adafruit_MotorShield ms = Adafruit_MotorShield();

Adafruit_StepperMotor *step1 = ms.getStepper(200, 1);
Adafruit_StepperMotor *step2 = ms.getStepper(200, 2);

void goHome() {
  while (digitalRead(LIMIT_1) == HIGH || digitalRead(LIMIT_2) == HIGH) {
    step1->onestep(FORWARD, INTERLEAVE);
  }
}

void readSerial() {
  if (Serial.avaiable() > 0) {
    int inByte = Serial.read();
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LIMIT_1, INPUT);
  pinMode(LIMIT_1, INPUT);

  ms.begin();

  goHome();

  step1->release();
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
