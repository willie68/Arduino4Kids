/*
  SOS: Wir senden SOS per LED
  Mehr zum Morsecode findet ihr hier: https://de.wikipedia.org/wiki/Morsezeichen

  Dieses kleine Programm lässt eine LED am Ausgang 7 SOS blinken.
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
}

/*#
  Diese Funktion wird automatisch immer wieder ausgeführt.
  D.h. sobald unser Programm unten angekommen ist, fängt es automatisch oben wieder an.
*/
void loop() {
  sende(BUCHSTABE_S);

  sende(BUCHSTABE_O);

  sende(BUCHSTABE_S);
  
  delay(WORT_PAUSE - BUCHSTABEN_PAUSE);

  delay(LOOP_PAUSE);
}

void sende(word symbole[]) {
  byte i = 0;
  while (symbole[i] > 0) {
    digitalWrite(LED, 1);
    delay(symbole[i]);
    digitalWrite(LED, 0);
    delay(SYMBOL_PAUSE);
    i++;
  }
  delay(BUCHSTABEN_PAUSE - SYMBOL_PAUSE);
}
