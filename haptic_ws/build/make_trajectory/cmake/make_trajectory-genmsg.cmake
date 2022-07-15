# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(WARNING "Invoking generate_messages() without having added any message or service file before.
You should either add add_message_files() and/or add_service_files() calls or remove the invocation of generate_messages().")
message(STATUS "make_trajectory: 0 messages, 0 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Ifranka_core_msgs:/home/student/haptic_ws/src/franka_ros_interface/franka_common/franka_core_msgs/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Icontrol_msgs:/opt/ros/noetic/share/control_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/noetic/share/actionlib_msgs/cmake/../msg;-Ifranka_msgs:/home/student/haptic_ws/src/franka_ros/franka_msgs/msg;-Ifranka_msgs:/home/student/haptic_ws/devel/.private/franka_msgs/share/franka_msgs/msg;-Itrajectory_msgs:/opt/ros/noetic/share/trajectory_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(make_trajectory_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_cpp(make_trajectory
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/make_trajectory
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(make_trajectory_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(make_trajectory_generate_messages make_trajectory_generate_messages_cpp)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(make_trajectory_gencpp)
add_dependencies(make_trajectory_gencpp make_trajectory_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS make_trajectory_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_eus(make_trajectory
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/make_trajectory
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(make_trajectory_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(make_trajectory_generate_messages make_trajectory_generate_messages_eus)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(make_trajectory_geneus)
add_dependencies(make_trajectory_geneus make_trajectory_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS make_trajectory_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_lisp(make_trajectory
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/make_trajectory
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(make_trajectory_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(make_trajectory_generate_messages make_trajectory_generate_messages_lisp)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(make_trajectory_genlisp)
add_dependencies(make_trajectory_genlisp make_trajectory_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS make_trajectory_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_nodejs(make_trajectory
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/make_trajectory
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(make_trajectory_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(make_trajectory_generate_messages make_trajectory_generate_messages_nodejs)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(make_trajectory_gennodejs)
add_dependencies(make_trajectory_gennodejs make_trajectory_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS make_trajectory_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services

### Generating Module File
_generate_module_py(make_trajectory
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/make_trajectory
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(make_trajectory_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(make_trajectory_generate_messages make_trajectory_generate_messages_py)

# add dependencies to all check dependencies targets

# target for backward compatibility
add_custom_target(make_trajectory_genpy)
add_dependencies(make_trajectory_genpy make_trajectory_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS make_trajectory_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/make_trajectory)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/make_trajectory
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(make_trajectory_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET franka_core_msgs_generate_messages_cpp)
  add_dependencies(make_trajectory_generate_messages_cpp franka_core_msgs_generate_messages_cpp)
endif()
if(TARGET panda_ik_generate_messages_cpp)
  add_dependencies(make_trajectory_generate_messages_cpp panda_ik_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/make_trajectory)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/make_trajectory
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(make_trajectory_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET franka_core_msgs_generate_messages_eus)
  add_dependencies(make_trajectory_generate_messages_eus franka_core_msgs_generate_messages_eus)
endif()
if(TARGET panda_ik_generate_messages_eus)
  add_dependencies(make_trajectory_generate_messages_eus panda_ik_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/make_trajectory)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/make_trajectory
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(make_trajectory_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET franka_core_msgs_generate_messages_lisp)
  add_dependencies(make_trajectory_generate_messages_lisp franka_core_msgs_generate_messages_lisp)
endif()
if(TARGET panda_ik_generate_messages_lisp)
  add_dependencies(make_trajectory_generate_messages_lisp panda_ik_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/make_trajectory)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/make_trajectory
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(make_trajectory_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET franka_core_msgs_generate_messages_nodejs)
  add_dependencies(make_trajectory_generate_messages_nodejs franka_core_msgs_generate_messages_nodejs)
endif()
if(TARGET panda_ik_generate_messages_nodejs)
  add_dependencies(make_trajectory_generate_messages_nodejs panda_ik_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/make_trajectory)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/make_trajectory\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/make_trajectory
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(make_trajectory_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET franka_core_msgs_generate_messages_py)
  add_dependencies(make_trajectory_generate_messages_py franka_core_msgs_generate_messages_py)
endif()
if(TARGET panda_ik_generate_messages_py)
  add_dependencies(make_trajectory_generate_messages_py panda_ik_generate_messages_py)
endif()
