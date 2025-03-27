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

  ROBOT_STATE_PKG rt_data = {};
  DescPose desc_pos, desc_rt, tcp, flange, etool, t_coord;
  DescTran coord;

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

  if (argc != 4) {
    printf("Usage: %s X Y Z \n", argv[0]);
    printf("\n");

    for (int i = 0; i < 4; i++) {
      robot.GetRobotRealTimeState(&rt_data);
      printf(
          "GetRobotRealTimeState :\t\tX %f, Y %f, Z %f, RX %f, RY %f, RZ %f\n",
          rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
          rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    return 1;
  }

  int xpos = atoi(argv[1]);
  int ypos = atoi(argv[2]);
  int zpos = atoi(argv[3]);

  //   robot.SetLoadWeight(0.5);
  //   coord.x = 0.0;
  //   coord.y = 0.0;
  //   coord.z = 0.0;
  //   robot.SetLoadCoord(&coord);
  //   int id = 10;
  //   t_coord.tran.x = 1.0;
  //   t_coord.tran.y = 2.0;
  //   t_coord.tran.z = 3.0;
  //   t_coord.rpy.rx = 4.0;
  //   t_coord.rpy.ry = 5.0;
  //   t_coord.rpy.rz = 6.0;
  //   int type = 0;
  //   int install = 0;
  //   robot.SetToolCoord(id, &t_coord, type, install, 2, 2);
  //   robot.SetToolList(id, &t_coord, type, install, 2);

  robot.GetActualTCPNum(flag, &tool);
  robot.GetRobotCurJointsConfig(&config);

  robot.SetSpeed(50);
  printf("\n");

  //   robot.GetActualTCPPose(flag, &tcp);
  //   robot.GetActualToolFlangePose(flag, &tcp);
  //   printf("GetActualTCPPose after:\t\t%f,%f,%f,%f,%f,%f\n", tcp.tran.x,
  //          tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
  // desc_pos.tran.x = xpos;
  // desc_pos.tran.y = ypos;
  // desc_pos.tran.z = zpos;
  // desc_pos.tran.x = tcp.tran.x + xpos;
  // desc_pos.tran.y = tcp.tran.y + ypos;
  // desc_pos.tran.z = tcp.tran.z + zpos;
  // desc_pos.rpy.rx = tcp.rpy.rx;
  // desc_pos.rpy.ry = tcp.rpy.ry;
  // desc_pos.rpy.rz = tcp.rpy.rz;

  // robot.MoveCart(&desc_pos, tool, user, vel, acc, ovl, blendT, config);
  // robot.WaitMs(100);

  robot.GetRobotRealTimeState(&rt_data);
  // printf("GetRobotRealTimeState :\t\tX %f, Y %f, Z %f, RX %f, RY %f, RZ
  // %f\n",
  //        rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
  //        rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4],
  //        rt_data.tl_cur_pos[5]);
  // desc_rt.tran.x = xpos;
  // desc_rt.tran.y = ypos;
  // desc_rt.tran.z = zpos;
  desc_rt.tran.x = rt_data.tl_cur_pos[0] + xpos;
  desc_rt.tran.y = rt_data.tl_cur_pos[1] + ypos;
  // desc_rt.tran.z = rt_data.tl_cur_pos[2] + zpos;
  desc_rt.tran.z = rt_data.tl_cur_pos[2];
  desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
  desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
  desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

  robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
  // robot.WaitMs(100);

  robot.WaitMs(1000);
  // robot.GetActualTCPPose(flag, &tcp);
  // robot.GetActualToolFlangePose(flag, &flange);
  robot.GetRobotRealTimeState(&rt_data);
  // printf("GetActualTCPPose after:\t\t%f,%f,%f,%f,%f,%f\n", tcp.tran.x,
  //        tcp.tran.y, tcp.tran.z, tcp.rpy.rx, tcp.rpy.ry, tcp.rpy.rz);
  // printf("GetActualToolFlangePose after:\t%f,%f,%f,%f,%f,%f\n\n",
  //        flange.tran.x,
  //        flange.tran.y, flange.tran.z, flange.rpy.rx, flange.rpy.ry,
  //        flange.rpy.rz);
  printf("GetRobotRealTimeState :\t\tX %f, Y %f, Z %f, RX %f, RY %f, RZ %f\n",
         rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
         rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

  return 0;
}
