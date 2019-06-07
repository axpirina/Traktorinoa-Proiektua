/* Sweep
by BARRAGAN <http://barraganstudio.com>
This example code is in the public domain.
 
translated 8 Nov 2017
by Aitor Azpiroz
http://www.arduino.cc/en/Tutorial/Sweep
*/
 
#include <Servo.h> //Serbomotorra kontrolatzen duen liburutegia                
Servo myservo; // Serbomotor objetu bat sortu
// 12 Serbomotor sortu daitezke programa berdinean
 
int pos = 0; // Serboaren posizioa gordeko duen aldagaia
 
void setup() {
  Serial.begin(9600);
  myservo.attach(6); // Serboa D6 pinean konektatua. D6 pinean
}
 
void loop() {
   for (pos = 0; pos <= 180; pos += 1) { // 0 gradutatik 180ra 
      // gradu bateko saltoarekin
      myservo.write(pos); // esan serboari ‘pos’ egoerara 
      Serial.print("Serboaren posizioa = "); 
      Serial.println(pos);
      delay(15); //15ms itxaron
   }
 
   for (pos = 180; pos >= 0; pos -= 1) { // 180 gradutatik 0 ra
      myservo.write(pos); // esan serboari ‘pos’ egoerara 
      Serial.print("Serboaren posizioa = "); 
      Serial.println(pos);
      delay(15); // 15ms itxaron
   }
}
