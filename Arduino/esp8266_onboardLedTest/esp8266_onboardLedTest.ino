    int pin = 2;
     
    void setup() {
      
      pinMode(pin, OUTPUT);
    }
     
     
    void loop() {
      Serial.begin(115200);
      Serial.println("Hello World");
      digitalWrite(pin, HIGH);   //bật led
      delay(100);               //dừng 1s
      digitalWrite(pin, LOW);    //tắt led
      delay(100);               //dừng 1s
    }
