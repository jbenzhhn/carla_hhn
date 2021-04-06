#include <stdio.h>
#include <iostream>

#include "ros/ros.h"
#include <car_szenario/SzenarioHandler.hpp>

int main(int argc, char **argv)
{
    std::cout << "Started road_szenario_node!" << std::endl;

    ros::init(argc, argv, "road_szenario_node");
    ros::NodeHandle n;

    SzenarioHandler sh(n);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        sh.publishRoadSzenario();

        ros::spinOnce();
        loop_rate.sleep();
    }
}
