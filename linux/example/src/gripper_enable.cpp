#include "libfairino/robot.h"
#ifdef WINDOWS_OPTION
#include <string.h>
#include <windows.h>
#elif LINUX_OPTION
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#endif

#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{

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

    robot.SetGripperConfig(company, device, softversion, bus);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    robot.GetGripperConfig(&company, &device, &softversion, &bus);
    printf("gripper config:%d,%d,%d,%d\n", company, device, softversion, bus);

    robot.ActGripper(index, act);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    robot.GetGripperActivateStatus(&fault, &active_status);
    printf("gripper active fault is: %u, status is: %u\n", fault, active_status);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    act = 1;
    robot.ActGripper(index, act);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    robot.GetGripperActivateStatus(&fault, &active_status);
    printf("gripper active fault is: %u, status is: %u\n", fault, active_status);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // robot.MoveGripper(index, gpos, 50, 40, max_time, block, 0, 0, 0, 0);

    // while (gstatus)
    // {
    //     status = 1;
    //     robot.GetGripperMotionDone(&fault, &status);
    //     if (status == 3)
    //     {
    //         gstatus = 0;
    //     }
    // }

    // std::this_thread::sleep_for(std::chrono::milliseconds(500));

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

    printf("\n");

    return 0;
}