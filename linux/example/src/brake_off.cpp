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

int main(void) {
  FRRobot robot;
  robot.RPC("192.168.58.2");

  uint8_t status = 0;
  uint8_t smooth = 0;
  uint8_t block = 0;

  status = 1;

  // robot.WaitMs(1000);
  // robot.SetAuxDO(7, status, smooth, block);
  robot.SetAuxDO(7, true, false, true);
  // robot.WaitMs(1000);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  printf("\n");

  return 0;
}