#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

class Debug
{
    public:
        Debug();
        void printSensorAndAction(int readings, int lastAction);
    private:
        String getActionDescription(int action);
};

#endif