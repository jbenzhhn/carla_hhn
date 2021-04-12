#!/home/automotive/venv/carla-venv/bin/python3.7

# Author: Johannes Benz, Adrian Auer

import glob
import os
import sys
import time
import rospy
import random
import time
from geometry_msgs.msg import Twist

print(sys.version_info.major)
print(sys.version_info.minor)
print(sys.path)

sys.path.remove('/home/automotive/carla0.9.11/carla/PythonAPI/carla/dist/python2.7/carla-0.9.11-py2.7-linux-x86_64.egg')
sys.path.append('/home/automotive/carla0.9.11/carla/dist/carla-0.9.11-py3.6-linux-x86_64.egg') 

import carla

client = carla.Client('localhost', 2000)
client.set_timeout(2.0)
position_of_ego_vehcile = 1

# get the argument for the starting position of the ego vehcile (defaul = 1)
if len(sys.argv) > 1:
    arg = int(sys.argv[1])
    position_of_ego_vehcile = arg

print("position of ego vehicle (argument)")
print(position_of_ego_vehcile)

rospy.init_node('ego_vehicle_spawner')


# Once we have a client we can retrieve the world that is currently
# running.
world = client.get_world()

#Check the existing ego vehicles
spawn_new_ego_vehicle = True
actor_list = world.get_actors()
vehicle_list = actor_list.filter('vehicle.tesla.model3')
length = len(vehicle_list)
print("List of existing ego vehicles:", length)

for actor in actor_list:
    at = actor.attributes 
    role_name = at.get('role_name')
    if role_name == 'ego_vehicle':
        spawn_new_ego_vehicle = False
        vehicle = actor

if spawn_new_ego_vehicle == True:
    print("A new ego vehicle has to be spawned")
else:
    print("No ego vehciles have to be spawn!")

#Spawn a new ego vehicle, if there are no exiting ego vehicles in the Game
if spawn_new_ego_vehicle == True:

    # The world contains the list blueprints that we can use for adding new
    # actors into the simulation.
    blueprint_library = world.get_blueprint_library()

    # Now let's filter all the blueprints of type 'vehicle' and choose one
    # at random.
    bp = random.choice(blueprint_library.filter('model3'))
    bp.set_attribute('role_name', 'ego_vehicle')

    # A blueprint contains the list of attributes that define a vehicle's
    # instance, we can read them and modify some of them. For instance,
    # let's randomize its color.

    # Now we need to give an initial transform to the vehicle. We choose a
    # random transform from the list of recommended spawn points of the map.
    transform = random.choice(world.get_map().get_spawn_points())

    # So let's tell the world to spawn the vehicle.
    vehicle = world.spawn_actor(bp, transform)

    # Add a camera in the front 
    camera_bp = blueprint_library.find('sensor.camera.rgb')
    camera_transform = carla.Transform(carla.Location(x=1.5, z=2.4))
    camera = world.spawn_actor(camera_bp, camera_transform, attach_to=vehicle)

    #Add a center lidar_sensor
    lidar_bp = blueprint_library.find('sensor.lidar.ray_cast')
    lidar_center_transform = carla.Transform(carla.Location(x=0, z=2))
    lidar_center = world.spawn_actor(lidar_bp, lidar_center_transform, attach_to=vehicle)

    print("A new ego vehcile is succesfully spawn!")

# Now we need to give an initial transform to the vehicle. We choose a
# random transform from the list of recommended spawn points of the map.
transform = random.choice(world.get_map().get_spawn_points())
blueprint_library = world.get_blueprint_library()

vehicle.set_autopilot(False)
vehicle_control = vehicle.get_control()
vehicle_control.hand_brake = True
vehicle_control.throttle = 0.0
vehicle_control.steer = 0.0
vehicle.apply_control(vehicle_control)


light_state_start = vehicle.get_light_state()
ls_wait = light_state_start.NONE
vehicle.set_light_state(ls_wait)

# Set the Location of the ego vehicle
# 1 = at the middle intersection (default)
# 2 = Narrow Lane Scenario

time.sleep(0.5)

if position_of_ego_vehcile == 1:
    transform.rotation.yaw = -90
    transform.location.x = 1.4
    transform.location.y = 20
    transform.rotation.pitch = 0
    transform.rotation.roll = 0
    vehicle.set_transform(transform)

elif position_of_ego_vehcile == 2:
    transform.rotation.yaw = -75
    transform.rotation.pitch = 0
    transform.rotation.roll = 0
    transform.location.x = -239.00
    transform.location.y = -9.70
    vehicle.set_transform(transform)

    number_of_cars = [0,1,2]
    parking_cars_posiions_x   = [-217.5,-227.6,-223.7]
    parking_cars_posiions_y   = [-56,-33,-43]
    parking_cars_posiions_yaw = [78, 82, 86]
    
    # for cars in number_of_cars:
    #     print("cars:", cars)
    #     transform.rotation.yaw = parking_cars_posiions_yaw[cars]
    #     transform.rotation.pitch = 0
    #     transform.rotation.roll = 0
    #     transform.location.x = parking_cars_posiions_x[cars]
    #     transform.location.y = parking_cars_posiions_y[cars]
    #     transform.location.z = 2.0
    #     vehicle.set_transform(transform)
    #     bp_other = random.choice(blueprint_library.filter('model3'))
    #     vehicle = world.spawn_actor(bp_other, transform)
	
    # 	# Let's put the vehicle to drive around.
    #     vehicle.set_autopilot(False)
    #     vehicle_control = vehicle.get_control()
    #     vehicle_control.hand_brake = True
    #     vehicle.apply_control(vehicle_control)
      


print("Position of ego vehicle is:", transform)

light_state = vehicle.get_light_state()
cmd_vel = rospy.wait_for_message('cmd_vel', Twist)
vehicle_control.hand_brake = False
ls_start_driving = light_state.All
vehicle.set_light_state(ls_start_driving)