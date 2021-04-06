
#ifndef DRIVEWAYSZENARIO_HPP
#define DRIVEWAYSZENARIO_HPP

#include <stdio.h>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <dynamic_reconfigure/DoubleParameter.h>
#include <car_szenario/RoadSzenario.hpp>


class DrivewaySzenario : public RoadSzenario
{
public:

    //default CTOR for map-creation
    DrivewaySzenario()
    {
    }

    DrivewaySzenario(ros::NodeHandle n) : RoadSzenario(n) //, "teb_local_planner_params_driveway_load.yaml")
    {
        n.param<double>("/move_base_flex/TebLocalPlannerROS/max_vel_x", vMax, 15);
        setVMaxOld = vMax;
    }

    virtual ~DrivewaySzenario()
    {
    }

    virtual void publishViaPoints() override;

    virtual void adaptTebParams() override;

    virtual void setTebParams() override;

protected:
    virtual double getExpDimFront(geometry_msgs::Point start, geometry_msgs::Point end);

private:

    int32_t getCarInFront();

    bool isObstInDriveway(nav_msgs::Odometry obst, geometry_msgs::Point start, geometry_msgs::Point end);

    double vMax = 0;
    double setVMaxOld = 0;
};

#endif /* DRIVEWAYSZENARIO_HPP */
