/*

*/
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include <SPI.h>

// configuration for WiFi stuff
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;
char server[] = "wled-1.local";
WiFiClient client;
const String on = "SM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=60&SX=64&IX=113&T=1";
const String red = "SM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=255&G=0&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=60&SX=203&IX=246&T=1";
const String green = "SM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=255&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=0&T=1";
const String spots = "SM=0&SS=0&SV=2&S=15&S2=299&GP=7&SP=30&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=0&T=1";
const String off = "&T=0";

// configuration for light detection
const int pinLight = A0;
int threshold = 400;
int sensorValue;


void setup() {
  // initialise serial port and wait for an connection
  Serial.begin(9600);
  while(!Serial);
  
  // try to connect to Network
  while (status != WL_CONNECTED) {
    Serial.print("Versuche Verbindung mit Netzwerk herzustellen: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    
    // delay to establish connection
    delay(10000);
  }
  // print Network information and wait 10 seconds
  Serial.println("Netzwerkinformationen:");
  printData();
  delay(10000);
}

void loop() {
  sensorValue = analogRead(pinLight);
  
  if(sensorValue > threshold) {
    Serial.println("Licht erkannt!");
    // send scenes
    Serial.println("Verbinden zum Server...");
    if (client.connect(server, 80)) {
      Serial.println("Verbindung hergestellt!");
      Serial.println("Sende scenen...");
      
      // make HTTP-GET requests
      // request for first animation (white flash)
      client.println("GET /win" + on + " HTTP/1.1");
      client.println("Host: wled-1.local");
      client.println("Connection: close");
      client.println();
      
      // 2.5 seconds
      delay(2500);
      
      // request for red animation
      client.println("GET /win" + red + " HTTP/1.1");
      client.println("Host: wled-1.local");
      client.println("Connection: close");
      client.println();
      
      // 24 seconds (door opens)
      delay(24000);
      
      // request for green flash
      client.println("GET /win" + green + " HTTP/1.1");
      client.println("Host: wled-1.local");
      client.println("Connection: close");
      client.println();
      
      // 5 seconds
      delay(5000);
      
      // request for white spots
      client.println("GET /win" + spots + " HTTP/1.1");
      client.println("Host: wled-1.local");
      client.println("Connection: close");
      client.println();
      
      Serial.println("Fertig!");
      // final delay (3min)
      delay(300000);
      
      client.println("GET /win" + off + " HTTP/1.1");
      client.println("Host: wled-1.local");
      client.println("Connection: close");
      client.println();
    }
  }
  else {
    Serial.println("Alles normal");
  }
}

void printData() {
  
  // local IPv4 IP
  Serial.println("Board Information");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // network name
  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
  
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
