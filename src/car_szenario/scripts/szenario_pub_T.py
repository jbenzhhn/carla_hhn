#!/usr/bin/env python

import rospy, math, random, re
from tf.transformations import quaternion_from_euler
from geometry_msgs.msg import Point, Twist, PolygonStamped, Quaternion, QuaternionStamped, TwistWithCovariance, Point32, PoseStamped
from nav_msgs.msg import Odometry, Path
from costmap_converter.msg import ObstacleArrayMsg, ObstacleMsg
from car_szenario.msg import RoadInfo

import time


def init_subscribers():
  rospy.init_node("szenario_provider")

  road = RoadInfo()
  road.szeneType = "TINTERSECTION"
  start = Point()
  start.x = 40 #20
  start.y = 50
  end = Point()
  end.x = 55
  end.y = 50
  road.startPoints.append(start)
  road.endPoints.append(end)

  szene_pub = rospy.Publisher('/provider/CurrentRoadSzene', RoadInfo, queue_size = 10)
  time.sleep(1)
  #r = rospy.Rate(10)

  #while not rospy.is_shutdown():
  szene_pub.publish(road)
  #rospy.spinOnce()
  #  r.sleep()


if __name__ == '__main__':
  try:
    #time.sleep(0.5) #workaround because subscribers were created before topic are presend from stage
    init_subscribers()
  except rospy.ROSInterruptException:
    pass

