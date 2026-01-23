#include <Debug.h>
#include <wifi_config.h>

Debug::Debug() {}

String Debug::getActionDescription(int action) {
  switch(action) {
    case 0b00000: return "RECOVERY";
    case 0b10000: return "ROTATE_LEFT";
    case 0b01000:
    case 0b11000:
    case 0b01100:
    case 0b11001:
    case 0b11100:
    case 0b11101: return "TURN_LEFT";
    case 0b00100:
    case 0b00101:
    case 0b10100:
    case 0b10101:
    case 0b10110:
    case 0b11011: return "MOVE_FORWARD";
    case 0b01001:
    case 0b01010:
    case 0b01011:
    case 0b01101:
    case 0b10001:
    case 0b10010:
    case 0b11010: return "MOVE_BACKWARD";
    case 0b00010:
    case 0b00011:
    case 0b00110:
    case 0b00111:
    case 0b10011:
    case 0b10111: return "TURN_RIGHT";
    case 0b00001: return "ROTATE_RIGHT";
    case 0b01110:
    case 0b01111:
    case 0b11110:
    case 0b11111: return "CROSSROAD";
    default: return "Unknown Action - Recovery";
  }
}



void Debug::printSensorAndAction(int readings, int lastAction) {
  // Parse sensor readings
  int farLeft = (readings >> 4) & 1;
  int left = (readings >> 3) & 1;
  int middle = (readings >> 2) & 1;
  int right = (readings >> 1) & 1;
  int farRight = readings & 1;
  
  // Get action description
  String actionDesc = getActionDescription(lastAction);
  
  // Print debug info with sensor details and action
  DebugSerial.print("[");
  DebugSerial.print(farLeft);
  DebugSerial.print(left);
  DebugSerial.print(middle);
  DebugSerial.print(right);
  DebugSerial.print(farRight);
  DebugSerial.print("] -> ");
  DebugSerial.println(actionDesc);
  
  static int printCounter = 0;
  if (printCounter++ % 10 != 0) {
    return;
  }/**/
  
}