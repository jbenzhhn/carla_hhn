#include <math.h>

#include <car_szenario/NarrowingSzenario.hpp>

//void NarrowingSzenario::publishViaPoints()
//{
//    if (1 <= CurrentRoadInfo.startPoints.size() && 1 <= CurrentRoadInfo.endPoints.size())
//    {
//        if (isViaPointNeeded(CurrentRoadInfo.startPoints[0], CurrentRoadInfo.endPoints[0]))
//        {
//            geometry_msgs::Point start = CurrentRoadInfo.startPoints[0];
//            //geometry_msgs::Point end= CurrentRoadInfo.endPoints[0];

//            nav_msgs::Path via_msg;
//            via_msg.header.stamp = ros::Time::now();
//            via_msg.header.frame_id = "map";

//            geometry_msgs::PoseStamped viaPose;
//            viaPose.pose.position = start;
//            via_msg.poses.push_back(viaPose);

//            via_pub.publish(via_msg);
//        }
//        else
//        {
//            //publish empty via-Points
//            nav_msgs::Path via_msg;
//            via_msg.header.stamp = ros::Time::now();
//            via_msg.header.frame_id = "map";
//            via_pub.publish(via_msg);
//        }
//    }
//    else
//    {
//        ROS_WARN("CurrentRoadInfo startPoints or endPoints empty! No ViaPoint sent!");
//    }
//}

void NarrowingSzenario::publishGoal()
{
    if (globalGoalRcv)
    {
        if (1 <= CurrentRoadInfo.startPoints.size() && 1 <= CurrentRoadInfo.endPoints.size())
        {
            //check for new goal if we're here the first time OR if hystere-time passed
            if (!actionNeeded || !timeSetGoal.isValid() ||  ros::Duration(5.0) < (ros::Time::now() - timeSetGoal))
            {
                if (isActionNeeded(CurrentRoadInfo.startPoints[0], CurrentRoadInfo.endPoints[0]))
                {
                    geometry_msgs::PoseStamped newGoal;
                    newGoal.header.stamp = ros::Time::now();
                    newGoal.header.frame_id = "map";

                    //calculate new goal Point in front of narrowing_start
                    Eigen::Vector2d narrow_vec(CurrentRoadInfo.endPoints[0].x - CurrentRoadInfo.startPoints[0].x, CurrentRoadInfo.endPoints[0].y - CurrentRoadInfo.startPoints[0].y);
                    narrow_vec.normalize();
                    Eigen::Vector2d narrow_start(CurrentRoadInfo.startPoints[0].x, CurrentRoadInfo.startPoints[0].y);
                    Eigen::Vector2d goalPos = narrow_start - 4*narrow_vec;

                    newGoal.pose.position.x = goalPos.x();
                    newGoal.pose.position.y = goalPos.y();
                    newGoal.pose.position.z = 0;

                    tf2::Quaternion tf_quat;
                    double yaw = atan2(narrow_vec.y(), narrow_vec.x());
                    tf_quat.setRPY( 0, 0, yaw );
                    geometry_msgs::Quaternion quat;
                    quat = tf2::toMsg(tf_quat);
                    newGoal.pose.orientation = quat;

//                    newGoal.pose.orientation.x = 0;
//                    newGoal.pose.orientation.y = 0;
//                    newGoal.pose.orientation.z = 0;
//                    newGoal.pose.orientation.w = 1;
                    if (newGoal.pose != lastGoal.pose)
                    {
                        goal_pub.publish(newGoal);
                        lastGoal = newGoal;
                        timeSetGoal = ros::Time::now();
                    }
                    actionNeeded = true;
                }
                else
                {
                    if (globalGoal.pose != lastGoal.pose)
                    {
                        goal_pub.publish(globalGoal);
                        lastGoal = globalGoal;
                        timeSetGoal = ros::Time::now();
                    }
                }
            }
        }
        else
        {
            ROS_WARN("CurrentRoadInfo startPoints or endPoints empty! No action checked!");
        }
    }
}

