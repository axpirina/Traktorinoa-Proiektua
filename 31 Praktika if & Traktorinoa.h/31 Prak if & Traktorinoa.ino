/* L298P Motor Shield-a eta Traktorino.h liburutegia erabiliaz sakatzaile bat sakatzen denean traktorinoa aurrerantz mugiarazten duen programa. 
  Begiratu traktorinoa.h liburutegiaren dokumentazioa eskuragarri dituzuen beste funtzio guztiak ezagutzeko.
          https://github.com/axpirina/Traktorinoa
  2020 ko Abenduan by Axpi
  This example code is in the public domain.
*/

#include <Traktorinoa.h>

int balioa = 0;
Traktorinoa niretraktorinoa;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  balioa = digitalRead(2);
  Serial.print("Sakatzailea: ");
  Serial.println(balioa);
  
  if ( balioa == 1 ){
    niretraktorinoa.aurrera();
  }
  else{
    niretraktorinoa.geratu();
  }
}
