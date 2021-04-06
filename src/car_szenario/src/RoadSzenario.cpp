#include <math.h>

#include <tf_conversions/tf_eigen.h>
#include <car_szenario/RoadSzenario.hpp>

RoadSzenario::RoadSzenario(ros::NodeHandle n)
{
    //std::string path = ros::package::getPath("car_situations_simulation");
    //paramFile = path + "/cfg/carlike/teb_local_planner_params_default_load.yaml";

    obstacle_pub = n.advertise<costmap_converter::ObstacleArrayMsg>("/move_base_flex/TebLocalPlannerROS/obstacles", 1000);
    via_pub = n.advertise<nav_msgs::Path>("/move_base_flex/TebLocalPlannerROS/via_points", 1000);
    goal_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);
    obstBox_pub = n.advertise<geometry_msgs::PolygonStamped>("RoadSzenario/obstBox", 1000);
}
//RoadSzenario::RoadSzenario(ros::NodeHandle n, std::string file)
//{
//    std::string path = ros::package::getPath("car_situations_simulation");
//    paramFile = path + "/cfg/carlike/" + file;

//    obstacle_pub = n.advertise<costmap_converter::ObstacleArrayMsg>("/robot_0/move_base/TebLocalPlannerROS/obstacles", 1000);
//    via_pub = n.advertise<nav_msgs::Path>("/robot_0/move_base/TebLocalPlannerROS/via_points", 1000);
//    goal_pub = n.advertise<geometry_msgs::PoseStamped>("/robot_0/move_base_simple/goal", 1000);
//    obstBox_pub = n.advertise<geometry_msgs::PolygonStamped>("RoadSzenario/obstBox", 1000);
//}

void RoadSzenario::publishObstacles()
{
    costmap_converter::ObstacleArrayMsg msg;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "map";

    for (auto const& obsMap : ObstacleList)
    {
        Eigen::Vector2d obst_vel(obsMap.second.twist.twist.linear.x, obsMap.second.twist.twist.linear.y);
        double yaw_twist = tf::getYaw(obsMap.second.pose.pose.orientation);
        Eigen::Rotation2Dd rot(yaw_twist);
        obst_vel = rot * obst_vel;

        costmap_converter::ObstacleMsg obs;
        obs.id = obsMap.first;
        obs.header.stamp = msg.header.stamp;
        obs.header.frame_id = obsMap.second.child_frame_id;

        Eigen::Vector2d obst_vel_full = obst_vel;
        obst_vel.normalize();
        Eigen::Vector2d obst_vel_orth(-obst_vel.y(), obst_vel.x());

        geometry_msgs::Point32 p1, p2, p3, p4;
        p1.x = obsMap.second.pose.pose.position.x - (0.5*obst_vel).x() - (1*obst_vel_orth).x();
        p1.y = obsMap.second.pose.pose.position.y - (0.5*obst_vel).y() - (1*obst_vel_orth).y();
        p1.z = obsMap.second.pose.pose.position.z;
        p2.x = obsMap.second.pose.pose.position.x + (4.2*obst_vel).x() - (1*obst_vel_orth).x();
        p2.y = obsMap.second.pose.pose.position.y + (4.2*obst_vel).y() - (1*obst_vel_orth).y();
        p2.z = obsMap.second.pose.pose.position.z;
        p3.x = obsMap.second.pose.pose.position.x + (4.2*obst_vel).x() + (1*obst_vel_orth).x();
        p3.y = obsMap.second.pose.pose.position.y + (4.2*obst_vel).y() + (1*obst_vel_orth).y();
        p3.z = obsMap.second.pose.pose.position.z;
        p4.x = obsMap.second.pose.pose.position.x - (0.5*obst_vel).x() + (1*obst_vel_orth).x();
        p4.y = obsMap.second.pose.pose.position.y - (0.5*obst_vel).y() + (1*obst_vel_orth).y();
        p4.z = obsMap.second.pose.pose.position.z;

        obs.polygon.points.push_back(p1);
        obs.polygon.points.push_back(p2);
        obs.polygon.points.push_back(p3);
        obs.polygon.points.push_back(p4);

        geometry_msgs::TwistWithCovariance twist;
        twist.covariance = obsMap.second.twist.covariance;
        twist.twist.linear.x = obst_vel_full.x();
        twist.twist.linear.y = obst_vel_full.y();

        tf2::Quaternion tf_quat;
        double yaw = atan2(twist.twist.linear.y, twist.twist.linear.x);
        tf_quat.setRPY( 0, 0, yaw );
        geometry_msgs::Quaternion quat;
        quat = tf2::toMsg(tf_quat);
        //obs.orientation = quat;
        obs.orientation = obsMap.second.pose.pose.orientation;
        obs.velocities = twist;

        msg.obstacles.push_back(obs);
    }
    obstacle_pub.publish(msg);
}

