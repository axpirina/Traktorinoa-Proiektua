/*  Bluethoot hargailua (SPP-C HC-06) erabiliaz Arduinoa haririk gabe kontrolatuko duen 
 *  programa da hurrengoa.
 *  
 *  Android bitartez kontrolatzeko erabiliko dugun aplikazioa "Arduino bluetooth controller"
 *  izango da. https://play.google.com/store/apps/details?id=com.giumig.apps.bluetoothserialmonitor&hl=en
 *  
 *  OHARRA: Programa igotzerako garaian Bluethoot gailua DESKONEKTATU !!!
 *  
 *  2021 ko Otsaila by Axpi
 *  Eskerrak https://create.arduino.cc/projecthub/SURYATEJA/bluetooth-control-leds-27edbd
 *  Eskerrak http://www.martyncurrey.com/bluetooth-modules/#SPP-C_HC-06-BT06_HC-06
 *  This example code is in the public domain.
 */

#include <Traktorinoa.h>
//#include<UltraDistSensor.h>
Traktorinoa niretraktorinoa;
//UltraDistSensor mysensor;
//float reading;

void setup()
{
  Serial.begin(9600);
  //mysensor.attach(7, 8); //Trigger pin , Echo pin
}

void loop() {

  if (Serial.available() > 0) {
    char data = Serial.read(); // bluetooth modulutik datorren datua irakurri
    switch (data)
    {
      case 'a': niretraktorinoa.aurrera(); break; 
      case 'b': niretraktorinoa.atzera(); break; 
      case 'c': niretraktorinoa.ezkerrera(); break; 
      case 'd': niretraktorinoa.eskuinera(); break; 
      case 'p': niretraktorinoa.geratu(); break;  
      default : break;
    }
  }
  delay(50);
 /* 
  reading = mysensor.distanceInCm();
  while (reading >1 && reading <25){
    niretraktorinoa.atzera();
    reading = mysensor.distanceInCm();
    } 
  */
}
