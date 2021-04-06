
#ifndef TINTERSECTIONSZENARIO_HPP
#define TINTERSECTIONSZENARIO_HPP

#include <stdio.h>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <car_szenario/DrivewaySzenario.hpp>


class TIntersectionSzenario : public DrivewaySzenario
{
public:

    //default CTOR for map-creation
    TIntersectionSzenario()
    {
    }

    TIntersectionSzenario(ros::NodeHandle n) : DrivewaySzenario(n) //, "teb_local_planner_params_driveway_load.yaml")
    {
    }

    virtual ~TIntersectionSzenario()
    {
    }

    virtual void setTebParams() override;

protected:
    virtual double getExpDimFront(geometry_msgs::Point start, geometry_msgs::Point end) override;

private:

};

#endif /* TINTERSECTIONSZENARIO_HPP */
