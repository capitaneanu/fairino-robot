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

  int company = 6;
  int device = 1;
  int softversion = 0;
  int bus = 2;
  int index = 2;
  int act = 0;
  int max_time = 30000;
  uint8_t block = 0;
  uint16_t fault = 0;
  uint8_t status = 0;
  uint16_t active_status = 0;
  uint8_t current_pos = 0;
  int8_t current = 0;
  int voltage = 0;
  int temp = 0;
  int8_t speed = 0;
  int8_t gstatus = 1;

  JointPos j, j1, j2, j3, j4, pj1, pj2, pj3, pj4;
  DescPose desc_pos, desc_pos1, desc_pos2, desc_pos3, desc_pos4, offset_pos,
      offset_pos1, offset_pos2;
  ExaxisPos epos;
  SpiralParam sp;

  memset(&j, 0, sizeof(JointPos));

  memset(&j1, 0, sizeof(JointPos));
  memset(&j2, 0, sizeof(JointPos));
  memset(&j3, 0, sizeof(JointPos));
  memset(&j4, 0, sizeof(JointPos));

  memset(&pj1, 0, sizeof(JointPos));
  memset(&pj2, 0, sizeof(JointPos));
  memset(&pj3, 0, sizeof(JointPos));
  memset(&pj4, 0, sizeof(JointPos));

  memset(&desc_pos, 0, sizeof(DescPose));
  memset(&desc_pos1, 0, sizeof(DescPose));
  memset(&desc_pos2, 0, sizeof(DescPose));
  memset(&desc_pos3, 0, sizeof(DescPose));
  memset(&desc_pos4, 0, sizeof(DescPose));

  memset(&offset_pos, 0, sizeof(DescPose));
  memset(&offset_pos1, 0, sizeof(DescPose));
  memset(&offset_pos2, 0, sizeof(DescPose));

  memset(&epos, 0, sizeof(ExaxisPos));
  memset(&sp, 0, sizeof(SpiralParam));

  j = {0.0, -90.0, -90.0, -90.0, 90.0, 0.0};

  pj1 = {-93.877197, -103.930008, -141.126892,
         -25.205683, 90.914146,   -42.579746};
  pj2 = {-93.849998, -112.919006, -142.742432,
         -13.090917, 90.698341,   -42.750957};
  pj3 = {-53.573254, -102.354721, -144.803497,
         -21.227325, 87.073288,   -3.555872};
  pj4 = {-52.531616, -107.041206, -145.414597,
         -18.076752, 86.398224,   -3.580238};

  j1.jPos[0] = -78.011;
  j1.jPos[1] = -93.495;
  j1.jPos[2] = -110.064;
  j1.jPos[3] = -60.077;
  j1.jPos[4] = 65.601;
  j1.jPos[5] = 21.277;

  int ret = 0;
  int err0 = 0;
  int tool = 0;
  int user = 0;
  float vel = 100.0;
  float acc = 100.0;
  float ovl = 100.0;
  float blendT = 0.0;
  float blendR = 0.0;
  uint8_t flag = 2;
  uint8_t search = 0;

  robot.SetSpeed(40);
  printf("\n");

  // The forward kinematic interface can be used to solve Cartesian space
  // coordinates with only joint positions
  ret = robot.GetForwardKin(&pj1, &desc_pos1);
  ret = robot.GetForwardKin(&pj2, &desc_pos2);
  ret = robot.GetForwardKin(&pj3, &desc_pos3);
  ret = robot.GetForwardKin(&pj4, &desc_pos4);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  err0 = robot.MoveJ(&pj1, &desc_pos1, tool, user, vel, acc, ovl, &epos, blendT,
                     flag, &offset_pos);
  robot.MoveGripper(index, 0, 60, 40, max_time, block, 0, 0, 0, 0);

  for (int i = 0; i < 4; i++) {

    err0 = robot.MoveJ(&pj2, &desc_pos2, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);
    robot.MoveGripper(index, 60, 60, 40, max_time, block, 0, 0, 0, 0);

    err0 = robot.MoveJ(&pj1, &desc_pos1, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);
    err0 = robot.MoveJ(&pj3, &desc_pos3, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);
    err0 = robot.MoveJ(&pj4, &desc_pos4, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);

    robot.MoveGripper(index, 0, 60, 40, max_time, block, 0, 0, 0, 0);
    robot.MoveGripper(index, 60, 60, 40, max_time, block, 0, 0, 0, 0);

    err0 = robot.MoveJ(&pj3, &desc_pos3, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);
    err0 = robot.MoveJ(&pj1, &desc_pos1, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);
    err0 = robot.MoveJ(&pj2, &desc_pos2, tool, user, vel, acc, ovl, &epos,
                       blendT, flag, &offset_pos);
    robot.MoveGripper(index, 0, 60, 40, max_time, block, 0, 0, 0, 0);
  }

  err0 = robot.MoveJ(&pj1, &desc_pos1, tool, user, vel, acc, ovl, &epos, blendT,
                     flag, &offset_pos);
  robot.MoveGripper(index, 100, 60, 40, max_time, block, 0, 0, 0, 0);
  printf("\n");

  return 0;
}
