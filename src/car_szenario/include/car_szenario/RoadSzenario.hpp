
#ifndef ROADSZENARIO_HPP
#define ROADSZENARIO_HPP

#include <stdio.h>
#include <iostream>

#include <ros/ros.h>
#include <ros/package.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>
#include <dynamic_reconfigure/DoubleParameter.h>
#include <dynamic_reconfigure/BoolParameter.h>
#include <dynamic_reconfigure/IntParameter.h>
#include <costmap_converter/ObstacleMsg.h>
#include <costmap_converter/ObstacleArrayMsg.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point32.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <car_szenario/RoadInfo.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf/transform_broadcaster.h>

#define CREATE_CONFIG                                   \
    dynamic_reconfigure::Config config;                 \
    dynamic_reconfigure::DoubleParameter dparam;        \
    dynamic_reconfigure::IntParameter iparam;           \
    dynamic_reconfigure::BoolParameter bparam

#define ADD_CONFIGPARAM_INT(paramName, val)             \
    iparam.name = paramName;                            \
    iparam.value = val;                                 \
    config.ints.push_back(iparam)

#define ADD_CONFIGPARAM_DOUBLE(paramName, val)          \
    dparam.name = paramName;                            \
    dparam.value = val;                                 \
    config.doubles.push_back(dparam)

#define ADD_CONFIGPARAM_BOOL(paramName, val)            \
    bparam.name = paramName;                            \
    bparam.value = val;                                 \
    config.bools.push_back(bparam)

class RoadSzenario
{
public:

    //default CTOR for map-creation
    RoadSzenario()
    {
    }

    RoadSzenario(ros::NodeHandle n);
    //RoadSzenario(ros::NodeHandle n, std::string file);

    virtual ~RoadSzenario()
    {
    }

    virtual void publishViaPoints();

    virtual void publishObstacles();

    virtual void adaptTebParams();

    virtual void publishGoal();

    virtual void setTebParams();

    void setObstacle(nav_msgs::Odometry obs, uint8_t id)
    {
        ObstacleList[id] = obs;
    }

    void setCarPosition(nav_msgs::Odometry pos) { CarPosition = pos; }

    void setCurrentRoadInfo(car_szenario::RoadInfo info) { CurrentRoadInfo = info; }

    void setGlobalGoal(geometry_msgs::PoseStamped goal)
    {
        if (globalGoal.pose != goal.pose)
        {
            globalGoal = goal;
            globalGoalRcv = true;
        }
    }

protected:

    bool sendTebParams(dynamic_reconfigure::Config conf);

    ros::Publisher obstacle_pub;
    ros::Publisher via_pub;
    ros::Publisher goal_pub;
    ros::Publisher obstBox_pub;

    std::map<uint8_t, nav_msgs::Odometry> ObstacleList;

    nav_msgs::Odometry CarPosition;

    car_szenario::RoadInfo CurrentRoadInfo;

    geometry_msgs::PoseStamped lastGoal;
    geometry_msgs::PoseStamped globalGoal;
    bool globalGoalRcv = false;

    std::string paramFile;

};

#endif /* ROADSZENARIO_HPP */
