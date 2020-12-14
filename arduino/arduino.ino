#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <Wire.h>

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
  return sqrt(sq(x2 - x1) + sq(y2 - y1));
}

float lerp(float start, float stop, float amt) {
  return start + (stop - start) * amt;
}

void upLeftStep() {
  step1->onestep(FORWARD, SINGLE);
  delay(5);
}

void downLeftStep() {
  step2->onestep(FORWARD, SINGLE);
  delay(5);
}

void upRightStep() {
  step2->onestep(BACKWARD, SINGLE);
  delay(5);
}

void downRightStep() {
  step1->onestep(BACKWARD, SINGLE);
  delay(5);
}

void stepIncreaseA() {
  downRightStep();
  currentA++;
}

void stepDecreaseA() {
  upLeftStep();
  currentA--;
}

void stepIncreaseB() {
  upRightStep();
  currentB++;
}

void stepDecreaseB() {
  downLeftStep();
  currentB--;
}

int locomoteTo(int a, int b) {

  int deltaA = a - currentA;
  int deltaB = b - currentB;

  // same position and straight line cases
  if (deltaA == 0 && deltaB == 0) {
    return 0;
  } else if (deltaA == 0) {
    for (int i = 0; i < abs(deltaB); ++i) {
      if (deltaB > 0) {
        stepIncreaseB();
      } else {
        stepDecreaseB();
      }
    }
    return 0;
  } else if (deltaB == 0) {
    for (int i = 0; i < abs(deltaA); ++i) {
      if (deltaA > 0) {
        stepIncreaseA();
      } else {
        stepDecreaseA();
      }
    }
    return 0;
  }

  float slope = deltaB / (float)deltaA;

  printf("slope=%.4f\n", slope);

  if (fabsf(slope) <= 1) {
    printf("case a\n");
    float bError = 0;
    //    int inProgressB = currentB;

    for (int i = 0; i < abs(deltaA); ++i) {
      float nextB;

      if (deltaA > 0) {
        stepIncreaseA();
        nextB = currentB + slope + bError;
      } else {
        stepDecreaseA();
        nextB = currentB - slope + bError;
      }

      int useB = roundf(nextB);
      bError = nextB - useB;

      int diffB = useB - currentB;
      //      int diffB = currentB - useB;
      if (diffB > 1 || diffB < -1) {
        return 1;
      } else if (diffB == 1) {
        stepIncreaseB();
      } else if (diffB == -1) {
        stepDecreaseB();
      }
    }
  } else {
    printf("case b\n");
    slope = 1.0f / slope;

    float aError = 0;

    for (int i = 0; i < abs(deltaB); ++i) {
      float nextA;

      if (deltaB > 0) {
        stepIncreaseB();
        nextA = currentA + slope + aError;
      } else {
        stepDecreaseB();
        nextA = currentA - slope + aError;
      }

      int useA = roundf(nextA);
      aError = nextA - useA;

      int diffA = useA - currentA;
      //      int diffA = currentA - useA;
      if (diffA > 1 || diffA < -1) {
        return 1;
      } else if (diffA == 1) {
        stepIncreaseA();
      } else if (diffA == -1) {
        stepDecreaseA();
      }
    }
  }

  return 0;
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
  //  delay(20);
}

void penDown() { penServo.write(PEN_DOWN); }

int getUInt16(char *bytes) {
  int ret = 0;
  memcpy(&ret, bytes, UINT16_SIZE);
  return ret;
}

float getFloat32(char *bytes) {
  float ret = 0;
  memcpy(&ret, bytes, FLOAT32_SIZE);
  return ret;
}

int getA(float x, float y) { return int((y * sqrt(2)) + (getB(x, y))); }

int getB(float x, float y) { return int(((x - y) * sqrt(2) / 2)); }

bool checkCoords(int a, int b) {
  if (a >= STEP_DIM_0 && a <= STEP_DIM_3 && b >= STEP_DIM_0 &&
      b <= STEP_DIM_3) {
    if (b < a) {
      return true;
    }
  }

  if (a >= STEP_DIM_3 && a <= STEP_DIM_4 && b >= STEP_DIM_2 &&
      b <= STEP_DIM_3) {
    if (b - STEP_DIM_2 < STEP_DIM_1 - (a - STEP_DIM_3)) {
      return true;
    }
  }

  if (a >= STEP_DIM_0 && a <= STEP_DIM_1 && b >= -STEP_DIM_1 &&
      b <= STEP_DIM_0) {
    if (b + STEP_DIM_1 > STEP_DIM_1 - a) {
      return true;
    }
  }

  if (a >= STEP_DIM_1 && a <= STEP_DIM_4 && b >= -STEP_DIM_1 &&
      b <= STEP_DIM_2) {
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

void executeLine(char *line) {
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
