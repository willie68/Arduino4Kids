/**
   LED Cube 3x3x3

   Dieser LED Cube ist als kleines Projekt für die Workshopreihe Arduino4Kids entstanden.
   Um den Aufbau schneller zu gestalten gibt es dazu eine kleine Platine, ein sog. Shield,
   was man direkt auf einen Arduino aaufsetzen kann.

   Die LEDs sind in 3 Ebenenen mit je 9 LEDs aufgeteilt und auch so auf die Pins verteilt.
   Dabei haben die Ebenen die Pins

   0 = D11,  1 = D12, 2 = D13

   Die LEDs sind dann von oben gesehen so durch numeriert

   6 7 8
   3 4 5
   0 1 2

   Verteilung auf die Pins:
   0 = D2, 1 = D5, 2 = D8,
   3 = D3, 4 = D6, 5 = D9,
   6 = D4, 7 = D7, 8 = D10,

   Die Verdahtung geht einmal im Kreis pro Ebene gegen den Uhrzeigersinn reihum, bei der
   mittleren LED zeigt die Kathode jeweils nach Rechts oben. Zum Biegen LED mit dem
   langen Pin (ANode) nach rechts, kürzerer Pin links nach hinten biegen. Längerer Pin
   wird nahe der LED um ca. 1,5mm ausgestellt. Dann alle LEDs wie oben beschrieben in die
   Montagehilfe (Abstandshilfe nicht vergessen) und die Kathoden auf die richtige Länge
   abknipsen.

   6<-7<-8
   |     ˄
   ˅ \   |
   3  4  5
   |     ˄
   ˅     |
   0->1->2

   Von jeder Ebene geht nun eine kleiner Draht auf die Kathodenanschlüsse.
   In den Anoden auf der Platine ist jeweils ein Vorwiderstand, die Kathoden
   werden mithilfe eines FET geschaltet.

   Um möglichst viel Rechenleistung in der Interruptroutine zu sparen,
   wird die tatsächliche Umrechnung von LED Nummer zur Position in der
   Setzroutine gemacht. Die Interrupt ist recht simpel. Pro Interruptcall
   wird ein Zähler (actLayer) von 0 anfangend immer um 1 hoch gezählt. Nur diese
   Ebene wird dargestellt.
   Dabei wird col auf die entsprechende Leitung nach Bild 1 umgerechnet.
   Alle anderen Leitungen bleiben 1, nur die aktive wird zu 0;
   Welche LEDs nun angezeigt werden steht dann in dem entsprechenden LEDs Array
   and der Position col.
   Und auch hier werden einfach die entsprechenden Ports gesetzt.

   Das ganze ist auf maximale Geschwindigkeit der Interruptroutine und auf einfache Hardwarebeschaltung
   getrimmt.
*/
#define debug
#include <debug.h>
#include <makros.h>
#include <TimerOne.h>
#include "cube333.h"

Cube333 cube333;

void setup() {
  initDebug();
  dbgOutLn("Start cubing...");
  cube333.initCube();

  Timer1.initialize(200);
  Timer1.attachInterrupt(updateCube);
}

void updateCube() {
  cube333.updateCube();
}

void loop() {
  cube333.clearLEDs();
  delay(1000);
  bright();
  allIn();
  testIt();
  rainDrops(32);
  xLine();
  yLine();
  zLine();
  xTile();
  delay(500);
  yTile();
  delay(500);
  zTile();
  delay(500);
  xyzAccess();
  rotate();
  /*
  */
}

void testIt() {
  cube333.allLEDs();
  for (byte x = 0; x < 27; x++) {
    if (!cube333.getLED(x)) {
      dbgOut("Fehler in");
      dbgOut(x);
      dbgOutLn();
    }
  }
  cube333.clearLEDs();
  for (byte x = 0; x < 27; x++) {
    if (cube333.getLED(x)) {
      dbgOut("Fehler in");
      dbgOut(x);
      dbgOutLn();
    }
  }

  for (int x = 0; x < 500; x++) {
    byte drop = random(0, 27);
    cube333.setLED(drop, !cube333.getLED(drop));
    delay(10);
  }
  cube333.clearLEDs();
}

