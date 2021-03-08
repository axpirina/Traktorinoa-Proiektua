/* IRremote: IR datuak jasotzeko balio duen programa.
 * Programa honekin IR mando baten seinaleak hartu eta Transistore baten bitartez DC motor bat gobernatzen da. 
   IR detektorea/demoduladorea kRecvPin-era konektatu behar da..
   Copyright 2009 Ken Shirriff, http://arcfn.com
   Version 0.2 June, 2017
   Version 0.1 Sept, 2015
   Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009
   Axpi-k itzulia eta aldatua 2018an.
*/

#include <IRremote.h>
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
int motorraPin=13;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  Serial.println("");
  Serial.println("");
  Serial.println("IR mandorekin motorra kontrolatu. V2.1. by Axpi ");
  Serial.println("OteitzaLP - 1 Elektrikoak fighting the power V1.0.");
  Serial.println();
  Serial.println("IRrecvDemo martxan da eta zain gaude IR mandoa sakatzeko ");
  pinMode(motorraPin,OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

  switch (results.value)
    { case 0xFFA25D:
        Serial.println("Motorra martxan");
        digitalWrite(motorraPin,HIGH);
        Serial.println("Motorra martxan2");
        break;
      case 0xFFE21D:
        Serial.println("Motorra geratu");
        digitalWrite(motorraPin,LOW);
        break;
      default:
        Serial.println("Okerreko botoia ");
    }
    irrecv.resume(); // Hurrengo balioa jaso
    delay(100);
}
