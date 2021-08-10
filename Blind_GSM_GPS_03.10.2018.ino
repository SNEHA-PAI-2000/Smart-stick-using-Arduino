// GSM Tx goes to RX pin of Arduino, Rx pin goes to TX pin of Arduino
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial serial_connection(11, 10);//RX= pin 10, TX=pin 11
TinyGPSPlus gps;  //Creates a new instance of the TinyGPS object


void setup()
{
  Serial.begin(9600);            //This opens up communication to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600); //This opens up communication to the GPS
  Serial.println("GPS Start");   
}

void loop()
{
    while (serial_connection.available())                 //While there are characters to come from the GPS
    {
      gps.encode(serial_connection.read());               
    }
      if (gps.location.isUpdated())
  {
    Serial.begin(9600);                                  //Baud rate of the GSM/GPRS Module
    Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r"); 
    delay(1000);
    Serial.println("AT + CMGS = \"+917892328325\"");// recipient's mobile number with country code
    delay(1000);
    Serial.print("I'm lost! Please help me im here ");//the message to be sent
    Serial.print("www.google.com.ph/maps/place/");    //link of google map
    Serial.print(gps.location.lat(), 6);              //to get the coordinate for Latitude
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);              //to get the coordinate for longitude
    Serial.print("\r");
    delay(1000);
    Serial.println((char)26); //ASCII code to end the message
    delay(1000);
    Serial.write(0x1A);
    Serial.write(0x0D);
    Serial.write(0x1A);
    delay(1000);
  }
}


