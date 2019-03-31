/*
  Fading

  Dieses kleine Programm läßt eine LED am Ausgang 5 in der Helligkeit dimmen.
*/

const byte LED = 5;
const int WARTEZEIT = 10;

void setup() {
  // Der Pin, an dem die LED hängt definieren wir als Ausgang.
  pinMode(LED, OUTPUT);
}

// wenn WAHR dann wird die Helligkeit größer, ansonsten kleiner
bool hoch = true; 

// aktuelle Helligkeit
byte helligkeit = 0; 

void loop() {
  analogWrite(LED, helligkeit);
  if (hoch) {
    if (helligkeit == 255) {
      hoch = false;
    } else {
      helligkeit++; 
    }
  } else {
    if (helligkeit == 0) {
      hoch = true;
    } else {
      helligkeit--;
    }
  }
  delay(WARTEZEIT);
}
