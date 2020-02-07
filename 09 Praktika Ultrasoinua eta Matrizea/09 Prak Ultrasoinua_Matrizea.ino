/*
   HC-SR04 Ultrasoinu sentsoreak neurri batetik behera neurtzen duenean X
   bat idazten duen 8x8 Matrize batean.
   Designed and developed by
   Shubham Trivedi on Oct 2017
   Edited by axpi

     Pin configuration
    ___________________
   | HC-SC04 | Arduino |
   |_________|_________|
   |   Vcc   |   5V    |
   |   Trig  |    8    |
   |   Echo  |    9    |
   |   Gnd   |   GND   |
   |_________|_________|
    ___________________
   | Matrix  | Arduino |
   |_________|_________|
   |   DIN  |   12    |
   |   CLK  |   11    |
   |   CS   |   10    |
   |________|_________|
*/
#include "LedControlMS.h"
#include<UltraDistSensor.h>
#define NumMatrix 1

LedControl lc = LedControl(12, 11, 10, NumMatrix);
UltraDistSensor mysensor;
float reading;

// happy face: 8 lerroak behekotik goikora eta eskubiko bit-etik ezkerrekora
byte hf[8] = {B00111100, B01000010, B10010101, B10100001, B10100001, B10010101, B01000010, B00111100};

// obstacle: 8 lerroak behekotik goikora eta eskubiko bit-etik ezkerrekora
byte ob[8] = {B10000001, B01000010, B00100100, B00011000, B00011000, B00100100, B01000010, B10000001};

void setup() {

  Serial.begin(9600);
  mysensor.attach(8, 9); //Trigger pin , Echo pin

  for (int i = 0; i < NumMatrix ; i++)
  {
    lc.shutdown(i, false); // Activar la matriz
    lc.setIntensity(i, 8); // Poner el brillo a un valor intermedio
    lc.clearDisplay(i);    // Y borrar todo
  }

}

void drawFace() {

  // Aurpegia marrazten duen funtzioa
  lc.setRow(0, 0, hf[0]);
  lc.setRow(0, 1, hf[1]);
  lc.setRow(0, 2, hf[2]);
  lc.setRow(0, 3, hf[3]);
  lc.setRow(0, 4, hf[4]);
  lc.setRow(0, 5, hf[5]);
  lc.setRow(0, 6, hf[6]);
  lc.setRow(0, 7, hf[7]);
}

void obstacle() {

  // Ixa marrazten duen funtzioa
  lc.setRow(0, 0, ob[0]);
  lc.setRow(0, 1, ob[1]);
  lc.setRow(0, 2, ob[2]);
  lc.setRow(0, 3, ob[3]);
  lc.setRow(0, 4, ob[4]);
  lc.setRow(0, 5, ob[5]);
  lc.setRow(0, 6, ob[6]);
  lc.setRow(0, 7, ob[7]);
}

void loop() {
  reading = mysensor.distanceInCm();
  Serial.print("Sensor Reading :"); Serial.print(reading); Serial.println(" ZM");

  if (reading >1 && reading < 6) {
    lc.clearDisplay(0);
    obstacle();
  }
  else if (reading > 6) {
    lc.clearDisplay(0);
    drawFace();
  }
}
