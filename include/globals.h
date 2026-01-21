#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>

typedef uint8_t Pin;



//ENUM DECLARATIONS
enum rotation {
  LEFT = 1,
  RIGHT = 2
};

enum PowerLevel {
  ON = 1,
  OFF = 0
};

enum direction {
  FORWARD = 1,
  BACKWARD = -1
};

enum movementAction {
  STOP = 0b000,
  ROTATE_LEFT = 0b100,
  TURN_LEFT = 0b110,
  MOVE_FORWARD = 0b010,
  TURN_RIGHT = 0b011,
  ROTATE_RIGHT = 0b001,
  CROSSROAD = 0b111
};


//PIN DECLARATIONS
// Motor A (left) connections
extern Pin enA;  //engine speed / on-off;
extern Pin enABack;  //directional control(BACKWARD)
extern Pin enAForward;  //directional control(FORWOARD)

// Motor B (right) connections
extern Pin enB;
extern Pin enBBack; // BACKWARD
extern Pin enBForward; //FORWARD

extern int pwmFrequency;
extern int pwmResolution;

extern Pin farRightSensor;
extern Pin rightSensor;
extern Pin middleSensor;
extern Pin leftSensor;
extern Pin farLeftSensor;


extern Pin frontLeftHall = 10;
extern Pin frontRightHall = 13;
extern Pin backLeftHall = 18;
extern Pin backRightHall = 14;

//VARIABLE DECLARATIONS
extern uint8_t readings;
extern int lineDetectionThreshold;
extern int lastMovementAction;
extern int recentReadingsChecked;
extern int kp;
extern Pin enPower;

extern QueueHandle_t IRReadingQueue;
extern QueueHandle_t HallReadingQueue;


struct IRreading{
    TickType_t timestamp;
    uint8_t readings;

};

struct HallReading{
    TickType_t timestamp;
    uint16_t totalRevolutions;
};




#endif