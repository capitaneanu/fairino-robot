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
  // DescPose desc_pos, desc_rt, tcp, flange, etool, t_coord;
  DescPose desc_pos, desc_rt, tcp, flange;
  DescTran coord;
  ForceTorque ft;

  memset(&ft, 0, sizeof(ForceTorque));
  memset(&desc_pos, 0, sizeof(DescPose));
  memset(&desc_rt, 0, sizeof(DescPose));
  memset(&tcp, 0, sizeof(DescPose));
  memset(&flange, 0, sizeof(DescPose));

  int tool = 0; // default = 0
  int user = 0;
  float vel = 50.0;
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

    for (int i = 0; i < 2; i++) {
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

  uint8_t sensor_id = 1;
  uint8_t select[6] = {0, 0, 1, 0, 0, 0};
  float ft_pid[6] = {0.0005, 0.0, 0.0, 0.0, 0.0, 0.0};
  uint8_t adj_sign = 0;
  uint8_t ILC_sign = 2;
  float max_dis = 100.0;
  float max_ang = 0.0;

  // robot.GetActualTCPNum(flag, &tool);
  // robot.GetRobotCurJointsConfig(&config);
  robot.SetSpeed(50);
  printf("\n");

  flag = 1;
  blendT = -1.0;
  ft.fx = -5.0;
  ft.fy = -5.0;
  ft.fz = -5.0;
  float p = 0.00005;
  float force = 1.0;
  float max_threshold[6] = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
  float min_threshold[6] = {-5.0, -5.0, -5.0, -5.0, -5.0, -5.0};

  robot.GetRobotRealTimeState(&rt_data);
  desc_rt.tran.x = rt_data.tl_cur_pos[0];
  desc_rt.tran.y = rt_data.tl_cur_pos[1];
  desc_rt.tran.z = rt_data.tl_cur_pos[2] + zpos;
  desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
  desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
  desc_rt.rpy.rz = rt_data.tl_cur_pos[5];
  robot.WaitMs(1000);

  // robot.FT_Control(flag, sensor_id, select, &ft, ft_pid, adj_sign, ILC_sign,
  //                  max_dis, max_ang);
  // robot.FT_ComplianceStart(p, force);
  // robot.FT_Guard(flag, sensor_id, select, &ft, max_threshold, min_threshold);

  robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
  // robot.WaitMs(100);
  robot.FT_Control(flag, sensor_id, select, &ft, ft_pid, adj_sign, ILC_sign,
                   max_dis, max_ang);
  // robot.FT_GetForceTorqueOrigin(flag, &ft);
  // printf("%f %f %f %f %f %f\n", ft.fx, ft.fy, ft.fz, ft.tx, ft.ty, ft.tz);

  robot.WaitMs(4000);

  // robot.FT_ComplianceStop();
  flag = 0;
  robot.FT_Control(flag, sensor_id, select, &ft, ft_pid, adj_sign, ILC_sign,
                   max_dis, max_ang);
  // robot.FT_Guard(flag, sensor_id, select, &ft, max_threshold, min_threshold);

  return 0;
}
