
/* POTENTZIOMETROA
  Arduino UNOaren 0 pin analogikoan potentziometroaren irakurketa egin da.
  13. Pinean dagoen LEDa erregulatu da proportzioan.
  by Axpi
  This example code is in the public domain.
*/
int sensorPin = 0;
int balioa = 0;
int LED_orlegia=11;

void setup() {
  Serial.begin(9600);
  pinMode(LED_orlegia,OUTPUT);
 }

void loop() {
  // Potentziometroa irakurri
  balioa = analogRead(sensorPin);
  balioa = map(balioa, 0, 1023, 0, 255);
  balioa = constrain(balioa, 0, 255);
  Serial.print("PoTentziometroa balioa=   ");
  Serial.println(balioa);
  
   // LED orlegia piztu piztu
  analogWrite(LED_orlegia, balioa);
  delay(50);
}
