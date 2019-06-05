/* LED
  Arduino UNOaren 10. pinean dagoen LED-a FADE eran piztu naiz itzaliko duen programa.
  by Axpi
  This example code is in the public domain.
*/

int led = 8;  //Aldagaien deklarazioa

void setup() {
  // Hasieran eta behin bakarrik exekutatzen den kodea
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  for (int i = 0; i <= 1023; i = i + 1) { // FADE eran LED-a piztu
    analogWrite(led, i);
    Serial.print("LED-aren balioa: ");
    Serial.println(i);
  }

  delay(0);

  for (int i = 1023; i >= 0; i = i - 1) { // FADE eran LED-a itzali
    analogWrite(led, i);
    Serial.print("LED-aren balioa: ");
    Serial.println(i);
  }

  delay(0);
}
