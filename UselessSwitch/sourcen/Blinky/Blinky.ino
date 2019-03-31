/*
  Blinky

  Dieses kleine Programm läßt eine LED am Ausgang 7 blinken.
*/

const byte LED = 7;

/*
    Diese Funktion wird nur einmal beim Start des Arduinos ausgeführt.
    Hier schreibt man die Dinge hin, die nur einmal am Anfang ausgeführt werden sollen
*/
void setup() {
  // Der Pin, an dem die LED hängt definieren wir als Ausgang.
  pinMode(LED, OUTPUT);
}

/*
  Diese Funktion wird automatisch immer wieder ausgeführt.
  D.h. sobald unser Programm unten angekommen ist, fängt es automatisch oben wieder an.
*/
void loop() {
  digitalWrite(LED, HIGH);   // Jetzt schalten wir die LED an (der Pin geht auf +5V)
  delay(1000);               // und warten 1 Sekunde
  digitalWrite(LED, LOW);    // Jetzt schalten wir die LED wieder aus (der Pin geht auf Masse)
  delay(1000);               // und warten 1 Sekunde
}
