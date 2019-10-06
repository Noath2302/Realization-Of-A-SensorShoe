//===== adding libraries(2) =====
#include <Wire.h>
#include "MPU9250.h"

//===== MPU9250 gyroscope device(1) =====
MPU9250 IMU(Wire,0x68);
int status;

//===== SETUP_MAIN =====
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  setupMPU9250();
}

void loop(void)
{
  readMPU9250();
  delay(1000);
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
