#include <Engine.h>
#include <Sensor.h>
#include <AlgorithmLineFollowing.h>
#include <Arduino.h>
#include "globals.h"

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
    int baseSpeed = 130; 

    int left = baseSpeed - steering;
    int right = baseSpeed + steering;

    left = constrain(left, 0, 255);
    right = constrain(right, 0, 255);

    engineLeft.setEngineSpeed(left);
    engineRight.setEngineSpeed(right);



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

  for(;;){

   vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void handleScreen(void* pv){

  for(;;){

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}





int lastSave = 0;
//SETUP
void setup() {
  Serial.begin(115200);  
  pinMode(enPower,OUTPUT);
  digitalWrite(enPower,HIGH);  
  Serial.begin(115200);  

  engineLeft.setEngineDirection(FORWARD);
  engineRight.setEngineDirection(FORWARD);

    engineLeft.setEngineSpeed(100);
    engineRight.setEngineSpeed(100);

  xTaskCreate(handleSensors,"handleSensors",4096,NULL,10,NULL);
  xTaskCreate(handleMovement,"handleMovement",4096,NULL,10,NULL);
  xTaskCreate(handleCommunication,"handleCommunication",4096,NULL,2,NULL);
  xTaskCreate(handleScreen,"handleScreen",4096,NULL,1,NULL);



  
}




void loop() {
  





  delay(200);
}
