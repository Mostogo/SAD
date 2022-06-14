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
int cercleRouge;
int cptHaut = 0;
int cptBas = 0;
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
  cercleRouge = radius/2;
  //pasHaut = (int) valeurHaut/10;
  
  // controler le servomoteur du haut
  if((valeurHaut <= radius) && (valeurHaut >= -radius)){
    if(cptHaut >= 2){
      pasHaut = 1;
      cptHaut = 0;
    }
    else{
      cptHaut++;
      pasHaut = 0;
    }
  }
 else if(((valeurHaut > radius) && (valeurHaut <= 150)) || ((valeurHaut < -radius) && (valeurHaut >= -150))){
    pasHaut = 1;
    cptHaut = 0;
  }
  
  else if(((valeurHaut > 150) && (valeurHaut <= 300)) || ((valeurHaut < -150) && (valeurHaut >= -300))){
    pasHaut = 2;
    cptHaut = 0;
  }
  
  else if(((valeurHaut > 300) && (valeurHaut <= 400)) || ((valeurHaut < -300) && (valeurHaut >= -400))) {
    pasHaut = 3;
    cptHaut = 0;
  }
  else if((valeurHaut >500) || (valeurHaut <-500)){
    pasHaut = 4;
    cptHaut = 0;
  }
//Bas
  if((valeurBas <= radius) && (valeurBas >= -radius)){
    if(cptBas >= 2){
      pasBas = 1;
      cptBas = 0;
    }
    else{
      cptBas++;
      pasBas = 0;
    }
  }
  else if((valeurBas <= 150) && ( valeurBas >= -150)){
    pasBas = 1;
    cptBas = 0;
  }
   else if(((valeurBas > 150) && (valeurBas <= 300)) || ((valeurBas <-150) && (valeurBas >= -300))){
    pasBas = 2;
    cptBas = 0;
  }
  else if(((valeurBas > 300) && (valeurBas <= 400)) || ((valeurBas <-300) && (valeurBas >= -400))){
    pasBas = 3;
    cptBas = 0;
  }
  else if((valeurBas >500) || (valeurBas < -500)){
    pasBas = 4;
    cptBas = 0;
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
  
  if (valeurHaut < -cercleRouge && positionServoHaut-1 >= 30)
  {
    positionServoHaut -= pasHaut;
    servoHaut.write(positionServoHaut);
    ////Serial.print("Position haut + arduino à python : ");
    ////Serial.println(positionServoHaut);
  }

  //Haut
  if (valeurHaut > cercleRouge && positionServoHaut+1<=100)
  {
    positionServoHaut += pasHaut;
    servoHaut.write(positionServoHaut);
    ////Serial.print("Position haut - arduino à python : ");
    ////////Serial.println(positionServoHaut);
  }


  // Droite
  
  if (valeurBas < -cercleRouge && positionServoBas-1>=0)
  {
    positionServoBas -= pasBas;
    servoBas.write(positionServoBas);
    //Serial.print("Droiiiiite : ");
    //Serial.println(positionServoBas);

  }
  
  // Gauche
  if (valeurBas > cercleRouge && positionServoBas+1<120)
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
  delay(60);
}