#include <string.h>
#include <Servo.h>

#define LEDPIN 13
#define LASER 7

Servo servoHaut;  // crée l’objet pour contrôler le servomoteur du haut
Servo servoBas;  // crée l’objet pour contrôler le servomoteur du bas


int valeurHaut = 0;
int valeurBas = 0;

int valeurTirer = 0;
String myMessage;

int positionServoHaut = 65;
int positionServoBas = 45;
int Index1;
int Index2;
int Index3;
int Index4;
String valeurRecueHaut;
  String valeurRecueTirer;
  String valeurRecueBas; 
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);

  servoHaut.attach(6); // utilise la broche 6 pour le contrôle du servomoteur
  servoBas.attach(9);  // utilise la broche 9 pour le contrôle du servomoteur
  servoHaut.write(65); // positionne le servomoteur à 90°
  servoBas.write(45);  // positionne le servomoteur à 90°

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
  valeurRecueHaut = myMessage.substring(Index1 + 1, Index2);
  valeurRecueTirer = myMessage.substring(Index2 + 1, Index3);
  valeurRecueBas = myMessage.substring(Index3 + 1, Index4);

  valeurHaut = valeurRecueHaut.toInt();
  valeurBas = valeurRecueBas.toInt();
  valeurTirer = valeurRecueTirer.toInt();

  // controler le servomoteur du haut
  if (valeurHaut < -5 && positionServoHaut-1 >= 30)
  {
    positionServoHaut--;
    servoHaut.write(positionServoHaut);
    Serial.print("Position haut + arduino à python : ");
    Serial.println(positionServoHaut);
  }
  if (valeurHaut > 5 && positionServoHaut+1<=100)
  {
    positionServoHaut++;
    servoHaut.write(positionServoHaut);
    Serial.print("Position haut - arduino à python : ");
    Serial.println(positionServoHaut);
  }

  if (valeurHaut == 0)
  {
    servoHaut.write(positionServoHaut);
  }

  // controler le servomoteur du bas
  if (valeurBas < -5 && positionServoBas-1>=0)
  {
    positionServoBas--;
    servoBas.write(positionServoBas);
    Serial.print("Position bas + arduino à python : ");
    Serial.println(positionServoBas);

  }

  if (valeurBas > 5 && positionServoBas+1>=0)
  {
    positionServoBas++;
    servoBas.write(positionServoBas);
    Serial.print("Position bas - arduino à python : ");
    Serial.println(positionServoBas);

  }

  if (valeurBas == 0)
  {
    servoBas.write(positionServoBas);
  }

  if (valeurTirer == 1)
  {
    digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
  }
  delay(10);
}