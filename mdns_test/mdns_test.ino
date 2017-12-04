#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
char ssid[] = "ssid";
char pass[] = "pw";
int port = 1234;
String request;
WiFiServer server(port);
WiFiClient client;
void setup() {
  Serial.begin(115200); 
  delay(20);
  if(WiFi.status() == WL_NO_SHIELD){
    Serial.println("No WiFi shield present. Connection will not be established.");
    while(true);
  }
  Serial.print("Connecting to WPA SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass); 
  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Network connection established.");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  server.begin();
  Serial.print("Listening to port: ");
  Serial.println(port);
  String ipText = String(ip[0]) + String(".") + String(ip[1]) + String(".") + String(ip[2]) + String(".") + String(ip[3]);
  String locator = "tcp://" + ipText + String(":") + String(port);
  Serial.println(locator);
  String agentName = "ESPAgent47" + String("@") + ipText + String(":") + String(port) + String("/JADE");
  agentName.replace(".", "?");
  
  char agentNameArr[50];
  agentName.toCharArray(agentNameArr, 50);
  
  MDNS.begin(agentNameArr);
  MDNS.addService("fipa_service_directory", "udp", port);
  MDNS.addServiceTxt("fipa_service_directory", "udp", "LOCATOR", locator);
  MDNS.addServiceTxt("fipa_service_directory", "udp", "DESCRIPTION", "Very Silent Agent");
  MDNS.addServiceTxt("fipa_service_directory", "udp", "TIMESTAMP", "20171031-21:57:38:513000");
  MDNS.addServiceTxt("fipa_service_directory", "udp", "TYPE", "mts_client");
}
void loop() {
  client = server.available();
  
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\n' && currentLineIsBlank) {
          Serial.println(request);
          client.println("I am an agent.");
          request = "";
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        } 
      }
    }
  }
    client.stop();
}
