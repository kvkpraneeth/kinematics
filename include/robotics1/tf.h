#pragma once

#include "geometry_msgs/Transform.h"
#include "ros/node_handle.h"
#include "ros/rate.h"
#include "ros/ros.h"
#include "ros/time.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include "tf2/LinearMath/Quaternion.h"

class robot_arm
{

    //Constructor.
    public: robot_arm();

    //Worker Functions.
    public: geometry_msgs::TransformStamped init_link(std::string link_name);
    public: geometry_msgs::Transform dh_to_transform(double alpha, double a, double r, double d);

    //Node Handles.
    private: ros::NodeHandle n;
        
    //Broadcasters
    private: tf2_ros::TransformBroadcaster br;

    //Crucial Members.
    private: int number_of_links;
    private: std::vector<geometry_msgs::TransformStamped> robot;

    //Timers.
    private: ros::Timer loopTimer;
        
    //Callbacks.
    public: void __timerCB();

};
