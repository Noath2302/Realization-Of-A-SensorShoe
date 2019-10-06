// Connect RX of GY 25 to TX3 Arduino Mega and TX of GY 25 to RX3 Arduino Mega
float Roll,Pitch,Yaw;
unsigned char Re_buf[8],counter=0;
void setup()
{
Serial.begin(115200);
delay(4000);     
Serial.write(0XA5);
Serial.write(0X54);//correction mode
delay(4000);
Serial.write(0XA5);
Serial.write(0X51);//0X51:query mode, return directly to the angle value, to be sent each read, 0X52:Automatic mode,send a direct return angle, only initialization
}

void loop() {
serialEvent();
Serial.print("roll= ");
Serial.print(Roll);
Serial.print(" pitch= ");                 
Serial.print(Pitch);
Serial.print(" yaw= ");                 
Serial.println(Yaw);
}

void serialEvent() {
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
