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
#include <NewPing.h>
#define MAX_DISTANCE 300 // Oztopora dagoen distantzia
#define TRIGGER_PIN D7
#define ECHO_PIN D8

 
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
char turndirection; //Biratze norantzak 'l', 'r' edo 'f'
int thereis; // Oztopoa aurkitu dela adierazten duen aldagaia
 
//Aldagai KONFIGURAGARRIEN deklarazioa
const int turntime = 100; //Traktorinoa biratzen
const int distancelimit = 20; //Traktorinoaren objeturako Distantzia
const int sidedistancelimit = 15;
int numcycles = 0; //ZIKLO MAXIMO kopurua.
//Objetuen deklarazioa
Servo head; // Serbomotor objetuaren deklarazioa 9G
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
// INIZIALIZAZIO BALDINTZAK
void setup() {
head.attach(D7); // Serboa D7 irteerara konektau
head.write(80); // Serboa inizializatu
Serial.begin(9600); //Serie komunikazioa ezarri 9600 baudiotan
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
// AURRERA funtzioa
void go() {
Serial.println("AURRERA: ");
digitalWrite (MotorA1, HIGH);
digitalWrite (MotorA2, LOW);
digitalWrite (MotorB1, HIGH);
digitalWrite (MotorB2, LOW);
}
// ATZERA funtzioa
int backwards(int t) {
Serial.println("ATZERA: ");
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
leftscanval = distance = sonar.ping_cm();
Serial.print("EZKERREKO Oztopora Distantzia: ");
Serial.println(leftscanval);
//AURRERA begiratu eta NEURTU
for (int a = 160; a > 80; a--) {
head.write(a);
delay(20);
}
centerscanval = distance = sonar.ping_cm();
Serial.print("ZENTRUKO Oztopora Distantzia: ");
Serial.println(centerscanval);
//ESKUBIRA begiratu eta NEURTU
for (int a = 80; a > 0; a--) {
head.write(a);
delay(20);
}
rightscanval = distance = sonar.ping_cm();
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
++numcycles;
//Kasu honetan 3330 ziklo ostean
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
distance = distance = sonar.ping_cm();
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
