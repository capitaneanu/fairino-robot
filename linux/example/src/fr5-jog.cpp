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
  if (argc != 4) {
    printf("Usage: %s X Y Z \n", argv[0]);
    return 1;
  }

  int xpos = atoi(argv[1]);
  int ypos = atoi(argv[2]);
  int zpos = atoi(argv[3]);

  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  DescPose desc_pos, tcp, flange, etool, t_coord;
  DescTran coord;

  memset(&desc_pos, 0, sizeof(DescPose));
  memset(&tcp, 0, sizeof(DescPose));
  memset(&etool, 0, sizeof(DescPose));
  memset(&t_coord, 0, sizeof(DescPose));

  int tool = 0; // default = 0
  int user = 0;
  float vel = 100.0;
  float acc = 50.0;
  float ovl = 50.0;
  float blendT = 0.0;
  float blendR = 0.0;
  uint8_t flag = 0;
  uint8_t search = 0;
  int config = -1; // default = -1

  robot.GetActualTCPNum(flag, &tool);
  robot.GetRobotCurJointsConfig(&config);

  robot.SetSpeed(50);
  printf("\n");

  // robot.GetActualTCPPose(flag, &tcp);
  // printf("GetActualTCPPose after:\t\t%f,%f,%f,%f,%f,%f\n", tcp.tran.x,
  // tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
  // robot.GetActualToolFlangePose(flag, &flange);
  // printf("GetActualToolFlangePose after:\t%f,%f,%f,%f,%f,%f\n\n",
  // flange.tran.x, flange.tran.y, flange.tran.z, flange.rpy.rx, flange.rpy.ry,
  // flange.rpy.rz);

  int xp = xpos;
  robot.StartJOG(4, 1, xpos >= 0 ? 1 : 0, 80.0, 80.0, xpos >= 0 ? xp : -xp);
  printf("Starjog X command success.\n");
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  robot.StopJOG(5);

  int yp = ypos;
  robot.StartJOG(4, 2, ypos >= 0 ? 1 : 0, 80.0, 80.0, ypos >= 0 ? yp : -yp);
  printf("Starjog Y command success.\n");
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  robot.StopJOG(5);

  int zp = zpos;
  robot.StartJOG(4, 3, zpos >= 0 ? 1 : 0, 60.0, 60.0, zpos >= 0 ? zp : -zp);
  printf("Starjog Z command success.\n");
  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  robot.StopJOG(5);

  printf("\n");
  // robot.GetActualTCPPose(flag, &tcp);
  // printf("GetActualTCPPose after:\t\t%f,%f,%f,%f,%f,%f\n", tcp.tran.x,
  // tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);

  return 0;
}
