//Declaración de variables del proceso
#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
   
  if (Serial.available()>0)   {
      int one = Serial.read();
      int two = Serial.read();

      unsigned int valor_medido = ( one - 48) *10 + (two - 48);

      float LR = ((valor_medido*100.0)/1023.0);
      Serial.print(LR);
  }
}
