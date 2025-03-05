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

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s X \n", argv[0]);
    return 1;
  }

  int xpos = atoi(argv[1]);

  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  robot.SetSpeed(40);
  printf("\n");

  // x
  if (xpos > 0) {
    robot.StartJOG(4, 1, 1, 20.0, 20.0,
                   xpos); // Point in the tool coordinate system
  }

  if (xpos < 0) {
    robot.StartJOG(4, 1, 0, 20.0, 20.0,
                   xpos * (-1)); // Point in the tool coordinate system
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(9999));
  robot.ImmStopJOG();

  return 0;
}
