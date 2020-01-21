#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Wifi Credentials
const char* ssid     = "SSID_NAME";
const char* password = "WIFI_PASSWORD";

//API Server Address
const char* host = "http://IP_ADDRESS:PORT/laundry/";

// I2C address of the MPU-6050
const int MPU_addr=0x68;

//Variables for storing sensor data
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup() {

  //Establish I2C Connection with MPU-6050
  Wire.begin(2,0); //SDA - GPIO2; SCL - GPIO0
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);    //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection 
    delay(500);
    Serial.println("Waiting for connection"); 
  }
}

void loop() {

  //Select MPU-6050 Data Register
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  //Request Data from MPU-6050
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Store data in JSON Structure
  const size_t capacity = JSON_OBJECT_SIZE(8);
  DynamicJsonDocument doc(capacity);
  
  doc["name"] = "MPU-6050 Laundry Sensor";
  doc["AccX"] = AcX;
  doc["AccY"] = AcY;
  doc["AccZ"] = AcZ;
  doc["GyX"] = GyX;
  doc["GyY"] = GyY;
  doc["GyZ"] = GyZ;
  doc["Temp"] = Tmp;

  //Print JSON to Serial Out
  serializeJsonPretty(doc, Serial);
 
  //If Connected to WiFi
  if (WiFi.status() == WL_CONNECTED) {

    //Stringify JSON
    String json;
    serializeJson(doc, json);

    
    //Send POST Request to API Server
    HTTPClient http;    //Declare object of class HTTPClient 
    http.begin(host);   //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    int httpCode = http.POST(json);
    
    //String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    
    //Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else { 
    Serial.println("Error in WiFi connection"); 
  }

  //Once per second
  delay(1000);
}
