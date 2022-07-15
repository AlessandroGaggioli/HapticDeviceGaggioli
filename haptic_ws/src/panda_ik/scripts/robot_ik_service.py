#!/usr/bin/env python3

import copy
import rospy
import logging
import argparse
import quaternion
import numpy as np
import franka_interface
from panda_robot import PandaArm
from panda_ik.srv import *


class PandaIk():
    def __init__(self):
        self.main()


    def ik_callback(self,req):
        pose = req.reference_pose
        res = pandaIkResponse()
        pos = np.array([pose.position.x,pose.position.y,pose.position.z])
        quat = np.quaternion(pose.orientation.w,pose.orientation.x,pose.orientation.y,pose.orientation.z)
        if len(req.seed_joints.position) != 0:
            seed = req.seed_joints.position
            [res.success,solution] = self.arm.inverse_kinematics(pos,quat,seed)
            res.solution.position = solution
        else:
            [res.success,solution] = self.arm.inverse_kinematics(pos,quat)
            print(solution)
            res.solution.position = solution
        return res

    def fk_callback(self,req):
        joints = req.reference_joints.position
        [pos,rot] = self.arm.forward_kinematics(joints)
        res = pandaFkResponse()
        res.solution.position.x = pos[0]
        res.solution.position.y = pos[1]
        res.solution.position.z = pos[2]
        res.solution.orientation.x = rot.x
        res.solution.orientation.y = rot.y
        res.solution.orientation.z = rot.z
        res.solution.orientation.w = rot.w
        return res

    def main(self):
        rospy.init_node("panda_ik_service")

        self.arm = PandaArm(reset_frames=False)
        self.arm_ik = rospy.Service('panda_ik_service', pandaIk, self.ik_callback)
        self.arm_fk = rospy.Service('panda_fk_service', pandaFk, self.fk_callback)
        rospy.spin()


if __name__ == '__main__':
    ik_obj = PandaIk()
