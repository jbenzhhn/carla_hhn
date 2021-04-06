#!/usr/bin/env python

import rospy, math, random, re
from tf.transformations import quaternion_from_euler
from geometry_msgs.msg import Point, Twist, PolygonStamped, Quaternion, QuaternionStamped, TwistWithCovariance, Point32, PoseStamped
from nav_msgs.msg import Odometry, Path
from costmap_converter.msg import ObstacleArrayMsg, ObstacleMsg
from car_szenario.msg import RoadInfo

import time

szenarios = list()
rob0_pose_x = -1
rob0_pose_y = -1

class Szenario:

    def __init__(self, xMin, xMax, yMin, yMax, type):
        self.xMin = xMin
        self.xMax = xMax
        self.yMin = yMin
        self.yMax = yMax
        self.type = type
        self.startPoints = list()
        self.endPoints = list()

    def addStartEnd(self, xStart, yStart, xEnd, yEnd):
        if xStart != None and yStart != None:
            start = Point()
            start.x = xStart
            start.y = yStart
            self.startPoints.append(start)
        if xEnd != None and yEnd != None:
            end = Point()
            end.x = xEnd
            end.y = yEnd
            self.endPoints.append(end)

    def isInRange(self, x, y):
        #print("Checking", x, y, "in", self.xMin, self.xMax, self.yMin, self.yMax)
        if x > self.xMin and x < self.xMax and y > self.yMin and y < self.yMax:
            return True

        return False


def genSzenario(type, xMin, xMax, yMin, yMax, xStart=None, yStart=None, xEnd=None, yEnd=None):
    sz = Szenario(xMin, xMax, yMin, yMax, type)
    sz.addStartEnd(xStart, yStart, xEnd, yEnd)

    return sz

def fillSzenarios():
    global szenarios
    #sz = genSzenario("NARROWING", 20, 130, 45, 70, 87, 50, 119, 50)
    szenarios.append(genSzenario("NARROWING", 5, 130, 45, 70, 87, 50, 119, 50))
    #sz = genSzenario("DRIVEWAY", 230, 350, 20, 40)
    szenarios.append(genSzenario("DRIVEWAY", 250, 350, 20, 40, 285, 32.5, 325, 32.5))

def callback_rob0_base_pose_ground_truth(base_pose_ground_truth):
    global rob0_pose_x
    global rob0_pose_y
    rob0_pose_x = base_pose_ground_truth.pose.pose.position.x
    rob0_pose_y = base_pose_ground_truth.pose.pose.position.y

def init_subscribers():
    rospy.init_node("szenario_provider")

    sub_rob0 = rospy.Subscriber("/robot_0/base_pose_ground_truth", Odometry, callback_rob0_base_pose_ground_truth)

    #road = RoadInfo()
    #road.szeneType = "DRIVEWAY"

    fillSzenarios()

    szene_pub = rospy.Publisher('CurrentRoadSzene', RoadInfo, queue_size = 10)
    r = rospy.Rate(10)

    lastId = -2;
    while not rospy.is_shutdown():
        road = RoadInfo()

        found = False
        for id, sz in enumerate(szenarios):
            if sz.isInRange(rob0_pose_x, rob0_pose_y):
                road.szeneType = sz.type
                road.startPoints = sz.startPoints.copy()
                road.endPoints = sz.endPoints.copy()
                newId = id
                found = True
                break;
        if not found:
            newId = -1
            road.szeneType = "DEFAULT"

        if newId != lastId:
            szene_pub.publish(road)
            lastId = newId
        r.sleep()


if __name__ == '__main__':
    try:
        #time.sleep(0.5) #workaround because subscribers were created before topic are presend from stage
        init_subscribers()
    except rospy.ROSInterruptException:
        pass

