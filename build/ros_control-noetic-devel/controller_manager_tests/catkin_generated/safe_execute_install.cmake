execute_process(COMMAND "/home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_manager_tests/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_manager_tests/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
