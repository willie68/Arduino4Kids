#ifndef Cube333_h
#define Cube333_h

#include <inttypes.h>

class Cube333 {
  public:
    // hier werden alle benötigten Leitungen initialisiert
    void initCube();
    // alle LEDs ausschalten
    void clearLEDs();
    // alle LEDs einschalten
    void allLEDs();
    // Helligkeit setzen, kann im Bereich 0..15 liegen
    void setBrightness(uint8_t value); 
    // Cube ein/ausschalten
    void setEnabled(bool enable);
    bool getEnabled();
    // setzte/löscht alle LEDs einer Fläche senkrecht zur x Achse
    void setXTile(uint8_t start, uint8_t value);
    // setzte/löscht alle LEDs einer Fläche senkrecht zur y Achse
    void setYTile(uint8_t start, uint8_t value);
    // setzte/löscht alle LEDs einer Fläche senkrecht zur z Achse
    void setZTile(uint8_t start, uint8_t value);
    
    // setzte/löscht alle LEDs einer Linie in Richtung x Achse beginnent mit der Start LED
    void setXLine(uint8_t startX, uint8_t value);
    // setzte/löscht alle LEDs einer Linie in Richtung y Achse beginnent mit der Start LED
    void setYLine(uint8_t startY, uint8_t value);
    // setzte/löscht alle LEDs einer Linie in Richtung z Achse beginnent mit der Start LED
    void setZLine(uint8_t x, uint8_t value);
    // setzt/löscht eine LED im Cubus mit den xyz Koordinaten (xyz = 0..2)
    void setLED(uint8_t x, uint8_t y, uint8_t z, uint8_t value);
    bool getLED(uint8_t x, uint8_t y, uint8_t z);
    // setzt/löscht eine LED im Cubus mit der Nummer 0..26
    void setLED(uint8_t number, uint8_t value);
    bool getLED(uint8_t number);
    // service Funktionen
    void updateCube();
    // hilfe beim debuggen
    void dbgOutLEDs();
  private:
    const uint8_t cols[3] = {11, 12, 13};
    const uint8_t rows[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 1. byte werden die bits 2-8 benutzt das sind die row 0..5, im 2 byte die ersten 3 bits sind die row 6..8. 
    // Die nächsten 3 Bits sind die Ebenen 0..2
    uint8_t leds[6] = {0, 0, 0, 0, 0, 0};

    uint8_t actLayer;
    uint8_t brightness;
    uint8_t brCounter;
    bool enabled;
};

#endif
