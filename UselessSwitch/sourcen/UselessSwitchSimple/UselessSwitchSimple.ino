#include <Servo.h>

/*
  Useless Switch

  Dieses kleine Programm schaltet einen Schalter wieder aus, den der Benutzer eingeschaltet hat.
*/

const byte LED = 6;
const byte SERVO = 5;
const byte SWITCH = 2;

Servo servo;

/*
    Diese Funktion wird nur einmal beim Start des Arduinos ausgeführt.
    Hier schreibt man die Dinge hin, die nur einmal am Anfang ausgeführt werden sollen
*/
void setup() {
  // Der Pin, an dem die LED hängt definieren wir als Ausgang.
  pinMode(LED, OUTPUT);

  // Der Pin, an dem der Schalter hängt definieren wir als Eingang.
  pinMode(SWITCH, INPUT_PULLUP);

  // Und wir brauchen noch einen Servo.
  servo.attach(SERVO);
  servo.write(0);
  digitalWrite(LED, LOW);    // Jetzt schalten wir die LED wieder aus (der Pin geht auf Masse)
}

/*
  Diese Funktion wird automatisch immer wieder ausgeführt.
  D.h. sobald unser Programm unten angekommen ist, fängt es automatisch oben wieder an.
*/
void loop() {
  if (digitalRead(SWITCH) == 0) {
    digitalWrite(LED, HIGH);   // Jetzt schalten wir die LED an (der Pin geht auf +5V)
    servo.write(180);
    while (digitalRead(SWITCH) == 0) {
      delay(10);
    }
    // Und jetzt wieder zurück auf die Ursprungsstellung
    servo.write(0);
    digitalWrite(LED, LOW);    // Jetzt schalten wir die LED wieder aus (der Pin geht auf Masse)
  }
}
