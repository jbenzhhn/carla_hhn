#!/home/automotive/venv/carlamap/bin/python3.6

"""
Simple unittest module to ensure that the Python binding is functional
"""
import sys
import unittest
import xmlrunner
import rospy
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Odometry
import ad_map_access as ad
import numpy as np
import cv2 as cv
import os


#import the own map
ad.map.access.init("/home/automotive/carlamap/test_files/FirstMap.txt")


#################################################   Maps   ##################################################
# map_global
# Create a white image for map_route
image_scale = 10
image_width = 1000 * image_scale
image_hight = 1000 * image_scale
img_glob = np.ones((image_width, image_hight, 3), np.uint8)
img_glob = img_glob * 255

# resolution in m/pixel
resolution = 1/image_scale

# get all Lane IDs in an array
lanes = ad.map.lane.getLanes()

# Get the left and right edge of the lanes
for lane_id in lanes:
    lane = ad.map.lane.getLane(lane_id)
    Edge_left = lane.edgeLeft
    Edge_right = lane.edgeRight

    # print the left edges of lanes
    for point in range(len(Edge_left.ecefEdge)-1):
        Edge_Left_start = Edge_left.ecefEdge[point]
        Edge_Left_end = Edge_left.ecefEdge[point+1]
        if lane.type == ad.map.lane.LaneType.NORMAL:
            cv.line(img_glob, (int(float(str(Edge_Left_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Left_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_end.z))*image_scale)+int(image_hight/2)), (0, 0, 0), 1)

    # print the right edges of lanes
    for point in range(len(Edge_right.ecefEdge)-1):
        Edge_Right_start = Edge_right.ecefEdge[point]
        Edge_Right_end = Edge_right.ecefEdge[point+1]
        if lane.type == ad.map.lane.LaneType.NORMAL:
            cv.line(img_glob, (int(float(str(Edge_Right_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Right_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_end.z))*image_scale)+int(image_hight/2)), (0, 0, 0), 1)



# save the picture as mapglobal.png
cv.imwrite('/home/automotive/catkin_ws/src/carla_navigation/maps/map_global.png', img_glob)

print("Global Map image saved succesfully!")



