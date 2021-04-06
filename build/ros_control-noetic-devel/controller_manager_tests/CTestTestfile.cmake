# CMake generated Testfile for 
# Source directory: /home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests
# Build directory: /home/automotive/catkin_ws/build/ros_control-noetic-devel/controller_manager_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_controller_manager_tests_nosetests_test "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/controller_manager_tests/nosetests-test.xml" "--return-code" "\"/usr/bin/cmake\" -E make_directory /home/automotive/catkin_ws/build/test_results/controller_manager_tests" "/usr/bin/nosetests-2.7 -P --process-timeout=60 --where=/home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests/test --with-xunit --xunit-file=/home/automotive/catkin_ws/build/test_results/controller_manager_tests/nosetests-test.xml")
add_test(_ctest_controller_manager_tests_rostest_test_cm_test.test "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/controller_manager_tests/rostest-test_cm_test.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests --package=controller_manager_tests --results-filename test_cm_test.xml --results-base-dir \"/home/automotive/catkin_ws/build/test_results\" /home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests/test/cm_test.test ")
add_test(_ctest_controller_manager_tests_rostest_test_cm_msgs_utils_rostest.test "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/controller_manager_tests/rostest-test_cm_msgs_utils_rostest.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests --package=controller_manager_tests --results-filename test_cm_msgs_utils_rostest.xml --results-base-dir \"/home/automotive/catkin_ws/build/test_results\" /home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests/test/cm_msgs_utils_rostest.test ")
add_test(_ctest_controller_manager_tests_rostest_test_controller_manager_scripts.test "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/controller_manager_tests/rostest-test_controller_manager_scripts.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests --package=controller_manager_tests --results-filename test_controller_manager_scripts.xml --results-base-dir \"/home/automotive/catkin_ws/build/test_results\" /home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests/test/controller_manager_scripts.test ")
add_test(_ctest_controller_manager_tests_rostest_test_controller_manager_interface_test.test "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/controller_manager_tests/rostest-test_controller_manager_interface_test.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests --package=controller_manager_tests --results-filename test_controller_manager_interface_test.xml --results-base-dir \"/home/automotive/catkin_ws/build/test_results\" /home/automotive/catkin_ws/src/ros_control-noetic-devel/controller_manager_tests/test/controller_manager_interface_test.test ")
