# CMake generated Testfile for 
# Source directory: /home/automotive/catkin_ws/src/move_base_flex/mbf_abstract_nav
# Build directory: /home/automotive/catkin_ws/build/move_base_flex/mbf_abstract_nav
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_mbf_abstract_nav_gtest_mbf_abstract_server_gtest "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/mbf_abstract_nav/gtest-mbf_abstract_server_gtest.xml" "--return-code" "/home/automotive/catkin_ws/devel/lib/mbf_abstract_nav/mbf_abstract_server_gtest --gtest_output=xml:/home/automotive/catkin_ws/build/test_results/mbf_abstract_nav/gtest-mbf_abstract_server_gtest.xml")
add_test(_ctest_mbf_abstract_nav_rostest_test_abstract_action_base.launch "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/mbf_abstract_nav/rostest-test_abstract_action_base.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/automotive/catkin_ws/src/move_base_flex/mbf_abstract_nav --package=mbf_abstract_nav --results-filename test_abstract_action_base.xml --results-base-dir \"/home/automotive/catkin_ws/build/test_results\" /home/automotive/catkin_ws/src/move_base_flex/mbf_abstract_nav/test/abstract_action_base.launch ")
add_test(_ctest_mbf_abstract_nav_rostest_test_abstract_planner_execution.launch "/home/automotive/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/automotive/catkin_ws/build/test_results/mbf_abstract_nav/rostest-test_abstract_planner_execution.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/automotive/catkin_ws/src/move_base_flex/mbf_abstract_nav --package=mbf_abstract_nav --results-filename test_abstract_planner_execution.xml --results-base-dir \"/home/automotive/catkin_ws/build/test_results\" /home/automotive/catkin_ws/src/move_base_flex/mbf_abstract_nav/test/abstract_planner_execution.launch ")