bool NarrowingSzenario::isActionNeeded(geometry_msgs::Point start, geometry_msgs::Point end)
{
    bool ret = false;

    for (auto const& obsMap : ObstacleList)
    {
        //std::cout << std::endl;
        Eigen::Vector2d car_obst_vec(obsMap.second.pose.pose.position.x-CarPosition.pose.pose.position.x, obsMap.second.pose.pose.position.y-CarPosition.pose.pose.position.y);
        Eigen::Vector2d car_vel(CarPosition.twist.twist.linear.x, CarPosition.twist.twist.linear.y);
        double car_vel_x = car_vel.x();
        double yaw_car = tf::getYaw(CarPosition.pose.pose.orientation);
        Eigen::Rotation2Dd rot(yaw_car);
        car_vel = rot * car_vel;

        //check if car is standing or driving backwards -> use last valid velocity to determine driving direction
        if (0 >= car_vel_x)
        {
            car_vel = last_valid_car_vel;
        }
        else
        {
            last_valid_car_vel = car_vel;
        }

        car_obst_vec.normalize();
        car_vel.normalize();
        double dotProd = car_obst_vec.dot(car_vel);
        if (dotProd >= 0)
        {
            //std::cout << "dotProd >= 0" << std::endl;
            Eigen::Vector2d obst_vec(obsMap.second.twist.twist.linear.x, obsMap.second.twist.twist.linear.y);
            double yaw = tf::getYaw(obsMap.second.pose.pose.orientation);
            Eigen::Rotation2Dd rot(yaw);
            obst_vec = rot * obst_vec;

            Eigen::Vector2d narrow_vec(end.x - start.x, end.y - start.y);
            Eigen::Vector2d obst_vec_normal = obst_vec; //original used later
            Eigen::Vector2d narrow_vec_normal = narrow_vec; //original used later
            obst_vec_normal.normalize();
            narrow_vec_normal.normalize();
            dotProd = narrow_vec_normal.dot(obst_vec_normal);
            if (dotProd < -0.45)
            {
                //std::cout << "dotProd < -0.45" << std::endl;
                //std::cout << "Obst Heading is relevant!" << std::endl;
                //check if narrowing is in front of obstacle and near enough

                //Transform to car coordSystem
                Eigen::Vector2d end_pos(end.x, end.y);
                Eigen::Vector2d t_vec(-obsMap.second.pose.pose.position.x, -obsMap.second.pose.pose.position.y);
                //double yaw = atan2(obsMap.second.twist.twist.linear.y, obsMap.second.twist.twist.linear.x);
                Eigen::Matrix2d r_vec;
                r_vec << cos(yaw), sin(yaw), -sin(yaw), cos(yaw);
                Eigen::Vector2d obst_end_car = r_vec*(end_pos+t_vec);

                //            std::cout << "end_pos: " << std::endl << end_pos << std::endl;
                //            std::cout << "t_vec(obst_pos): " << std::endl << t_vec << std::endl;
                //            std::cout << "r_vec(" << yaw << "): " << std::endl << r_vec << std::endl;
                //            std::cout << "obst_end_car: " << std::endl << obst_end_car << std::endl;

                Eigen::Vector2d car_pos(CarPosition.pose.pose.position.x, CarPosition.pose.pose.position.y);
                double carDist = (end_pos - car_pos).norm();
                double tCar = carDist/(vMax/3);
                //            std::cout << "vMax: " << vMax << std::endl;
                //            std::cout << "carDist: " << carDist << std::endl;
                //            std::cout << "tCar: " << tCar << std::endl;

                double obstDist = tCar*obst_vec.norm(); //TODO: perhaps safetay margin

//                geometry_msgs::PolygonStamped obstBox;
//                obstBox.header.stamp = ros::Time::now();
//                obstBox.header.frame_id = "map";

//                geometry_msgs::Point32 p;
//                Eigen::Matrix2d r_vec_inv = r_vec.transpose();
//                //r_vec << cos(-yaw), sin(-yaw), -sin(-yaw), cos(-yaw);
//                Eigen::Vector2d P1_car(obstDist, 7.5);
//                Eigen::Vector2d P1_w = r_vec_inv*P1_car-t_vec;
//                p.x = P1_w.x();
//                p.y = P1_w.y();
//                obstBox.polygon.points.push_back(p);
//                Eigen::Vector2d P2_car(obstDist, -2.5);
//                Eigen::Vector2d P2_w = r_vec_inv*P2_car-t_vec;
//                p.x = P2_w.x();
//                p.y = P2_w.y();
//                obstBox.polygon.points.push_back(p);
//                //Eigen::Vector2d P3_car(-narrow_vec.norm(), -5);
//                Eigen::Vector2d P3_car(0, -2.5);
//                Eigen::Vector2d P3_w = r_vec_inv*P3_car-t_vec;
//                p.x = P3_w.x();
//                p.y = P3_w.y();
//                obstBox.polygon.points.push_back(p);
//                //Eigen::Vector2d P4_car(-narrow_vec.norm(), 10);
//                Eigen::Vector2d P4_car(0, 7.5);
//                Eigen::Vector2d P4_w = r_vec_inv*P4_car-t_vec;
//                p.x = P4_w.x();
//                p.y = P4_w.y();
//                obstBox.polygon.points.push_back(p);

                  //Box for showing used narrowing
//                geometry_msgs::Point32 p;
//                p.x = start.x;
//                p.y = start.y;
//                obstBox.polygon.points.push_back(p);
//                p.x = end.x;
//                p.y = end.y;
//                obstBox.polygon.points.push_back(p);
//                p.x = end.x+1;
//                p.y = end.y+1;
//                obstBox.polygon.points.push_back(p);
//                p.x = start.x+1;
//                p.y = start.y+1;
//                obstBox.polygon.points.push_back(p);

//                obstBox_pub.publish(obstBox);

                if (obst_end_car.x() < obstDist && obst_end_car.x() > -(narrow_vec + 5*narrow_vec_normal).norm()
                        && obst_end_car.y() < 7.5 && obst_end_car.y() > -2.5)
                {
                    //std::cout << "Narrowing is in front of obst and in rectangle of interest! " << std::endl << std::endl;
                    ret = true;
                }
//                else
//                {
//                    std::cout << "Narrowing is NOT in rectangle of interest! " << std::endl << std::endl;
//                }
            }
            else {
                //std::cout << "Obst is not heading in correct direction!" << std::endl;
            }
        }
        else
        {
            //std::cout << "Obstacle is behind car -> irrelevant" << std::endl << std::endl;
        }

    }

    return ret;
}

