#!/home/automotive/venv/carlamap/bin/python3.6


"""
Author: Johannes Benz and Adrian Auer

Tool to get informations of an .xodr-file
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
from std_msgs.msg import Float64
from carla_msgs.msg import CarlaTrafficLightStatusList, CarlaTrafficLightInfoList

#import the own map
ad.map.access.init("/home/automotive/carlamap/test_files/FirstMap.txt")

lanes = ad.map.lane.getLanes()

for lane in lanes:
    landmarks = ad.map.landmark.getVisibleLandmarks(lane)

#start map_server_node
rospy.init_node('opendrive_map_server')

#get reference height of one CEFpoint
lanes_ref = ad.map.lane.getLanes()
lane_ref = ad.map.lane.getLane(lanes_ref[0])
ecef_edge_ref = lane_ref.edgeLeft
ecef_point_ref = ecef_edge_ref.ecefEdge[0]#print(ecef_point_ref)

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

#  map_route
# Create a white image for map_route
image_scale = 10
image_width = 1000 * image_scale
image_hight = 1000 * image_scale
img_route = np.ones((image_width, image_hight, 3), np.uint8)
img_route = img_route * 255

# resolution in m/pixel
resolution = 1/image_scale

#################################################   Routing Points  ###########################################

## Route Start
# wait for ego_position
ego_position = rospy.wait_for_message('carla/ego_vehicle/odometry', Odometry)

# create ECEF-Start-Point
start_point = ad.map.point.ECEFPoint()
start_point.x = ecef_point_ref.x
start_point.y = ad.map.point.ECEFCoordinate(ego_position.pose.pose.position.x)
start_point.z = ad.map.point.ECEFCoordinate(ego_position.pose.pose.position.y)

# map matching
geopoint_start = ad.map.point.toGeo(start_point)
mapMatching = ad.map.match.AdMapMatching()
mapMatchingResult_start = mapMatching.getMapMatchedPositions(geopoint_start, ad.physics.Distance(0.01), ad.physics.Probability(0.05))
print(len(mapMatchingResult_start), "Starting Point was found!")
routingStart = mapMatchingResult_start[0].lanePoint.paraPoint

## Route End
# wait for navgoal
navgoal = rospy.wait_for_message('/simpleGoal', PoseStamped)

# create ECEF-Goal-Point
goal_point = ad.map.point.ECEFPoint()
goal_point.x = ecef_point_ref.x
goal_point.y = ad.map.point.ECEFCoordinate(navgoal.pose.position.x)
goal_point.z = ad.map.point.ECEFCoordinate(navgoal.pose.position.y)

# map matching
geopoint_end = ad.map.point.toGeo(goal_point)
mapMatching_end = ad.map.match.AdMapMatching()
mapMatchingResult_end = mapMatching_end.getMapMatchedPositions(geopoint_end, ad.physics.Distance(1), ad.physics.Probability(0.05))
routingEnd = mapMatchingResult_end[0].lanePoint.paraPoint

#################################################   Routing  ###########################################

# Set the Route Mode
routemode = ad.map.route.RouteCreationMode.SameDrivingDirection

# Routing from Start Point to End Point
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

# Print the length of the Route
print('Length of the Route:')
print(routeLength)

# Get the left and right edge of the Routing lanes
for lane_id in lane_id_array:
    lane = ad.map.lane.getLane(lane_id)
    Edge_left = lane.edgeLeft
    Edge_right = lane.edgeRight

    for point in range(len(Edge_left.ecefEdge)-1):
        Edge_Left_start = Edge_left.ecefEdge[point]
        Edge_Left_end = Edge_left.ecefEdge[point+1]
        # Print the Borders with Open-CV
        cv.line(img_route, (int(float(str(Edge_Left_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Left_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_end.z))*image_scale)+int(image_hight/2)), (255, 0, 0), 1)
        cv.line(img_glob, (int(float(str(Edge_Left_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Left_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Left_end.z))*image_scale)+int(image_hight/2)), (255, 0, 0), 1)

    for point in range(len(Edge_right.ecefEdge)-1):
        Edge_Right_start = Edge_right.ecefEdge[point]
        Edge_Right_end = Edge_right.ecefEdge[point+1]
        # Print the Borders with Open-CV
        cv.line(img_route, (int(float(str(Edge_Right_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Right_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_end.z))*image_scale)+int(image_hight/2)), (255, 0, 0), 1)
        cv.line(img_glob, (int(float(str(Edge_Right_start.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_start.z))*image_scale)+int(image_hight/2)), (int(float(str(Edge_Right_end.y))*image_scale)+int(image_width/2), -int(float(str(Edge_Right_end.z))*image_scale)+int(image_hight/2)), (255, 0, 0), 1)

cv.imwrite('/home/automotive/catkin_ws/src/carla_navigation/maps/map_route.png', img_route)

############### Get the Traffic Lights on the Route ###############################

# Get Lane Ids of the Route
routeLength = ad.physics.Distance(0)
lane_id_array = []
print('The Route has the following Lane Ids:')

for road_segment in routeResult.roadSegments:
    le = ad.map.route.calcLength(routeResult.roadSegments[x])
    routeLength = routeLength + le
    #road_segment = routeResult.roadSegments[x]
    lane_segment = road_segment.drivableLaneSegments[0]
    lane_interval = lane_segment.laneInterval
    lane_id = lane_interval.laneId
    print(lane_id)
    lane_id_array.append(lane_id)

## Get Contact Lanes of the Route Lanes
lanes_with_TL = []

print("Cl of Lanes with TL")
# Save the Contact Lane List for each Road in the array contact_lane_array
for lane_id in lane_id_array:
    lane = ad.map.lane.getLane(lane_id)
    contact_lane_list = lane.contactLanes
    #contact_lane_array.append(contact_lane_list)
    for cl in contact_lane_list:
        types = cl.types
        #print(cl)
        if types[0] == ad.map.lane.ContactType.TRAFFIC_LIGHT:
            lanes_with_TL.append(lane_id)

print(lanes_with_TL)

# Get the Distance from Car to the Traffic Light
TL_StartPoint = routingStart #hierfür später die aktuelle Position des Autos eintragen
TL_ParaPoint = ad.map.point.createParaPoint(ad.map.lane.LaneId(lanes_with_TL[0]), ad.physics.ParametricValue(0))

route_to_TL = ad.map.route.planRoute(TL_StartPoint, TL_ParaPoint, routemode)

distance_to_TL = ad.physics.Distance(0)
print('Number of Road Segments:')
print(len(route_to_TL.roadSegments))

for x in range(len(route_to_TL.roadSegments)):
    road_segment = route_to_TL.roadSegments[x]
    lane_segment = road_segment.drivableLaneSegments[0]
    lane_interval = lane_segment.laneInterval
    distance_to_TL = distance_to_TL + ad.map.route.calcLength(lane_interval)

print('Distance to Traffic Light:')
print(distance_to_TL)

# show global_map_with route
#cv.namedWindow("global_map", cv.WND_PROP_FULLSCREEN)
#cv.setWindowProperty("global_map",cv.WND_PROP_FULLSCREEN,cv.WINDOW_FULLSCREEN)
#cv.imshow('global_map',img_glob)
#cv.waitKey(0)
cv.imwrite('/home/automotive/catkin_ws/src/carla_navigation/maps/map_with_route.png', img_glob)

global traffic_light_ahead
global carla_tl_id
global tl_y_pos
global tl_status
global tl_list
traffic_light_ahead = 1

tl_status = 1 # default value for tl_status

#Traffic light y-positions
y_1 = -5.260565757751465
y_2 = -3.279059648513794
y_3 = 14.378301620483398
y_4 = 11.247918128967285
y_5 = 12.394646644592285

# Traffic Light Array
traffic_light_ids = np.array([[336, y_3], [337, y_3], [329, y_3], [340, y_2], [339, y_2], [338, y_2], [330, y_1], [332, y_1], [331, y_1], [333, y_4], [335, y_5], [334, y_5]])
print(traffic_light_ids)


tl_list_msg = rospy.wait_for_message('carla/traffic_lights_info', CarlaTrafficLightInfoList)
tl_list = tl_list_msg.traffic_lights


def callback_traffic_light_state(tl_list_msg):
    global carla_tl_id
    global tl_status
    tl_list = tl_list_msg.traffic_lights
    for tl in tl_list:
        if tl.id == carla_tl_id:
            tl_status = tl.state

def callback_ego_postion(ego_odom):
    global traffic_light_ahead
    global carla_tl_id
    global tl_status
    global tl_y_pos
    global tl_list
    # read position of ego_vehicle
    position_point = ad.map.point.ECEFPoint()
    position_point.x = ecef_point_ref.x
    position_point.y = ad.map.point.ECEFCoordinate(ego_odom.pose.pose.position.x)
    position_point.z = ad.map.point.ECEFCoordinate(ego_odom.pose.pose.position.y)

    #calculate live route to destination point
    geopoint_position = ad.map.point.toGeo(position_point)
    mapMatching = ad.map.match.AdMapMatching()
    mapMatchingResult_start = mapMatching.getMapMatchedPositions(geopoint_position, ad.physics.Distance(0.1),
                                                                 ad.physics.Probability(0.05))
    position_live_para = mapMatchingResult_start[0].lanePoint.paraPoint
    live_route = ad.map.route.planRoute(position_live_para, routingEnd, routemode)

    lane_id_array = []
    #Save alla lane ids of the Route in the array lane_id_array
    for road_segment in live_route.roadSegments:
        lane_segment = road_segment.drivableLaneSegments[0]
        lane_interval = lane_segment.laneInterval
        lane_id = lane_interval.laneId
        lane_id_array.append(lane_id)

    lanes_with_TL = []
    traffic_light_id_list = []
    # Save the Contact Lane List for each Road in the array contact_lane_array
    for lane_id in lane_id_array:
        lane = ad.map.lane.getLane(lane_id)
        contact_lane_list = lane.contactLanes
        # contact_lane_array.append(contact_lane_list)
        for cl in contact_lane_list:
            types = cl.types
            # print(cl)
            if types[0] == ad.map.lane.ContactType.TRAFFIC_LIGHT:
                lanes_with_TL.append(lane_id)
                traffic_light_id_list.append(cl.trafficLightId)

    # find corresponding trafic light id in carla
    if len(traffic_light_id_list) > 0:
        tl_id = str(traffic_light_id_list[0])
        index = np.where(traffic_light_ids == int(tl_id))
        index_row = index[0]
        tl_y_pos = traffic_light_ids[index_row[0], 1]

    #search for traffic light id in tl_pos_list
    for tl in tl_list:
        if tl.transform.position.y == tl_y_pos:
            carla_tl_id = tl.id

    #Information, that the car drove over a Traffic Light Contact Lane
    if lane_id_array[0] == lanes_with_TL[0]:
        traffic_light_ahead = 0
        print("Traffic Light reached")

    if traffic_light_ahead == 1:
        # map matching
        geopoint_position = ad.map.point.toGeo(position_point)
        mapMatching = ad.map.match.AdMapMatching()
        mapMatchingResult_start = mapMatching.getMapMatchedPositions(geopoint_position, ad.physics.Distance(0.01),
                                                                     ad.physics.Probability(0.05))
        position_live_para = mapMatchingResult_start[0].lanePoint.paraPoint

        #Decide, if you need the beginnin or the end of the lane with Traffic Light (depends on Lane Orientation)
        x = 0
        y = 1
        para_value = 1
        TL_ParaPoint_1 = ad.map.point.createParaPoint(ad.map.lane.LaneId(lanes_with_TL[0]),
                                                      ad.physics.ParametricValue(x))
        TL_ParaPoint_2 = ad.map.point.createParaPoint(ad.map.lane.LaneId(lanes_with_TL[0]),
                                                      ad.physics.ParametricValue(y))

        route_to_tl_live_1 = ad.map.route.planRoute(position_live_para, TL_ParaPoint_1, routemode)
        route_to_tl_live_2 = ad.map.route.planRoute(position_live_para, TL_ParaPoint_2, routemode)

        distance_to_TL_1 = ad.physics.Distance(0)
        for x in range(len(route_to_tl_live_1.roadSegments)):
            road_segment = route_to_tl_live_1.roadSegments[x]
            lane_segment = road_segment.drivableLaneSegments[0]
            lane_interval = lane_segment.laneInterval
            distance_to_TL_1 = distance_to_TL_1 + ad.map.route.calcLength(lane_interval)

        distance_to_TL_2 = ad.physics.Distance(0)
        for x in range(len(route_to_tl_live_2.roadSegments)):
            road_segment = route_to_tl_live_2.roadSegments[x]
            lane_segment = road_segment.drivableLaneSegments[0]
            lane_interval = lane_segment.laneInterval
            distance_to_TL_2 = distance_to_TL_2 + ad.map.route.calcLength(lane_interval)

        if distance_to_TL_1 > distance_to_TL_2:
            route_to_tl_live = route_to_tl_live_2
        else:
            route_to_tl_live = route_to_tl_live_1

        #calculate the live distance to the Traffic Light and publish it
        distance_to_TL = ad.physics.Distance(0)
        for x in range(len(route_to_tl_live.roadSegments)):
            road_segment = route_to_tl_live.roadSegments[x]
            lane_segment = road_segment.drivableLaneSegments[0]
            lane_interval = lane_segment.laneInterval
            distance_to_TL = distance_to_TL + ad.map.route.calcLength(lane_interval)

        tl_colors = ['red', 'yellow', 'green']
        print("Traffic light ahead in: ", distance_to_TL, "m ", "with status", tl_colors[tl_status])
        pub.publish(distance_to_TL)
    else:
        pub.publish(0.0)

#Call the callback_ego_position Function and subscribe the live Odometry of the Ego Vehicle
rospy.Subscriber("carla/ego_vehicle/odometry", Odometry, callback_ego_postion)
rospy.Subscriber("carla/traffic_lights", CarlaTrafficLightStatusList, callback_traffic_light_state)

#publish the Distance to the Traffic Light on the topic: carla/ego_vehicle/traffic_light/distance
pub = rospy.Publisher("carla/ego_vehicle/traffic_light/distance", Float64, queue_size=10)
# spin() simply keeps python from exiting until this node is stopped
rospy.spin()
