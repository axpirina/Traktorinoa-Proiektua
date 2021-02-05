#include <Traktorinoa.h>
#include<UltraDistSensor.h>

Traktorinoa niretraktorinoa;
UltraDistSensor mysensor;

float reading;

void setup() {
  Serial.begin(9600);
  mysensor.attach(7, 8); //Trigger pin , Echo pin
}

void loop() {
  reading = mysensor.distanceInCm();
  Serial.print("Sensor Reading :"); Serial.print(reading); Serial.println(" ZM");
  if (reading >1 && reading<20){
     niretraktorinoa.atzera();
    }
  else{

  niretraktorinoa.aurrera();
  }
}
