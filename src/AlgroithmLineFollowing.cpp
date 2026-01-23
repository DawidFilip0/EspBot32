#include <AlgorithmLineFollowing.h>
#include "globals.h"


AlgorithmLineFollwing::AlgorithmLineFollwing(Engine& engineLeft, Engine& engineRight)
:_enL(engineLeft), _enR(engineRight)
{}







int AlgorithmLineFollwing::determineSteering() {

std::array<IRreading,50> readingsArr;
  int head = 0;
  IRreadingBuffer.copyBuffer(readingsArr,head);
  uint8_t sensorReadings = readingsArr[head].readings;

  // // Extract individual sensor bits (5 bits: bit4=farLeft, bit3=left, bit2=middle, bit1=right, bit0=farRight)
  int farLeft = (sensorReadings >> 4) & 1;
  int left = (sensorReadings >> 3) & 1;
  int middle = (sensorReadings >> 2) & 1;
  int right = (sensorReadings >> 1) & 1;
  int farRight = sensorReadings & 1;

  // // Base forward speed
  int baseSpeed = 220;
  int leftSpeed = baseSpeed;
  int rightSpeed = baseSpeed;

  int lastRotationDirection = 0;
  int lostLineCounter = 0;

  // // Determine correction based on sensor pattern
  if (middle == 1) {
    // Line found - reset lost counter
    lostLineCounter = 0;
    
  //   // Middle sensor on the line - move forward
    if (left == 0 && right == 0) {
      // Perfect alignment - go straight
      _enL.setEngineDirection(FORWARD);
      _enR.setEngineDirection(FORWARD);
      _enL.setEngineSpeed(baseSpeed);
      _enR.setEngineSpeed(baseSpeed);
    } 
    else if (left == 1 && right == 0) {
      // Line drifting left - gentle right correction
      lastRotationDirection = 1;  // Remember we're rotating left
      if (farLeft == 1) {
        // Line far left - stronger correction
        leftSpeed = baseSpeed - 40;
        rightSpeed = baseSpeed + 40;
      } else {
        // Line slightly left - gentle correction
        leftSpeed = baseSpeed - 20;
        rightSpeed = baseSpeed + 20;
      }
      _enL.setEngineDirection(FORWARD);
      _enR.setEngineDirection(FORWARD);
      _enL.setEngineSpeed(leftSpeed);
      _enR.setEngineSpeed(rightSpeed);
    }
    else if (right == 1 && left == 0) {
      // Line drifting right - gentle left correction
      lastRotationDirection = -1;  // Remember we're rotating right
      if (farRight == 1) {
        // Line far right - stronger correction
        leftSpeed = baseSpeed + 40;
        rightSpeed = baseSpeed - 40;
      } else {
        // Line slightly right - gentle correction
        leftSpeed = baseSpeed + 20;
        rightSpeed = baseSpeed - 20;
      }
      _enL.setEngineDirection(FORWARD);
      _enR.setEngineDirection(FORWARD);
      _enL.setEngineSpeed(leftSpeed);
      _enR.setEngineSpeed(rightSpeed);
    }
    else if (left == 1 && right == 1) {
      // Both left and right - sharp turn, slow forward
      _enL_enL.setEngineDirection(FORWARD);
      _enR.setEngineDirection(FORWARD);
      _enL.setEngineSpeed(leftSpeed);
      _enR.setEngineSpeed(rightSpeed);
    }
    else if (left == 1 && right == 1) {
      // Both left and right - sharp turn, slow forward
      _enL.setEngineDirection(FORWARD);
      _enR.setEngineDirection(FORWARD);
      _enL.setEngineSpeed(baseSpeed-20);
      _enR.setEngineSpeed(baseSpeed -20);
    }
  } 
  else if (middle == 0) {
    // Middle sensor not on line - search for line
    if (left == 1 || farLeft == 1) {
      // Only left sensors detect line - rotate left
      lostLineCounter = 0;  // Found something, reset counter
      lastRotationDirection = 1;
      _enL.setEngineDirection(BACKWARD);
      _enR.setEngineDirection(FORWARD);
      if (farLeft == 1) {
        // Far left - strong rotation
        _enL.setEngineSpeed(leftSpeed);
        _enR.setEngineSpeed(rightSpeed);
      } else {
        // Near left - gentle rotation
        _enL.setEngineSpeed(110);
        _enR.setEngineSpeed(125);
      }
    }
    else if (right == 1 || farRight == 1) {
      // Only right sensors detect line - rotate right
      lostLineCounter = 0;  // Found something, reset counter
      lastRotationDirection = -1;
      _enR.setEngineDirection(BACKWARD);
      _enL.setEngineDirection(FORWARD);
      if (farRight == 1) {
        // Far right - strong rotation
        _enR.setEngineSpeed(110);
        _enL.setEngineSpeed(130);
      } else {
        // Near right - gentle rotation
        _enR.setEngineSpeed(110);
        _enL.setEngineSpeed(130);
      }
    }
    else {
      // No line detected - recovery mode
      lostLineCounter++;
      
      if (lostLineCounter < 3) {
        // Just lost line - try rotating in the direction we were going
        if (lastRotationDirection == 1) {
          // Keep rotating left
          _enL.setEngineDirection(BACKWARD);
          _enR.setEngineDirection(FORWARD);
          _enL.setEngineSpeed(110);
          _enR.setEngineSpeed(130);
        } else if (lastRotationDirection == -1) {
          // Keep rotating right
          _enR.setEngineDirection(BACKWARD);
          _enL.setEngineDirection(FORWARD);
          _enL.setEngineSpeed(110);
          _enR.setEngineSpeed(130);
        } else {
          // No previous direction - rotate left by default
          lastRotationDirection = 1;
          _enL.setEngineDirection(BACKWARD);
          _enR.setEngineDirection(FORWARD);
           _enL.setEngineSpeed(110);
          _enR.setEngineSpeed(130);
        }
      }
      else if (lostLineCounter < 6) {
        // Still lost after 3 frames - go backward to recover
          _enL.setEngineDirection(BACKWARD);
          _enR.setEngineDirection(BACKWARD);
          _enL.setEngineSpeed(120);
          _enR.setEngineSpeed(120);
        Serial.println("BACKING UP - searching for line");
      }
      else if (lostLineCounter < 10) {
        // After 6+ frames lost - rotate opposite direction
        if (lastRotationDirection == 1) {
          // Try rotating right instead
          _enR.setEngineDirection(BACKWARD);
          _enL.setEngineDirection(FORWARD);
          _enR.setEngineSpeed(90);
          _enL.setEngineSpeed(130);
        } else {
          // Try rotating left instead
          _enL.setEngineDirection(BACKWARD);
          _enR.setEngineDirection(FORWARD);
          _enL.setEngineSpeed(90);
          _enR.setEngineSpeed(130);
        }
      }
      else {
        // Completely lost - back up
          _enL.setEngineDirection(BACKWARD);
          _enR.setEngineDirection(BACKWARD);
          _enL.setEngineSpeed(120);
          _enR.setEngineSpeed(120);
        Serial.println("COMPLETELY LOST - backing up");
      }
    }
  }


IRreading reading;
int position = 0;
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


