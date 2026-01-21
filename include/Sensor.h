#ifndef SENSOR_H
#define SENSOR_H
#include <globals.h>

class Sensor
{
    public:
        Sensor();
        void readIRSensors();
        static void handleHallSensors();
        static void calculateMovementData();

        static uint16_t totalHallReadings;
        static uint8_t hallReadingsSinceLastTime;
        static TickType_t lastReadingTime;
        static int cmPerSecond;
        static int distanceSinceLastTime;
    private:

        

};

#endif