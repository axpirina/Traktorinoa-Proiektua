/*
  TRAKTORINOA 2019/2020 UNO L298P
  Zarauzko Oteitza Lizeoan eginiko Traktorino proiektua.
  Zirkuitua eta muntaia gida hurrengo estekan aurkituko dituzue:
  - http://oteitzalp.com
  created 09 Sep 2014
  by Unknown
  modified 09 Sep 2019
  by Axpirina
  This example code is in the public domain.
  http://www.arduino.cc
*/

//ALDAGAI ETA LIBURUTEGIEN DEKLARAZIOA
#include <Servo.h>
#include<UltraDistSensor.h>
#define MAX_DISTANCE 300 // Oztopora dagoen distantzia

UltraDistSensor mysensor;

//1. Motorraren PINak
const int SpeedA1 = 10;
const int DirectionA1 = 12;

//2. Motorarren PINak
const int SpeedA2 = 11;
const int DirectionA2 = 13;

//Aldagai FINKOEN deklarazioa
int leftscanval, centerscanval, rightscanval;
char choice;
int distance;
char turndirection; //Biratze norantzak 'l', 'r' edo 'f'
int thereis; // Oztopoa aurkitu dela adierazten duen aldagaia

//Aldagai KONFIGURAGARRIEN deklarazioa
const int turntime = 100; //Traktorinoa biratzen
const int distancelimit = 20; //Traktorinoaren objeturako Distantzia

int numcycles = 0; //ZIKLO MAXIMO kopurua.
//Objetuen deklarazioa
Servo head; // Serbomotor objetuaren deklarazioa 9G

// INIZIALIZAZIO BALDINTZAK
void setup() {
  mysensor.attach(7, 8); //Trigger pin , Echo pin
  head.attach(9); // Serboa D7 irteerara konektau
  head.write(90); // Serboa inizializatu
  Serial.begin(9600); //Serie komunikazioa ezarri 9600 baudiotan
  
  //Motorren PINak irteera bezala inizializatu
  pinMode(DirectionA1, OUTPUT);
  pinMode(DirectionA2, OUTPUT);

  //Traktorinoa geldirikk jarri
  digitalWrite(DirectionA1, LOW);
  analogWrite(SpeedA1, 0);
  digitalWrite(DirectionA2, LOW);
  analogWrite(SpeedA2, 0);
}

// FUNTZIO BEREZIAK ETA BERAIEN KODEA
// AURRERA funtzioa
void go() {
  Serial.println("AURRERA: ");
  digitalWrite(DirectionA1, HIGH);
  analogWrite(SpeedA1, 255);
  digitalWrite(DirectionA2, HIGH);
  analogWrite(SpeedA2, 255);
}
// ATZERA funtzioa
int backwards(int t) {
  Serial.println("ATZERA: ");
  digitalWrite(DirectionA1, LOW);
  analogWrite(SpeedA1, 220);
  digitalWrite(DirectionA2, LOW);
  analogWrite(SpeedA2, 220);
  delay(t);
}
// EZKERRERA biratu funtzioa
void turnleft(int t) {
  stopmove();
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(DirectionA1, LOW);
    analogWrite(SpeedA1, 220);
    digitalWrite(DirectionA2, HIGH);
    analogWrite(SpeedA2, 220);
    delay(t);
  }
}
// ESKUINERA biratu funtzioa
void turnright(int t) {
  stopmove();
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(DirectionA1, HIGH);
    analogWrite(SpeedA1, 220);
    digitalWrite(DirectionA2, LOW);
    analogWrite(SpeedA2, 220);
    delay(t);
  }
}
// STOP funtzioa, Traktorinoa GERATU
void stopmove() {
  digitalWrite(DirectionA1, LOW);
  analogWrite(SpeedA1, 0);
  digitalWrite(DirectionA2, LOW);
  analogWrite(SpeedA2, 0);
}

//Traktorinoaren inguruko 3 puntuetan OZTOPORIK dagoenaren
void watchsurrounding() {
  //Aurrera begira jarri eta itxaron
  head.write(80);
  delay(800);
  //EZKERRERA begiratu eta NEURTU
  for (int a = 80; a < 165; a++) {
    head.write(a);
    delay(20);
  }
  leftscanval = distance = mysensor.distanceInCm();
  Serial.print("EZKERREKO Oztopora Distantzia: ");
  Serial.println(leftscanval);
  //AURRERA begiratu eta NEURTU
  for (int a = 160; a > 80; a--) {
    head.write(a);
    delay(20);
  }
  centerscanval = distance = mysensor.distanceInCm();
  Serial.print("ZENTRUKO Oztopora Distantzia: ");
  Serial.println(centerscanval);
  //ESKUBIRA begiratu eta NEURTU
  for (int a = 80; a > 0; a--) {
    head.write(a);
    delay(20);
  }
  rightscanval = distance = mysensor.distanceInCm();
  Serial.print("ESKUBIKO Oztopora Distantzia: ");
  Serial.println(rightscanval);
  //AURRERA begira jarri berriz
  for (int a = 0; a < 80; a++) {
    head.write(a);
    delay(10);
  }
}


// Oztopoen neurketaren ondoren ZEIN NORANTZA hartu ERABAKITZEN duen funtzioa
char decide() {
  watchsurrounding();
  if (leftscanval > rightscanval) {
    choice = 'l';
  }
  else if (rightscanval > leftscanval) {
    choice = 'r';
  }
  return choice;
}

//FUNTZIO NAGUSI ETA ERREPIKAKORRA (PROGRAMA NAGUSIA)
void loop() {
  go(); //AURRERANTZ mugitzen hasi
  distance = distance = mysensor.distanceInCm();
  Serial.print("Oztopora Distantzia: ");
  Serial.println(distance);
  
  if ((distance < distancelimit) && (distance > 0)) {
    ++thereis;
  }
  if (distance > distancelimit) {
    thereis = 0;
  } //Oztopo neurgailua erreseteatu
  if (thereis > 2) {
    stopmove(); // Oztopoa aurkitu da, STOP
    turndirection = decide();
    switch (turndirection) {
      case 'l':
        backwards(600);
        turnleft(turntime);
        break;
      case 'r':
        turnright(turntime);
        break;
      case 'f':
        delay(0); //EZ BIRATU, AURRERANTZ jarraitu
        break;
    }
    thereis = 0;
  }
}
