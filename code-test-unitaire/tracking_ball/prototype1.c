#include <string.h>
#include <Servo.h>

#define LEDPIN 13
#define LASER 7

Servo servoHaut;  // crée l’objet pour contrôler le servomoteur du haut
Servo servoBas;  // crée l’objet pour contrôler le servomoteur du bas


int valeurHaut = 0;
int valeurBas = 0;
int pasHaut = 2;
int pasBas = 2;

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

  //pasHaut = (int) valeurHaut/10;
  
  // controler le servomoteur du haut
  /*
  if((valeurHaut <= 150) || (valeurHaut >= -150)){
    pasHaut = 1;
  }
  if((valeurBas <= 150) || (valeurBas >= -150)){
    pasBas = 1;
  }*/
  /*
  else if((valeurHaut > 200 && valeurHaut <= 400) || (valeurHaut < -200 && valeurHaut >= -400)) {
    pasHaut = 3;
  }
  else if((valeurHaut >400) || (valeurHaut <-400)){
    pasHaut = 4;
  }
  
   if((valeurBas <= 200) || (valeurBas >= -200)){
    pasBas = 2;
  }
  else if((valeurBas > 200 && valeurHaut <= 400) || (valeurBas <-200 && valeurHaut >= -400)){
    pasBas = 3;
  }
  else if((valeurBas >400) || (valeurBas < -400)){
    pasBas = 4;
  }*/
  ////Serial.print("PasHaut : ");
  ////Serial.println(pasHaut);

  ////Serial.print("PasBas : ");
  ////Serial.println(pasBas);
  ////Serial.print("valeurHaut : ");
  ////Serial.println(valeurHaut );
/*
  //Serial.print("valeurBas : ");
  //Serial.println(valeurBas );

  //Serial.print("valeurTirer : ");
  //Serial.println(valeurTirer );

  //Serial.print("raidus : ");
  //Serial.println(radius );*/
  
  
  //Bas
  
  if (valeurHaut < -40 && positionServoHaut-1 >= 30)
  {
    positionServoHaut -= pasHaut;
    servoHaut.write(positionServoHaut);
    //Serial.print("Position haut + arduino à python : ");
    //Serial.println(positionServoHaut);
  }

  //Haut
  if (valeurHaut > 40 && positionServoHaut+1<=100)
  {
    positionServoHaut += pasHaut;
    servoHaut.write(positionServoHaut);
    //Serial.print("Position haut - arduino à python : ");
    //////Serial.println(positionServoHaut);
  }
  /*
  if (valeurHaut == 0)
  {
    servoHaut.write(positionServoHaut);
  }*/

  // GAUCHE
  
  if (valeurBas > 40 && positionServoBas+1<120)
  {
    positionServoBas -= pasBas;
    servoBas.write(positionServoBas);
    //Serial.print("Position bas + arduino à python : ");
    //Serial.println(positionServoBas);

  }
  
  // Droite
  if (valeurBas < -40 && positionServoBas-1>=0)
  {
    positionServoBas += pasBas;
    servoBas.write(positionServoBas);
    //Serial.print("Position bas - arduino à python : ");
    //Serial.println(positionServoBas);

  }
  /*
  if (valeurBas == 0)
  {
    servoBas.write(positionServoBas);
  }*/

  if (valeurTirer == 1)
  {
    digitalWrite(LASER, HIGH);
    //digitalWrite(LEDPIN, HIGH);
  }
  if(valeurTirer == 0)
  {
    digitalWrite(LASER, LOW);
   // digitalWrite(LEDPIN, LOW);
  }
  delay(10);
}
