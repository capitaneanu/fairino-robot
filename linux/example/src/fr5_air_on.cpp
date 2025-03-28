#include "libfairino/robot.h"
#ifdef WINDOWS_OPTION
#include <string.h>
#include <windows.h>
#elif LINUX_OPTION
#include <stdio.h>
#include <unistd.h>

#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#endif

#include <chrono>
#include <thread>

using namespace std;

int main(void) {
  FRRobot robot;             // 实例化机器人对象
  robot.RPC("192.168.58.2"); // 与机器人控制器建立通信连接

  uint8_t status = 0;
  uint8_t smooth = 0;
  uint8_t block = 0;
  // uint8_t di = 0, tool_di = 0;
  // float ai = 0.0, tool_ai = 0.0;
  // float value = 0.0;
  int i;
  uint8_t do_state_h = 0;
  uint8_t do_state_l = 0;
  // uint8_t tool_do_state = 0;

  status = 1;
  robot.SetDO(7, status, smooth, block);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // robot.GetDO(&do_state_h, &do_state_l);
  // std::bitset<sizeof(do_state_h) * 8> bitsetHigh(do_state_h);
  // std::bitset<sizeof(do_state_l) * 8> bitsetLow(do_state_l);
  // std::cout << "DO" << i << " state high : " << bitsetHigh << " state low : "
  // << bitsetLow << std::endl;
  // std::this_thread::sleep_for(std::chrono::milliseconds(4000));

  // status = 0;
  // robot.SetDO(7, status, smooth, block);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // robot.GetDO(&do_state_h, &do_state_l);
  // std::bitset<sizeof(do_state_h) * 8> bitsetHigh(do_state_h);
  // std::bitset<sizeof(do_state_l) * 8> bitsetLow(do_state_l);
  // std::cout << "DO" << i << " state high : " << bitsetHigh << " state low : "
  // << bitsetLow << std::endl;
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  // printf("set DO status to 0\n");
  // for (i = 0; i < 8; i++)
  // {
  //   robot.SetDO(i, status, smooth, block);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  //   robot.GetDO(&do_state_h, &do_state_l);
  //   std::bitset<sizeof(do_state_h) * 8> bitsetHigh(do_state_h);
  //   std::bitset<sizeof(do_state_l) * 8> bitsetLow(do_state_l);
  //   std::cout << "DO" << i << " state high : " << bitsetHigh << " state low :
  //   " << bitsetLow << std::endl;
  //   // printf("\n");
  // }
  // std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  // printf("\n");

  // status = 1;

  // printf("set DO status to 1\n");
  // for (i = 0; i < 8; i++)
  // {
  //   robot.SetDO(i, status, smooth, block);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  //   robot.GetDO(&do_state_h, &do_state_l);
  //   std::bitset<sizeof(do_state_h) * 8> bitsetHigh(do_state_h);
  //   std::bitset<sizeof(do_state_l) * 8> bitsetLow(do_state_l);
  //   std::cout << "DO" << i << " state high : " << bitsetHigh << " state low :
  //   " << bitsetLow << std::endl;
  //   // printf("\n");
  // }
  // std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  // printf("\n");

  // status = 0;

  // printf("set DO status to 0\n");
  // for (i = 0; i < 8; i++)
  // {
  //   robot.SetDO(i, status, smooth, block);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  //   robot.GetDO(&do_state_h, &do_state_l);
  //   std::bitset<sizeof(do_state_h) * 8> bitsetHigh(do_state_h);
  //   std::bitset<sizeof(do_state_l) * 8> bitsetLow(do_state_l);
  //   std::cout << "DO" << i << " state high : " << bitsetHigh << " state low :
  //   " << bitsetLow << std::endl;
  //   // printf("\n");
  // }
  // std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  // printf("\n");

  // status = 0;

  // for (i = 0; i < 2; i++)
  // {
  // robot.SetToolDO(i, status, smooth, block);
  // robot.WaitMs(1000);
  // }
  // printf("set tool DO status to 0\n");
  // robot.GetToolDO(&tool_do_state);
  // printf("tool DO state is: %u\n", tool_do_state);
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  // printf("\n");

  // status = 1;
  //
  // for (i = 0; i < 2; i++) {
  // robot.SetToolDO(i, status, smooth, block);
  // robot.WaitMs(1000);
  // }
  // printf("set tool DO status to 1\n");
  // robot.GetToolDO(&tool_do_state);
  // printf("tool DO state is: %u\n", tool_do_state);
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  // printf("\n");
  //
  // value = 50.0;
  // robot.SetAO(0, value, block);
  // value = 100.0;
  // robot.SetAO(1, value, block);
  // robot.WaitMs(1000);
  // value = 0.0;
  // robot.SetAO(0, value, block);
  // value = 0.0;
  // robot.SetAO(1, value, block);
  //
  // value = 100.0;
  // robot.SetToolAO(0, value, block);
  // robot.WaitMs(1000);
  // value = 0.0;
  // robot.SetToolAO(0, value, block);
  //
  // robot.GetDI(0, block, &di);
  // printf("di0:%u\n", di);
  // robot.WaitDI(0, 1, 1000, 1);
  // robot.WaitMultiDI(1, 3, 3, 10000, 1);
  // tool_di = robot.GetToolDI(1, block, &tool_di);
  // printf("tool_di1:%u\n", tool_di);
  // robot.WaitToolDI(1, 1, 0, 1);
  //
  // robot.GetAI(0, block, &ai);
  // printf("ai0:%f\n", ai);
  // robot.WaitAI(0, 0, 50, 1000, 1);
  // robot.WaitToolAI(0, 0, 50, 1000, 1);
  // tool_ai = robot.GetToolAI(0, block, &tool_ai);
  // printf("tool_ai0:%f\n", tool_ai);
  //
  // uint8_t _button_state = 0;
  // int times = 0;
  // do {
  // robot.GetAxlePointRecordBtnState(&_button_state);
  // printf("_button_state is: %u\n", _button_state);
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  // times++;
  // } while (times < 5);
  //
  return 0;
}