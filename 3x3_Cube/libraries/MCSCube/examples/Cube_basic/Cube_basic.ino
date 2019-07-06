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
 // ab hier kann jetzt dein Code stehen...
}
