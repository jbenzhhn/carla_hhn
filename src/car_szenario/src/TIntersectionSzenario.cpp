#include <math.h>

#include <car_szenario/TIntersectionSzenario.hpp>


double TIntersectionSzenario::getExpDimFront(geometry_msgs::Point start, geometry_msgs::Point end)
{
    Eigen::Vector2d driveway_vec(end.x-start.x, end.y-start.y);
    Eigen::Vector2d car_vel(CarPosition.twist.twist.linear.x, CarPosition.twist.twist.linear.y);

    return driveway_vec.norm()+car_vel.norm();
}

void TIntersectionSzenario::setTebParams()
{
    CREATE_CONFIG;
    //ADD_CONFIGPARAM_DOUBLE("min_obstacle_dist", 0.8);
    //ADD_CONFIGPARAM_DOUBLE("inflation_dist", 1);
    ADD_CONFIGPARAM_DOUBLE("dynamic_obstacle_inflation_dist", 1);
    //ADD_CONFIGPARAM_DOUBLE("weight_max_vel_x", 2);
    ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_x", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_theta", 100);
    ADD_CONFIGPARAM_DOUBLE("weight_optimaltime", 0.0000001);
    //ADD_CONFIGPARAM_DOUBLE("weight_kinematics_turning_radius", 25);
//    ADD_CONFIGPARAM_DOUBLE("weight_optimaltime", 0.05);
    ADD_CONFIGPARAM_DOUBLE("weight_shortest_path", 10);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_right", 100);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_left", 100);
    //ADD_CONFIGPARAM_DOUBLE("weight_inflation_right", 0.6); //0.15
    //ADD_CONFIGPARAM_DOUBLE("weight_inflation_left", 0.8); //0.6
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle", 800);
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle_inflation", 0.8);
    ADD_CONFIGPARAM_DOUBLE("weight_viapoint", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_adapt_factor", 7);
    ADD_CONFIGPARAM_BOOL("viapoints_all_candidates", false);
    //ADD_CONFIGPARAM_BOOL("via_points_ordered", true);
    ADD_CONFIGPARAM_DOUBLE("via_points_distance", 10);

    sendTebParams(config);
}