void bright() {
  cube333.setBrightness(0);
  cube333.allLEDs();
  for (byte x = 0; x < 16; x++) {
    cube333.setBrightness(x);
    delay(100);
  }
  delay(500);
  cube333.allLEDs();
  for (byte x = 0; x < 3; x++) {
    cube333.setEnabled(false);
    delay(500);
    cube333.setEnabled(true);
    delay(500);
  }
  cube333.clearLEDs();
}

void allIn() {
  for (byte x = 0; x < 27; x++) {
    cube333.setLED(x, 1);
    delay(50);
  }
  delay(500);
  for (byte x = 0; x < 27; x++) {
    cube333.setLED(x, 0);
    delay(50);
  }
  delay(500);
  cube333.clearLEDs();
}

void xLine() {
  cube333.setXLine(0, 1);
  delay(150);
  cube333.setXLine(0, 0);
  delay(150);

  cube333.setXLine(12, 1);
  delay(150);
  cube333.setXLine(12, 0);
  delay(150);

  cube333.setXLine(24, 1);
  delay(150);
  cube333.setXLine(24, 0);
  delay(150);

  delay(500);
  cube333.clearLEDs();
}

void yLine() {
  cube333.setYLine(0, 1);
  delay(150);
  cube333.setYLine(10, 1);
  delay(150);
  cube333.setYLine(20, 1);
  delay(150);

  delay(500);
  cube333.clearLEDs();
}

void zLine() {
  cube333.setZLine(0, 1);
  delay(150);
  cube333.setZLine(4, 1);
  delay(150);
  cube333.setZLine(8, 1);
  delay(150);

  delay(500);
  cube333.clearLEDs();
}

void xTile() {
  for (byte x = 0; x < 3; x++) {
    cube333.setXTile(x, 1);
    delay(150);
  }
  delay(500);
  cube333.clearLEDs();
}

void yTile() {
  for (byte x = 0; x < 3; x++) {
    cube333.setYTile(x, 1);
    delay(150);
  }
  delay(500);
  cube333.clearLEDs();
}

void zTile() {
  for (byte x = 0; x < 3; x++) {
    cube333.setZTile(x, 1);
    delay(150);
  }
  delay(500);
  cube333.clearLEDs();
}

void xyzAccess() {
  cube333.setLED(0, 0, 0, 1);
  delay(150);
  cube333.setLED(1, 1, 1, 1);
  delay(150);
  cube333.setLED(2, 2, 2, 1);
  delay(500);
  cube333.clearLEDs();
}

void rotate() {
  cube333.setXTile(1, 1);
  delay(150);

  for (byte x = 0; x < 6; x++) {
    cube333.setZLine(1, 0);
    cube333.setZLine(7, 0);

    cube333.setZLine(0, 1);
    cube333.setZLine(8, 1);
    delay(150);

    cube333.setZLine(0, 0);
    cube333.setZLine(8, 0);

    cube333.setZLine(3, 1);
    cube333.setZLine(5, 1);
    delay(150);

    cube333.setZLine(3, 0);
    cube333.setZLine(5, 0);

    cube333.setZLine(2, 1);
    cube333.setZLine(6, 1);
    delay(150);

    cube333.setZLine(2, 0);
    cube333.setZLine(6, 0);

    cube333.setZLine(1, 1);
    cube333.setZLine(7, 1);
    delay(150);
  }
  cube333.clearLEDs();
}

byte  dropsArray[2][3] = { {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}};
void rainDrops(byte maxCount) {
  for (byte count = maxCount; count > 0; count --) {
    // let drop fall
    for (byte x = 0; x < 9; x++) {
      cube333.setLED(x, 0);
    }

    for (byte row = 0; row < 2; row++) {
      for (byte x = 0; x < 3; x++) {
        byte drop = dropsArray[row][x];
        if (drop > 0) {
          cube333.setLED(drop, 0);
          dropsArray[row][x] = 0;
          drop = drop - 9;
          cube333.setLED(drop, 1);
          if (row > 0) {
            dropsArray[row - 1][x] = drop;
          }
        }
      }
    }
    if (count > 4) {
      // new Drops
      byte drops = random (1, 2);
      for (byte x = 0; x < drops; x++) {
        byte drop = random(18, 27);
        cube333.setLED(drop, 1);
        dropsArray[1][x] = drop;
        //delay(50);
      }
    }
    delay(200);
  }
  cube333.clearLEDs();
  delay(1000);
}
