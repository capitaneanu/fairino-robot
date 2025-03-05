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

  // 操控机械臂
  robot.SetGripperConfig(company, device, softversion, bus);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  robot.GetGripperConfig(&company, &device, &softversion, &bus);
  // printf("gripper config:%d,%d,%d,%d\n", company, device, softversion, bus);

  // robot.ActGripper(index, act);
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  // robot.GetGripperActivateStatus(&fault, &active_status);
  // printf("gripper active fault is: %u, status is: %u\n", fault,
  // active_status);
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  act = 1;
  robot.ActGripper(index, act);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  robot.GetGripperActivateStatus(&fault, &active_status);
  // printf("gripper active fault is: %u, status is: %u\n", fault,
  // active_status);

  // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  // // 第一次移动
  // robot.MoveGripper(index, 100, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 90, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 80, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 70, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 60, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 50, 5, 50, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 40, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 30, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // // 第一次移动
  // robot.MoveGripper(index, 20, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // // 第一次移动
  // robot.MoveGripper(index, 10, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  for (int i = 0; i < 10; i++) {
    robot.GetGripperCurPosition(&fault, &current_pos);
    printf("fault is:%u, current position is: %u\n", fault, current_pos);
  }

  // 第一次移动
  // robot.MoveGripper(index, 0, 50, 5, max_time, block, 0, 0, 0, 0);
  // 获取当前位置、电流、电压、温度和速度
  // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // 第一次移动
  // robot.MoveGripper(index, 0, 50, 5, max_time, block, 0, 0, 0, 0);
  // 获取当前位置、电流、电压、温度和速度
  // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  // // 第一次移动
  // robot.MoveGripper(index, 10, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 20, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 30, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 40, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 50, 5, 50, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 60, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 70, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // // 第一次移动
  // robot.MoveGripper(index, 80, 50, 5, max_time, block, 0, 0, 0, 0);
  // // 获取当前位置、电流、电压、温度和速度
  // // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // 第一次移动
  // robot.MoveGripper(index, 60, 50, 5, max_time, block, 0, 0, 0, 0);
  // 获取当前位置、电流、电压、温度和速度
  // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // 第一次移动
  // robot.MoveGripper(index, 60, 50, 5, max_time, block, 0, 0, 0, 0);
  // 获取当前位置、电流、电压、温度和速度
  // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // 第一次移动
  // robot.MoveGripper(index, 60, 50, 5, max_time, block, 0, 0, 0, 0);
  // 获取当前位置、电流、电压、温度和速度
  // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // robot.GetGripperCurCurrent(&fault, &current);
  // printf("fault is:%u, current current is: %d\n", fault, current);

  // robot.GetGripperVoltage(&fault, &voltage);
  // printf("fault is:%u, current voltage is: %d \n", fault, voltage);

  // robot.GetGripperTemp(&fault, &temp);
  // printf("fault is:%u, current temperature is: %d\n", fault, temp);

  // robot.GetGripperCurSpeed(&fault, &speed);
  // printf("fault is:%u, current speed is: %d\n", fault, speed);

  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  // status = 0;
  // robot.GetGripperMotionDone(&fault, &status);
  // printf("motion status:%u,%u\n", fault, status);

  printf("\n");

  // 第二次移动
  // block = 1;
  // robot.MoveGripper(index, 50, 5, 0, max_time, block, 0, 0, 0, 0);

  // robot.GetGripperCurSpeed(&fault, &speed);
  // printf("fault is:%u, current speed is: %d\n", fault, speed);

  // robot.GetGripperCurPosition(&fault, &current_pos);
  // printf("fault is:%u, current position is: %u\n", fault, current_pos);

  // robot.GetGripperCurCurrent(&fault, &current);
  // printf("fault is:%u, current current is: %d\n", fault, current);

  // robot.GetGripperVoltage(&fault, &voltage);
  // printf("fault is:%u, current voltage is: %d \n", fault, voltage);

  // robot.GetGripperTemp(&fault, &temp);
  // printf("fault is:%u, current temperature is: %d\n", fault, temp);

  // printf("\n");

  // std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  // status = 0;
  // robot.GetGripperMotionDone(&fault, &status);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // printf("motion status:%u,%u\n", fault, status);

  // act = 0;
  // // robot.ActGripper(index, act);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // robot.GetGripperActivateStatus(&fault, &active_status);
  // printf("gripper active fault is: %u, status is: %u\n", fault,
  // active_status);

  // 机械臂

  // int retval = 0;
  // DescPose prepick_pose;
  // DescPose postpick_pose;
  // memset(&prepick_pose, 0, sizeof(DescPose));
  // memset(&postpick_pose, 0, sizeof(DescPose));

  // DescPose desc_p1;
  // desc_p1.tran.x = -351.553;
  // desc_p1.tran.y = 87.913;
  // desc_p1.tran.z = 354.175;
  // desc_p1.rpy.rx = -179.680;
  // desc_p1.rpy.ry = -0.133;
  // desc_p1.rpy.rz = 2.472;

  // DescPose desc_p2;
  // desc_p2.tran.x = -351.535;
  // desc_p2.tran.y = -247.222;
  // desc_p2.tran.z = 354.173;
  // desc_p2.rpy.rx = -179.680;
  // desc_p2.rpy.ry = -0.137;
  // desc_p2.rpy.rz = 2.473;

  // retval = robot.ComputePrePick(&desc_p1, 10, 0, &prepick_pose);
  // printf("ComputePrePick retval is: %d\n", retval);
  // printf("xyz is: %f, %f, %f; rpy is: %f, %f, %f\n", prepick_pose.tran.x,
  // prepick_pose.tran.y, prepick_pose.tran.z, 	   prepick_pose.rpy.rx,
  // prepick_pose.rpy.ry, prepick_pose.rpy.rz);

  // retval = robot.ComputePostPick(&desc_p2, -10, 0, &postpick_pose);
  // printf("ComputePostPick retval is: %d\n", retval);
  // printf("xyz is: %f, %f, %f; rpy is: %f, %f, %f\n", postpick_pose.tran.x,
  // postpick_pose.tran.y, postpick_pose.tran.z, 	   postpick_pose.rpy.rx,
  // postpick_pose.rpy.ry, postpick_pose.rpy.rz);

  return 0;
}