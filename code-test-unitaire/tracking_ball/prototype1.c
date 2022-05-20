#include <string.h>
#include <Servo.h>

#define LEDPIN 13
#define LASER 7

Servo servoHaut;  // crée l’objet pour contrôler le servomoteur du haut
Servo servoBas;  // crée l’objet pour contrôler le servomoteur du bas


int valeurHaut = 0;
int valeurBas = 0;
int pasHaut = 1;
int pasBas = 1;

int valeurTirer = 0;
int radius = 0;

String myMessage;

int positionServoHaut = 65;
int positionServoBas = 60;
int Index1;
int Index2;
int Index3;
int Index4;
int Index5;
int cercleJaune;
String valeurradius;
String valeurRecueHaut;
String valeurRecueTirer;
String valeurRecueBas; 

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);

  servoHaut.attach(6); // utilise la broche 6 pour le contrôle du servomoteur
  servoBas.attach(9);  // utilise la broche 9 pour le contrôle du servomoteur
  servoHaut.write(65); // positionne le servomoteur à 90°
  servoBas.write(60);  // positionne le servomoteur à 90°

  pinMode(LASER, OUTPUT);
  digitalWrite(LASER, LOW);
  while (!Serial.available());
}

void loop() {

  myMessage = Serial.readString();
  Index1 = myMessage.indexOf('/');
  Index2 = myMessage.indexOf('/', Index1 + 1);
  Index3 = myMessage.indexOf('/', Index2 + 1);
  Index4 = myMessage.indexOf('/', Index3 + 1);
  Index5 = myMessage.indexOf('/', Index4 + 1);

   valeurRecueHaut = myMessage.substring(Index1 + 1, Index2);
   valeurRecueBas= myMessage.substring(Index2 + 1, Index3);
   valeurRecueTirer= myMessage.substring(Index3 + 1, Index4);
  valeurradius = myMessage.substring(Index4 + 1, Index5);

  valeurHaut = valeurRecueHaut.toInt();
  valeurBas = valeurRecueBas.toInt();
  valeurTirer = valeurRecueTirer.toInt();
  radius = valeurradius.toInt();
  cercleJaune = radius/2;
  //pasHaut = (int) valeurHaut/10;
  
  // controler le servomoteur du haut
  if((valeurHaut <= radius) || (valeurHaut >= -radius)){
    pasHaut = 1;
  }
  
  if((valeurHaut > radius && valeurHaut <= ((int) radius*1.8) ) || (valeurHaut < -radius && valeurHaut >= -((int) radius*1.8))){
    pasHaut = 2;
  }
  
  if((valeurHaut > ((int) radius*1.8)&& valeurHaut <= 400) || (valeurHaut < -((int) radius*1.8) && valeurHaut >= -400)) {
    pasHaut = 3;
  }
  if((valeurHaut >500) || (valeurHaut <-500)){
    pasHaut = 4;
  }


  if((valeurBas <= radius) || (valeurBas >= -radius)){
    pasHaut = 1;
  }
  if((valeurBas > radius && valeurHaut <= ((int) radius*1.8)   ) || (valeurBas < -radius && valeurBas >=  -((int) radius*1.8) )){
    pasBas = 1;
  }
  if((valeurBas > ((int) radius*1.8) && valeurHaut <= 400) || (valeurBas <-((int) radius*1.8)&& valeurHaut >= -400)){
    pasBas = 3;
  }
  else if((valeurBas >500) || (valeurBas < -500)){
    pasBas = 4;
  }
  Serial.print("PasHaut : ");
  Serial.println(pasHaut);

  Serial.print("PasBas : ");
  Serial.println(pasBas);
  //////Serial.print("valeurHaut : ");
  //////Serial.println(valeurHaut );
  ////Serial.print("valeurTirer : ");
  ////Serial.println(valeurTirer );
/*
  ////Serial.print("valeurBas : ");
  ////Serial.println(valeurBas );

  

  ////Serial.print("raidus : ");
  ////Serial.println(radius );*/
  
  
  //Bas
  
  if (valeurHaut < -cercleJaune && positionServoHaut-1 >= 30)
  {
    positionServoHaut -= pasHaut;
    servoHaut.write(positionServoHaut);
    ////Serial.print("Position haut + arduino à python : ");
    ////Serial.println(positionServoHaut);
  }

  //Haut
  if (valeurHaut > cercleJaune && positionServoHaut+1<=100)
  {
    positionServoHaut += pasHaut;
    servoHaut.write(positionServoHaut);
    ////Serial.print("Position haut - arduino à python : ");
    ////////Serial.println(positionServoHaut);
  }
  /*
  if (valeurHaut == 0)
  {
    servoHaut.write(positionServoHaut);
  }*/

  // Droite
  
  if (valeurBas < -cercleJaune && positionServoBas-1>=0)
  {
    positionServoBas -= pasBas;
    servoBas.write(positionServoBas);
    //Serial.print("Droiiiiite : ");
    //Serial.println(positionServoBas);

  }
  
  // Gauche
  if (valeurBas > cercleJaune && positionServoBas+1<120)
  {
    positionServoBas += pasBas;
    servoBas.write(positionServoBas);
    //Serial.print("Gauuuuche : ");
    //Serial.println(positionServoBas);

  }
  /*
  if (valeurBas == 0)
  {
    servoBas.write(positionServoBas);
  }*/

  if (valeurRecueTirer[0] == '1')
  {
    digitalWrite(LASER, HIGH);
    //digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    digitalWrite(LASER, LOW);
   // digitalWrite(LEDPIN, LOW);
  }
  delay(100);
}
