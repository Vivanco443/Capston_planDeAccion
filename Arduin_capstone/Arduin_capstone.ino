/*
A0  -   Señal sensor 
2   -   Salida a ESP 

*/

#include <Arduino.h>
#define fron_sens 0   //  A0 pin
#define back_sens 1   //  A1 pin
#define signalpin 2    //  Digital output
#define ledpin 13
#define highsen 7    //  Digital output
#define lowsen 6

int fronSenVal = 0;
int backSenVal = 0;

void setup()
{
  //  Inicializa puerto serie
  Serial.begin(9600);   
  //  Declara puertos de salida
  pinMode(signalpin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(highsen, OUTPUT);
  pinMode(lowsen, OUTPUT);
  digitalWrite(signalpin, HIGH);
  digitalWrite(ledpin, LOW);
  digitalWrite(highsen, HIGH);
  digitalWrite(lowsen, LOW);
}

void loop()
{
  // Hace lectura analógica del sensor
  fronSenVal = analogRead(fron_sens);
  backSenVal = analogRead(back_sens);

  // Pregunta si han cruzado el umbral
  if (fronSenVal < 1000 || backSenVal < 1000)
  {
    digitalWrite(signalpin, LOW); 
    digitalWrite(ledpin, HIGH); 
    Serial.println("Activacion del sensor");
    delay(500);    // Envía una señal el tiempo suficiente para  que la detecte
    digitalWrite(signalpin, HIGH);
    digitalWrite(ledpin, LOW);
    delay(500);
  }
}
