execute_process(COMMAND "/home/student/haptic_ws/build/panda_gazebo/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/student/haptic_ws/build/panda_gazebo/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
