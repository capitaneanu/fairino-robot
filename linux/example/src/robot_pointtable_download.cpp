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
#include <fstream>
#include <thread>

using namespace std;

int main(void) {
  FRRobot robot;
  robot.RPC("192.168.58.2");

  string save_path = "D://sharkLog/";
  string point_table_name = "point_table_a.db";

  int retval = robot.PointTableDownLoad(point_table_name, save_path);
  cout << "download : " << point_table_name << " fail: " << retval << endl;
}