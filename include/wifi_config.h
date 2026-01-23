#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>
#include <ArduinoOTA.h>

// WiFi Access Point Configuration
#define WIFI_SSID "MazeBot-DebugTEST"
#define WIFI_PASSWORD "mazebot123"
#define TCP_PORT 23  // Telnet port for serial monitoring

extern WiFiServer wifiServer;
extern WiFiClient wifiClient;

void initWiFiAP();
void initOTA();
void handleWiFiSerial();

// Override Serial.print to forward to WiFi clients
class SerialWithWiFi {
public:
  void print(const char* str);
  void print(int num);
  void print(int num, int format);
  void println(String str);
  void println(const char* str);
  void println(int num);
  void println(int num, int format);
};

extern SerialWithWiFi DebugSerial;

#endif