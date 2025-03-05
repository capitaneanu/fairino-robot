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
    printf("Usage: %s 0 \n", argv[0]);
    return 1;
  }

  int cpos = atoi(argv[1]);

  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  DescPose desc_pos, tcp, flange;

  memset(&desc_pos, 0, sizeof(DescPose));
  memset(&tcp, 0, sizeof(DescPose));

  int tool = 0; // default = 0 and actual = 3
  int user = 0;
  float vel = 100.0;
  float acc = 50.0;
  float ovl = 50.0;
  float blendT = 0.0;
  float blendR = 0.0;
  uint8_t flag = 0;
  uint8_t search = 0;
  int config = -1; // default = -1 and actual config = 5

  robot.GetActualTCPNum(flag, &tool);
  robot.GetRobotCurJointsConfig(&config);
  robot.SetSpeed(40);
  // printf("\n");

  for (int i = 0; i < 1; i++) {
    robot.GetActualTCPPose(flag, &tcp);
    // printf("GetActualTCPPose:\t\t%f,%f,%f,%f,%f,%f\n\n", tcp.tran.x,
    // tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);

    desc_pos.tran.x = tcp.tran.x; // + 10mm
    desc_pos.tran.y = tcp.tran.y + cpos;
    desc_pos.tran.z = tcp.tran.z;
    desc_pos.rpy.rx = tcp.rpy.rx;
    desc_pos.rpy.ry = tcp.rpy.ry;
    desc_pos.rpy.rz = tcp.rpy.rz;

    robot.MoveCart(&desc_pos, tool, user, vel, acc, ovl, blendT, config);

    robot.WaitMs(100);

    // robot.GetActualTCPPose(flag, &tcp);
    // printf("GetActualTCPPose after:\t\t%f,%f,%f,%f,%f,%f\n", tcp.tran.x,
    // tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
    // robot.GetActualToolFlangePose(flag, &flange);
    // printf("GetActualToolFlangePose after:\t%f,%f,%f,%f,%f,%f\n\n",
    // flange.tran.x, flange.tran.y, flange.tran.z, flange.rpy.rx,
    // flange.rpy.ry, flange.rpy.rz);
  }

  return 0;
}
