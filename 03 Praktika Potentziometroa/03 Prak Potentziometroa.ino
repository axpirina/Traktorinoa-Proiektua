
/* POTENTZIOMETROA
  Arduino UNOaren 0 pin analogikoan potentziometroaren irakurketa egin da.
  by Axpi
  This example code is in the public domain.
*/
int sensorPin = 0;
int balioa = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  balioa = analogRead(sensorPin);
  //balioa = map(balioa, 0, 1023, 0, 1023);
  //balioa = constrain(balioa, 0, 1023);
  Serial.print("Sentsorearen balioa=   ");
  Serial.println(balioa);
  delay(50);
}
