#include <wifi_config.h>

// Global variable definitions
WiFiServer wifiServer(TCP_PORT);
WiFiClient wifiClient;
SerialWithWiFi DebugSerial;

void initWiFiAP() {
  // Start WiFi in Access Point mode
  Serial.println("Starting WiFi Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP: ");
  Serial.println(IP);
  Serial.print("SSID: ");
  Serial.println(WIFI_SSID);
  Serial.print("Password: ");
  Serial.println(WIFI_PASSWORD);
  
  // Start TCP server for serial monitoring
  wifiServer.begin();
  Serial.println("TCP Server started on port 23");
}

void initOTA() {
  // Configure OTA
  ArduinoOTA.setHostname("MazeBot");
  
  ArduinoOTA.onStart([]() {
    Serial.println("OTA Update started...");
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA Update completed!");
  });
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
}

void handleWiFiSerial() {
  // Check for new client connection
  if (wifiServer.hasClient()) {
    if (!wifiClient || !wifiClient.connected()) {
      if (wifiClient) wifiClient.stop();
      wifiClient = wifiServer.available();
      Serial.println("New WiFi client connected");
    }
  }
  
  // Forward data from WiFi client to Serial
  if (wifiClient && wifiClient.connected()) {
    if (wifiClient.available()) {
      char c = wifiClient.read();
      Serial.write(c);
    }
  }
}

// SerialWithWiFi implementations
void SerialWithWiFi::print(const char* str) {
  Serial.print(str);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.print(str);
  }
}

void SerialWithWiFi::print(int num) {
  Serial.print(num);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.print(num);
  }
}

void SerialWithWiFi::print(int num, int format) {
  Serial.print(num, format);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.print(num, format);
  }
}

void SerialWithWiFi::println(String str) {
  Serial.println(str);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.println(str);
  }
}

void SerialWithWiFi::println(const char* str) {
  Serial.println(str);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.println(str);
  }
}

void SerialWithWiFi::println(int num) {
  Serial.println(num);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.println(num);
  }
}

void SerialWithWiFi::println(int num, int format) {
  Serial.println(num, format);
  if (wifiClient && wifiClient.connected()) {
    wifiClient.println(num, format);
  }
}