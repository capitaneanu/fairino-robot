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
    printf("Usage: %s Z \n", argv[0]);
    return 1;
  }

  int zpos = atoi(argv[1]);

  FRRobot robot;             // Instantiate the robot object
  robot.RPC("192.168.58.2"); // Establish a communication connection with the
                             // robot controller

  robot.SetSpeed(40);
  printf("\n");

  ForceTorque ft;
  memset(&ft, 0, sizeof(ForceTorque));

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

  uint8_t sensor_id = 1;
  uint8_t select[6] = {0, 0, 1, 0, 0, 0};
  float ft_pid[6] = {0.0005, 0.0, 0.0, 0.0, 0.0, 0.0};
  uint8_t adj_sign = 0;
  uint8_t ILC_sign = 2;
  float max_dis = 100.0;
  float max_ang = 0.0;

  flag = 1;
  blendT = -1.0;
  // ft.fx = -2.0;
  // ft.fy = -2.0;
  // ft.fz = -2.0;
  float p = 0.00005;
  float force = 1.0;
  float max_threshold[6] = {4.0, 4.0, 4.0, 4.0, 4.0, 4.0};
  float min_threshold[6] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0};

  // robot.FT_Control(flag, sensor_id, select, &ft, ft_pid, adj_sign, ILC_sign,
  //                  max_dis, max_ang);
  // robot.FT_ComplianceStart(p, force);
  robot.FT_Guard(flag, sensor_id, select, &ft, max_threshold, min_threshold);

  // z
  if (zpos > 0) {
    robot.StartJOG(4, 3, 1, 20.0, 20.0, zpos);
  }

  if (zpos < 0) {
    robot.StartJOG(4, 3, 0, 20.0, 20.0, zpos * (-1));
  }

  // robot.FT_Control(flag, sensor_id, select, &ft, ft_pid, adj_sign, ILC_sign,
  //                  max_dis, max_ang);

  std::this_thread::sleep_for(std::chrono::milliseconds(3999));
  // robot.ImmStopJOG();

  // robot.FT_ComplianceStop();
  robot.FT_GetForceTorqueOrigin(flag, &ft);
  printf("%f %f %f %f %f %f\n", ft.fx, ft.fy, ft.fz, ft.tx, ft.ty, ft.tz);
  flag = 0;
  // robot.FT_Control(flag, sensor_id, select, &ft, ft_pid, adj_sign, ILC_sign,
  //                  max_dis, max_ang);
  robot.FT_Guard(flag, sensor_id, select, &ft, max_threshold, min_threshold);

  return 0;
}
