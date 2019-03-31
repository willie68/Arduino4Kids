/*
  Ampel

  Dieses kleine Programm steuert eine kleine Anforderungs Fußgängerampel.
  Die Ampel für die Autos bestehen aus 3 LEDs, die Ampel der Fußgänger aus 2.
  Zusätzlich benötigen wir noch einen Taster für die Fußgänger.
*/
#define debug
#include "debug.h"

// Wo ist was angeschlossen
const byte LED_AUTO_ROT = 12;
const byte LED_AUTO_GELB = 11;
const byte LED_AUTO_GRUEN = 10;
const byte LED_FUSS_ROT = 7;
const byte LED_FUSS_GRUEN = 6;
const byte TASTER_ANFORDERUNG = 2;

enum AMPEL {
  ROT, GELB, GRUEN, ROT_GELB
};

enum ZUSTAENDE {
  AMPEL_AUTO_GRUEN, AMPEL_AUTO_GELB, AMPEL_AUTO_ROT, AMPEL_FUSS_GRUEN, AMPEL_FUSS_ROT, AMPEL_AUTO_ROT_GELB
};

ZUSTAENDE zustand;

/*
    Diese Funktion wird nur einmal beim Start des Arduinos ausgeführt.
    Hier schreibt man die Dinge hin, die nur einmal am Anfang ausgeführt werden sollen
*/
void setup() {
  initDebug();
  // Die Pins, an dem eine LED hängt definieren wir als Ausgang.
  pinMode(LED_AUTO_ROT, OUTPUT);
  pinMode(LED_AUTO_GELB, OUTPUT);
  pinMode(LED_AUTO_GRUEN, OUTPUT);
  pinMode(LED_FUSS_ROT, OUTPUT);
  pinMode(LED_FUSS_GRUEN, OUTPUT);

  // Die Pins, an dem ein Taster hängt definieren wir als Eingang.
  pinMode(TASTER_ANFORDERUNG, INPUT_PULLUP);

  digitalWrite(LED_AUTO_ROT, 1);
  digitalWrite(LED_AUTO_GELB, 1);
  digitalWrite(LED_AUTO_GRUEN, 1);
  digitalWrite(LED_FUSS_ROT, 1);
  digitalWrite(LED_FUSS_GRUEN, 1);

  // der aktuelle Zustand
  zustand = AMPEL_AUTO_GRUEN;
  setzeZustand();
}

/*
  Diese Funktion wird automatisch immer wieder ausgeführt.
  D.h. sobald unser Programm unten angekommen ist, fängt es automatisch oben wieder an.
*/
void loop() {
  // Hier kommt jetzt der Zustandsautomat
  switch (zustand) {
    case AMPEL_AUTO_GRUEN:
      warteAnforderung();
      zustand = AMPEL_AUTO_GELB;
      delay(1000);
      break;
    case AMPEL_AUTO_GELB:
      fussAmpel(ROT);
      autoAmpel(GELB);
      delay(1000);
      zustand = AMPEL_AUTO_ROT;
      break;
    case AMPEL_AUTO_ROT:
      fussAmpel(ROT);
      autoAmpel(ROT);
      delay(2000);
      zustand = AMPEL_FUSS_GRUEN;
      break;
    case AMPEL_FUSS_GRUEN:
      fussAmpel(GRUEN);
      autoAmpel(ROT);
      delay(10000);
      zustand = AMPEL_FUSS_ROT;
      break;
    case AMPEL_FUSS_ROT:
      fussAmpel(ROT);
      autoAmpel(ROT);
      delay(5000);
      zustand = AMPEL_AUTO_ROT_GELB;
      break;
    case AMPEL_AUTO_ROT_GELB:
      fussAmpel(ROT);
      autoAmpel(ROT_GELB);
      delay(1000);
      zustand = AMPEL_AUTO_GRUEN;
      break;
  }
  setzeZustand();
}

void warteAnforderung() {
  while (digitalRead(TASTER_ANFORDERUNG) == 1) {
    delay(10);
  }
}

void setzeZustand() {
  dbgOutLn(".");
  switch (zustand) {
    case AMPEL_AUTO_GRUEN:
      dbgOutLn("AGr");
      fussAmpel(ROT);
      autoAmpel(GRUEN);
      break;
    case AMPEL_AUTO_GELB:
      dbgOutLn("AGe");
      fussAmpel(ROT);
      autoAmpel(GELB);
      break;
    case AMPEL_AUTO_ROT:
      dbgOutLn("AR");
      fussAmpel(ROT);
      autoAmpel(ROT);
      break;
    case AMPEL_FUSS_GRUEN:
      dbgOutLn("FGr");
      fussAmpel(GRUEN);
      autoAmpel(ROT);
      break;
    case AMPEL_FUSS_ROT:
      dbgOutLn("FR");
      fussAmpel(ROT);
      autoAmpel(ROT);
      break;
    case AMPEL_AUTO_ROT_GELB:
      dbgOutLn("ARG");
      fussAmpel(ROT);
      autoAmpel(ROT_GELB);
      break;
  }
}

void autoAmpel(AMPEL ampel) {
  switch (ampel) {
    case ROT:
      digitalWrite(LED_AUTO_ROT, 1);
      digitalWrite(LED_AUTO_GELB, 0);
      digitalWrite(LED_AUTO_GRUEN, 0);
      break;
    case ROT_GELB:
      digitalWrite(LED_AUTO_ROT, 1);
      digitalWrite(LED_AUTO_GELB, 1);
      digitalWrite(LED_AUTO_GRUEN, 0);
      break;
    case GRUEN:
      digitalWrite(LED_AUTO_ROT, 0);
      digitalWrite(LED_AUTO_GELB, 0);
      digitalWrite(LED_AUTO_GRUEN, 1);
      break;
    case GELB:
      digitalWrite(LED_AUTO_ROT, 0);
      digitalWrite(LED_AUTO_GELB, 1);
      digitalWrite(LED_AUTO_GRUEN, 0);
      break;
  }
}

void fussAmpel(AMPEL ampel) {
  switch (ampel) {
    case ROT:
      digitalWrite(LED_FUSS_ROT, 1);
      digitalWrite(LED_FUSS_GRUEN, 0);
      break;
    case GRUEN:
      digitalWrite(LED_FUSS_ROT, 0);
      digitalWrite(LED_FUSS_GRUEN, 1);
      break;
  }
}
