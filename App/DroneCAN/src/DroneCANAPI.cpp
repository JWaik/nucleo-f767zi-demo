// MotorWrapper.cpp
#include "DroneCAN.h"

// Create a single global instance of the C++ class
static DroneCANNode node;
extern "C" {
void dronecan_start_node_api(const char *interface_name) {
    node.start_node(interface_name);
}
}
