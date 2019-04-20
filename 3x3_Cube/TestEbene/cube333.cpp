#include "Cube333.h"
#define debug
#include "debug.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

void Cube333::initCube() {
  dbgOutLn("init cube");
  actLayer = 0;
  for (uint8_t row = 0; row < 9; row++) {
    pinMode(rows[row], OUTPUT);
    digitalWrite(rows[row], 0);
  }
  for (uint8_t col = 0; col < 3; col++) {
    pinMode(cols[col], OUTPUT);
    digitalWrite(cols[col], 0);
  }
  setBrightness(15);
  setEnabled(true);
}

void Cube333::clearLEDs() {
  for (uint8_t x = 0; x < sizeof(leds); x++) {
    leds[x] = 0;
  }
}

void Cube333::allLEDs() {
  for (uint8_t x = 0; x < sizeof(leds); x++) {
    leds[x] = 0xFF;
  }
}

void Cube333::setBrightness(uint8_t value) {
  brightness = 0x0F - (value & 0x0F);
  brCounter = brightness;
}

void Cube333::setEnabled(bool enable) {
  enabled = enable;
}
bool Cube333::getEnabled() {
  return enabled;
}

void Cube333::setXTile(uint8_t start, uint8_t value) {
  uint8_t x = start;
  setYLine(x, value);
  setYLine(x + 9, value);
  setYLine(x + 18, value);
}

void Cube333::setYTile(uint8_t start, uint8_t value) {
  uint8_t x = start * 3;
  setXLine(x, value);
  setXLine(x + 9, value);
  setXLine(x + 18, value);
}

void Cube333::setZTile(uint8_t start, uint8_t value) {
  uint8_t x = start * 9;
  setYLine(x, value);
  setYLine(x + 1, value);
  setYLine(x + 2, value);
}


void Cube333::setXLine(uint8_t startX, uint8_t value) {
  uint8_t x = startX;
  do {
    setLED(x, value);
    x += 1;
  }
  while ((x % 3) != 0);
}

void Cube333::setYLine(uint8_t startY, uint8_t value) {
  uint8_t x = startY;
  for (uint8_t i = 0; i < 3; i++) {
    setLED(x, value);
    x += 3;
  }
}

void Cube333::setZLine(uint8_t x, uint8_t value) {
  setLED(x, value);
  setLED(x + 9, value);
  setLED(x + 18, value);
}

void Cube333::setLED(uint8_t x, uint8_t y, uint8_t z, uint8_t value) {
  setLED(x + (y * 3) + (z * 9), value);
}

bool Cube333::getLED(uint8_t x, uint8_t y, uint8_t z) {
  return getLED(x + (y * 3) + (z * 9));
}

void Cube333::setLED(uint8_t number, uint8_t value) {
  uint8_t layer = number / 9;
  uint8_t pos = number % 9;
  uint8_t teiler = pos / 3;
  uint8_t rest = pos % 3;
  pos = rest * 3 + teiler;
  layer = (2 - layer) * 2;
  if (value) {
    if (pos > 5) {
      leds[layer + 1] |= 1 << (pos - 6);
    } else {
      leds[layer] |= 1 << (pos + 2);
    }
  } else {
    if (pos > 5) {
      leds[layer + 1] &= ~(1 << (pos - 6));
    } else {
      leds[layer] &= ~(1 << (pos + 2));
    }
  }
  //dbgOutLEDs();
}

bool Cube333::getLED(uint8_t number) {
  uint8_t layer = number / 9;
  uint8_t pos = number % 9;
  uint8_t teiler = pos / 3;
  uint8_t rest = pos % 3;
  pos = rest * 3 + teiler;
  layer = (2 - layer) * 2;
    if (pos > 5) {
      return (leds[layer + 1] & 1 << (pos - 6)) > 0;
    } else {
      return (leds[layer] & 1 << (pos + 2)) > 0;
    }
}

void Cube333::dbgOutLEDs() {
  dbgOut("LEDs:");
  for (uint8_t x = 0; x < sizeof(leds); x++) {
    dbgOut2(leds[x], DEC);
    dbgOut(" ");
  }
}

void Cube333::updateCube() {
  uint8_t row1 = leds[actLayer * 2];
  uint8_t row2 = leds[(actLayer * 2) + 1];

  row1 = row1 & 0b11111100;
  row2 = row2 & 0b00000111;

  // Ebenen ausschalten
  PORTB  = 0b00000000;

  if (!enabled) {
    return;
  }
  if (brCounter > 0) {
    brCounter--;
    return;
  }

  brCounter = brightness;
  // ersten 6 LEDs schalten
  PORTD  = row1;

  uint8_t mask = 0x01 << actLayer;
  mask = mask << 3;
  //mask = mask ^ 0b11111000;

  uint8_t result = mask | row2;

  PORTB  = result;

  actLayer++;
  if (actLayer > 2) {
    actLayer = 0;
  }
}
