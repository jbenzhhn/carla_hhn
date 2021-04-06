#include <math.h>

#include <car_szenario/DrivewaySzenario.hpp>

void DrivewaySzenario::publishViaPoints()
{
    //std::cout << "publishViaPoints entered" << std::endl;
    nav_msgs::Path via_msg;
    via_msg.header.stamp = ros::Time::now();
    via_msg.header.frame_id = "map";
    if (1 <= CurrentRoadInfo.startPoints.size() && 1 <= CurrentRoadInfo.endPoints.size())
    {
        for (auto const& obsMap : ObstacleList)
        {
            if (isObstInDriveway(obsMap.second, CurrentRoadInfo.startPoints[0], CurrentRoadInfo.endPoints[0]))
            {
                //std::cout << "publish ViaPoint for car " << std::to_string(obsMap.first) << std::endl;
                geometry_msgs::PoseStamped viaPose;
                viaPose.pose.position.x = obsMap.second.pose.pose.position.x - 0.5;
                viaPose.pose.position.y = obsMap.second.pose.pose.position.y;// - 1.8;
                viaPose.pose.orientation.x = 0;
                viaPose.pose.orientation.y = 0;
                viaPose.pose.orientation.z = 0;
                viaPose.pose.orientation.w = 1;
                //std::cout << "pos: " << viaPose.pose.position.x << " - " << viaPose.pose.position.y << std::endl;
                via_msg.poses.push_back(viaPose);
            }
        }
    }
    via_pub.publish(via_msg);
}

void DrivewaySzenario::adaptTebParams()
{
    double setVMax = vMax;
    int32_t carId = getCarInFront();
    if (-1 < carId)
    {
        nav_msgs::Odometry obst = ObstacleList[carId];
        setVMax = sqrt(obst.twist.twist.linear.x*obst.twist.twist.linear.x+obst.twist.twist.linear.y*obst.twist.twist.linear.y);
    }
    if (setVMax != setVMaxOld)
    {
        setVMaxOld = setVMax;
        std::cout << "SET MAX_VEL_X TO " << setVMax << std::endl;
        CREATE_CONFIG;
        ADD_CONFIGPARAM_DOUBLE("max_vel_x", setVMax);
        sendTebParams(config);
    }
}

int32_t DrivewaySzenario::getCarInFront()
{
    double minDist = 7.5; //std::numeric_limits<double>::max();
    int32_t retId = -1;
    int32_t Id = -1;
    for (auto const& obsMap : ObstacleList)
    {
        ++Id;
        Eigen::Vector2d car_obst_vec(obsMap.second.pose.pose.position.x-CarPosition.pose.pose.position.x, obsMap.second.pose.pose.position.y-CarPosition.pose.pose.position.y);
        Eigen::Vector2d car_vel(CarPosition.twist.twist.linear.x, CarPosition.twist.twist.linear.y);
        car_obst_vec.normalize();
        car_vel.normalize();
        double dotProd = car_obst_vec.dot(car_vel);
        //std::cout << "DOTPROD: " << dotProd << std::endl;
        if (dotProd >= 0.45)
        {
            //Eigen::Vector2d car_pos(CarPosition.pose.pose.position.x, CarPosition.pose.pose.position.y);
            Eigen::Vector2d obst_pos(obsMap.second.pose.pose.position.x, obsMap.second.pose.pose.position.y);
            Eigen::Vector2d t_vec(-CarPosition.pose.pose.position.x, -CarPosition.pose.pose.position.y);
            double yaw = atan2(CarPosition.twist.twist.linear.y, CarPosition.twist.twist.linear.x);
            Eigen::Matrix2d r_vec;
            r_vec << cos(yaw), sin(yaw), -sin(yaw), cos(yaw);
            Eigen::Vector2d obst_pos_car = r_vec*(obst_pos+t_vec);

//            geometry_msgs::PolygonStamped obstBox;
//            obstBox.header.stamp = ros::Time::now();
//            obstBox.header.frame_id = "map";

//            geometry_msgs::Point32 p;
//            Eigen::Matrix2d r_vec_inv = r_vec.transpose();
//            //r_vec << cos(-yaw), sin(-yaw), -sin(-yaw), cos(-yaw);
//            Eigen::Vector2d P1_car(minDist, 3);
//            Eigen::Vector2d P1_w = r_vec_inv*P1_car-t_vec;
//            p.x = P1_w.x();
//            p.y = P1_w.y();
//            obstBox.polygon.points.push_back(p);
//            Eigen::Vector2d P2_car(minDist, -3);
//            Eigen::Vector2d P2_w = r_vec_inv*P2_car-t_vec;
//            p.x = P2_w.x();
//            p.y = P2_w.y();
//            obstBox.polygon.points.push_back(p);
//            //Eigen::Vector2d P3_car(-narrow_vec.norm(), -5);
//            Eigen::Vector2d P3_car(0, -3);
//            Eigen::Vector2d P3_w = r_vec_inv*P3_car-t_vec;
//            p.x = P3_w.x();
//            p.y = P3_w.y();
//            obstBox.polygon.points.push_back(p);
//            //Eigen::Vector2d P4_car(-narrow_vec.norm(), 10);
//            Eigen::Vector2d P4_car(0, 3);
//            Eigen::Vector2d P4_w = r_vec_inv*P4_car-t_vec;
//            p.x = P4_w.x();
//            p.y = P4_w.y();
//            obstBox.polygon.points.push_back(p);

//            obstBox_pub.publish(obstBox);

            if (obst_pos_car.x() < minDist && obst_pos_car.x() > 0
                    && obst_pos_car.y() < 1.5 && obst_pos_car.y() > -1.5)
            {
                retId = Id;
            }

//            double dist = (obst_pos - car_pos).norm();
//            //std::cout << "dist: " << dist << std::endl;
//            if (dist < minDist)
//            {
//                minDist = dist;
//                retId = Id;
//            }
        }
    }

    return retId;
}

