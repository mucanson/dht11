#include <FirebaseArduino.h>
#include<ESP8266WiFi.h>
#include"DHT.h"
#define FIREBASE_HOST "dht11-b2648.firebaseio.com" //firebase host
#define FIREBASE_AUTH "U4rZOb8v5JyKSTvEd5h0NMZaDfzaQSm8yrH4G3D1" //firebase database secret 
#define WIFI_SSID "UIT Public"
#define WIFI_PASSWORD ""
#define DHTPIN D1 
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);
float t,h;   
void setup() {
 Serial.begin(9600);
 delay(1000);
 
 WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
 Serial.print("Connecting to ");
 Serial.println(WIFI_SSID);
 while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
    
 }
 Serial.println();
 Serial.print("Connected to ");
 Serial.println(WIFI_SSID);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP()); //print local IP
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //connect to firebase
 Serial.print("success");
 dht.begin(); // dht11 starts to reading 
 Serial.println ("dht11 begin");
}

void loop() {
  // put your main code here, to run repeatedly:
 t=dht.readTemperature();
 h=dht.readHumidity();
 if(isnan(h)||isnan(t)){
  Serial.println("Failed to read data from DHT11");
  return;
 } //check if read failed 
 Serial.print("Temp: "); Serial.println(t);
 String temp=String(t); //convert float to string 
 Serial.print("Humid: "); Serial.println(h);
 String humid=String(h);  
   delay(3000);
 Firebase.pushString("Temperature",temp); //send temp to firebase
 Firebase.pushString("Humidity",humid); //send humid to firebase
}
