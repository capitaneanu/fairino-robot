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
  if (argc != 2) {
    printf("Usage: %s 0 \n", argv[0]);
    printf("      0 - 100 move gripper \n");

    return 1;
  }

  int gpos = atoi(argv[1]);

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
  uint8_t current_pos = 0;
  int8_t current = 0;
  int voltage = 0;
  int temp = 0;
  int8_t speed = 0;
  int8_t gstatus = 1;

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  robot.MoveGripper(index, gpos, 80, 50, max_time, block, 0, 0, 0, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  printf("\n");

  return 0;
}