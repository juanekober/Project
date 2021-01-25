int Sensor = 0;         // Pin that reads the temperature
int umbral = 20;        // set temperature
const int control = 3;  // Alarm pin


#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // Configure the serial port for the SIM900

void setup()
{
  Serial.begin(19200);
  pinMode(control, OUTPUT);

  digitalWrite(9,HIGH); // Activate the feeding by software
  delay(1000);
  digitalWrite(9,LOW);
  
  delay (5000);
  SIM900.begin(19200); //Set serial port speed for SIM900
  Serial.begin(19200); //Set serial port speed for Arduino
  Serial.println("-- WELCOME TO CONTROL TEMPERATURE --");
  Serial.println("-- LOOKING FOR OPERATOR --");
  delay(1000);
  SIM900.println("AT + CPIN = \"1234\"");
  delay(25000); //Tiempo en encontrar red
  Serial.println("-- OPERATOR FOUND --");
}

void loop() //Funcion para leer temperatura del sensor
{
  int lectura = analogRead(Sensor);
  float voltaje = 5.0 /1024 * lectura;
  float temp = voltaje * 100 -3;
  Serial.println("-- TEMPERATURE --");
  Serial.print(temp,1);
  Serial.println(" ªC");
  delay(1000);


  if (temp >= umbral) {
    digitalWrite(control, HIGH);

    Serial.println("Sending SMS..");
    SIM900.print("AT+CMGF=1\r");
    delay(1000);
    SIM900.println("AT+CMGS=\"626305062\"");
    delay(1000);
    SIM900.print("High temperature, value: ");
    SIM900.print(temp);
    SIM900.println(" C");
    delay(100);
    SIM900.println((char)26);
    delay(100);
    SIM900.println();
    delay(5000);
    Serial.println("SMS sent");
    
    llamar();
    //while(1);
  }

  else
    digitalWrite(control, LOW);
 
}

void llamar() // Funcion para realizar llamada
{
  Serial.println("Calling..");
  SIM900.println("ATD626305062;");
  delay(10000);
  SIM900.println("ATH");
  delay(1000);
  Serial.println("Finished call");
}
