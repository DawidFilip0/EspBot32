#include <Engine.h>
#include <Sensor.h>
#include <AlgorithmLineFollowing.h>
#include <Arduino.h>
#include "globals.h"
#include "Display.h"
#include "Debug.h"
#include "wifi_config.h"

//CREATE CLASS OBJECTS
Engine engineLeft(enAForward,enABack,1,2);
Engine engineRight(enBForward,enBBack,3,4);
Sensor sensors;
AlgorithmLineFollwing algorithm(engineLeft, engineRight);

void handleMovement(void* pv){

  engineLeft.setEngineDirection(FORWARD);
  engineRight.setEngineDirection(FORWARD);
  for(;;){
    int steering = algorithm.determineSteering();
    // int baseSpeed = 130; 

    // int left = baseSpeed - steering;
    // int right = baseSpeed + steering;

    // left = constrain(left, 0, 255);
    // right = constrain(right, 0, 255);

    // engineLeft.setEngineSpeed(left);
    // engineRight.setEngineSpeed(right);


    vTaskDelay(pdMS_TO_TICKS(50));
  }
}



void handleSensors(void* pv){
  attachInterrupt(digitalPinToInterrupt(frontLeftHall), Sensor::handleHallSensors, FALLING);
  attachInterrupt(digitalPinToInterrupt(frontRightHall), Sensor::handleHallSensors, FALLING);
  attachInterrupt(digitalPinToInterrupt(backLeftHall), Sensor::handleHallSensors, FALLING);
  attachInterrupt(digitalPinToInterrupt(backRightHall), Sensor::handleHallSensors, FALLING);
  
  for(;;){
    sensors.readIRSensors();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void handleCommunication(void* pv){ //debug
  Debug debugger;
  initWiFiAP();
  vTaskDelay(pdMS_TO_TICKS(500));
  initOTA();
  vTaskDelay(pdMS_TO_TICKS(500));
  for(;;){
    ArduinoOTA.handle();
    handleWiFiSerial();
    debugger.printSensorAndAction(0b01010,BACKWARD);
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void handleScreen(void* pv){
  Display screen;
  screen.initDisplay();
  vTaskDelay(pdMS_TO_TICKS(500));
  for(;;){
    screen.displayArrow(1);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

//SETUP
void setup() {
  Serial.begin(115200);  
  pinMode(enPower,OUTPUT);
  digitalWrite(enPower,HIGH);  


  engineLeft.setEngineDirection(FORWARD);
  engineRight.setEngineDirection(FORWARD);

  engineLeft.setEngineSpeed(100);
  engineRight.setEngineSpeed(100);

  xTaskCreate(handleSensors,"handleSensors",4096,NULL,10,NULL);
  xTaskCreate(handleMovement,"handleMovement",4096,NULL,10,NULL);
  xTaskCreate(handleCommunication,"handleCommunication",4096,NULL,5,NULL);
  xTaskCreate(handleScreen,"handleScreen",4096,NULL,3,NULL);
  
}




void loop() {
  
  delay(200);
}
