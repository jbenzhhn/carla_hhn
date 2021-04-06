# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "car_szenario: 1 messages, 0 services")

set(MSG_I_FLAGS "-Icar_szenario:/home/automotive/catkin_ws/src/car_szenario/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Inav_msgs:/opt/ros/melodic/share/nav_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/melodic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(car_szenario_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" NAME_WE)
add_custom_target(_car_szenario_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_szenario" "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(car_szenario
  "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_szenario
)

### Generating Services

### Generating Module File
_generate_module_cpp(car_szenario
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_szenario
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(car_szenario_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(car_szenario_generate_messages car_szenario_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" NAME_WE)
add_dependencies(car_szenario_generate_messages_cpp _car_szenario_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_szenario_gencpp)
add_dependencies(car_szenario_gencpp car_szenario_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_szenario_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(car_szenario
  "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_szenario
)

### Generating Services

### Generating Module File
_generate_module_eus(car_szenario
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_szenario
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(car_szenario_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(car_szenario_generate_messages car_szenario_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" NAME_WE)
add_dependencies(car_szenario_generate_messages_eus _car_szenario_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_szenario_geneus)
add_dependencies(car_szenario_geneus car_szenario_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_szenario_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(car_szenario
  "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_szenario
)

### Generating Services

### Generating Module File
_generate_module_lisp(car_szenario
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_szenario
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(car_szenario_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(car_szenario_generate_messages car_szenario_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" NAME_WE)
add_dependencies(car_szenario_generate_messages_lisp _car_szenario_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_szenario_genlisp)
add_dependencies(car_szenario_genlisp car_szenario_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_szenario_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(car_szenario
  "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_szenario
)

### Generating Services

### Generating Module File
_generate_module_nodejs(car_szenario
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_szenario
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(car_szenario_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(car_szenario_generate_messages car_szenario_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" NAME_WE)
add_dependencies(car_szenario_generate_messages_nodejs _car_szenario_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_szenario_gennodejs)
add_dependencies(car_szenario_gennodejs car_szenario_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_szenario_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(car_szenario
  "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_szenario
)

### Generating Services

### Generating Module File
_generate_module_py(car_szenario
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_szenario
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(car_szenario_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(car_szenario_generate_messages car_szenario_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/automotive/catkin_ws/src/car_szenario/msg/RoadInfo.msg" NAME_WE)
add_dependencies(car_szenario_generate_messages_py _car_szenario_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_szenario_genpy)
add_dependencies(car_szenario_genpy car_szenario_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_szenario_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_szenario)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_szenario
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(car_szenario_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(car_szenario_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(car_szenario_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_szenario)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_szenario
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(car_szenario_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(car_szenario_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(car_szenario_generate_messages_eus nav_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_szenario)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_szenario
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(car_szenario_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(car_szenario_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(car_szenario_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_szenario)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_szenario
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(car_szenario_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(car_szenario_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(car_szenario_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_szenario)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_szenario\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_szenario
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(car_szenario_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(car_szenario_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(car_szenario_generate_messages_py nav_msgs_generate_messages_py)
endif()
