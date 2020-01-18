/*  Bluethoot hargailua (SPP-C HC-06) erabiliaz Arduinoa haririk gabe kontrolatuko duen 
 *  programa da hurrengoa.
 *  
 *  13. Pinean konektatua duen LED-a kontrolatuko dugu praktika honetan baina kode hau
 *  Traktorino proiektu osoa gomandatzeko ere erabil daiteke.
 *  
 *  Android bitartez kontrolatzeko erabiliko dugun aplikazioa "Arduino bluetooth controller"
 *  izango da. https://play.google.com/store/apps/details?id=com.giumig.apps.bluetoothserialmonitor&hl=en
 *  
 *  OHARRA: Programa igotzerako garaian Bluethoot gailua DESKONEKTATU !!!
 *  
 *  2019 ko Azaroan by Axpi
 *  Eskerrak https://create.arduino.cc/projecthub/SURYATEJA/bluetooth-control-leds-27edbd
 *  Eskerrak http://www.martyncurrey.com/bluetooth-modules/#SPP-C_HC-06-BT06_HC-06
 *  This example code is in the public domain.
 */
// int E1 = 10; //Motorraren Abiadura PWM.
// int M1 = 12; // Motorraren Norantza.
// int piezoPin = 4;

int led = 13;

void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    char data = Serial.read(); // bluetooth modulutik datorren datua irakurri
    switch (data)
    {
      case 'a': digitalWrite(13, HIGH); break; // Datuaren balioaren arabera aukera desberdinak egin
      case 'b': digitalWrite(13, LOW); break; 
      default : break;
    }
  }
  delay(50);
}
