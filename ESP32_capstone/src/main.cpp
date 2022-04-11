/*
 *  Envío de evidencia fotográfica tras una señal de impacto por medio de IoT
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
 *  Especia agradecimiento a Rui Santos de Random Nerd Tutorials que con su proyecto
 *  "ESP32-CAM Post Images to Local or Cloud Server using PHP (Photo Manager)"
 *  pudimos llevar acabo este proyecto
 */

#include <Arduino.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include <PubSubClient.h>
// Credenciales ssid (WiFi)
const char *ssid = "G307";     // Cuca's_chan ; G307 ; Totalplay-73A0-_2.4Gnormal ; IZZI-A42E ; 
const char *password = "G307PASS"; //  Naylita2021 ; G307PASS ; D43FCB10A42E ; C3rradur45_C4D1

String serverName = "148.206.74.17"; // REEMPLAZAR CON EL IP DEL SERVIDOR // 148.206.74.17
// String serverName = "example.com";   // O REMPLAZALO CON EL NOMBRE DE TU DOMINIO

String serverPath = "/webapp/upload.php"; // EL DIRECTORIO POR DEFECTO DEBERIA SER upload.php

const int serverPort = 80; // El puerto a conectarse

//  Variables MQTT
const char *mqtt_server = "realdtc.ga"; //  148.206.74.17
const int mqtt_port = 1883;             // ???
const char *mqtt_user = "web_client";   // Credenciales MQTT
const char *mqtt_pass = "121212";
char msg[25]; // Este char se usa para enviar el mensaje

const int readPin = 16; // frontSignal_pin
bool reading = LOW;

WiFiClient client;
PubSubClient mqttclient(client);

// Serie de constantes para que lea la cámara el ESP
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

const int timerInterval = 3000;   // tiempo minimo entre cada imagen
unsigned long previousMillis = 0; // ultima vez de imagen enviada
camera_config_t config;

int picknum = 5; // Numero de fotos que se envían

//************************************
//***** Declaracion de funciones *****    No se hace en Arduino IDE
//************************************
String sendPhoto();
void configInitCamera();
void alertaMqtt();
void reconnect();
void setup_wifi();

void setup()
{
  pinMode(readPin, INPUT); // seteamos modo de lectura al pin
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);

  setup_wifi();                                 //  Iniciamos conexión wifi
  mqttclient.setServer(mqtt_server, mqtt_port); // Establece servidor MQTT
  Serial.println("MQTT settings setted");
  configInitCamera();                           // Se inicia la cámara
  Serial.println("Camara settings setted");
}

void loop()
{
  if (!mqttclient.connected()) //  Checa conexion mqtt
  {
    Serial.println("Conecting MQTT");
    reconnect(); // Llama función
  }
  reading = digitalRead(readPin); // Lee el sensor frontal

  if (reading) // Si está activo cualquier sensor
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= timerInterval)
    {
      Serial.println("¡¡Crushed!!");
      for (int i = 0; i < picknum; i++) // Para enviar "picknum" fotos
      {
        if (i == 0)
          alertaMqtt(); // Solo una vez envia la alerta
        sendPhoto();    // Llama la función
        delay(50);
      }
      previousMillis = currentMillis; // Setea valor
    }
  }
}

String sendPhoto()
{
  String getAll;
  String getBody;
  // Las siguientes dos líneas toman la foto
  camera_fb_t *fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) // Si no se tomó
  {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }

  Serial.println("Connecting to server: " + serverName);

  if (client.connect(serverName.c_str(), serverPort)) // Se conecta
  {
    Serial.println("Connection successful!"); //
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
  else // Si no logra hacer la conexión FTP
  {
    getBody = "Connection to " + serverName + " failed.";
    Serial.println(getBody);
  }
  return getBody; // Regresa el valor getBody
}

void configInitCamera()
{
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
    config.jpeg_quality = 10; // 0-63 lower number means higher quality
    config.fb_count = 2;
  }
  else
  {
    config.frame_size = FRAMESIZE_CIF;
    config.jpeg_quality = 12; // 0-63 lower number means higher quality
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);   // Checa esta línea
    ESP.restart(); // Checa esta linea (no está en el otro código)
  }
}

void alertaMqtt()
{
  String to_send = "Crushed front!";  // Cadena a enviar   $$$ - Cambiar para cada ESP32 - $$$
  to_send.toCharArray(msg, 25); //  Se convierte a CharArray
  Serial.print("Publicamos mensaje -> ");
  Serial.println(msg);
  mqttclient.publish("vehicle_state", msg); // Se publica con orden: ("Topico", mensaje)
}

void reconnect()
{

  while (!mqttclient.connected())
  {
    Serial.print("Intentando conexión Mqtt...");
    // Creamos un cliente ID
    String clientId = "esp32_";
    clientId += String(random(0xffff), HEX); // Crea cliente con numeros random
    // Intentamos conectar
    if (mqttclient.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conectado!");
      // mqttclient.subscribe("led1");   // Se suscribe al tópico
    }
    else
    {
      Serial.print("falló :( con error -> ");
      Serial.print(mqttclient.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");

      delay(5000);
    }
  }
}

void setup_wifi()
{
  delay(10);
  WiFi.mode(WIFI_STA); // Setea el modo de wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);           // Inicia wifi
  while (WiFi.status() != WL_CONNECTED) // Espera a que conecte
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("¡¡Conected!!");
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());
}
