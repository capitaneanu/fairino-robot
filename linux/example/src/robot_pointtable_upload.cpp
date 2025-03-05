#include "libfairino/robot.h"
#ifdef WINDOWS_OPTION
#include <string.h>
#include <windows.h>

#include <string>
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

  string save_path = "D://sharkLog/0.db";

  int retval = robot.PointTableUpLoad(save_path);
  cout << "retval is: " << retval << endl;
}