#include "libfairino/robot.h"
// #include "libfairino/robot_types.h"
#include "libfairino/robot_error.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("Usage: %s Z \n", argv[0]);
        return 1;
    }

    int zpos = atoi(argv[1]);

    FRRobot robot;             // Instantiate the robot object
    robot.RPC("192.168.58.2"); // Establish a communication connection with the robot controller

    robot.SetSpeed(40);
    printf("\n");

    // z
    if (zpos > 0)
    {
        robot.StartJOG(4, 3, 1, 20.0, 20.0, zpos);
    }

    if (zpos < 0)
    {
        robot.StartJOG(4, 3, 0, 20.0, 20.0, zpos * (-1));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(9999));
    robot.ImmStopJOG();

    return 0;
}
