## *********************************************************
##
## File autogenerated for the panda_joint_trajectory_action package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'name': 'Default', 'type': '', 'state': True, 'cstate': 'true', 'id': 0, 'parent': 0, 'parameters': [{'name': 'goal_time', 'type': 'double', 'default': 0.1, 'level': 0, 'description': 'Amount of time (s) controller is permitted to be late achieving goal', 'min': 0.0, 'max': 120.0, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'stopped_velocity_tolerance', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'Maximum velocity (m/s) at end of trajectory to be considered stopped', 'min': -1.0, 'max': 1.0, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint1_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint1 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint2_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint2 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint3_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint3 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint4_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint4 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint5_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint5 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint6_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint6 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint7_goal', 'type': 'double', 'default': -0.2, 'level': 0, 'description': 'panda_joint7 - maximum final error', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint1_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint1 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint2_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint2 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint3_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint3 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint4_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint4 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint5_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint5 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint6_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint6 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'panda_joint7_trajectory', 'type': 'double', 'default': 0.2, 'level': 0, 'description': 'panda_joint7 - maximum error during trajectory execution', 'min': -0.5, 'max': 0.5, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}], 'groups': [], 'srcline': 246, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT', 'parentclass': '', 'parentname': 'Default', 'field': 'default', 'upper': 'DEFAULT', 'lower': 'groups'}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

