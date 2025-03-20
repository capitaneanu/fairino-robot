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

       ROBOT_STATE_PKG rt_data = {};
       int rcs = 0;
       uint8_t dir = 1;
       uint8_t axis = 1;
       float lin_v = 40.0;
       float lin_a = 0.0;
       float maxdis = 50.0;
       float ft_goal = 2.0;

       DescPose desc_pos, desc_pos1, xcenter, ycenter;
       ForceTorque ft;

       memset(&desc_pos, 0, sizeof(DescPose));
       memset(&desc_pos1, 0, sizeof(DescPose));
       memset(&xcenter, 0, sizeof(DescPose));
       memset(&ycenter, 0, sizeof(DescPose));
       memset(&ft, 0, sizeof(ForceTorque));

       desc_pos.tran.x = -37.65;
       desc_pos.tran.y = -333.05;
       desc_pos.tran.z = 400.75;
       desc_pos.rpy.rx = -180.0;
       desc_pos.rpy.ry = 0.0;
       desc_pos.rpy.rz = 155.0;

       desc_pos1.tran.x = -37.65;
       desc_pos1.tran.y = -333.05;
       desc_pos1.tran.z = 200.75;
       desc_pos1.rpy.rx = -180.0;
       desc_pos1.rpy.ry = 0.0;
       desc_pos1.rpy.rz = 155.0;

       robot.MoveCart(&desc_pos, 0, 0, 100.0, 100.0, 100.0, -1.0, -1);
       robot.WaitMs(4000);
       robot.FT_CalCenterStart();
       robot.FT_FindSurface(1, 2, 3, lin_v, lin_a, 200.0, -4.0);
       robot.FT_CalCenterEnd(&xcenter);
       printf("xcenter:%f,%f,%f,%f,%f,%f\n", xcenter.tran.x, xcenter.tran.y, xcenter.tran.z, xcenter.rpy.rx, xcenter.rpy.ry, xcenter.rpy.rz);

       robot.FT_GetForceTorqueOrigin(0, &ft);
       printf("%f %f %f %f %f %f\n", ft.fx, ft.fy, ft.fz, ft.tx, ft.ty, ft.tz);

       robot.WaitMs(4000);
       robot.GetRobotRealTimeState(&rt_data);
       printf(
           "Coordinates: %f, %f, %f, %f, %f, %f\n",
           rt_data.tl_cur_pos[0], rt_data.tl_cur_pos[1], rt_data.tl_cur_pos[2],
           rt_data.tl_cur_pos[3], rt_data.tl_cur_pos[4], rt_data.tl_cur_pos[5]);

       //   dir = 2;
       //   robot.FT_FindSurface(rcs, dir, axis, lin_v, lin_a, maxdis, ft_goal);
       //   robot.FT_CalCenterEnd(&xcenter);
       //   printf("xcenter:%f,%f,%f,%f,%f,%f\n", xcenter.tran.x, xcenter.tran.y,
       //          xcenter.tran.z, xcenter.rpy.rx, xcenter.rpy.ry, xcenter.rpy.rz);
       //   robot.MoveCart(&xcenter, 9, 0, 60.0, 50.0, 50.0, -1.0, -1);

       //   robot.FT_CalCenterStart();
       //   dir = 1;
       //   axis = 2;
       //   lin_v = 6.0;
       //   maxdis = 150.0;
       //   robot.FT_FindSurface(rcs, dir, axis, lin_v, lin_a, maxdis, ft_goal);
       //   robot.MoveCart(&desc_pos, 9, 0, 100.0, 100.0, 100.0, -1.0, -1);
       //   robot.WaitMs(1000);

       //   dir = 2;
       //   robot.FT_FindSurface(rcs, dir, axis, lin_v, lin_a, maxdis, ft_goal);
       //   robot.FT_CalCenterEnd(&ycenter);
       //   printf("ycenter:%f,%f,%f,%f,%f,%f\n", ycenter.tran.x, ycenter.tran.y,
       //          ycenter.tran.z, ycenter.rpy.rx, ycenter.rpy.ry, ycenter.rpy.rz);
       //   robot.MoveCart(&ycenter, 9, 0, 60.0, 50.0, 50.0, 0.0, -1);

       return 0;
}