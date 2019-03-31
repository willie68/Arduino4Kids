#define debug 
#include <debug.h>

/*
  SOS: Wir senden SOS per LED
  Mehr zum Morsecode findet ihr hier: https://de.wikipedia.org/wiki/Morsezeichen

  Dieses kleine Programm läßt eine LED am Ausgang 7 SOS blinken.
*/
#include "MorseAlphabet.h"
const byte LED = 13;

/*
    Diese Funktion wird nur einmal beim Start des Arduinos ausgeführt.
    Hier schreibt man die Dinge hin, die nur einmal am Anfang ausgeführt werden sollen
*/
void setup() {
  // Der Pin, an dem die LED hängt definieren wir als Ausgang.
  pinMode(LED, OUTPUT);
  initDebug();
}

/*#
  Diese Funktion wird automatisch immer wieder ausgeführt.
  D.h. sobald unser Programm unten angekommen ist, fängt es automatisch oben wieder an.
*/
void loop() {
  dbgOutLn("start")
  dbgOut("S")
  sende(BUCHSTABE_S);
  dbgOut("O")
  sende(BUCHSTABE_O);
  dbgOut("S")
  sende(BUCHSTABE_S);
  delay(WORT_PAUSE - BUCHSTABEN_PAUSE);
  dbgOutLn();
  dbgOutLn("stop")
  delay(LOOP_PAUSE);
}

void sende(word symbole[]) {
  int i = 0;
  while(symbole[i] > 0) {
    digitalWrite(LED, 1);
    delay(symbole[i]);
    digitalWrite(LED, 0);
    delay(SYMBOL_PAUSE);
    i++;
  }
  delay(BUCHSTABEN_PAUSE - SYMBOL_PAUSE);
}
