/* LED
  Arduino UNOaren 8. pinean dagoen LED-a dir dir jartzen duen programa 
  by Axpi
  This example code is in the public domain.
*/
int led = 8;  //Aldagaien deklarazioa

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(led, HIGH);   
  Serial.print("LED-a  ");          
  Serial.println("ON");
  delay(1000);                       
  digitalWrite(led, LOW);    
  Serial.print("LED-a  ");           
  Serial.println("OFF");
  delay(1000);                       
}
