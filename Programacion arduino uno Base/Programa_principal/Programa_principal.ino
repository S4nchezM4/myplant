//Importar librerias
#include <Wire.h>
#include <DHT.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Definir constantes e inicializar DHT22
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Pines de la libreria de la oled
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



//Variables necesarias DHT22
int chk;
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

//Uso del Wifi en ESP32
void Wifi(){

}

//Muestreo de Variables en Oled
void displayTempHumid (){

  delay(1000);
  //Establecer variables con las lecturas
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  humF = analogRead(humfPin);
  uv = analogRead(uvPin);

  //Configuracion Oled
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0.5);
  

  //Impresion de variables
  display.setCursor(0,0);
  display.print("H-S: ");
  display.print(humF);
  display.setCursor(0,10);
  display.print("H-A: ");
  display.print(hum);
  display.print("%");
  display.setCursor(0,20);
  display.print("T: ");
  display.print(temp);
  display.print("C");
  display.setCursor(60,20);
  display.print("UV: ");
  display.print(uv);
}


//Muestreo de variables en Serial
void serialPrintln(){
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  humF = analogRead(humfPin);
  uv = analogRead(uvPin);

  Serial.print("Humedad suelo:");
  Serial.println(humF);
  Serial.print("Humedad ambiental:");
  Serial.println(hum);
  Serial.print("Temperatura ambiental:");
  Serial.println(temp);
  Serial.print("Rayos UV:");
  Serial.println(uv);
  Serial.println("-----------------------------------------------------------------");
  delay(1000);
}

//Repeticion del 
void loop() {
  serialPrintln();
  displayTempHumid();
  display.display();

}
