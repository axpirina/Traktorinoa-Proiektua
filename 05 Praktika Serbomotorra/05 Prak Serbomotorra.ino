/* Serbomotor bat potentziometro bitartez kontrolatzeko programa.
  by Axpi
  This example code is in the public domain.
*/
#include <Servo.h>

int x = 0;
int angelua = 0;

Servo nireSerboa; // Serbo objetua sortzen du

void setup() {
  Serial.begin(9600);
  nireSerboa.attach(6); // Serboa  Arduinoko 6. Pin-era
}

void loop() {
  
  x = analogRead(0);           // Irakurketa 10 bit-etan (0-1023) balio artean
  angelua = map(x, 0, 1023, 0, 180); // Irteerara mappeatu 0-180 artean
  
  Serial.print("Serboaren angelua:   ");
  Serial.println(angelua);
  Serial.println(" ");
  
  nireSerboa.write(angelua);
  
  delay(20);
}
