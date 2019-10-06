//===== adding libraries(3) =====
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "MPU9250.h"
#include <ESP8266WiFi.h>

//===== ADS1115 adc devices(2) =====
Adafruit_ADS1115 ads0(0x48);
Adafruit_ADS1115 ads1(0x49);
double adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7; 
String adc = "";
//===== GY-25 gyroscope device(1) =====
String gy = "";
float Roll,Pitch,Yaw;
unsigned char Re_buf[8],counter=0;
//===== ESP8266 Wifi module test =====

const char* ssid     = "smartShoe";
const char* password = "123456789";
const char* host     = "192.168.137.1";
const uint16_t port = 22222;
int count = 1;
WiFiClient client1;
//===== Speed test =====
String probeString = "";
int currentMillis=0;
int previousMillis=0;
int startMillis = 0;
//===== SETUP_MAIN =====
void setup(void)
{
  probeString+=setupProbeString();
  Serial.begin(115200);
  //Serial.println("Hello!");
  //setupADS1115();
  setupGY25();
  setupESP8266();
  startMillis = millis();
}

//===== LOOP_MAIN =====
void loop(void)
{
  previousMillis=millis();
  while (client1.connected() and previousMillis-startMillis<30000) {
    //readADS1115();
    readGY25();
    currentMillis = millis();
    client1.println(adc+String(currentMillis-previousMillis)+String("\t")+currentMillis+String("\t")+count+String("\t")+Roll+String("\t")+Pitch+String("\t")+Yaw);
    delay(50);
    previousMillis = currentMillis;
  }
  client1.stop();  
}

void readADS1115(){
  adc = "";
  adc0 = ads1.readADC_SingleEnded(0)*0.1875*0.001;  adc+=adc0+String("\t");
  adc1 = ads1.readADC_SingleEnded(1)*0.1875*0.001;  adc+=adc1+String("\t");
  adc2 = ads1.readADC_SingleEnded(2)*0.1875*0.001;  adc+=adc2+String("\t");
  adc3 = ads1.readADC_SingleEnded(3)*0.1875*0.001;  adc+=adc3+String("\t");
  adc4 = ads0.readADC_SingleEnded(0)*0.1875*0.001;  adc+=adc4+String("\t");
  adc5 = ads0.readADC_SingleEnded(1)*0.1875*0.001;  adc+=adc5+String("\t");
  adc6 = ads0.readADC_SingleEnded(2)*0.1875*0.001;  adc+=adc6+String("\t");
  adc7 = ads0.readADC_SingleEnded(3)*0.1875*0.001;  adc+=adc7+String("\t");
//  Serial.print("AIN0: ");
//  Serial.println(adc0);
//  Serial.print("AIN1: ");
//  Serial.println(adc1);
//  Serial.print("AIN2: ");
//  Serial.println(adc2);
//  Serial.print("AIN3: ");
//  Serial.println(adc3);
//  Serial.print("AIN4: ");
//  Serial.println(adc4);
//  Serial.print("AIN5: ");
//  Serial.println(adc5);
//  Serial.print("AIN6: ");
//  Serial.println(adc6);
//  Serial.print("AIN7: ");
//  Serial.println(adc7);
//  Serial.println(" ");
 }
void setupADS1115(){
//  Serial.println("Getting single-ended readings from AIN0..3");
//  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  ads0.begin();
  ads1.begin();
 }
void setupGY25(){
delay(4000);
Serial.write(0XA5);
Serial.write(0X54);//correction mode
delay(4000);
Serial.write(0XA5);
Serial.write(0X51);//0X51:query mode, return directly to the angle value, to be sent each read, 0X52:Automatic mode,send a direct return angle, only initialization
  }
void readGY25(){
  Serial.write(0XA5);
Serial.write(0X51);//send it for each read
while (Serial.available()) {   
Re_buf[counter]=(unsigned char)Serial.read();
if(counter==0&&Re_buf[0]!=0xAA) return;       
counter++;       
if(counter==8)               
{   
  counter=0;                 
  if(Re_buf[0]==0xAA && Re_buf[7]==0x55)  // data package is correct     
    {         
     Yaw=(int16_t)(Re_buf[1]<<8|Re_buf[2])/100.00;   
     Pitch=(int16_t)(Re_buf[3]<<8|Re_buf[4])/100.00;
     Roll=(int16_t)(Re_buf[5]<<8|Re_buf[6])/100.00;
    }     
} 
}
}
void setupESP8266() {
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
  //creating socket

  while (!client1.connect(host, port)) {
//    Serial.println("connection pending");
  }
}
String setupProbeString(){
    String probeString="";
    for(long int i=0;i<4000;i+=1){
      probeString+="i";
      }
    return probeString;
  }
