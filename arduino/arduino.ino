#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

#define LIMIT_1 7
#define LIMIT_2 6

#define PEN_DOWN 60
#define PEN_UP 0

#define LINE_BUFFER_SIZE 100

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

void processCommand(char* command) {
  Serial.print("Recived: ");
  Serial.println(command);

  if (strcmp(command, "G28") == 0) {
    goHome();
  }

  if (strcmp(command, "M05") == 0) {
    penUp();
  }

  if (strcmp(command, "M03") == 0) {
    penDown();
  }
}

void readSerial() {
  char buffer[LINE_BUFFER_SIZE];
  int in;
  int index = 0;
  while (Serial.available() > 0 && index < LINE_BUFFER_SIZE) {
    in = Serial.read();
    buffer[index] = (char) in;
    index++;
  }
  if (index > 0) {
    buffer[index] = '\0';
    processCommand(buffer);
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LIMIT_1, INPUT);
  pinMode(LIMIT_1, INPUT);

  penServo.attach(10);

  ms.begin();
}

void loop() {
  delay(200);
  readSerial();
}
