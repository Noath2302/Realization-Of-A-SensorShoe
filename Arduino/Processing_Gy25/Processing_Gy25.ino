//Remove TX and RX pins that connect to Arduino when upload Arduino program. 
//Connect TX/RX (D1/D0) to GY-25 
//Use D10 and D11 to translate the tilt results. 
#include <SoftwareSerial.h> 
const byte rxPin = 10; 
const byte txPin = 11; 
SoftwareSerial teraTerm (rxPin, txPin); //for Tera Term 
unsigned char returnBuffer[8],counter=0; //buffer where the received data will be stored 
unsigned char fullBuffer=0; //0: buffer not full, 1: buffer is full 
unsigned char yawPitchRoll[3]; //An array of three integers. Index 0: Yaw, Index 1: Pitch, Index 2: roll. 
unsigned char inty[5]; 
void setup() { 
  Serial.begin(115200); // initialize serial communication between the Arduino and tilt angle module 
  delay(2000); 
  Serial.write(0XA5); // request the data 
  Serial.write(0X52); 
  teraTerm.begin(115200); // initialize serial communication between the Arduino and the PC 
  TIMSK0 = 0; } // the loop function runs over and over again forever: 
  void loop() { 
    if(fullBuffer == 1 && returnBuffer[0]==0xAA && returnBuffer[7]==0x55) //Check if buffer is full and if packet is correct 
    { 
      inty[0]=returnBuffer[1]; 
      inty[1]=returnBuffer[3]; 
      inty[2]=returnBuffer[5]; 
      //Print angles and sync 
      teraTerm.write(returnBuffer[0]); 
      teraTerm.write(returnBuffer[7]); 
      teraTerm.write(inty[0]); 
      teraTerm.write(inty[1]); 
      teraTerm.write(inty[2]); //Debug 
      //teraTerm.print(inty[0]); 
      //teraTerm.print("\t"); 
      //teraTerm.print(inty[1]); 
      //teraTerm.print("\t"); 
      //teraTerm.println(inty[2]); 
      } fullBuffer=0; 
      angleModulePortEvent(); 
      // Checks if data has been received 
      } 
      void angleModulePortEvent() { 
        while (Serial.available()) { 
          returnBuffer[counter]=(unsigned char)Serial.read(); 
          if(counter==0&&returnBuffer[0]!=0xAA) return; //wait for start character 
          counter++; 
          if(counter==8) {
            counter=0; 
            fullBuffer=1; //mark buffer as full } } }﻿
          }
    }
}
