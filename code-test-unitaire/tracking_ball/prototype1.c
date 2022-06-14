#include <string.h>
#include <Servo.h>

#define LEDPIN 13
#define LASER 7
#define HAUT 1
#define BAS 2

Servo servoHaut;  // crée l’objet pour contrôler le servomoteur du haut
Servo servoBas;  // crée l’objet pour contrôler le servomoteur du bas


int valeurHaut = 0;
int valeurBas = 0;
int pasHaut = 1;
int pasBas = 1;
int compteurHaut=0;
int compteurBas=0;

int valeurTirer = 0;
int radius = 0;

int tabHaut[10] = {0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0};
int tabBas[10]  = {0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0};
int cptPos = 0;
int vitesseHaut = 0;
int vitesseBas = 0;
int vitesseHaut_tmp = 0;
int vitesseBas_tmp=0; 
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
  calculVitesse();
  Serial.print("vitesse Haut :");
  // controler le servomoteur du haut
  if((vitesseHaut <= radius) || (vitesseHaut >= -radius)){
    set_vitesse_cyclique(HAUT,8);//vitesse 1/5
  }
  
  if((vitesseHaut > radius && vitesseHaut <= ((int) radius*1.8) ) || (vitesseHaut < -radius && vitesseHaut >= -((int) radius*1.8))){
    set_vitesse_cyclique(HAUT,5);//vitesse 1/3
  }
  
  if((vitesseHaut > ((int) radius*1.8)&& vitesseHaut <= 400) || (vitesseHaut < -((int) radius*1.8) && vitesseHaut >= -400)) {
    set_vitesse_cyclique(HAUT,2);//vitesse 1/3
  }
  if((vitesseHaut >500) || (vitesseHaut <-500)){
    pasHaut = 1;
  }


  if((vitesseBas <= radius) || (vitesseBas >= -radius)){
     set_vitesse_cyclique(HAUT,8);//vitesse 1/5
  }
  if((vitesseBas > radius && vitesseBas <= ((int) radius*1.8)   ) || (vitesseBas < -radius && vitesseBas >=  -((int) radius*1.8) )){
   set_vitesse_cyclique(HAUT,5);//vitesse 1/3
  }
  if((vitesseBas > ((int) radius*1.8) && vitesseBas <= 400) || (vitesseBas <-((int) radius*1.8)&& vitesseBas >= -400)){
   set_vitesse_cyclique(HAUT,2);//vitesse 1/3
  }
  else if((vitesseBas >500) || (vitesseBas < -500)){
    pasBas = 1;
  }
  //Serial.print("PasHaut : ");
  //Serial.println(pasHaut);

  //Serial.print("PasBas : ");
  //Serial.println(pasBas);
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
  
  if (vitesseHaut < -cercleJaune && positionServoHaut-1 >= 30)
  {
    positionServoHaut -= pasHaut;
    servoHaut.write(positionServoHaut);
    ////Serial.print("Position haut + arduino à python : ");
    ////Serial.println(positionServoHaut);
  }

  //Haut
  if (vitesseHaut > cercleJaune && positionServoHaut+1<=100)
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
  
  if (vitesseBas < -cercleJaune && positionServoBas-1>=0)
  {
    positionServoBas -= pasBas;
    servoBas.write(positionServoBas);
    //Serial.print("Droiiiiite : ");
    //Serial.println(positionServoBas);

  }
  
  // Gauche
  if (vitesseBas > cercleJaune && positionServoBas+1<120)
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
  delay(20);
}

void set_vitesse_cyclique(int pas, int diviseur)
{
  if(pas==1) //pas du haut
  {
    compteurHaut=compteurHaut+1;
    if(diviseur==compteurHaut)
    {
      compteurHaut=0;
      pasHaut=1;
    }
  }
  else if(pas==2) //pas du bas
  {
    compteurBas=compteurBas+1;
    if(diviseur==compteurBas)
    {
      compteurBas=0;
      pasBas=1;
    }
  }
}

void calculVitesse(){
  int somme = 0;
  tabHaut[cptPos%10] =   valeurHaut;
  tabBas[cptPos%10] =   valeurBas;
  cptPos++;
  for(int i =0; i<10;i++){
    somme = somme + tabHaut[cptPos%10];
  }
  vitesseHaut = (int) somme/10;
  for(int i =0; i<10;i++){
    somme = somme + tabBas[cptPos%10];
  }
  vitesseBas = (int) somme/10;
  
}
