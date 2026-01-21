#include <Engine.h>

Engine::Engine(int _pin0, int _pin1,int channel0, int channel1)
:_pin0(_pin0), _pin1(_pin1),_channel0(channel0),_channel1(channel1)
{
    int speed = 0;


    pinMode(_pin0, OUTPUT);
    pinMode(_pin1 , OUTPUT);
    
    ledcSetup(channel0, pwmFrequency, pwmResolution);
    ledcAttachPin(_pin0, channel0);

    ledcSetup(channel1, pwmFrequency, pwmResolution);
    ledcAttachPin(_pin1, channel1);
    
    stopEngine();
    setEngineDirection(FORWARD);
}

void Engine::setEngineDirection(int direction)
{
    this->direction = direction;
}

void Engine::setEngineSpeed(int speed)
{   speed = constrain(speed, 0, 255);
    if(this->direction == FORWARD){
        ledcWrite(_channel0, speed);
        ledcWrite(_channel1, 0);
    }
    else if(this->direction == BACKWARD){
 
        ledcWrite(_channel1, speed);
        ledcWrite(_channel0, 0);
    }

}

void Engine::stopEngine()
{
    setEngineSpeed(OFF);
}