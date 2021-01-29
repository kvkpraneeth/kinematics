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

    public:

        robot_arm()
        {
            
            this->n.getParam("number_of_links", this->number_of_links);
            this->randy = rand();

        }

        void loop()
        {
            
            this->transforms();

        }

        void transforms()
        {

            this->br.sendTransform(init_link("link0"));
            this->br.sendTransform(init_link("link1"));
            this->br.sendTransform(init_link("link2"));

        }

        geometry_msgs::TransformStamped init_link(std::string link_name)
        {

            geometry_msgs::TransformStamped temp;

            temp.header.stamp = ros::Time::now();

            this->n.getParam("links/" + link_name +"/parent",temp.header.frame_id);

            this->n.getParam("links/"+ link_name +"/name",temp.child_frame_id);

            double alpha, a, r, d;

            this->n.getParam("links/" + link_name + "/alpha", alpha);
            this->n.getParam("links/" + link_name + "/a", a);
            this->n.getParam("links/" + link_name + "/r", r);
            this->n.getParam("links/" + link_name + "/d", d);

            temp.transform = dh_to_transform(alpha,a,r,d);

            return temp;
        }

        geometry_msgs::Transform dh_to_transform(double alpha, double a, double r, double d)
        {

            geometry_msgs::Transform sol1, sol2;
           
            double rot[3][3];

            double roll1, roll2, pitch1, pitch2, yaw1, yaw2, x, y, z;

            tf2::Quaternion q1,q2;

            rot[0][0] = std::cos(a);
        
            rot[0][1] = -(std::sin(a))*(std::cos(alpha));

            rot[0][2] = std::sin(a)*std::sin(alpha);

            rot[1][0] = std::sin(a);

            rot[1][1] = std::cos(a)*std::cos(alpha);

            rot[1][2] = -std::cos(a)*std::sin(alpha);

            rot[2][0] = 0;

            rot[2][1] = std::sin(alpha);

            rot[2][2] = std::cos(alpha);

            roll1 = -std::asin(rot[2][0]);

            roll2 = 3.14 - roll1;

            pitch1 = std::atan2((rot[2][1]/std::cos(roll1)),(rot[2][2]/std::cos(roll1)));

            pitch2 = std::atan2((rot[2][1]/std::cos(roll2)),(rot[2][2]/std::cos(roll2)));

            yaw1 = std::atan2((rot[1][0]/std::cos(roll1)),(rot[0][0]/std::cos(roll1)));

            yaw2 = std::atan2((rot[1][0]/std::cos(roll2)),(rot[0][0]/std::cos(roll2)));

            q1.setRPY(roll1, pitch1, yaw1);

            q2.setRPY(roll2, pitch2, yaw2);

            q1.normalize();

            q2.normalize();

            x = r*std::cos(a);

            y = r*std::sin(a);

            z = d;

            sol1.rotation.w = q1.w();
            sol1.rotation.x = q1.x();
            sol1.rotation.y = q1.y();
            sol1.rotation.z = q1.z();

            sol1.translation.x = x;
            sol1.translation.y = y;
            sol1.translation.z = z;

            sol2.rotation.w = q2.w();
            sol2.rotation.x = q2.x();
            sol2.rotation.y = q2.y();
            sol2.rotation.z = q2.z();

            sol2.translation.x = x;
            sol2.translation.y = y;
            sol2.translation.z = z;

            if(this->randy%2 == 0)
            {
                return sol1;
            }
            else 
            {
                return sol2;
            }

        }

    private:
    
        ros::NodeHandle n;
        
        tf2_ros::TransformBroadcaster br;

        int number_of_links;

        std::vector<geometry_msgs::TransformStamped> robot;

        int randy;
};

