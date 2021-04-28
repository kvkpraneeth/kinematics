#!/usr/bin/python3

import rosparam
import rospy
import yaml

class update_params:

    def __init__(self):

        rospy.init_node("update_params")
        self.filename = "/home/pkvk/ros1_ws/src/robotics1/config/robot_arm.yaml" 

    def read(self):
        with open(self.filename, 'r') as yaml_file:
            yaml_data = yaml.load(yaml_file, Loader=yaml.FullLoader)
            rospy.set_param('/links', yaml_data['links'])

if __name__ == "__main__":
   
    up = update_params()

    while not rospy.is_shutdown():
        up.read()

