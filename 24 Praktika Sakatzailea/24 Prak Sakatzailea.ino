/* Hurrengo programak pultsagailu baten irakurketa egiten du.   
   Ondoren Serie Monitorean idazten ditu balioak.
   Modified By Axpi 2017
   CC. Creatives Commons.
*/


int botoia= 2;
int balioa = 0;
// Sarrera-Irteeren Inizializazioa

void setup() 

  {
 pinMode (botoia, INPUT);
 Serial.begin (9600);
  }

// Ziklo Programa edo Programa nagusia

void loop() 
  {
 balioa = digitalRead(botoia); //Pultsadorea irakurri
 Serial.print ("Pultsagailuaren balioa=  "); //Serie Monitorean idatzi
 Serial.println (balioa); 
 delay (150);  // Debouncing denbora
  }
