
#ifndef SZENARIOHANDLER_HPP
#define SZENARIOHANDLER_HPP

#include <stdio.h>
#include <iostream>
#include <mutex>

#include "ros/ros.h"
#include <car_szenario/RoadSzenario.hpp>
#include <car_szenario/NarrowingSzenario.hpp>
#include <car_szenario/DrivewaySzenario.hpp>
#include <car_szenario/TIntersectionSzenario.hpp>

#define ADD_ROADSZENARIO(name, szenetype) rs_vec[name]=std::make_shared<szenetype>(n)

class SzenarioHandler
{
public:

    SzenarioHandler(ros::NodeHandle n);

    virtual ~SzenarioHandler()
    {
    }

    void publishRoadSzenario();

private:

    void callback_rob0(const nav_msgs::Odometry::ConstPtr& msg);

    void callback_robX(const nav_msgs::Odometry::ConstPtr& msg, uint8_t id);

    void callback_roadSzene(const car_szenario::RoadInfo::ConstPtr& msg);

    void callback_goal(const geometry_msgs::PoseStamped::ConstPtr& msg);

    void setupRoadSzenarios(ros::NodeHandle n);

    //string->define Szenario; RoadSzenario->the used RoadSzenario
    std::map<std::string, std::shared_ptr<RoadSzenario>> rs_vec;
    std::shared_ptr<RoadSzenario> active_rs;
    std::mutex rs_mtx;

    ros::Subscriber roadSzene_sub;
    ros::Subscriber rob0_sub;
    std::vector<ros::Subscriber> robX_subs; //store subscribers here so they are alive as long as main() is alive
    ros::Subscriber goal_sub;
    geometry_msgs::PoseStamped goal;

};

#endif /* SZENARIOHANDLER_HPP */
