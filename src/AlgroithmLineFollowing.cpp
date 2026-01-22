#include <AlgorithmLineFollowing.h>
#include "globals.h"


AlgorithmLineFollwing::AlgorithmLineFollwing(Engine& engineLeft, Engine& engineRight)
:_enL(engineLeft), _enR(engineRight)
{}

int AlgorithmLineFollwing::determineSteering() {

IRreading reading;
int position = 0;
// if(xQueueReceive(IRReadingQueue, &reading, pdMS_TO_TICKS(500)) == pdPASS){
//   position = calcPostion(reading.readings);
// }

// IRreadingBuffer.

int steering = position * kp;
return steering;
}



int AlgorithmLineFollwing::calcPostion(int reading){
    int s0 = (reading >> 4) & 1;  
    int s1 = (reading >> 3) & 1;
    int s2 = (reading >> 2) & 1;  
    int s3 = (reading >> 1) & 1;
    int s4 = (reading >> 0) & 1;  
    int activeBits = s0 + s1 + s2 + s3 + s4;

    int position = 0;

    if (activeBits > 0) {
      position = ((-2 * s0) + (-1 * s1) + (0 * s2) + (1 * s3) + (2 * s4)) / activeBits;
    } else {

    }

    return position;


}