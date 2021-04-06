   #include <ros/ros.h>
   #include <tf/transform_broadcaster.h>
   #include <nav_msgs/Odometry.h>
   #include "odom_tf.hh"

ros::Subscriber odom_sub;
ros::Publisher odom_shift_pub;

struct Quaternion {
    double w, x, y, z;
};

struct EulerAngles {
    double roll, pitch, yaw;
};

EulerAngles ToEulerAngles(Quaternion q) {
    EulerAngles angles;

    // roll (x-axis rotation)
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    angles.roll = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (std::abs(sinp) >= 1)
        angles.pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.pitch = std::asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    angles.yaw = std::atan2(siny_cosp, cosy_cosp);

    return angles;
}

    void odom_callback(const nav_msgs::Odometry odom)
    {
      x = odom.pose.pose.position.x;
      y = odom.pose.pose.position.y;
      tf::poseMsgToTF(odom.pose.pose, pose);
      double yaw_angle = tf::getYaw(pose.getRotation());
      th = yaw_angle;

      nav_msgs::Odometry odom_shifted;
      odom_shifted = odom;

      Quaternion shifted_q;
      shifted_q.x = odom_shifted.pose.pose.orientation.x;
      shifted_q.y = odom_shifted.pose.pose.orientation.y;
      shifted_q.z = odom_shifted.pose.pose.orientation.z;
      shifted_q.w = odom_shifted.pose.pose.orientation.w;

      EulerAngles angles_odom = ToEulerAngles(shifted_q);


      odom_shifted.pose.pose.position.x = x - 1.5 * std::cos(angles_odom.yaw);
      odom_shifted.pose.pose.position.y = y - 1.5 * std::sin(angles_odom.yaw);
      odom_shift_pub.publish(odom_shifted);
    }


   int main(int argc, char** argv){
    ros::init(argc, argv, "odometry_publisher");

     ros::NodeHandle n;
     odom_sub = n.subscribe("carla/ego_vehicle/odometry", 1, &odom_callback);
     tf::TransformBroadcaster odom_broadcaster;
     odom_shift_pub = n.advertise<nav_msgs::Odometry>("carla/ego_vehicle/odometry_shifted", 1000);


     ros::Time current_time, last_time;
     current_time = ros::Time::now();
     last_time = ros::Time::now();



     ros::Rate r(50.0);
     while(n.ok()){

      ros::spinOnce();               // check for incoming messages
      current_time = ros::Time::now();



       //since all odometry is 6DOF we'll need a quaternion created from yaw
       geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

       //first, we'll publish the transform over tf
       geometry_msgs::TransformStamped odom_trans;
       odom_trans.header.stamp = current_time;
       odom_trans.header.frame_id = "map";
       odom_trans.child_frame_id = "base_link";



       odom_trans.transform.translation.z = 0.0;
       odom_trans.transform.rotation = odom_quat;

       Quaternion quat;
       quat.w = odom_quat.w;
       quat.x = odom_quat.x;
       quat.y = odom_quat.y;
       quat.z = odom_quat.z;

       EulerAngles angles = ToEulerAngles(quat);


       odom_trans.transform.translation.x = x - 1.5 * std::cos(angles.yaw);
       odom_trans.transform.translation.y = y - 1.5 * std::sin(angles.yaw);
       //odom_trans.transform.translation.x = x;
       //odom_trans.transform.translation.y = y;

       //send the transform
       odom_broadcaster.sendTransform(odom_trans);



      last_time = current_time;
      r.sleep();
    }
  }
