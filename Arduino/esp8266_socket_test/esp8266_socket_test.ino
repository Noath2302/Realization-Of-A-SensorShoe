
#include <ESP8266WiFi.h>

const char* ssid     = "smartShoe";
const char* password = "123456789";
const char* host     = "192.168.137.1";
const uint16_t port = 22222;
WiFiClient client1;
void setup() {
  Serial.begin(115200);
  setupESP8266();
}

void loop() {
  // Use WiFiClient class to create TCP connections

  while (client1.connected()) {
    client1.println("hello from ESP8266");
    if(1){
      // Close the connection
      Serial.println();
      Serial.println("closing connection");
      client1.stop();
      }
  }

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

  while (!client1.connect(host, port)) {
    Serial.println("connection pending");
  }
}
