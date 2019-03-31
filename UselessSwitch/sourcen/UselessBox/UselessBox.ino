#define debug
#include "debug.h"
#include <Servo.h>

/*
  Useless Switch

  Dieses kleine Programm schaltet einen Schalter wieder aus, den der Benutzer eingeschaltet hat.
*/

const byte LED = 13;
const byte SERVO_DECKEL = 5;
const byte SERVO_ARM = 6;
const byte SWITCH = 12;
const byte SWITCH_GND = 11;

const byte MAX_DECKEL_WINKEL = 90;
const byte MAX_ARM_WINKEL = 180;
const byte MAX_MUSTER = 1;

Servo servoDeckel;
Servo servoArm;

/*
    Diese Funktion wird nur einmal beim Start des Arduinos ausgeführt.
    Hier schreibt man die Dinge hin, die nur einmal am Anfang ausgeführt werden sollen
*/
void setup() {
  initDebug();
  randomSeed(analogRead(0));
  // Der Pin, an dem die LED hängt definieren wir als Ausgang.
  pinMode(LED, OUTPUT);

  // Der Pin, an dem der Schalter hängt definieren wir als Eingang.
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(SWITCH_GND, OUTPUT);
  digitalWrite(SWITCH_GND, 0);
  
  // Und wir brauchen noch einen Servo.
  servoDeckel.attach(SERVO_DECKEL);
  servoDeckel.write(90);

  servoArm.attach(SERVO_ARM);
  servoArm.write(MAX_ARM_WINKEL);

  digitalWrite(LED, LOW);    // Jetzt schalten wir die LED wieder aus (der Pin geht auf Masse)
  dbgOutLn("end of setup");
}

/*
  Diese Funktion wird automatisch immer wieder ausgeführt.
  D.h. sobald unser Programm unten angekommen ist, fängt es automatisch oben wieder an.
*/
void loop() {
  byte muster = random(MAX_MUSTER);
  if (digitalRead(SWITCH) == 0) {
    digitalWrite(LED, HIGH);   // Jetzt schalten wir die LED an (der Pin geht auf +5V)
    switch (muster) {
      case 0:
        muster0();
        break;
      case 1:
        muster1();
        break;
    }
    while(digitalRead(SWITCH) == 0) {
      delay(20);
    }
    digitalWrite(LED, LOW);    // Jetzt schalten wir die LED wieder aus (der Pin geht auf Masse)
  }
}

void muster0() {
    deckelAuf(10);
    delay(100);
    schalterAus(5);
    delay(1000);
    deckelZu();
}

void muster1() {
  muster0();
}

void deckelAuf(byte pause) {
  byte angle = MAX_DECKEL_WINKEL;
  while (angle > 0) {
    angle -= 1;
    servoDeckel.write(angle);
    delay(pause);
  }
}

void deckelZu() {
  servoDeckel.write(MAX_DECKEL_WINKEL);
}

void schalterAus(byte pause) {
   byte angle = MAX_ARM_WINKEL;
   while (digitalRead(SWITCH) == 0) {
      angle -= 1;
      if (angle > 0) {
        servoArm.write(angle);
      } else {
        angle = 1;
      }
      delay(pause);
    }
    // wir fahren dem Servo noch 5° weiter, damit der Schalter sicher schaltet.
    byte i = 0;
    while (i < 5) {
      i++;
      angle -= 1;
      if (angle >= 0) {
        servoArm.write(angle);
      } else {
        angle = 0;
      }
      delay(pause);
    }
    // Und jetzt wieder zurück auf die Ursprungsstellung
    servoArm.write(MAX_ARM_WINKEL);
}
