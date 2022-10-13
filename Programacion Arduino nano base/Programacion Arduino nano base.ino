//Importar librerias
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Librerias Wifi y ThingSpeak
#include "WiFiEsp.h"
#include "secrets.h"
#include "ThingSpeak.h"

//Definir constantes e inicializar DHT22
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Pines de la libreria de la oled
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


//Variables necesarias DHT22
//int chk;
float hum;
float temp;
float humF;

//Variables Humedad en suelo
int humfPin = A0;

//Variables Sensor UV
int uvPin = A1;
int uv;


void setup() {

  //Serial Setup
  Serial.begin(115200);

  //Iniciar sensores y display
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();

}





void configDisplay(){

//Configuracion Oled
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0.5);
}






//Conexion Wifi
void Wifi(){
    if(WiFi.status() != WL_CONNECTED){
      display.setCursor(0,0);
      display.print("Conectando a: ");
      display.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); //Variables de conexion
      display.setCursor(0,10);
      display.print("Conectando.");
      display.print("Conectando..");
      display.print("Conectando...");
      delay(5000);     
    } 
    display.print("\nConectado.");
  }

}







//Llamado de programas
void loop() {
  configDisplay();
  WiFi();
  display.display();

  //llamado de variables
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  humF = analogRead(humfPin);
  uv = analogRead(uvPin);

  ThingSpeak.setField(1, hum);
  ThingSpeak.setField(2, temp);
  ThingSpeak.setField(3, humF);
  ThingSpeak.setField(4, uv);

  ThingSpeak.setStatus(myStatus);
    
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    display.setCursor(0,20);
    display.print("Updated");
  } else {
    display.print("Error: " + String(x));
  }
  delay(20000);



  

  void setEspBaudRate(unsigned long baudrate){
  long rates[6] = {115200,74880,57600,38400,19200,9600};

  Serial.print("Setting ESP8266 baudrate to ");
  Serial.print(baudrate);
  Serial.println("...");

  for(int i = 0; i < 6; i++){
    Serial1.begin(rates[i]);
    delay(100);
    Serial1.print("AT+UART_DEF=");
    Serial1.print(baudrate);
    Serial1.print(",8,1,0,0\r\n");
    delay(100);  
  }
    
  Serial1.begin(baudrate);

}
