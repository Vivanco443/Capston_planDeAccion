/*
  Especia agradecimiento a Rui Santos de Random Nerd Tutorials
  que con su proyecto "ESP32-CAM Post Images to Local or Cloud Server using PHP (Photo Manager)"
  pudimos llevar acabo este proyecto

*/
/*  Envío de evidencia fotográfica tras una señal de impacto por medio de IoT
 *  Por: Israel Santiafo / Enrique Vivanco
 *  Fecha: 8 de marzo de 2022
 *  
 *  Este programa lee la señal de entrada de un sensor on/off que al activarse 
 *  envía un mensaje vía MQTT hacia un broker localizado en un servidor remoto. 
 *  También envía n fotografias, las cuales se guardan en el mismo servidor 
 *  para posteriormente exhibirlas en una página web 
 *  
 *  Configuración del hardware;
 *  Sensor on/off        GPIO16
 *  Vcc   --------------  5V
 *  GND    -------------- GND
 *  
 */

#include <Arduino.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
// Credenciales ssid (WiFi)
const char *ssid = "Heuristicas";   // **Totalplay-73A0-_2.4Gnormal   ||    Cuca's_chan
const char *password = "optimizacion";   // **Naylita2021

String serverName = "realdtc.ga"; // REEMPLAZAR CON EL IP DEL SERVIDOR   148.206.74.17
// String serverName = "example.com";   // O CON EL NOMBRE DEL DOMINIO

String serverPath = "/upload.php"; // EL DIRECTORIO POR DEFAULT /upload.php

const int serverPort = 80;

// button pin
const int buttonPin = 16;       // GPIO16
int buttonState = HIGH;         
int lastButtonState = LOW;          // ultima lectura del input pin
unsigned long lastDebounceTime = 0; // ultima vez que el pin se activó
unsigned long debounceDelay = 50;   // tiempo para evitar ruido; si la salida parpadea

WiFiClient client;    // Se crea una instancia del cliente WiFi
// Constantes para configutacion de la cámara
// CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

const int timerInterval = 30000;  // tiempo minimo entre cada post HTTP
unsigned long previousMillis = 0; // ultima vez que se envió
camera_config_t config;

int picknum = 5;  // Numero de fotos que se envían

// Solo necesario si se programa sin Arduino IDE
//####################################
//##### Declaracion de funciones #####
//####################################
String sendPhoto();
void configInitCamera();
void setupWiFi();

void setup()
{
  pinMode(buttonPin, INPUT);    // Declaración pin de entrada
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);   // Declaración velocidad de puerto serial
  setupWiFi();    // Se inicia WiFi
  configInitCamera();   // Se inicia cámara
}

void loop()
{
  int reading = digitalRead(buttonPin); // Se lee la entrada
  if (reading != lastButtonState)   
  {
    // resetea el debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)    //  Para evitar el ruido
  {
    if (reading != buttonState) // si el estado del boton ha cambiado:
    {
      buttonState = reading;
      if (buttonState == LOW)   //  se activó el sensor
      {
        unsigned long currentMillis = millis();   //  Se toma el tiempo
        if (currentMillis - previousMillis >= timerInterval)    // Tiempo minimo para volver a enviar
        {
          Serial.println("¡¡Crushed!!");
          for(int i=0; i < picknum; i++){     //  picknum = numero de fotos
            sendPhoto();    // Toma y envía foto
            delay(50);
          }
          previousMillis = currentMillis;   // Actualiza tiempo
        }
      }
    }
  }
  lastButtonState = reading;    // Actualiza estado 
}

String sendPhoto()
{
  String getAll;
  String getBody;
  // Las siguientes dos líneas toman la foto
  camera_fb_t *fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb)    // Si no se toma
  {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }

  Serial.println("Connecting to server: " + serverName);

  if (client.connect(serverName.c_str(), serverPort))   // Se conecta al servidor
  {
    Serial.println("Connection successful!");     // Esto que onda?? vvv
    String head = "--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"imageFile\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--RandomNerdTutorials--\r\n";

    uint32_t imageLen = fb->len;
    uint32_t extraLen = head.length() + tail.length();
    uint32_t totalLen = imageLen + extraLen;

    client.println("POST " + serverPath + " HTTP/1.1");
    client.println("Host: " + serverName);
    client.println("Content-Length: " + String(totalLen));
    client.println("Content-Type: multipart/form-data; boundary=RandomNerdTutorials");
    client.println();
    client.print(head);

    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    for (size_t n = 0; n < fbLen; n = n + 1024)
    {
      if (n + 1024 < fbLen)
      {
        client.write(fbBuf, 1024);
        fbBuf += 1024;
      }
      else if (fbLen % 1024 > 0)
      {
        size_t remainder = fbLen % 1024;
        client.write(fbBuf, remainder);
      }
    }
    client.print(tail);

    esp_camera_fb_return(fb);

    int timoutTimer = 10000;
    long startTimer = millis();
    boolean state = false;

    while ((startTimer + timoutTimer) > millis())
    {
      Serial.print(".");
      delay(100);
      while (client.available())
      {
        char c = client.read();
        if (c == '\n')
        {
          if (getAll.length() == 0)
          {
            state = true;
          }
          getAll = "";
        }
        else if (c != '\r')
        {
          getAll += String(c);
        }
        if (state == true)
        {
          getBody += String(c);
        }
        startTimer = millis();
      }
      if (getBody.length() > 0)
      {
        break;
      }
    }
    Serial.println();
    client.stop();
    Serial.println(getBody);
  }
  else    // Si no logra hacer la conexión FTP
  {
    getBody = "Connection to " + serverName + " failed.";
    Serial.println(getBody);
  }
  return getBody;
}

void configInitCamera()
{
  // COnfiguración necesaria para una buena foto
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // init with high specs to pre-allocate larger buffers
  if (psramFound())
  {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 10; // 0-63 menor numero = mayor calidad
    config.fb_count = 2;
  }
  else
  {
    config.frame_size = FRAMESIZE_CIF;
    config.jpeg_quality = 12; // 0-63 menor numero = mayor calidad
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);   
    ESP.restart(); 
  }
}

void setupWiFi()
{
  WiFi.mode(WIFI_STA);    // Modo de WiFI
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);   // Establece conección a internet
  while (WiFi.status() != WL_CONNECTED)   // Mientras se conecta
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());
}
