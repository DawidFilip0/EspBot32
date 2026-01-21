#ifndef ENGINE_H
#define ENGINE_H

#include <globals.h>

class Engine 
{
    public:
        Engine(int pwmChannel0, int pwmChannel1,int channel0, int channel1);
        void setEngineDirection(int direction);
        void setEngineSpeed(int speed);
        void stopEngine();
    private:
        int _channel0;
        int _channel1;
        int _pin0;
        int _pin1;
        int direction;
};

#endif