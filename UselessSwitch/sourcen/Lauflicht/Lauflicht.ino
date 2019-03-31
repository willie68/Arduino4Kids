/*
   Lauflicht mit 5 LED's an den Ausgängen D8..D12.
   1 Taster zum Einschalten an D2.
*/

// das ist die aktuelle Position des Lichtes
#define LED_ANZAHL 5
#define LED_PIN_START 8
#define TASTER 2
#define WARTZEIT 200

byte pos;

void setup() {
  // Alle LED's Pins als Ausgang
  for (byte i = 1; i <= LED_ANZAHL ; i++) {
    pinMode(LED_PIN_START + i - 1, OUTPUT);
  }

  // Taster Pin als Eingang
  pinMode(TASTER, INPUT_PULLUP);

  pos = 1;
}

void loop() {
  if (digitalRead(TASTER) == 0) {
    // Knopf gedrückt, jetzt geht's los
    pos++;
    if (pos > LED_ANZAHL) {
      pos = 1;
    }

    // jetzt die richtigen LED's anschalten
    for (int i = 1; i <= LED_ANZAHL; i++) {
      // die richtige position muss immer leuchten
      if (i == pos) {
        LEDAnAus(i, HIGH);
      } else {
        // die anderen aus
        LEDAnAus(i, LOW);
      }
    }
    delay(WARTZEIT);
  }
  else {
    // Knopf nicht gedrückt, alles aus machen
    for (int i = 1; i <= LED_ANZAHL; i++) {
      LEDAnAus(i, LOW);
    }
    // und damit er auch schön wieder am Anfang anfängt
    pos = 0;
  }
}

void LEDAnAus(byte led_nummer, byte value) {
  digitalWrite(LED_PIN_START + led_nummer - 1, value);
}

