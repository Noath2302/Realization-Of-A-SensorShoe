//===== adding libraries(3) ================================
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "MPU9250.h"
#include <ESP8266WiFi.h>

//===== ADS1115 adc devices(2) =============================
Adafruit_ADS1115 ads0(0x48);
Adafruit_ADS1115 ads1(0x49);
long adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7; 
String adc = "";
//===== MPU9250 gyroscope device(1) ========================
MPU9250 IMU(Wire,0x68);
int status;
String imu = "";
//===== ESP8266 Wifi module test ===========================
String message;
const char* ssid     = "smartShoe";
const char* password = "123456789";
//const char* ssid     = "toan";
//const char* password = "deochomay";
const uint16_t port = 22222;
int count = 1;
WiFiClient client1;
//===== Speed test =========================================
double currentMillis=0;
double previousMillis=0;
double startMillis = 0;
//===== SETUP_MAIN =========================================
void setup(void)
{
  Serial.begin(115200);
  setupADS1115();
  setupMPU9250();
  setupESP8266();
  delay(2000);
  startMillis = millis()/10;
}

//===== LOOP_MAIN ==========================================
void loop(void)
{
  previousMillis=millis()/10;
  while (client1.connected() and previousMillis-startMillis<3000) {
    message = "";
    for(int i = 0;i<3;i+=1){
      readADS1115();
      readMPU9250();
      currentMillis = millis()/10;
      message += adc+"\t"+String(currentMillis)+"\t"+imu+"\t"+"Z";
      previousMillis = currentMillis;
    }
    client1.print(message);
  }
  client1.println(String("END"));
  client1.stop();    
}

void readADS1115(){
  adc = "";
  adc0 = ads1.readADC_SingleEnded(0)/*0.1875*0.001*/;  adc+=adc0+String("\t");
  adc1 = ads1.readADC_SingleEnded(1)/*0.1875*0.001*/;  adc+=adc1+String("\t");
  adc2 = ads1.readADC_SingleEnded(2)/*0.1875*0.001*/;  adc+=adc2+String("\t");
  //adc3 = ads1.readADC_SingleEnded(3)/*0.1875*0.001*/;  adc+=adc3+String("\t");
  adc4 = ads0.readADC_SingleEnded(0)/*0.1875*0.001*/;  adc+=String(adc4)+"\t";
  adc5 = ads0.readADC_SingleEnded(1)/*0.1875*0.001*/;  adc+=String(adc5)+"\t";
  adc6 = ads0.readADC_SingleEnded(2)/*0.1875*0.001*/;  adc+=String(adc6)+"\t";
  //adc7 = ads0.readADC_SingleEnded(3)/*0.1875*0.001*/;  adc+=String(adc7)+"\t";
 }
void setupADS1115(){
  ads0.begin();
  ads1.begin();
 }
void setupMPU9250(){
  while(!Serial) {}
  status = IMU.begin();
  if (status < 0) {
    while(1) {}
  }
}
void readMPU9250(){
  IMU.readSensor();
  imu = "";
  imu+=String(IMU.getAccelX_mss())+"\t";
  imu+=String(IMU.getAccelY_mss())+"\t";
  imu+=String(IMU.getAccelZ_mss())+"\t";
  imu+=IMU.getGyroX_rads()+String("\t");
  imu+=IMU.getGyroY_rads()+String("\t");
  imu+=IMU.getGyroZ_rads()+String("\t");
  //imu+=IMU.getMagX_uT()+String("\t");
  //imu+=IMU.getMagY_uT()+String("\t");
  //imu+=IMU.getMagZ_uT()+String("\t");
  //imu+=IMU.getTemperature_C()+String("\t");  
}
void setupESP8266() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //creating socket

  while (!client1.connect(WiFi.gatewayIP(), port)) {
    Serial.println("connection pending");
  }
}
