//===== adding libraries(3) =====
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "MPU9250.h"

//===== ADS1115 adc devices(2) =====
Adafruit_ADS1115 ads0(0x48);
Adafruit_ADS1115 ads1(0x49);
double adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7; 

//===== MPU9250 gyroscope device(1) =====
MPU9250 IMU(Wire,0x68);
int status;

//===== SETUP_MAIN =====
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  setupADS1115();
  setupMPU9250();
}

void loop(void)
{
  readADS1115();
  readMPU9250();
  delay(1000);
}

void readADS1115(){
  adc0 = ads1.readADC_SingleEnded(0)*0.1875*0.001;
  adc1 = ads1.readADC_SingleEnded(1)*0.1875*0.001;
  adc2 = ads1.readADC_SingleEnded(2)*0.1875*0.001;
  adc3 = ads1.readADC_SingleEnded(3)*0.1875*0.001;
  adc4 = ads0.readADC_SingleEnded(0)*0.1875*0.001;
  adc5 = ads0.readADC_SingleEnded(1)*0.1875*0.001;
  adc6 = ads0.readADC_SingleEnded(2)*0.1875*0.001;
  adc7 = ads0.readADC_SingleEnded(3)*0.1875*0.001;  
  Serial.print("AIN0: ");
  Serial.println(adc0);
  Serial.print("AIN1: ");
  Serial.println(adc1);
  Serial.print("AIN2: ");
  Serial.println(adc2);
  Serial.print("AIN3: ");
  Serial.println(adc3);
  Serial.print("AIN4: ");
  Serial.println(adc4);
  Serial.print("AIN5: ");
  Serial.println(adc5);
  Serial.print("AIN6: ");
  Serial.println(adc6);
  Serial.print("AIN7: ");
  Serial.println(adc7);
  Serial.println(" ");
 }
void setupADS1115(){
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  ads0.begin();
  ads1.begin();
 }
void setupMPU9250(){
  while(!Serial) {}
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}
void readMPU9250(){
    IMU.readSensor();
  // display the data
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);
}
