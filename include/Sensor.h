#ifndef SENSOR_H
#define SENSOR_H
#include <globals.h>

class Sensor
{
    public:
        Sensor();
        void readIRSensors();
        static void handleHallSensors();
    private:
        static uint16_t totalHallReadings;

};

#endif