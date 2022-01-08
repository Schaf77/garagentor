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
const String on = "SM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=255&FX=60&SX=64&IX=113&T=1";
const String red = "SM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=255&G=0&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=60&SX=203&IX=246&T=1";
const String green = "SM=0&SS=0&SV=2&S=0&S2=299&GP=1&SP=0&RV=0&SB=255&A=255&R=0&G=255&B=0&W=0&R2=0&G2=0&B2=0&W2=0&FX=0&T=1";
const String spots = "SM=0&SS=0&SV=2&S=15&S2=299&GP=7&SP=30&RV=0&SB=255&A=255&R=0&G=0&B=0&W=255&R2=0&G2=0&B2=0&W2=0&FX=0&T=1";
const String off = "&T=0";

// configuration for light detection
const int pinLight = A0;
int threshold = 400;
int sensorValue;
bool doorClosed = true;


void setup() {
  // initialise serial port and wait for an connection
  Serial.begin(9600);
  // ONLY FOR DEBUGGING
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
  
  // 10 Second delay, before loop starts
  delay(10000);
}

void loop() {
  sensorValue = analogRead(pinLight);
  
  if(sensorValue > threshold) {
    Serial.println("Licht erkannt!");
    // send scenes
    if (doorClosed) {
      Serial.println("Spiele Hochfahranimation...");
      Serial.println("Verbinden zum Server...");
      if (client.connect(server, 80)) {
        Serial.println("Verbunden!");
        Serial.println("Sende scenen...");
        
        // make HTTP-GET requests
        // request for first animation (white flash)
        Serial.println("Einschaltanimation");
        client.println("GET /win" + on + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // 3,8 seconds
        delay(3800);
        
        // request for red animation
        Serial.println("Rotes Lauflicht");
        client.println("GET /win" + red + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // 24 seconds (door opens)
        delay(24000);
        
        // request for green flash
        Serial.println("Grünes Licht");
        client.println("GET /win" + green + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // 5 seconds
        delay(5000);
        
        // request for white spots
        Serial.println("Spots");
        client.println("GET /win" + spots + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        Serial.println("Fertig!");
        // Update door position
        doorClosed = false;
      }
    else {
      Serial.println("Spiele Runterfahranimation...");
      Serial.println("Verbinde mit Server...");
      if (client.connect(server, 80)) {
        Serial.println("Verbunden!");
        
        // rotes Lauflicht
        Serial.println("Rotes Lauflicht");
        client.println("GET /win" + red + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // 24 Sekunden
        delay(24000);
        
        // grün
        Serial.println("Grünes Licht");
        client.println("GET /win" + green + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // 3 Sekunden
        delay(3000);
        
        // spots
        Serial.println("Spots");
        client.println("GET /win" + spots + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // 1 Minute
        delay(60000);
        
        // ausschalten
        Serial.println("Aus");
        client.println("GET /win" + off + " HTTP/1.1");
        client.println("Host: wled-1.local");
        client.println("Connection: close");
        client.println();
        
        // Update door position
        doorClosed = true;
      }
    }
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
  
  // encryption type
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
