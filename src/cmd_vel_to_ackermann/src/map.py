#!/bin/env python

# ----------------- BEGIN LICENSE BLOCK ---------------------------------
#
# Copyright (c) 2019-2020 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
# ----------------- END LICENSE BLOCK -----------------------------------

"""
Simple unittest module to ensure that the Python binding is functional
"""

import unittest
import xmlrunner
import ad_map_access as ad
import numpy as np
import cv2 as cv
import rospy
import sys
import os

# map_global
# Create a white image for map_route
image_scale = 10
image_width = 1000 * image_scale
image_hight = 1000 * image_scale
img = np.ones((image_width, image_hight, 3), np.uint8)
img = img * 255

# resolution in m/pixel
resolution = 1/image_scale

ad.map.access.init("test_files/FirstMap.txt")


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
            cv.line(img, (int(float(str(Edge_Left_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Left_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_end.z))*image_scale)+int(image_hight/2)), (0, 0, 0), 1)

    # print the right edges of lanes
    for point in range(len(Edge_right.ecefEdge) - 1):
        Edge_Right_start = Edge_right.ecefEdge[point]
        Edge_Right_end = Edge_right.ecefEdge[point + 1]
        if lane.type == ad.map.lane.LaneType.NORMAL:
            cv.line(img, (int(float(str(Edge_Right_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Right_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_end.z))*image_scale)+int(image_hight/2)), (0, 0, 0), 1)

cv.imwrite('/home/automotive/catkin_ws/src/carla_navigation/maps/map_global.png', img)




# map_route
# Create a white image for map_route
image_scale = 10
image_width = 1000 * image_scale
image_hight = 1000 * image_scale
img = np.ones((image_width, image_hight, 3), np.uint8)
img = img * 255

# resolution in m/pixel
resolution = 1/image_scale

ad.map.access.init("test_files/FirstMap.txt")

# route planning
routingStart = ad.map.point.createParaPoint(ad.map.lane.LaneId(30149), ad.physics.ParametricValue(0.1))
routingEnd = ad.map.point.createParaPoint(ad.map.lane.LaneId(380149), ad.physics.ParametricValue(1))
routemode = ad.map.route.RouteCreationMode.SameDrivingDirection
routeResult = ad.map.route.planRoute(routingStart, routingEnd, routemode)

# Calculate complete distance and save all laneIds
routeLength = ad.physics.Distance(0)
lane_id_array = []

for x in range(len(routeResult.roadSegments)):
    le = ad.map.route.calcLength(routeResult.roadSegments[x])
    routeLength = routeLength + le
    road_segment = routeResult.roadSegments[x]
    lane_segment = road_segment.drivableLaneSegments[0]
    lane_interval = lane_segment.laneInterval
    lane_id = lane_interval.laneId
    lane_id_array.append(lane_id)

    # successors = lane_segment.successors
    # predecessors = lane_segment.predecessors

print(routeLength)


# Get the left and right edge of the lanes
for lane_id in lane_id_array:
    lane = ad.map.lane.getLane(lane_id)
    Edge_left = lane.edgeLeft
    Edge_right = lane.edgeRight

    for point in range(len(Edge_left.ecefEdge)-1):
        Edge_Left_start = Edge_left.ecefEdge[point]
        Edge_Left_end = Edge_left.ecefEdge[point+1]
        Edge_Right_start = Edge_right.ecefEdge[point]
        Edge_Right_end = Edge_right.ecefEdge[point + 1]

# Print the Borders with Open-CV

        cv.line(img, (int(float(str(Edge_Left_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Left_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_end.z))*image_scale)+int(image_hight/2)), (0, 0, 0), 1)
        cv.line(img, (int(float(str(Edge_Right_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Right_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_end.z))*image_scale)+int(image_hight/2)), (0, 0, 0), 1)

#cv.imshow('test', img)
cv.imwrite('/home/automotive/catkin_ws/src/carla_navigation/maps/map_route.png', img)

# cv.waitKey(0)


#self.assertEqual(int(float(routeLength)), 4)

#print(routeResult)
#ad.map.access.cleanup()



