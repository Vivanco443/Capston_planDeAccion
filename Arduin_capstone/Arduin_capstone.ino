/*
A0  -   Señal sensor 
2   -   Salida a ESP 

*/

#include <Arduino.h>
#define sensor 0   //  A0 pin
#define signalpin 2    //  Digital output
#define ledpin 13
int senVal = 0;

void setup()
{
  //  Inicializa puerto serie
  Serial.begin(9600);   
  //  Declara puertos de salida
  pinMode(signalpin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  digitalWrite(signalpin, LOW);
  digitalWrite(ledpin, LOW);
}

void loop()
{
  // Hace lectura analógica del sensor
  senVal = analogRead(sensor);

  // Pregunta si han cruzado el umbral
  if (senVal < 1000)
  {
    digitalWrite(signalpin, HIGH); 
    digitalWrite(ledpin, HIGH); 
    Serial.println("Activacion del sensor");
    delay(500);    // Envía una señal el tiempo suficiente para  que la detecte
    digitalWrite(signalpin, LOW);
    digitalWrite(ledpin, LOW);
    delay(500);
  }
}
