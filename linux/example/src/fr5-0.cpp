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

  JointPos j, j1, j2, j3, j4, start_joint_pose;
  DescPose desc_pos, desc_pos1, desc_pos2, desc_pos3, desc_pos4, offset_pos,
      offset_pos1, offset_pos2;
  ExaxisPos epos;
  SpiralParam sp;

  memset(&start_joint_pose, 0, sizeof(JointPos));
  memset(&j, 0, sizeof(JointPos));
  memset(&j1, 0, sizeof(JointPos));
  memset(&j2, 0, sizeof(JointPos));
  memset(&j3, 0, sizeof(JointPos));
  memset(&j4, 0, sizeof(JointPos));
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

  j1.jPos[0] = -78.011;
  j1.jPos[1] = -93.495;
  j1.jPos[2] = -110.064;
  j1.jPos[3] = -60.077;
  j1.jPos[4] = 65.601;
  j1.jPos[5] = 21.277;

  // desc_pos = {14.013096 + 50, -518.617126, 339.769684, -164.425659,
  // -20.019272, 166.569366};

  // j2.jPos[0] = -34.08;
  // j2.jPos[1] = -93.504;
  // j2.jPos[2] = -110.073;
  // j2.jPos[3] = -66.142;
  // j2.jPos[4] = 91.713;
  // j2.jPos[5] = 21.167;

  // sp.circle_num = 5;
  // sp.circle_angle = 5.0;
  // sp.rad_init = 50.0;
  // sp.rad_add = 10.0;
  // sp.rotaxis_add = 10.0;
  // sp.rot_direction = 0;

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

  // for (int i = 0; i < 6; i++)	{ printf("J(%d) %f\t", i + 1,
  // j.jPos[i]); } printf("\n\n");

  // int retval = robot.GetInverseKinRef(0, &desc_pos, &j1, &start_joint_pose);
  // printf("GetInverseKinRef retval is: %d \n", retval);
  // printf("joint is: %f, %f, %f,%f, %f, %f\n", start_joint_pose.jPos[0],
  // start_joint_pose.jPos[1], start_joint_pose.jPos[2],
  // start_joint_pose.jPos[3], start_joint_pose.jPos[4],
  // start_joint_pose.jPos[5]);

  int ret0 = robot.GetForwardKin(
      &j1, &desc_pos); // The forward kinematic interface can be used to solve
                       // Cartesian space coordinates with only joint positions
  printf(
      "ForwardKinematics is:  x %f\t  y %f\t  z %f\t rx %f\t ry %f\t rz %f \n",
      desc_pos.tran.x, desc_pos.tran.y, desc_pos.tran.z, desc_pos.rpy.rx,
      desc_pos.rpy.ry, desc_pos.rpy.rz);
  printf("\n");

  int ret = robot.GetInverseKin(0, &desc_pos, -1, &j4);
  printf(
      "JointPositions are  : J1 %f\t J2 %f\t J3 %f\t J4 %f\t J5 %f\t J6 %f\t "
      "\n",
      j1.jPos[0], j1.jPos[1], j1.jPos[2], j1.jPos[3], j1.jPos[4], j1.jPos[5]);
  printf(
      "GetInverseKin result: J1 %f\t J2 %f\t J3 %f\t J4 %f\t J5 %f\t J6 %f\t "
      "\n",
      j4.jPos[0], j4.jPos[1], j4.jPos[2], j4.jPos[3], j4.jPos[4], j4.jPos[5]);
  printf("\n");

  // if (ret == 0)
  // {
  // int err0 = robot.MoveJ(&j, &desc_pos, tool, user, vel, acc, ovl, &epos,
  // blendT, flag, &offset_pos1); printf("movej errcode:%d \n", err0); int err1
  // = robot.MoveJ(&j1, &desc_pos1, tool, user, vel, acc, ovl, &epos, blendT,
  // flag, &offset_pos); printf("movej errcode:%d\n", err1); int err2 =
  // robot.MoveL(&j2, &desc_pos2, tool, user, vel, acc, ovl, blendR, &epos,
  // search, flag, &offset_pos); printf("movel errcode:%d\n", err2); int err3 =
  // robot.MoveC(&j3, &desc_pos3, tool, user, vel, acc, &epos, flag,
  // &offset_pos, &j4, &desc_pos4, tool, user, vel, acc, &epos, flag,
  // &offset_pos, ovl, blendR); printf("movec errcode:%d\n", err3); int err4 =
  // robot.MoveJ(&j2, &desc_pos2, tool, user, vel, acc, ovl, &epos, blendT,
  // flag, &offset_pos); printf("movej errcode:%d\n", err4); int err5; for (int
  // i = 0; i < 8; i++)
  // {
  // err5 = robot.Circle(&j3, &desc_pos3, tool, user, vel, acc, &epos, &j4,
  // &desc_pos4, tool, user, vel, acc, &epos, ovl, flag, &offset_pos);
  // printf("circle%d errcode:%d\n", i + 1, err5);
  // }
  // int err2 = robot.NewSpiral(&j, &desc_pos, tool, user, vel, acc, &epos, ovl,
  // flag, &offset_pos2, sp); printf("newspiral errcode:%d\n", err2); int retval
  // = robot.StopMotion(); printf("StopMotion retval is: %d\n", retval); retval
  // = robot.PauseMotion(); printf("PauseMotion retval is: %d\n", retval);
  // retval = robot.ResumeMotion();
  // printf("ResumeMotion retval is: %d\n", retval);
  // }
  // else
  // {
  // 	printf("GetForwardKin errcode:%d\n", ret);
  // }

  printf("\n");

  return 0;
}
