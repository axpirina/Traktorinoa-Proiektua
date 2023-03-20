/* Blink
  Arduino UNOaren barne LEDa dir dirka jartzen du segundu batetako maiztasuna eta serial 
  monitorean bere egoera adierazten digu.
  https://www.arduino.cc/en/Main/Products
  modified 8 May 2014
  by Scott Fitzgerald
  dified 03 June 2019
  by Axpi
  This example code is in the public domain.
*/

// Setup funtzioa behin bakarrik exekutatzen da
void setup() {
  // Inizializazio baldintzak jartzen dira bertan
  pinMode(13, OUTPUT);
}

// Loop funtzioak behin eta berriz exekutatzen ditu bertako aginduak
void loop() {
  digitalWrite(13, HIGH);   // LED-a piztu
  delay(1000);                       // Segundu bat itxaron
  digitalWrite(13, LOW);    // LED-a itzaldu
  delay(1000);                       // Segundu bat itxaron
}
