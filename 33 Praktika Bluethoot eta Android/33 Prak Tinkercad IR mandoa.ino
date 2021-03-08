#include <IRremote.h>
int RECV_PIN = 2;
int red = 9;
int green = 10;
int blue = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(RECV_PIN, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}
void loop(){
  if(irrecv.decode(&results)){
  Serial.println(results.value,HEX);
    if(results.value==0xFD08F7){
     digitalWrite(red,!digitalRead(red)); 
    }
     if(results.value==0xFD8877){
     digitalWrite(green,!digitalRead(green)); 
    }
     if(results.value==0xFD48B7){
     digitalWrite(blue,!digitalRead(blue)); 
    }
    if(results.value==0xFD00FF){
     digitalWrite(red,0);
     digitalWrite(green,0);
     digitalWrite(blue,0);
    }
    
    
  irrecv.resume();
  }
  delay(100);
}
