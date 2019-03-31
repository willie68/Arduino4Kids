void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  for (byte i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (byte i = 0; i < 27; i++) {
    clear();
    digitalWrite(11 + (i / 9), 0);
    digitalWrite((i % 9) +2, 1);
    delay(100);
  }
}

void clear() {
  for (byte i = 2; i < 14; i++) {
    if (i < 11) {
      digitalWrite(i, 0);
    } else {
      digitalWrite(i, 1);
    }
  }
}
