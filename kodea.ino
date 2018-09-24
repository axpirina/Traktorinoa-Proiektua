/*
  TRAKTORINOA 2017/2018 NodeMCU  V4.0

  Zarauzko Oteitza Lizeoan eginiko Traktorino proiektua.

  Zirkuitua eta muntaia gida hurrengo estekan aurkituko dituzue:
  - http://oteitzalp.com

  created 09 Sep 2014
  by Unknown
  modified 09 Sep 2018
  by Axpirina

  This example code is in the public domain.

  http://www.arduino.cc
  https://github.com/axpirina/Traktorinoa
*/

//ALDAGAI ETA LIBURUTEGIEN DEKLARAZIOA

#include <Servo.h>
#include <NewPing.h>

#define MAX_DISTANCE 300 // Oztopora dagoen distantzia maximo (zentimetrotan). Sentsorearen distantzia maximoa 400-500zm dira.
#define TRIGGER_PIN  D5
#define ECHO_PIN     D6

// NodeMCU aren pin moldaketa, eta PINen funtzio bereziak
#define D0 16
#define D1 5   // I2C Bus SCL (clock)
#define D2 4   // I2C Bus SDA (data)
#define D3 0
#define D4 2   // Same as "LED_BUILTIN", but inverted logic
#define D5 14  // SPI Bus SCK (clock)
#define D6 12  // SPI Bus MISO 
#define D7 13  // SPI Bus MOSI
#define D8 15  // SPI Bus SS (CS)
#define D9 3   // RX0 (Serial console)
#define D10 1  // TX0 (Serial console)

//1. Motorraren PINak
const int MotorA1 = D1;
const int MotorA2 = D3;

//2. Motorarren PINak
const int MotorB1 = D2;
const int MotorB2 = D4;

//Aldagai FINKOEN deklarazioa
int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
char choice;
int distance;
char turndirection; //Biratze norantzak 'l', 'r' edo 'f' balioak hartuko ditu
int thereis;   // Oztopoa aurkitu dela adierazten duen aldagaia

//Aldagai KONFIGURAGARRIEN deklarazioa
const int turntime = 40;     //Traktorinoak biratzen pasatzen duen denbora
const int distancelimit = 20;     //Traktorinoaren objeturako  STOP Distantzia
const int sidedistancelimit = 15;    //Traktorinoaren alboetarako Distantzia maximoa
int numcycles = 0;   //Traktorinoak oztoporik atzeman gabe aurrerantz mugituko den ZIKLO MAXIMO kopurua.

//Objetuen deklarazioa
Servo head;  // Serbomotor objetuaren deklarazioa 9G
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Ultrasoinu elementuaren deklarazioa HC SR04



// INIZIALIZAZIO BALDINTZAK

void setup() {

  head.attach(D7);  // Serboa D7 irteerara konektau
  head.write(70);  // Serboa inizializatu begiak aurrera begira egon daitezen
  Serial.begin(9600);  //Serie komunikazioa ezarri 9600 baudiotan

  //Motorren PINak irteera bezala inizializatu
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);

  //Traktorinoa geldirikk jarri
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
}



// FUNTZIO BEREZIAK ETA BERAIEN KODEA

// AURRERA funtzioa (Bi motorrak norantza berdinean biratuz AURRERANTZ)
void go() {
  Serial.println("AURRERA:  ");
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
}
// ATZERA funtzioa (Bi motorrak norantza berdinean biratuz ATZERANTZ)
int backwards(int t) {
  Serial.println("ATZERA:  ");
  digitalWrite (MotorA1 , LOW);
  digitalWrite (MotorA2, HIGH);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, HIGH);
  delay(t);
}

// EZKERRERA biratu funtzioa
void turnleft(int t) {

  stopmove();
  for (int i = 0; i < 10; i++)
  {
    digitalWrite (MotorA1, HIGH);
    digitalWrite (MotorA2, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, HIGH);
    delay(t);
  }
}

// ESKUINERA biratu funtzioa
void turnright(int t) {

  stopmove();
  for (int i = 0; i < 10; i++)
  {
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorA2, HIGH);
    digitalWrite (MotorB1, HIGH);
    digitalWrite (MotorB2, LOW);
    delay(t);
  }
}

