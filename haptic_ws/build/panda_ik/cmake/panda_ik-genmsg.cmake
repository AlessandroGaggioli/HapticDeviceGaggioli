# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "panda_ik: 0 messages, 2 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(panda_ik_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" NAME_WE)
add_custom_target(_panda_ik_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "panda_ik" "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" "geometry_msgs/Point:geometry_msgs/Quaternion:geometry_msgs/Pose:std_msgs/Header:sensor_msgs/JointState"
)

get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" NAME_WE)
add_custom_target(_panda_ik_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "panda_ik" "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" "geometry_msgs/Point:geometry_msgs/Quaternion:geometry_msgs/Pose:std_msgs/Header:sensor_msgs/JointState"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/panda_ik
)
_generate_srv_cpp(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/panda_ik
)

### Generating Module File
_generate_module_cpp(panda_ik
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/panda_ik
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(panda_ik_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(panda_ik_generate_messages panda_ik_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_cpp _panda_ik_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_cpp _panda_ik_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(panda_ik_gencpp)
add_dependencies(panda_ik_gencpp panda_ik_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS panda_ik_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/panda_ik
)
_generate_srv_eus(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/panda_ik
)

### Generating Module File
_generate_module_eus(panda_ik
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/panda_ik
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(panda_ik_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(panda_ik_generate_messages panda_ik_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_eus _panda_ik_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_eus _panda_ik_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(panda_ik_geneus)
add_dependencies(panda_ik_geneus panda_ik_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS panda_ik_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/panda_ik
)
_generate_srv_lisp(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/panda_ik
)

### Generating Module File
_generate_module_lisp(panda_ik
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/panda_ik
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(panda_ik_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(panda_ik_generate_messages panda_ik_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_lisp _panda_ik_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_lisp _panda_ik_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(panda_ik_genlisp)
add_dependencies(panda_ik_genlisp panda_ik_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS panda_ik_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/panda_ik
)
_generate_srv_nodejs(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/panda_ik
)

### Generating Module File
_generate_module_nodejs(panda_ik
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/panda_ik
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(panda_ik_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(panda_ik_generate_messages panda_ik_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_nodejs _panda_ik_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_nodejs _panda_ik_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(panda_ik_gennodejs)
add_dependencies(panda_ik_gennodejs panda_ik_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS panda_ik_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik
)
_generate_srv_py(panda_ik
  "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik
)

### Generating Module File
_generate_module_py(panda_ik
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(panda_ik_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(panda_ik_generate_messages panda_ik_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaIk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_py _panda_ik_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/student/haptic_ws/src/panda_ik/srv/pandaFk.srv" NAME_WE)
add_dependencies(panda_ik_generate_messages_py _panda_ik_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(panda_ik_genpy)
add_dependencies(panda_ik_genpy panda_ik_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS panda_ik_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/panda_ik)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/panda_ik
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(panda_ik_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(panda_ik_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(panda_ik_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/panda_ik)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/panda_ik
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(panda_ik_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(panda_ik_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(panda_ik_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/panda_ik)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/panda_ik
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(panda_ik_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(panda_ik_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(panda_ik_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/panda_ik)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/panda_ik
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(panda_ik_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(panda_ik_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(panda_ik_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik
    DESTINATION ${genpy_INSTALL_DIR}
    # skip all init files
    PATTERN "__init__.py" EXCLUDE
    PATTERN "__init__.pyc" EXCLUDE
  )
  # install init files which are not in the root folder of the generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik
    DESTINATION ${genpy_INSTALL_DIR}
    FILES_MATCHING
    REGEX "${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/panda_ik/.+/__init__.pyc?$"
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(panda_ik_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(panda_ik_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(panda_ik_generate_messages_py sensor_msgs_generate_messages_py)
endif()
