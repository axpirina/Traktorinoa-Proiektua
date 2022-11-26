/* LED
  Arduino UNOaren 8. pinean dagoen LED-a dir dir jartzen duen programa 
  by Axpi
  This example code is in the public domain.
*/
int led = 13;  //Aldagaien deklarazioa

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(led, HIGH);   
  Serial.println("LED-a ON");          
  delay(1000);                       
  digitalWrite(led, LOW);    
  Serial.println("LED-a OFF ");           
  delay(1000);                       
}
