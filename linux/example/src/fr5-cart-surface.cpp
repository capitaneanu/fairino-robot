#include "libfairino/robot.h"
// #include "libfairino/robot_types.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

    FRRobot robot;             // Instantiate the robot object
    robot.RPC("192.168.58.2"); // Establish a communication connection with the
                               // robot controller

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

    if (argc != 4)
    {
        printf("Usage: %s X Y Z \n", argv[0]);
        printf("\n");

        robot.GetRobotRealTimeState(&rt_data);
        printf(
            "GetRobotRealTimeState :\t\tX %f, Y %f, Z %f, RX %f, RY %f, RZ %f\n",
            rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
            rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

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
    robot.GetRobotRealTimeState(&rt_data);
    printf("Coordinates: %f, %f, %f, %f, %f, %f\n",
           rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
           rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

    // desc_rt.tran.x = xpos;
    // desc_rt.tran.y = ypos;
    // desc_rt.tran.z = zpos;
    // desc_rt.tran.x = rt_data.tl_cur_pos[0] + xpos;
    // desc_rt.tran.y = rt_data.tl_cur_pos[1] + ypos;
    // desc_rt.tran.z = rt_data.tl_cur_pos[2] + zpos;
    desc_rt.tran.x = rt_data.tl_cur_pos[0];
    desc_rt.tran.y = rt_data.tl_cur_pos[1];
    desc_rt.tran.z = rt_data.tl_cur_pos[2];
    desc_rt.tran.z = rt_data.tl_cur_pos[2];
    desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
    desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
    desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

    robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
    robot.WaitMs(100);

    int rcs = 1;
    uint8_t dir = 2;
    uint8_t axis = 3;
    float lin_v = 30.0;
    float lin_a = 0.0;
    float maxdis = 400.0;
    float ft_goal = -2.0;

    robot.WaitMs(2000);
    robot.FT_CalCenterStart();
    robot.FT_FindSurface(rcs, dir, axis, lin_v, lin_a, maxdis, ft_goal);

    robot.WaitMs(1000);
    robot.FT_GetForceTorqueOrigin(0, &ft);
    printf("FT Torque:   %f, %f, %f, %f, %f, %f\n", ft.fx, ft.fy, ft.fz, ft.tx, ft.ty, ft.tz);
    robot.GetRobotRealTimeState(&rt_data);
    printf("Coordinates: %f, %f, %f, %f, %f, %f\n",
           rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
           rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

    desc_rt.tran.x = rt_data.tl_cur_pos[0];
    desc_rt.tran.y = rt_data.tl_cur_pos[1];
    desc_rt.tran.z = rt_data.tl_cur_pos[2] + 4;
    desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
    desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
    desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

    robot.WaitMs(1000);
    robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
    robot.WaitMs(100);

    uint8_t status = 0;
    uint8_t smooth = 0;
    uint8_t block = 0;
    status = 1;
    robot.SetDO(7, status, smooth, block);

    robot.GetRobotRealTimeState(&rt_data);
    printf("Coordinates: %f, %f, %f, %f, %f, %f\n",
           rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
           rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

    desc_rt.tran.x = rt_data.tl_cur_pos[0];
    desc_rt.tran.y = rt_data.tl_cur_pos[1];
    desc_rt.tran.z = rt_data.tl_cur_pos[2] + 46;
    desc_rt.rpy.rx = rt_data.tl_cur_pos[3];
    desc_rt.rpy.ry = rt_data.tl_cur_pos[4];
    desc_rt.rpy.rz = rt_data.tl_cur_pos[5];

    robot.WaitMs(5000);
    robot.MoveCart(&desc_rt, tool, user, vel, acc, ovl, blendT, config);
    robot.WaitMs(100);

    robot.WaitMs(2000);
    status = 0;
    robot.SetDO(7, status, smooth, block);

    return 0;
}
