#ifndef ALGORITHMLINEFOLLOWING_H
#define ALGORITHMLINEFOLLOWING_H

#include <Engine.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>

class AlgorithmLineFollwing
{
    public:
        AlgorithmLineFollwing(Engine& engineLeft, Engine& engineRight);
        int determineSteering();
        int calcPostion(int position);
    private:
        Engine& _enL;
        Engine& _enR;
};

#endif