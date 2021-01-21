int Sensor = 0;         //Pin que lee la temperatura
int umbral = 10;        //Temperatura configurada
const int control = 3;  //Pin de alarma


#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // Configura el puerto serial para el SIM900

void setup()
{
  Serial.begin(115200);
  pinMode(control, OUTPUT);
  delay (5000);
  SIM900.begin(19200);
  Serial.begin(19200);
  Serial.println("OK");
  delay(1000);
  SIM900.println("AT + CPIN = \"1234\"");
  delay(25000);
}

void loop()
{
  int lectura = analogRead(Sensor);
  float voltaje = 5.0 /1024 * lectura;
  float temp = voltaje * 100 -3;
  Serial.println(temp);
  if (temp >= umbral) {
    digitalWrite(control, HIGH);
    llamar();
    while(1);
  }

  else
    digitalWrite(control, LOW);
  
  delay(200);
}

void llamar()
{
  Serial.println("Realizando llamada..");
  SIM900.println("ATD626305062;");
  delay(10000);
  SIM900.println("ATH");
  delay(1000);
  Serial.println("Llamada finalizada");
}
