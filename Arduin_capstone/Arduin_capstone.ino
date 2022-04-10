#include <Arduino.h>
#define fron_sens 0   //  A0 pin
#define back_sens 1   //  A1 pin
#define fronpin 2    //  Digital output
#define backpin 3    //  Digital output
#define ledpin 13
int fronSenVal = 0;
int backSenVal = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(fronpin, OUTPUT);
  pinMode(backpin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  digitalWrite(fronpin, LOW);
  digitalWrite(backpin, LOW);
  digitalWrite(ledpin, LOW);
}

void loop()
{
  // Hace lectura analógica de cada sensor
  fronSenVal = analogRead(fron_sens);   
  backSenVal = analogRead(back_sens);

  // Pregunta si han cruzado el umbral
  if (fronSenVal < 1000)
  {
    digitalWrite(fronpin, HIGH); 
    digitalWrite(ledpin, HIGH); 
    delay(500);    // Envía una señal el tiempo suficiente para  que la detecte
    digitalWrite(fronpin, LOW);
    digitalWrite(ledpin, LOW);
    delay(500);
  }
  // Hace lo mismo pero para el sensor trasero
  else if (backSenVal < 1000)
  {
    digitalWrite(backpin, HIGH);
    digitalWrite(ledpin, HIGH);
    delay(500);
    digitalWrite(backpin, LOW);
    digitalWrite(ledpin, LOW);
    delay(500);
  }
}