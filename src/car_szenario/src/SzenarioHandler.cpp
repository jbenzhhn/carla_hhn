#include <regex>
#include <thread>
#include <chrono>
#include <car_szenario/SzenarioHandler.hpp>

SzenarioHandler::SzenarioHandler(ros::NodeHandle n)
{
    //add possible RoadSzenarios to list
    setupRoadSzenarios(n);

    rob0_sub = n.subscribe<nav_msgs::Odometry>("/carla/ego_vehicle/odometry", 1000, boost::bind(&SzenarioHandler::callback_rob0, this, _1));
    robX_subs.push_back(n.subscribe<nav_msgs::Odometry>("/carla/hero/odometry", 1000, boost::bind(&SzenarioHandler::callback_robX, this, _1, 0)));

    //std::this_thread::sleep_for(std::chrono::seconds(10));

    bool rob0_present = false;
    while (!rob0_present)
    {
        //https://stackoverflow.com/questions/26785675/ros-get-current-available-topic-in-code-not-command
        ros::master::V_TopicInfo master_topics;
        ros::master::getTopics(master_topics);

        uint8_t id = 1;
        for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++)
        {
            const ros::master::TopicInfo& info = *it;
            std::string topicName = info.name;
            //std::cout << "topic_" << it - master_topics.begin() << ": " << info.name << std::endl;

            if (std::regex_match (topicName, std::regex("^\\/carla\\/vehicle\\/([0-9]*)\\/odometry$") ))
            {
                std::cout << "subscribe to " << topicName << " with id " << std::to_string(id) << std::endl;

                //ros::Subscriber robX_sub = n.subscribe<nav_msgs::Odometry>(topicName, 1000, boost::bind(callback_robX, _1, id));
                robX_subs.push_back(n.subscribe<nav_msgs::Odometry>(topicName, 1000, boost::bind(&SzenarioHandler::callback_robX, this, _1, id)));

                ++id;
            }
            else if (std::regex_match (topicName, std::regex("^\\/carla\\/ego_vehicle\\/odometry$") ))
            {
                rob0_present = true;
                std::cout << "REGX ego_vehicle MATCH" << std::endl;
            }
        }
        if (!rob0_present)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    goal_sub = n.subscribe<geometry_msgs::PoseStamped>("simpleGoal", 1000, boost::bind(&SzenarioHandler::callback_goal, this, _1));
}

void SzenarioHandler::publishRoadSzenario()
{
    const std::lock_guard<std::mutex> lock(rs_mtx);

    active_rs->publishGoal();
    active_rs->publishObstacles();
    active_rs->publishViaPoints();
    active_rs->adaptTebParams();
}

void SzenarioHandler::callback_rob0(const nav_msgs::Odometry::ConstPtr& msg)
{
    //std::cout << "I heard: " << msg->pose.pose.position.x << std::endl;

    const std::lock_guard<std::mutex> lock(rs_mtx);
    active_rs->setCarPosition(*msg);
}

void SzenarioHandler::callback_robX(const nav_msgs::Odometry::ConstPtr& msg, uint8_t id)
{
    //std::cout << "I heard: " << msg->pose.pose.position.x << " from id " << std::to_string(id) << std::endl;

    const std::lock_guard<std::mutex> lock(rs_mtx);
    active_rs->setObstacle(*msg, id);
}

void SzenarioHandler::callback_roadSzene(const car_szenario::RoadInfo::ConstPtr& msg)
{
    std::cout << "I heard: " << msg->szeneType << std::endl;

    const std::lock_guard<std::mutex> lock(rs_mtx);

    if (rs_vec.count(msg->szeneType))
    {
        active_rs = rs_vec[msg->szeneType];
        active_rs->setCurrentRoadInfo(*msg);
        active_rs->setGlobalGoal(goal);
        active_rs->setTebParams();
    }
    else
    {
        ROS_WARN("No szenario found for %s", msg->szeneType.c_str());
    }

}

void SzenarioHandler::callback_goal(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    //std::cout << "New goal: " << msg->pose.position.x << ", " << msg->pose.position.x << std::endl;
    goal = *msg;

    const std::lock_guard<std::mutex> lock(rs_mtx);
    active_rs->setGlobalGoal(*msg);
}

void SzenarioHandler::setupRoadSzenarios(ros::NodeHandle n)
{
    const std::lock_guard<std::mutex> lock(rs_mtx);

    //rs_vec["DEFAULT"]=RoadSzenario(n);
    ADD_ROADSZENARIO("DEFAULT", RoadSzenario);
    ADD_ROADSZENARIO("NARROWING", NarrowingSzenario);
    ADD_ROADSZENARIO("DRIVEWAY", DrivewaySzenario);
    ADD_ROADSZENARIO("TINTERSECTION", TIntersectionSzenario);
    //add more

    //choose DEFAULT as initial active Szenario
    active_rs = rs_vec["DEFAULT"];

    roadSzene_sub = n.subscribe<car_szenario::RoadInfo>("CurrentRoadSzene", 1000, boost::bind(&SzenarioHandler::callback_roadSzene, this, _1));
}
