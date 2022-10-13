#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include "WiFiEsp.h"
#include "secrets.h"
#include "ThingSpeak.h"

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiEspClient  client;

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

//Definir constantes e inicializar DHT22
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Pines de la libreria de la oled
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

unsigned int myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

//Variables necesarias
int hum;
int temp;
int humF;
int humfPin = A0;
int uvPin = A1;
int uv;
String myStatus = "";

void setup() {
  //Initialize serial and wait for port to open
  Serial.begin(115200);  // Initialize serial
    //Iniciar sensores y display
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
  
  // initialize serial for ESP module  

  //Config Display
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0.5);
  

  Serial.print("Buscando."); 
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Error: no hay");
    // don't continue
    while (true);
  }
  Serial.println("OK");
   
  ThingSpeak.begin(client);

}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Conectando a:");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  //Establecer Variables
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  humF = analogRead(humfPin);
  uv = analogRead(uvPin);

  // set the fields with the values
  ThingSpeak.setField(1, hum);
  ThingSpeak.setField(2, temp);
  ThingSpeak.setField(3, humF);
  ThingSpeak.setField(4, uv);

  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Updated");
  }
  else{
    Serial.println("Error: " + String(x));
  }

  //Display
  display.display();
  
  delay(20000);
}