void NarrowingSzenario::setTebParams()
{
    //reset actionNeeded here, because it is called when szenario is activated
    actionNeeded = false;

    CREATE_CONFIG;
    //ADD_CONFIGPARAM_DOUBLE("min_obstacle_dist", 0.6);
    //ADD_CONFIGPARAM_DOUBLE("inflation_dist", 1);
    //ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_x", 10);
    //ADD_CONFIGPARAM_DOUBLE("weight_acc_lim_theta", 50);
    ADD_CONFIGPARAM_DOUBLE("weight_kinematics_turning_radius", 100);
    ADD_CONFIGPARAM_DOUBLE("weight_optimaltime", 0.0000001);
    ADD_CONFIGPARAM_DOUBLE("weight_shortest_path", 10);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_right", 5);
    ADD_CONFIGPARAM_DOUBLE("weight_obstacle_left", 5);
    //ADD_CONFIGPARAM_DOUBLE("weight_inflation_right", 0.5); //0.15
    //ADD_CONFIGPARAM_DOUBLE("weight_inflation_left", 0.6); //0.6
    ADD_CONFIGPARAM_DOUBLE("weight_dynamic_obstacle", 200);
    ADD_CONFIGPARAM_DOUBLE("weight_adapt_factor", 3);
    ADD_CONFIGPARAM_DOUBLE("selection_obst_cost_scale", 0.75);

    sendTebParams(config);
}
