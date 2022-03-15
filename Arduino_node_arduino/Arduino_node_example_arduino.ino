#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "Yunwoo";
const char* password = "91773882";

WiFiUDP Udp;
unsigned int localUdpPort = 12345;  
char incomingPacket[255];  

void setup()
{
  Serial.begin(115200);
  delay(1000);
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localUdpPort);
  Serial.printf("UDP port: %d\n", localUdpPort);
}


void loop()
{ 
  int val = random(100);

  //make JSON format
  String test = "{\"project\":\"ArduinoNodeExample\",\"value\":" + String(val) + "}";
  String replyPacket = test; 
  char charBuf[replyPacket.length()+1];
  replyPacket.toCharArray(charBuf, replyPacket.length()+1);

  //send to node server
  Udp.beginPacket("cidrdev.kaist.ac.kr", 4559); 
  Udp.write(charBuf);
  Udp.endPacket(); 
  delay(100);
}
