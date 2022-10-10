unsigned int valor_medido;                                //Valor obtenido al leer por A0.
int ledPin = 10;                                     //Pin de conexión del led de prueba.
float LR;                                               //Variable para almacenar la luminosidad relativa.
float val;                                              //Variable empleada para el mapeo del valor medido para enviarlo al pin 10.

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Trans.begin(115200);                           //Velocidad de envío para la transmisión al NodeMCU.
}

void loop()
{
  valor_medido = analogRead(A0);                      //Valor de luminosidad medido en A0
  LR = (valor_medido * 100) / 1023.0;                   //Luminosidad medida en tanto por ciento
  Serial.print(LR);                                               //Para mostrar el valor en el monitor serie de arduino.
  Serial.println(" % luminosidad relativa");
  delay(1000);                                                                           //encender el led.
  analogWrite(ledPin, val);
  delay(1000);
  Trans.print(valor_medido);                                                    //Transmisión del valor a NodeMCU.
  delay(1000);  
}
