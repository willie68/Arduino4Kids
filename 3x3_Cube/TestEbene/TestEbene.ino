#define debug
#include <debug.h>
#include <makros.h>
#include <TimerOne.h>
#include "cube333.h"

Cube333 cube333;

void setup() {
  initDebug();
  dbgOutLn("Start cubing...");
  cube333.initCube();

  Timer1.initialize(200);
  Timer1.attachInterrupt(updateCube);
}

void updateCube() {
  cube333.updateCube();
}

void loop() {
  cube333.clearLEDs();
  delay(500);
  cube333.allLEDs();
  delay(500);
  // put your main code here, to run repeatedly:

}
