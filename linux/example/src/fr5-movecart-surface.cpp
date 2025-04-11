#include "libfairino/robot.h"
// #include "libfairino/robot_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>

#include "libfairino/robot_error.h"

using namespace std;
// using namespace std::chrono_literals;

int main(int argc, char **argv)
{

    FRRobot robot;                        // Instantiate the robot object
    int rrpc = robot.RPC("192.168.58.2"); // Establish a communication connection with the
                                          // robot controller

    printf("robot RPC %d\n", rrpc);
    if (rrpc != 0)
    {
        robot.CloseRPC();
        robot.RPC("192.168.58.2");
    }

    ROBOT_STATE_PKG rt_data = {};
    DescPose desc_rt, tcp;
    memset(&desc_rt, 0, sizeof(DescPose));
    ForceTorque ft;
    memset(&ft, 0, sizeof(ForceTorque));

    int tool = 0; // default = 0
    int user = 0;
    float vel = 100.0;
    float acc = 50.0;
    float ovl = 50.0;
    float blendT = 0.0;
    float blendR = 0.0;
    uint8_t flag = 0;
    int config = -1; // default = -1
    int rcs = 1;
    uint8_t dir = 2;
    uint8_t axis = 3;
    float lin_v = 20.0;
    float lin_a = 0.0;
    float maxdis = 400.0;
    float ft_goal = -1.1; // without set zero -2.1;
    uint8_t status = 0;
    uint8_t smooth = 0;
    uint8_t block = 0;

    if (argc != 4)
    {
        printf("Usage: %s X Y Z \n", argv[0]);
        printf("\n");

        robot.GetRobotRealTimeState(&rt_data);
        printf("Coordinates: X %12f, Y %12f, Z %12f, RX %12f, RY %12f, RZ %12f\n", rt_data.tl_cur_pos[0],
               rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2], rt_data.tl_cur_pos[3],
               rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

        return 1;
    }

    int xpos = atoi(argv[1]);
    int ypos = atoi(argv[2]);
    int zpos = atoi(argv[3]);

    robot.GetActualTCPNum(flag, &tool);
    robot.GetRobotCurJointsConfig(&config);

    robot.SetSpeed(50);
    printf("\n");

    //   robot.GetActualTCPPose(flag, &tcp);
    //   robot.GetActualToolFlangePose(flag, &tcp);
    // robot.GetRobotRealTimeState(&rt_data);
    // printf("Coordinates: X %12f, Y %12f, Z %12f, RX %12f, RY %12f, RZ %12f\n", rt_data.tl_cur_pos[0],
    //        rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2], rt_data.tl_cur_pos[3],
    //        rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

    // desc_rt.tran.x = xpos;
    // desc_rt.tran.y = ypos;
    // desc_rt.tran.z = zpos;
    // desc_rt.tran.x = rt_data.tl_cur_pos[0] + xpos;
    // desc_rt.tran.y = rt_data.tl_cur_pos[1] + ypos;
    // desc_rt.tran.z = rt_data.tl_cur_pos[2] + zpos;
    // desc_rt.tran.x = rt_data.tl_cur_pos[0];
    // desc_rt.tran.y = rt_data.tl_cur_pos[1];
    // desc_rt.tran.z = rt_data.tl_cur_pos[2];
    // desc_rt.tran.z = rt_data.tl_cur_pos[2];
    // desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
    // desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
    // desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

    // robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
    // robot.WaitMs(100);

    // robot.WaitMs(500);
    robot.FT_CalCenterStart();
    robot.FT_FindSurface(rcs, dir, axis, lin_v, lin_a, maxdis, ft_goal);
    robot.WaitMs(100);
    
    // robot.GetRobotRealTimeState(&rt_data);
    // robot.FT_GetForceTorqueOrigin(0, &ft);
    // printf("ft_sensor_raw_data: FX%12f, FY%12f, FZ%12f, TX%12f,  TY%12f, TZ%12f\n", rt_data.ft_sensor_raw_data[0],
    //        rt_data.ft_sensor_raw_data[1], rt_data.ft_sensor_raw_data[2], rt_data.ft_sensor_raw_data[3],
    //        rt_data.ft_sensor_raw_data[4], rt_data.ft_sensor_raw_data[5]);
    // printf("ft_sensor_data: X %12f, Y %12f, Z %12f, RX %12f, RY %12f, RZ %12f\n", rt_data.ft_sensor_data[0],
    //        rt_data.ft_sensor_data[1], rt_data.ft_sensor_data[2], rt_data.ft_sensor_data[3],
    //        rt_data.ft_sensor_data[4], rt_data.ft_sensor_data[5]);

    // printf("ft_sensor_active %d\n", rt_data.ft_sensor_active);

    // printf("FT Torque:  FX %12f, FY %12f, FZ %12f, TX %12f, TY %12f, TZ %12f\n", ft.fx, ft.fy, ft.fz, ft.tx,
    //        ft.ty, ft.tz);

    // robot.GetRobotRealTimeState(&rt_data);
    // printf("Coordinates:  %12f,  %12f,  %12f,  %12f,  %12f,  %12f\n",
    //        rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
    //        rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4],
    //        rt_data.tl_cur_pos[5]);

    // desc_rt.tran.x = rt_data.tl_cur_pos[0];
    // desc_rt.tran.y = rt_data.tl_cur_pos[1];
    // desc_rt.tran.z = rt_data.tl_cur_pos[2] + 4;
    // desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
    // desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
    // desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

    // robot.WaitMs(1000);
    // robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
    // robot.WaitMs(100);

    // status = 1;
    // robot.SetDO(7, status, smooth, block);

    // robot.WaitMs(500);
    robot.GetRobotRealTimeState(&rt_data);
    printf("Coordinates:        X %12f, Y %12f, Z %12f, RX %12f, RY %12f, RZ %12f\n", rt_data.tl_cur_pos[0],
           rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2], rt_data.tl_cur_pos[3],
           rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

    desc_rt.tran.x = rt_data.tl_cur_pos[0];
    desc_rt.tran.y = rt_data.tl_cur_pos[1];
    desc_rt.tran.z = rt_data.tl_cur_pos[2] + 100;
    desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
    desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
    desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

    // robot.WaitMs(500);
    robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
    robot.WaitMs(100);

    // robot.WaitMs(2000);
    // status = 0;
    // robot.SetDO(7, status, smooth, block);

    return 0;
}
