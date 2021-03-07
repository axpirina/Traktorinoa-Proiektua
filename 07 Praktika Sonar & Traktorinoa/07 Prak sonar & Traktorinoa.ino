/* L298P Motor Shield-a eta Traktorino.h liburutegia eta HC-SR04 sentsorea erabiliaz sakatzaile bat sakatzen denean traktorinoa aurrerantz 
mugiaraztuko da 25zm azpitik oztoporen bat aurkitu biartean. Orduan atzera egingo du.  

  Debounce metodoa aplikatu zaio sakatzaileari.
  created 21 Nov 2006 by David A. Mellis
  modified 20 sep 2018 by Axpi
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/Debounce
*/

#include <Traktorinoa.h>
#include<UltraDistSensor.h>
Traktorinoa niretraktorinoa;
UltraDistSensor mysensor;
float reading;

// Aldagaiak definitu
const int buttonPin = 2;
int State = LOW; // LED-aren hasierako balioa
int buttonState; // Sakatzailearen oraingo egoera
int lastButtonState = LOW; // Sakatzailearen aurreko egoera

// DEBOUNCE denborak.
unsigned long lastDebounceTime = 0; // Lehen aldiz sakatua
unsigned long debounceDelay = 50; // Debounce denbora.

void setup() {
  Serial.begin(9600); // Serie komunikazioa martxan jarri.
  pinMode(buttonPin, INPUT);
  mysensor.attach(7, 8); //Trigger pin , Echo pin

  Serial.print("Sakatzailea sakatu zain...........");
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) { //Sakatzailea sakatu
    lastDebounceTime = millis();   //Timerra inizializatu
  }
  // Botoiaren egoera aldatu baldin bada:
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {  // Botoia aldatu bada
      buttonState = reading; // Balioak eguneratu
      if (buttonState == HIGH) {//LED-a HIGH bada soilik
        State = !State;
        Serial.print("Egoera: ");
        Serial.println(State);
      }
    }
  }
  lastButtonState = reading; // Balioak eguneratu
  reading = mysensor.distanceInCm();
  Serial.print("Sensor Reading :"); Serial.print(reading); Serial.println(" ZM");

  if ( State == 1 ) {
    niretraktorinoa.aurrera();

    while (reading > 1 && reading < 25) {
      niretraktorinoa.atzera();
      reading = mysensor.distanceInCm();
    }
  }
  else {
    niretraktorinoa.geratu();
  }
}
