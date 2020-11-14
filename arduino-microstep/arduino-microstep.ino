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

#define STANDARD_MODE 0

#define STEPS_PER_MM 7.47169811321

#define STEP_DIM_0 0
#define STEP_DIM_1 1075
#define STEP_DIM_2 455
#define STEP_DIM_3 (STEP_DIM_1 + STEP_DIM_2)
#define STEP_DIM_4 (STEP_DIM_1 * 2 + STEP_DIM_2)

Adafruit_MotorShield ms = Adafruit_MotorShield();

Adafruit_StepperMotor *step1 = ms.getStepper(200, 1);
Adafruit_StepperMotor *step2 = ms.getStepper(200, 2);

int currentA;
int currentB;

Servo penServo;

float dist(float x1, float y1, float x2, float y2) {
  return sqrt(sq(x2-x1) + sq(y2-y1));
}

float lerp(float start, float stop, float amt) {
  return start + (stop-start) * amt;
}

void upLeftStep() {
  step1->onestep(FORWARD, MICROSTEP);
  delay(5);
}

void downLeftStep() {
  step2->onestep(FORWARD, MICROSTEP);
  delay(5);
}

void upRightStep() {
  step2->onestep(BACKWARD, MICROSTEP);
  delay(5);
}

void downRightStep() {
  step1->onestep(BACKWARD, MICROSTEP);
  delay(5);
}

void locomoteTo(int a, int b) {
  float d = dist(currentA, currentB, a, b);

  int inProgressA = currentA;
  int inProgressB = currentB;

  for (int i = 0; i < d; ++i) {
    float amt = i / d;

    int nextA = int(lerp(currentA, a, amt));
    int nextB = int(lerp(currentB, b, amt));

    int diffA = nextA - inProgressA;
    if (diffA <= -1) {
      upLeftStep();
    }
    if (diffA >= 1) {
      downRightStep();
    }

    int diffB = nextB - inProgressB;
    if (diffB <= -1) {
      downLeftStep();
    }
    if (diffB >= 1) {
      upRightStep();
    }

    inProgressA = nextA;
    inProgressB = nextB;
  }
  currentA = a;
  currentB = b;
}

void goHome() {
  step1->release();
  step2->release();
  while (digitalRead(LIMIT_1) == HIGH || digitalRead(LIMIT_2) == HIGH) {
    upLeftStep();
  }
  currentA = -10;
  currentB = 0;
  locomoteTo(0, 0);
}

void penUp() {
  penServo.write(PEN_UP);
}

void penDown() {
  penServo.write(PEN_DOWN);
}

int getUInt16(char* bytes) {
  int ret = 0;
  memcpy(&ret, bytes, UINT16_SIZE);
  return ret;
}

float getFloat32(char* bytes) {
  float ret = 0;
  memcpy(&ret, bytes, FLOAT32_SIZE);
  return ret;
}

//int getA(float x, float y) {
//  return int((y * sqrt(2)) + (getB(x, y)));
//}
//
//int getB(float x, float y) {
//  return int(((x - y) * sqrt(2) / 2));
//}

int getA(float x, float y) {
  return x;
}

int getB(float x, float y) {
  return y;
}

bool checkCoords(int a, int b) {
  if (a >= STEP_DIM_0 && a <= STEP_DIM_3 && b >= STEP_DIM_0 && b <= STEP_DIM_3) {
    if (b < a) {
      return true;
    }
  }
  
  if (a >= STEP_DIM_3 && a <= STEP_DIM_4 && b >= STEP_DIM_2 && b <= STEP_DIM_3) {
    if (b - STEP_DIM_2 < STEP_DIM_1 - (a - STEP_DIM_3)) {
      return true;
    }
  }
  
  if (a >= STEP_DIM_0 && a <= STEP_DIM_1 && b >= -STEP_DIM_1 && b <= STEP_DIM_0) {
    if (b + STEP_DIM_1 > STEP_DIM_1 - a) {
      return true;
    }
  }
  
  if (a >= STEP_DIM_1 && a <= STEP_DIM_4 && b >= -STEP_DIM_1 && b <= STEP_DIM_2) {
    if (b + STEP_DIM_1 > a - STEP_DIM_1) {
      return true;
    }
  }

  return false;
}

bool locomote(float x, float y) {
  int a = getA(x, y);
  int b = getB(x, y);

  bool valid = checkCoords(a, b);

  if (valid) {
    locomoteTo(a, b);
  }
  return valid;
}

void executeLine(char* line) {
  char command[COMMAND_SIZE + 1];
//  strncpy(command, line, COMMAND_SIZE);
  memcpy(command, line, COMMAND_SIZE);
  command[COMMAND_SIZE] = '\0';

  char tempUInt16[UINT16_SIZE];
  char tempFloat32[FLOAT32_SIZE];

  if (strcmp(command, "star") == 0) {
    
    int major, minor, patch, mode;
    
    memcpy(tempUInt16, line + COMMAND_SIZE, UINT16_SIZE);
    major = getUInt16(tempUInt16);

    memcpy(tempUInt16, line + COMMAND_SIZE + UINT16_SIZE, UINT16_SIZE);
    minor = getUInt16(tempUInt16);

    memcpy(tempUInt16, line + COMMAND_SIZE + (UINT16_SIZE * 2), UINT16_SIZE);
    patch = getUInt16(tempUInt16);

    memcpy(tempUInt16, line + COMMAND_SIZE + (UINT16_SIZE * 3), UINT16_SIZE);
    mode = getUInt16(tempUInt16);

    if (major != 0 || minor != 1 || patch != 0) {
      Serial.print("erorInvalid open plot version!");
    } else if (mode != 0) {
      Serial.print("erorInvalid mode!");
    } else {
      Serial.print("done");
    }
  }

  if (strcmp(command, "home") == 0) {
    penUp();
    goHome();
    Serial.print("done");
  }

  int movecmp = strcmp(command, "move");
  if (movecmp == 0 || strcmp(command, "mark") == 0) {
    float x, y;
    
    memcpy(tempFloat32, line + COMMAND_SIZE, FLOAT32_SIZE);
    x = getFloat32(tempFloat32);

    memcpy(tempFloat32, line + COMMAND_SIZE + FLOAT32_SIZE, FLOAT32_SIZE);
    y = getFloat32(tempFloat32);

    if (movecmp == 0) {
      penUp();
    } else {
      penDown();
    }
    
    bool worked = locomote(x, y);

    if (worked) {
      Serial.print("done");
    } else {
      Serial.print("erorInvalid location!");
    }
  }
}

void readSerial() {
  if (Serial.available() == LINE_SIZE) {
    char line[LINE_SIZE];
    for (int i = 0; i < LINE_SIZE; ++i) {
      line[i] = Serial.read();
    }
    executeLine(line);
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LIMIT_1, INPUT);
  pinMode(LIMIT_2, INPUT);

  penServo.attach(10);

  ms.begin();

  currentA = 0;
  currentB = 0;
}

void loop() {
  delay(200);
  readSerial();
}
