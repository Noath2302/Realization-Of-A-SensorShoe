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
//===== MPU9250 gyroscope device(1) =====
MPU9250 IMU(Wire,0x68);
int status;

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
  setupMPU9250();
  setupESP8266();
  startMillis = millis();
}

//===== LOOP_MAIN =====
void loop(void)
{
  previousMillis=millis();
  while (client1.connected() and previousMillis-startMillis<30000) {
    //readADS1115();
    readMPU9250();
    currentMillis = millis();
    client1.println(adc+String(currentMillis-previousMillis)+String("\t")+currentMillis+String("\t"));
    delay(10);
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
void setupMPU9250(){
  while(!Serial) {}
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
//    Serial.println("IMU initialization unsuccessful");
//    Serial.println("Check IMU wiring or try cycling power");
//    Serial.print("Status: ");
//    Serial.println(status);
    while(1) {}
  }
}
void readMPU9250(){
    IMU.readSensor();
    adc = "";
  // display the data
//  Serial.print(IMU.getAccelX_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getAccelY_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getAccelZ_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroX_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroY_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroZ_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagX_uT(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagY_uT(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagZ_uT(),6);
//  Serial.print("\t");
//  Serial.println(IMU.getTemperature_C(),6);
  adc+=IMU.getAccelX_mss()+String("\t");
  adc+=IMU.getAccelY_mss()+String("\t");
  adc+=IMU.getAccelZ_mss()+String("\t");
  adc+=IMU.getGyroX_rads()+String("\t");
  adc+=IMU.getGyroY_rads()+String("\t");
  adc+=IMU.getGyroZ_rads()+String("\t");
  //adc+=IMU.getMagX_uT()+String("\t");
  //adc+=IMU.getMagY_uT()+String("\t");
  //adc+=IMU.getMagZ_uT()+String("\t");
  //adc+=IMU.getTemperature_C()+String("\t");  
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
