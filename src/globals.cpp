#include <globals.h>

//PIN DECLARATIONS
// Motor A (left) connections

Pin enABack = 17;  //directional control(BACKWARD)
Pin enAForward = 16;  //directional control(FORWOARD)

// Motor B (right) connections

Pin enBBack = 12; // BACKWARD
Pin enBForward  = 11; //FORWARD

int pwmFrequency = 20000;
int pwmResolution = 8;


Pin farRightSensor = 6; 
Pin rightSensor =  5;
Pin middleSensor = 15;
Pin leftSensor = 7;
Pin farLeftSensor = 9;
Pin enPower = 4;


Pin frontLeftHall = 10;
Pin frontRightHall = 13;
Pin backLeftHall = 18;
Pin backRightHall = 14;


//VARIABLE DECLARATIONS
int lineDetectionThreshold = 1500;
int lastMovementAction = FORWARD;
int recentReadingsChecked = 50;

int kp = 10;


QueueHandle_t HallReadingQueue = NULL;
RingBuffer<IRreading, 50> IRreadingBuffer;