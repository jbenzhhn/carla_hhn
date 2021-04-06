# Install script for directory: /home/automotive/catkin_ws/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/automotive/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/automotive/catkin_ws/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/automotive/catkin_ws/install" TYPE PROGRAM FILES "/home/automotive/catkin_ws/build/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/automotive/catkin_ws/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/automotive/catkin_ws/install" TYPE PROGRAM FILES "/home/automotive/catkin_ws/build/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/automotive/catkin_ws/install/setup.bash;/home/automotive/catkin_ws/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/automotive/catkin_ws/install" TYPE FILE FILES
    "/home/automotive/catkin_ws/build/catkin_generated/installspace/setup.bash"
    "/home/automotive/catkin_ws/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/automotive/catkin_ws/install/setup.sh;/home/automotive/catkin_ws/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/automotive/catkin_ws/install" TYPE FILE FILES
    "/home/automotive/catkin_ws/build/catkin_generated/installspace/setup.sh"
    "/home/automotive/catkin_ws/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/automotive/catkin_ws/install/setup.zsh;/home/automotive/catkin_ws/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/automotive/catkin_ws/install" TYPE FILE FILES
    "/home/automotive/catkin_ws/build/catkin_generated/installspace/setup.zsh"
    "/home/automotive/catkin_ws/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/automotive/catkin_ws/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/automotive/catkin_ws/install" TYPE FILE FILES "/home/automotive/catkin_ws/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/automotive/catkin_ws/build/gtest/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/carla_mbf/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/carla_navigation/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach-master/executive_smach/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach_visualization-kinetic-devel/executive_smach_visualization/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/gazebo_ros_pkgs/gazebo_dev/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/gazebo_ros_pkgs/gazebo_ros_pkgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/image_common/image_common/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/move_base_flex/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/odom_pub/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/odom_tf/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/ros_control/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/rqt_controller_manager/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach-master/smach/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_manager_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_abstract_core/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach-master/smach_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_mbf/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_navigation/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_simulations/turtlebot3_simulations/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/xdot-master/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/cmd_vel_to_ackermann/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/hardware_interface/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/combined_robot_hw/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_interface/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/map_server_od/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach_visualization-kinetic-devel/rqt_smach/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach-master/smach_ros/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/executive_smach_visualization-kinetic-devel/smach_viewer/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_manager/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_manager_tests/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/combined_robot_hw_tests/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/realtime_tools-melodic-devel/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/control_toolbox/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/image_common/camera_calibration_parsers/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/gazebo_ros_pkgs/gazebo_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/image_common/image_transport/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/image_common/camera_info_manager/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/image_common/polled_camera/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/gazebo_ros_pkgs/gazebo_ros/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_utility/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_abstract_nav/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_simple_nav/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/tf2_sensor_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/pointcloud_to_laserscan-lunar-devel/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/transmission_interface/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_bringup/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_example/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_simulations/turtlebot3_fake/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_simulations/turtlebot3_gazebo/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_slam/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_teleop/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot_msgs/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/gazebo_ros_pkgs/gazebo_plugins/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/ros_control-noetic-devel/joint_limits_interface/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/gazebo_ros_pkgs/gazebo_ros_control/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/car_szenario/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_costmap_core/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/move_base_flex/mbf_costmap_nav/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/teb_local_planner/cmake_install.cmake")
  include("/home/automotive/catkin_ws/build/turtlebot3_description/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/automotive/catkin_ws/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
