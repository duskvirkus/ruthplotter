#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

int currentA;
int currentB;
int testA;
int testB;

int lastA;
int lastB;

void stepIncreaseA() {
  // downRightStep();
  currentA++;
}

void stepDecreaseA() {
  // upLeftStep();
  currentA--;
}

void stepIncreaseB() {
  // upRightStep();
  currentB++;
}

void stepDecreaseB() {
  // downLeftStep();
  currentB--;
}

int improvedLocomoteTo(int a, int b) {

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

  float slope = deltaB / (float) deltaA;

  if (abs(slope) <= 1) {
    float bError = 0;
    int inProgressB = currentB;

    for (int i = 0; i < abs(deltaA); ++i) {
      if (deltaA > 0) {
        stepIncreaseA();
      } else {
        stepDecreaseA();
      }

      float nextB = inProgressB + slope + bError;
      int useB = roundf(nextB);
      bError = nextB - useB;

      int diffB = useB - inProgressB;
      if (diffB > 1 || diffB < -1) {
        return 1;
      } else if (diffB == 1) {
        stepIncreaseB();
      } else if (diffB == -1) {
        stepDecreaseB();
      }
      inProgressB = useB;
    }
  } else {
    slope = 1 / slope;

    float aError = 0;
    int inProgressA = currentA;

    for (int i = 0; i < abs(deltaB); ++i) {
      if (deltaB > 0) {
        stepIncreaseB();
      } else {
        stepDecreaseB();
      }

      float nextA = inProgressA + slope + aError;
      int useA = roundf(nextA);
      aError = nextA - useA;

      int diffA = useA - inProgressA;
      if (diffA > 1 || diffA < -1) {
        return 1;
      } else if (diffA == 1) {
        stepIncreaseA();
      } else if (diffA == -1) {
        stepDecreaseA();
      }
      inProgressA = useA;
    }
  }

  return 0;
}

void setLast() {
  lastA = currentA;
  lastB = currentB;
}

void setTest(int a, int b) {
  testA = a;
  testB = b;
  setLast();
}

void check(int i, int ret) {
//  if (currentA != testA || currentB != testB) {
    printf("check=%d returnval=%d\n", i, ret);
    printf("  last    a=%d b=%d\n", lastA, lastB);
    printf("  test    a=%d b=%d\n", testA, testB);
    printf("  current a=%d b=%d\n", currentA, currentB);
//  }
}

int main() {

  int ret = 0;

  currentA = 100;
  currentB = 100;

  setTest(100, 100);
  ret = improvedLocomoteTo(testA, testB);
  check(-1, ret);

  setTest(200, 100);
  ret = improvedLocomoteTo(testA, testB);
  check(-2, ret);

  setTest(200, 200);
  ret = improvedLocomoteTo(testA, testB);
  check(-3, ret);

  for (int i = 0; i < 10; ++i) {
    setTest((int) (rand() % 5000) - 1500, (int) (rand() % 5000) - 1500);
    ret = improvedLocomoteTo(testA, testB);
    check(i, ret);
  }

  return 0;
}

//float sq(float num) {
//  return num * num;
//}
//
//float dist(float x1, float y1, float x2, float y2) {
//  return sqrt(sq(x2 - x1) + sq(y2 - y1));
//}
//
//float lerp(float start, float stop, float amt) {
//  return start + (stop - start) * amt;
//}
//
//void locomoteTo(int a, int b) {
//  float d = dist(currentA, currentB, a, b);
//
//  int inProgressA = currentA;
//  int inProgressB = currentB;
//
//  for (int i = 0; i < d; ++i) {
//    float amt = (i + 1) / d;
//
//    int nextA = (int) (lerp(currentA, a, amt));
//    int nextB = (int) (lerp(currentB, b, amt));
//
//    int diffA = nextA - inProgressA;
//    assert(diffA >= -1 && diffA <= 1);
//    if (diffA <= -1) {
////            upLeftStep();
//    }
//    if (diffA >= 1) {
////            downRightStep();
//    }
//
//    int diffB = nextB - inProgressB;
//    assert(diffB >= -1 && diffB <= 1);
//    if (diffB <= -1) {
////            downLeftStep();
//    }
//    if (diffB >= 1) {
////            upRightStep();
//    }
//
//    inProgressA = nextA;
//    inProgressB = nextB;
//  }
//
//  if (a != inProgressA || b != inProgressB) {
//    printf("a = %d inProgressA = %d\n", a, inProgressA);
//    printf("b = %d inProgressB = %d\n", b, inProgressB);
//  }
////    assert(a == inProgressA);
////    assert(b == inProgressB);
//
//  currentA = a;
//  currentB = b;
//}

//void improvedLocomoteTo(int a, int b) {
//    float d = dist(currentA, currentB, a, b) * 2;
//
//    int inProgressA = currentA;
//    int inProgressB = currentB;
//    float errorA = 0;
//    float errorB = 0;
//
//    for (int i = 0; i < d; ++i) {
//        float amt = (i + 1) / d;
//
//        float nextAFloat = lerp(currentA, a, amt) + errorA;
//        float nextBFloat = lerp(currentB, b, amt) + errorB;
//        int nextA = roundf(nextAFloat);
//        int nextB = roundf(nextBFloat);
//        errorA = nextAFloat - nextA;
//        errorB = nextBFloat - nextB;
//
//        int diffA = nextA - inProgressA;
//        if (!(diffA >= -1 && diffA <= 1)) {
//            printf("diffA=%d\n", diffA);
//        }
//
////        assert(diffA >= -1 && diffA <= 1);
//        if (diffA <= -1) {
////            upLeftStep();
//        }
//        if (diffA >= 1) {
////            downRightStep();
//        }
//
//        int diffB = nextB - inProgressB;
////        assert(diffB >= -1 && diffB <= 1);
//        if (diffB <= -1) {
////            downLeftStep();
//        }
//        if (diffB >= 1) {
////            upRightStep();
//        }
//
//        inProgressA = nextA;
//        inProgressB = nextB;
//    }
//
//    if (a != inProgressA || b != inProgressB) {
//        printf("a = %d inProgressA = %d\n", a, inProgressA);
//        printf("b = %d inProgressB = %d\n", b, inProgressB);
//    }
////    assert(a == inProgressA);
////    assert(b == inProgressB);
//
//    currentA = a;
//    currentB = b;
//}
