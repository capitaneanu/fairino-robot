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

  string point_tablename = "point_table_test.db";
  // string point_tablename = "point_table_a.db";
  string lua_name = "testPoint.lua";

  int retval = robot.PointTableUpdateLua(point_tablename, lua_name);
  cout << "retval is: " << retval << endl;
}