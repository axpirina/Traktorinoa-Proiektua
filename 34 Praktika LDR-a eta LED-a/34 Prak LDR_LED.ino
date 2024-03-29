/*
Arduino batekin ingurunean dugun argi kantitatea neurtu eta LED bat proportzioan pizten duen programa.
* By TheCircuit
* Modified by Axpi 2019
* Creatives Commons
*/
 
int argiValue = 0; // Aldagaien deklarazioa
int led = 6; 
  
void setup() {
 
// Serie komunikazioa martxan jarri
Serial.begin(9600);
pinMode(led,OUTPUT);
}
 
void loop() {
 
argiValue = analogRead(A0);           // 0 pin analogikoa irakurri eta aldagaiean gorde
//argiValue = map (argiValue,ARGI MAXIMOA,ARGI MINIMOA,0,255);   // Sentsorea kalibratzeko ondorengoak bistaratu
//argiValue = constrain(argiValue,0,255);
Serial.print("Gelako argiaren balioa 1-255 artean: ");    // Irakurririko balioa inprimatu
Serial.println(argiValue); 

analogWrite(led,argiValue);

delay(150);
}
