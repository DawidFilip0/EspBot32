#include <Sensor.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>


Sensor::Sensor()
{
    IRReadingQueue = xQueueCreate(50,sizeof(IRreading));
    HallReadingQueue = xQueueCreate(50,sizeof(IRreading));
    totalHallReadings = 0
}

void Sensor::readIRSensors()
{
    Serial.print("farr left sensor: ");
    Serial.print(analogRead(farLeftSensor));
    Serial.print(" ");
    Serial.println(analogRead(farLeftSensor) > lineDetectionThreshold);

    Serial.print("left sensor: ");
    Serial.print(analogRead(leftSensor));
    Serial.print(" ");
    Serial.println(analogRead(leftSensor) > lineDetectionThreshold);

    Serial.print("middle sensor: ");
    Serial.print(analogRead(middleSensor));
    Serial.print(" ");
    Serial.println(analogRead(middleSensor) > lineDetectionThreshold);

    Serial.print("right sensor: ");
    Serial.print(analogRead(rightSensor));
    Serial.print(" ");
    Serial.println(analogRead(rightSensor) > lineDetectionThreshold);

    Serial.print("far right sensor: ");
    Serial.print(analogRead(farRightSensor));
    Serial.print(" ");
    Serial.println(analogRead(farRightSensor) > lineDetectionThreshold);


    IRreading sensorsValues;
    uint8_t  readings = 0;
    readings = 0b00000000;
    readings |= (analogRead(farLeftSensor) > lineDetectionThreshold) ? 0b00010000 : 0b00000000;
    readings |= (analogRead(leftSensor) > lineDetectionThreshold) ? 0b00001000 : 0b00000000;
    readings |= (analogRead(middleSensor) > lineDetectionThreshold) ? 0b00000100 : 0b00000000;
    readings |= (analogRead(rightSensor) > lineDetectionThreshold) ? 0b00000010 : 0b00000000;
    readings |= (analogRead(farRightSensor) > lineDetectionThreshold) ? 0b00000001 : 0b00000000;

    sensorsValues.readings = readings;
    sensorsValues.timestamp = xTaskGetTickCount();


    if(xQueueSend(IRReadingQueue, &sensorsValues, pdMS_TO_TICKS(50)) != pdPASS){
        Serial.println("Failed to send data to queue");
    }
    

}


void IRAM_ATTR Sensor::handleHallSensors(){
    totalHallReadings++;

}





// #include <Arduino.h>
//  //detection thresholds
//   int thresholdLow = 1800;
//   int thresholdHigh = 1900;

//   //logic variables
//   bool passed =  true;
//   int total_wheel_spins = 0;
//   int last_time_measurment = millis();
//   int spins_since_last_measurment = 0;
//   int wheel_circumference = 2; //cm
//   int measurment_delay = 3000;

//   //calculated information (output)
//   int distance_since_last_measurment = 0;
//   int total_distance = 0;
//   int cm_per_sec = 0;


// void count_speed();

// void setup() {
//   pinMode(4,INPUT);
//   Serial.begin(9600);

 
// }

// void loop() {
//   int reading = analogRead(4);

//   if(reading < (thresholdLow) && passed == true){
//     passed = false;
//     spins_since_last_measurment++;
//     Serial.print("pass : ");
//     Serial.println(total_wheel_spins);
//   }

//   if(reading > (thresholdHigh )){
//     passed = true;
 
//   }


//   count_speed();
 

//   // Serial.println(analogRead(4));
//   delay(5);

// }

// void count_speed(){
//   if( millis() - last_time_measurment > measurment_delay){
//     last_time_measurment = millis();

//       Serial.print("cm/s: ");
//    Serial.println(cm_per_sec);


//     total_wheel_spins += spins_since_last_measurment;
//     total_distance = total_wheel_spins * wheel_circumference;
//     cm_per_sec =  spins_since_last_measurment * wheel_circumference;  //cm per second
//     distance_since_last_measurment = spins_since_last_measurment * wheel_circumference / measurment_delay ;

//     spins_since_last_measurment = 0;

//   }

// };