// STOP funtzioa, Traktorinoa GERATU
void stopmove() {
  digitalWrite (MotorA1 , LOW);
  digitalWrite (MotorA2, LOW);
  digitalWrite (MotorB1, LOW);
  digitalWrite (MotorB2, LOW);
}

//Traktorinoaren inguruko 3 puntuetan OZTOPORIK dagoenaren TXEKEOA
void watchsurrounding() { //Ezkerretan, aurrean eta eskubitan dituen oztopoetara dagoen DISTANTZIA neurtzen du

  //Aurrera begira jarri eta itxaron
  head.write(80);
  delay(800);

  //EZKERRERA begiratu eta NEURTU
  for (int a = 80; a < 165; a++) {
    head.write(a);
    delay(20);
  }
  leftscanval = distance = sonar.ping_cm();
  Serial.print("EZKERREKO Oztopora Distantzia:  ");
  Serial.println(leftscanval);

  //AURRERA begiratu eta NEURTU
  for (int a = 160; a > 80; a--) {
    head.write(a);
    delay(20);
  }
  centerscanval = distance = sonar.ping_cm();
  Serial.print("ZENTRUKO Oztopora Distantzia:  ");
  Serial.println(centerscanval);

  //ESKUBIRA begiratu eta NEURTU
  for (int a = 80; a > 0; a--) {
    head.write(a);
    delay(20);
  }
  rightscanval = distance = sonar.ping_cm();
  Serial.print("ESKUBIKO Oztopora Distantzia:  ");
  Serial.println(rightscanval);

  //AURRERA begira jarri berriz
  for (int a = 0; a < 80; a++) {
    head.write(a); //Didn't use 180 degrees because my servo is not able to take this angle
    delay(10);
  }
}

// Oztopoen neurketaren ondoren ZEIN NORANTZA hartu ERABAKITZEN duen funtzioa
char decide() {

  watchsurrounding();

  if (leftscanval > rightscanval) { //EZKERREKO distantzia ESKUBIKOa baino handiagoa bada EZKERRERA biratu
    choice = 'l';
  }
  else if (rightscanval > leftscanval) { //ESKUBIKO distantzia EZKERREKOA baino handiagoa bada ESKUBIRA biratu
    choice = 'r';
  }
  return choice;
}




//FUNTZIO NAGUSI ETA ERREPIKAKORRA (PROGRAMA NAGUSIA)

void loop() {

  go();  //AURRERANTZ mugitzen hasi

  ++numcycles;

  //Kasu honetan 3330 ziklo ostean, eta OZTOPORIK aurkitzen ez bada, GERATU eta TXEKEATU

  if (numcycles > 3330) {

    stopmove();
    turndirection = decide();
    switch (turndirection) {
      case 'l':
        backwards(600);
        turnleft(turntime);
        break;
      case 'r':
        backwards(600);
        turnright(turntime);
        break;
      case 'f':
        delay(0);
        break;
    }
    numcycles = 0;
  }




  distance = distance = sonar.ping_cm(); // AURRERANTZ goazen guztietan BEGIRATU egingo dugu ea OZTOPORIK ba ote den
  Serial.print("Oztopora Distantzia:  ");
  Serial.println(distance);

  if ((distance < distancelimit) && (distance > 0)) { // Traktorinoak OZTOPOREN bat baden testatzen du. (2 aldiz testatu irakurketa txarrak ekiditeko)
    ++thereis;
  }

  if (distance > distancelimit) {
    thereis = 0;
  } //Oztopo neurgailua erreseteatu

  if (thereis > 2) {
    stopmove(); // Oztopoa aurkitu da, STOP
    turndirection = decide(); //Zein NORANTZA hartu aukeratu
    switch (turndirection) {
      case 'l':                //EZKERRERA aukeratu bada lehenengo ATZERA egin eta gero EZKERRERA
        backwards(600);
        turnleft(turntime);
        break;
      case 'r':                 //ESKUBIRA aukeratu bada lehenengo ATZERA egin eta gero ESKUBIRA
        backwards(600);
        turnright(turntime);
        break;
      case 'f':
        delay(0); //EZ BIRATU, AURRERANTZ jarraitu
        break;
    }
    thereis = 0;
  }

}

