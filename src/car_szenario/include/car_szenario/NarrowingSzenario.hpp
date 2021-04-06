
#ifndef NARROWINGSZENARIO_HPP
#define NARROWINGSZENARIO_HPP

#include <stdio.h>
#include <iostream>

#include <dynamic_reconfigure/DoubleParameter.h>
#include <car_szenario/RoadSzenario.hpp>


class NarrowingSzenario : public RoadSzenario
{
public:

    //default CTOR for map-creation
    NarrowingSzenario()
    {
    }

    NarrowingSzenario(ros::NodeHandle n) : RoadSzenario(n), last_valid_car_vel(0,0) //, "teb_local_planner_params_narrow_street_load.yaml")
    {
        n.param<double>("/move_base_flex/TebLocalPlannerROS/max_vel_x", vMax, 15);
    }

    virtual ~NarrowingSzenario()
    {
    }

    virtual void publishGoal() override;

    virtual void setTebParams() override;

private:

    bool isActionNeeded(geometry_msgs::Point start, geometry_msgs::Point end);
    ros::Time timeSetGoal;
    bool actionNeeded = false;

    Eigen::Vector2d last_valid_car_vel;

    double vMax = 0;
};

#endif /* NARROWINGSZENARIO_HPP */
