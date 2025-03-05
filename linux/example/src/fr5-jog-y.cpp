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
    printf("Usage: %s Y \n", argv[0]);
    return 1;
  }

  int ypos = atoi(argv[1]);

  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  robot.SetSpeed(40);
  printf("\n");

  // y
  if (ypos > 0) {
    robot.StartJOG(4, 2, 1, 20.0, 20.0, ypos);
  }

  if (ypos < 0) {
    robot.StartJOG(4, 2, 0, 20.0, 20.0, ypos * (-1));
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(9999));
  robot.ImmStopJOG();

  return 0;
}
