int latchPin = 4;
int clockPin = 5;
int dataPin = 0;
byte leds = 0;
 
void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(2,INPUT);
  pinMode(16,INPUT);
  pinMode(14,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  pinMode(15,INPUT);
}
 
void loop() 
{
  leds = 0;
  updateShiftRegister();
  delay(500);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(500);
    showShift4bitBCDEvalue();
  }
}
 
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void showShift4bitBCDEvalue()
{
  Serial.print(digitalRead(2));
  Serial.print(digitalRead(16));
  Serial.print(digitalRead(14));
  Serial.print(digitalRead(12));
  Serial.print(digitalRead(13));
  Serial.print(digitalRead(15));
  Serial.print("00");
  Serial.println();
}
