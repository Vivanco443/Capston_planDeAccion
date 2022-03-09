# Capston_proyect
Envío de evidencia fotográfica tras una señal de impacto por medio de IoT.

Material: 
- ESP32-Cam
- Sensor de tipo on/off
- Servidor web local o remoto

Este proyecto contiene los códigos necesarios para tomar fotografías desde un ESP32Cam
y enviarlas a un servidor remoto por medio de TCP junto con un mensaje enviado via MQTT. 
Esto activado desde un sensor on / off que puede ser inclusive un simple interruptor.

El objetivo que se tiene al plantear el proyecto de esta manera, es el de usar este sistema 
como un prototipo de un sistema de camara de curcero y un sensor de impacto; ambos instalados 
en un vehículo que, al activarse toma fotografías a modo de evidencia del suceso 
(una colision). Esta evidencia junto con una alerta de que esto ocurrió será enviado a 
un servidor con broker MQTT y a su vez a los dispositivos con acceso a internet que 
sean necesarios para informar al dueño o interesado de la unidad.

Al esp32cam se le conecta el sensor y se le conecta la camara, junto con el programador
Después se modifica el código y se agregan los datos del WiFi, de la url del servidor
remoto o local, y las credenciales MQTT.
Se agrega en el servidor la carpeta "webapp" que contiene la plantilla de una app web
configurada para poder recibir mensajes MQTT y modificar texto para avisar que recibio
el mensaje y las fotografías desde el ESP32cam.
