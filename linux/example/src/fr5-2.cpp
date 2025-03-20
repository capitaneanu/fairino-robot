#include "libfairino/robot.h"
// #include "libfairino/robot_types.h"
#include <stdio.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>

#include "libfairino/robot_error.h"

using namespace std;

int main(void) {
  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  int retval = 0;
  int index = 2;
  int max_time = 30000;
  uint8_t block = 0;
  uint16_t fault = 0;
  uint8_t status = 0;
  uint16_t active_status = 0;
  uint8_t current_pos = 0;

  retval = robot.MoveGripper(index, 0, 50, 100, max_time, block, 0, 0, 0, 0);
  printf("MoveGripper retval is: %d\n", retval);

  retval = robot.MoveGripper(index, 80, 50, 100, max_time, block, 0, 0, 0, 0);
  printf("MoveGripper retval is: %d\n", retval);

  robot.WaitMs(1000);

  status = 0;
  robot.GetGripperMotionDone(&fault, &status);
  printf("motion status:%u,%u\n", fault, status);

  robot.GetGripperCurPosition(&fault, &current_pos);
  printf("fault is:%u, current position is: %u\n", fault, current_pos);

  robot.WaitMs(1000);

  robot.GetGripperCurPosition(&fault, &current_pos);
  printf("fault is:%u, current position is: %u\n", fault, current_pos);

  status = 1;
  robot.GetGripperMotionDone(&fault, &status);
  printf("motion status:%u,%u\n", fault, status);

  return 0;
}
