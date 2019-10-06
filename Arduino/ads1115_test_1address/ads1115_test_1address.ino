#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads0(0x48);
Adafruit_ADS1115 ads1(0x49);
double adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7; 

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  ads0.begin();
  ads1.begin();
  
}

void loop(void)
{
  readData();

  

  delay(0);
}

void readData(){
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
