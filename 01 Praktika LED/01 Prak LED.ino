/* LED
  Arduino UNOaren 10. pinean dagoen LED-a dir dir jartzen duen programa 
  by Axpi
  This example code is in the public domain.
*/
int led = 10;  //Aldagaien deklarazioa

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