bool DrivewaySzenario::isObstInDriveway(nav_msgs::Odometry obst, geometry_msgs::Point start, geometry_msgs::Point end)
{
    Eigen::Vector2d start_vec(start.x, start.y);
    Eigen::Vector2d end_vec(end.x, end.y);
    Eigen::Vector2d driveway_vec(end.x-start.x, end.y-start.y);
    Eigen::Vector2d driveway_vec_rot(-(end.y-start.y), end.x-start.x);
    driveway_vec.normalize();
    driveway_vec_rot.normalize();

//    Eigen::Vector2d P1 = start_vec - 5*driveway_vec + 5*driveway_vec_rot;
//    Eigen::Vector2d P2 = start_vec - 5*driveway_vec - 5*driveway_vec_rot;
//    Eigen::Vector2d P3 = end_vec + 5*driveway_vec - 5*driveway_vec_rot;
//    Eigen::Vector2d P4 = end_vec + 5*driveway_vec + 5*driveway_vec_rot;

    double driveway_box_exp_dim_front = getExpDimFront(start, end);
    double driveway_box_exp_dim_height = 2.5;

    Eigen::Vector2d P1 = start_vec - driveway_box_exp_dim_front*driveway_vec + driveway_box_exp_dim_height*driveway_vec_rot;
    Eigen::Vector2d P2 = start_vec - driveway_box_exp_dim_front*driveway_vec - driveway_box_exp_dim_height*driveway_vec_rot;
    Eigen::Vector2d P3 = end_vec + driveway_vec - driveway_box_exp_dim_height*driveway_vec_rot;
    Eigen::Vector2d P4 = end_vec + driveway_vec + driveway_box_exp_dim_height*driveway_vec_rot;

//    geometry_msgs::PolygonStamped obstBox;
//    obstBox.header.stamp = ros::Time::now();
//    obstBox.header.frame_id = "map";
//    geometry_msgs::Point32 p;
//    p.x = P1.x();
//    p.y = P1.y();
//    obstBox.polygon.points.push_back(p);
//    p.x = P2.x();
//    p.y = P2.y();
//    obstBox.polygon.points.push_back(p);
//    p.x = P3.x();
//    p.y = P3.y();
//    obstBox.polygon.points.push_back(p);
//    p.x = P4.x();
//    p.y = P4.y();
//    obstBox.polygon.points.push_back(p);
//    obstBox_pub.publish(obstBox);

    if (obst.pose.pose.position.x > P1.x() && obst.pose.pose.position.x < P3.x()
            && obst.pose.pose.position.y > P2.y() && obst.pose.pose.position.y < P4.y())
    {
        return true;
    }
    else
    {
        return false;
    }

}

double DrivewaySzenario::getExpDimFront(geometry_msgs::Point start, geometry_msgs::Point end)
{
    return 1;
}

void DrivewaySzenario::setTebParams()
{
    CREATE_CONFIG;
    //ADD_CONFIGPARAM_DOUBLE("min_obstacle_dist", 0.8);
    ADD_CONFIGPARAM_DOUBLE("inflation_dist", 0.75);
    ADD_CONFIGPARAM_DOUBLE("dynamic_obstacle_inflation_dist", 1);
    //ADD_CONFIGPARAM_DOUBLE("weight_max_vel_x", 2);
    ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_x", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_theta", 250);
    ADD_CONFIGPARAM_DOUBLE("weight_optimaltime", 0.0000001);
//    ADD_CONFIGPARAM_DOUBLE("weight_optimaltime", 0.05);
    ADD_CONFIGPARAM_DOUBLE("weight_shortest_path", 10);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_right", 10);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_left", 10);
    //ADD_CONFIGPARAM_DOUBLE("weight_inflation_right", 0.6); //0.15
    //ADD_CONFIGPARAM_DOUBLE("weight_inflation_left", 0.6); //0.6
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle", 800);
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle_inflation", 0.8);
    ADD_CONFIGPARAM_DOUBLE("weight_viapoint", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_adapt_factor", 7);
    ADD_CONFIGPARAM_BOOL("viapoints_all_candidates", false);
    //ADD_CONFIGPARAM_BOOL("via_points_ordered", true);
    ADD_CONFIGPARAM_DOUBLE("via_points_distance", 5);

    sendTebParams(config);
}
