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
  // if (argc != 2)
  // {
  // printf("Usage: %s 0 \n", argv[0]);
  // return 1;
  // }

  // int cpos = atoi(argv[1]);

  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  JointPos j1, j2, j3, j4;
  DescPose desc_pos1, desc_pos2, desc_pos3, desc_pos4, offset_pos, offset_pos1,
      offset_pos2, tcp;
  ExaxisPos epos;
  SpiralParam sp;
  JointPos start_joint_pose;
  int semn = 1;

  memset(&start_joint_pose, 0, sizeof(JointPos));

  memset(&j1, 0, sizeof(JointPos));
  memset(&j2, 0, sizeof(JointPos));
  memset(&j3, 0, sizeof(JointPos));
  memset(&j4, 0, sizeof(JointPos));

  memset(&desc_pos1, 0, sizeof(DescPose));
  memset(&desc_pos2, 0, sizeof(DescPose));
  memset(&desc_pos3, 0, sizeof(DescPose));
  memset(&desc_pos4, 0, sizeof(DescPose));

  memset(&tcp, 0, sizeof(DescPose));

  memset(&offset_pos, 0, sizeof(DescPose));
  memset(&offset_pos1, 0, sizeof(DescPose));
  memset(&offset_pos2, 0, sizeof(DescPose));

  memset(&epos, 0, sizeof(ExaxisPos));

  memset(&sp, 0, sizeof(SpiralParam));

  int tool = 0;
  int user = 0;
  float vel = 100.0;
  float acc = 50.0;
  float ovl = 50.0;
  float blendT = 0.0;
  float blendR = 0.0;
  uint8_t flag = 2;
  uint8_t search = 0;
  int config = -1;

  robot.SetSpeed(40);
  printf("\n");

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      semn = 1;

      robot.GetActualTCPPose(flag, &tcp);
      // printf("tcp pose:%f,%f,%f,%f,%f,%f\n", tcp.tran.x, tcp.tran.y,
      // tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
      desc_pos1.tran.x = tcp.tran.x + 200 * semn; // + 10mm
      desc_pos1.tran.y = tcp.tran.y;
      desc_pos1.tran.z = tcp.tran.z;
      desc_pos1.rpy.rx = tcp.rpy.rx;
      desc_pos1.rpy.ry = tcp.rpy.ry;
      desc_pos1.rpy.rz = tcp.rpy.rz;
      robot.MoveCart(&desc_pos1, tool, user, vel, acc, ovl, blendT, config);

      robot.WaitMs(100);

      robot.GetActualTCPPose(flag, &tcp);
      // printf("tcp pose:%f,%f,%f,%f,%f,%f\n", tcp.tran.x, tcp.tran.y,
      // tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
      desc_pos1.tran.x = tcp.tran.x; // + 10mm
      desc_pos1.tran.y = tcp.tran.y - 25;
      desc_pos1.tran.z = tcp.tran.z;
      desc_pos1.rpy.rx = tcp.rpy.rx;
      desc_pos1.rpy.ry = tcp.rpy.ry;
      desc_pos1.rpy.rz = tcp.rpy.rz;
      robot.MoveCart(&desc_pos1, tool, user, vel, acc, ovl, blendT, config);
      robot.WaitMs(100);

      semn = -1;

      robot.GetActualTCPPose(flag, &tcp);
      // printf("tcp pose:%f,%f,%f,%f,%f,%f\n", tcp.tran.x, tcp.tran.y,
      // tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
      desc_pos1.tran.x = tcp.tran.x + 200 * semn; // + 10mm
      desc_pos1.tran.y = tcp.tran.y;
      desc_pos1.tran.z = tcp.tran.z;
      desc_pos1.rpy.rx = tcp.rpy.rx;
      desc_pos1.rpy.ry = tcp.rpy.ry;
      desc_pos1.rpy.rz = tcp.rpy.rz;
      robot.MoveCart(&desc_pos1, tool, user, vel, acc, ovl, blendT, config);
      robot.WaitMs(100);

      robot.GetActualTCPPose(flag, &tcp);
      // printf("tcp pose:%f,%f,%f,%f,%f,%f\n", tcp.tran.x, tcp.tran.y,
      // tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
      desc_pos1.tran.x = tcp.tran.x; // + 10mm
      desc_pos1.tran.y = tcp.tran.y - 25;
      desc_pos1.tran.z = tcp.tran.z;
      desc_pos1.rpy.rx = tcp.rpy.rx;
      desc_pos1.rpy.ry = tcp.rpy.ry;
      desc_pos1.rpy.rz = tcp.rpy.rz;
      robot.MoveCart(&desc_pos1, tool, user, vel, acc, ovl, blendT, config);

      robot.WaitMs(100);
    }

    robot.GetActualTCPPose(flag, &tcp);
    // printf("tcp pose:%f,%f,%f,%f,%f,%f\n", tcp.tran.x, tcp.tran.y,
    // tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
    desc_pos1.tran.x = tcp.tran.x; // + 10mm
    desc_pos1.tran.y = tcp.tran.y + 200;
    desc_pos1.tran.z = tcp.tran.z;
    desc_pos1.rpy.rx = tcp.rpy.rx;
    desc_pos1.rpy.ry = tcp.rpy.ry;
    desc_pos1.rpy.rz = tcp.rpy.rz;
    robot.MoveCart(&desc_pos1, tool, user, vel, acc, ovl, blendT, config);

    robot.WaitMs(100);

    robot.GetActualTCPPose(flag, &tcp);
    // printf("tcp pose:%f,%f,%f,%f,%f,%f\n", tcp.tran.x, tcp.tran.y,
    // tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
    desc_pos1.tran.x = tcp.tran.x; // + 10mm
    desc_pos1.tran.y = tcp.tran.y;
    desc_pos1.tran.z = tcp.tran.z - 20;
    desc_pos1.rpy.rx = tcp.rpy.rx;
    desc_pos1.rpy.ry = tcp.rpy.ry;
    desc_pos1.rpy.rz = tcp.rpy.rz;
    robot.MoveCart(&desc_pos1, tool, user, vel, acc, ovl, blendT, config);

    robot.WaitMs(100);
  }

  return 0;
}
