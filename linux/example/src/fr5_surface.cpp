#include "libfairino/robot.h"
// #include "libfairino/robot_types.h"
#include "libfairino/robot_error.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(void)
{
    FRRobot robot;             // Instantiate the robot object
    robot.RPC("192.168.58.2"); // Establish a communication connection with the
    // robot controller

    int rcs = 1;
    uint8_t dir = 2;
    uint8_t axis = 3;
    float lin_v = 50.0;
    float lin_a = 0.0;
    float maxdis = 400.0;
    float ft_goal = -4.0;

    ROBOT_STATE_PKG rt_data = {};
    DescPose desc_pos0, dcenter;
    ForceTorque ft;

    memset(&desc_pos0, 0, sizeof(DescPose));
    memset(&dcenter, 0, sizeof(DescPose));
    memset(&ft, 0, sizeof(ForceTorque));

    desc_pos0.tran.x = -37.65;
    desc_pos0.tran.y = -333.05;
    desc_pos0.tran.z = 400.75;
    desc_pos0.rpy.rx = -180.0;
    desc_pos0.rpy.ry = 0.0;
    desc_pos0.rpy.rz = 155.0;

    robot.MoveCart(&desc_pos0, 0, 0, 100.0, 100.0, 100.0, -1.0, -1);
    robot.WaitMs(2000);
    robot.FT_CalCenterStart();
    robot.FT_FindSurface(rcs, dir, axis, lin_v, lin_a, maxdis, ft_goal);

    DescPose center_pose;
    memset(&center_pose, 0, sizeof(DescPose));
    int retval = robot.FT_CalCenterEnd(&center_pose);
    printf("FT_CalCenterEnd retval is: %d \n", retval);
    printf("xyz is: %f, %f, %f; rpy is: %f, %f, %f\n", center_pose.tran.x, center_pose.tran.y, center_pose.tran.z,
           center_pose.rpy.rx, center_pose.rpy.ry, center_pose.rpy.rz);

    // robot.FT_CalCenterEnd(&dcenter);
    // printf("xcenter:     %f, %f, %f, %f, %f, %f\n", dcenter.tran.x, dcenter.tran.y, dcenter.tran.z, dcenter.rpy.rx, dcenter.rpy.ry, dcenter.rpy.rz);

    robot.FT_GetForceTorqueOrigin(0, &ft);
    printf("FT Torque:   %f, %f, %f, %f, %f, %f\n", ft.fx, ft.fy, ft.fz, ft.tx, ft.ty, ft.tz);

    robot.WaitMs(1000);
    robot.GetRobotRealTimeState(&rt_data);
    printf("Coordinates: %f, %f, %f, %f, %f, %f\n",
           rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
           rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

    robot.WaitMs(2000);
    desc_pos0.tran.x = rt_data.tl_cur_pos[0];
    desc_pos0.tran.y = rt_data.tl_cur_pos[1];
    desc_pos0.tran.z = rt_data.tl_cur_pos[2] + 50;
    desc_pos0.rpy.rx = rt_data.tl_cur_pos[3];
    desc_pos0.rpy.ry = rt_data.tl_cur_pos[4];
    desc_pos0.rpy.rz = rt_data.tl_cur_pos[5];

    robot.MoveCart(&desc_pos0, 0, 0, 100.0, 100.0, 100.0, -1.0, -1);

    return 0;
}