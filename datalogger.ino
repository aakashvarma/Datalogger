#include <SoftwareSerial.h>
int sensor1=A2;
int sensor2=A4;
int sensor3=A5;
int sensor1State=0;
int sensor2State=0;
int sensor3State=0;
String apiKey = "NRD5I1JZ5SKOFXE0";
SoftwareSerial ser(10, 11); // RX, TX
void setup() {
  ser.println("AT+RST");
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);

  // enable debug serial
  Serial.begin(115200);
  // enable software serial
  ser.begin(115200);

  // reset ESP8266


}

void loop() {
  sensor1State = analogRead(sensor1);
  sensor2State = analogRead(sensor2);
  sensor3State = analogRead(sensor3);
  String state1=String(sensor1State);


  String state2=String(sensor2State);


  String state3=String(sensor3State);
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
  Serial.println(cmd);
  delay(1500);
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(state1);
  getStr +="&field2=";
  getStr += String(state2);
  getStr +="&field3=";
  getStr += String(state3);
  getStr += "\r\n\r\n";
   cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  Serial.println(cmd);


  if(ser.find(">")){
    ser.print(getStr);
    Serial.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");

      }

  // thingspeak needs 15 sec delay between updates
  delay(16000);}