void RoadSzenario::publishViaPoints()
{
    //Nothing todo in default impl
}

void RoadSzenario::adaptTebParams()
{
    //Nothing todo in default impl
    //When used, call sendTebParams with filled config
}

void RoadSzenario::publishGoal()
{
    if (globalGoal != lastGoal)
    {
        goal_pub.publish(globalGoal);
        lastGoal = globalGoal;
    }
}

void RoadSzenario::setTebParams()
{
//    std::cout << "Updating teb-parameters from " << paramFile << std::endl;
//    std::string cmd = "rosrun dynamic_reconfigure dynparam load /robot_0/move_base/TebLocalPlannerROS " + paramFile;

//    system(cmd.c_str());

//    dynamic_reconfigure::Config config;
//    dynamic_reconfigure::DoubleParameter min_obstacle_dist;
//    enable_param.name = "min_obstacle_dist";
//    enable_param.value = 1;
//    conf.doubles.push_back(enable_param);

    CREATE_CONFIG;
    ADD_CONFIGPARAM_DOUBLE("min_obstacle_dist", 0.5);
    ADD_CONFIGPARAM_DOUBLE("inflation_dist", 0.5);
    ADD_CONFIGPARAM_BOOL("include_costmap_obstacles", true);
    ADD_CONFIGPARAM_DOUBLE("costmap_obstacles_behind_robot_dist", 0.5);
    ADD_CONFIGPARAM_INT("obstacle_poses_affected", 15);
    ADD_CONFIGPARAM_DOUBLE("dynamic_obstacle_inflation_dist", 0.5);
    ADD_CONFIGPARAM_BOOL("include_dynamic_obstacles", true);
    ADD_CONFIGPARAM_INT("no_inner_iterations", 5);
    ADD_CONFIGPARAM_INT("no_outer_iterations", 4);
    ADD_CONFIGPARAM_DOUBLE("penalty_epsilon", 0.1);
    ADD_CONFIGPARAM_DOUBLE("obstacle_cost_exponent", 2);
    ADD_CONFIGPARAM_DOUBLE("weight_max_vel_x", 10);
    ADD_CONFIGPARAM_DOUBLE("weight_max_vel_theta", 10);
    ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_x", 500);
    ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_theta", 500);
    ADD_CONFIGPARAM_DOUBLE("weight_kinematics_nh", 1000);
    ADD_CONFIGPARAM_DOUBLE("weight_kinematics_forward_drive", 1);
    ADD_CONFIGPARAM_DOUBLE("weight_kinematics_turning_radius", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_optimaltime", 0.5);
    ADD_CONFIGPARAM_DOUBLE("weight_shortest_path", 0.15);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_right", 75);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_left", 75);
    ADD_CONFIGPARAM_DOUBLE("weight_inflation_right", 0.3);
    ADD_CONFIGPARAM_DOUBLE("weight_inflation_left", 0.3);
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle_inflation", 0);
    ADD_CONFIGPARAM_DOUBLE("weight_viapoint", 0);
    ADD_CONFIGPARAM_DOUBLE("weight_adapt_factor", 3);
    ADD_CONFIGPARAM_DOUBLE("selection_obst_cost_scale", 1);
    ADD_CONFIGPARAM_BOOL("selection_alternative_time_cost", false);
    ADD_CONFIGPARAM_DOUBLE("obstacle_heading_threshold", 0.45);
    ADD_CONFIGPARAM_BOOL("viapoints_all_candidates", true);
    ADD_CONFIGPARAM_BOOL("via_points_ordered", true);
    ADD_CONFIGPARAM_DOUBLE("via_points_distance", -0.1);
    ADD_CONFIGPARAM_DOUBLE("selection_viapoint_cost_scale", 1);

    sendTebParams(config);
}

bool RoadSzenario::sendTebParams(dynamic_reconfigure::Config conf)
{
    // http://ros-robotics.blogspot.com/2016/03/controling-dynamic-reconfiguration-from.html
    dynamic_reconfigure::ReconfigureRequest srv_req;
    dynamic_reconfigure::ReconfigureResponse srv_resp;

    srv_req.config = conf;

    bool retval = ros::service::call("/move_base_flex/TebLocalPlannerROS/set_parameters", srv_req, srv_resp);
    if (retval) {
        ROS_INFO("call to set TebLocalPlannerROS parameters succeeded");
    } else {
        ROS_INFO("call to set TebLocalPlannerROS parameters failed");
    }

    return retval;
}
