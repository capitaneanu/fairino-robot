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
  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  uint8_t flag = 0;
  DescPose tcp;
  memset(&tcp, 0, sizeof(DescPose));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  robot.ImmStopJOG();

  // printf("\n");
  robot.GetActualTCPPose(flag, &tcp);
  printf("GetActualTCPPose after:\t\t%f,%f,%f,%f,%f,%f\n", tcp.tran.x,
         tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
  // robot.GetActualToolFlangePose(flag, &flange);
  // printf("GetActualToolFlangePose after:\t%f,%f,%f,%f,%f,%f\n\n",
  // flange.tran.x, flange.tran.y, flange.tran.z, flange.rpy.rx, flange.rpy.ry,
  // flange.rpy.rz);

  return 0;
}
