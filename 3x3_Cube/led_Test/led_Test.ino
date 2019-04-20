void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  for (byte i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(8, 1);
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(8, 0);
    digitalWrite(13, 0);
    delay(500);
}
