execute_process(COMMAND "/home/automotive/catkin_ws/build/executive_smach-master/smach_ros/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/automotive/catkin_ws/build/executive_smach-master/smach_ros/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
