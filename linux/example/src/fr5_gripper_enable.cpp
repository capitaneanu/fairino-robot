#include "libfairino/robot.h"
#ifdef WINDOWS_OPTION
#include <string.h>
#include <windows.h>
#elif LINUX_OPTION
#include <stdio.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#endif

#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char **argv) {
  FRRobot robot;             // 实例化机器人对象
  robot.RPC("192.168.58.2"); // 与机器人控制器建立通信连接

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

  robot.SetGripperConfig(company, device, softversion, bus);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  robot.GetGripperConfig(&company, &device, &softversion, &bus);
  printf("gripper config:%d,%d,%d,%d\n", company, device, softversion, bus);

  robot.ActGripper(index, act);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  robot.GetGripperActivateStatus(&fault, &active_status);
  printf("gripper active fault is: %u, status is: %u\n", fault, active_status);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  act = 1;
  robot.ActGripper(index, act);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  robot.GetGripperActivateStatus(&fault, &active_status);
  printf("gripper active fault is: %u, status is: %u\n", fault, active_status);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  printf("\n");

  return 0;
}