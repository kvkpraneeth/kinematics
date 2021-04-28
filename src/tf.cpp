#include "robotics1/tf.h"
#include "geometry_msgs/TransformStamped.h"
#include "ros/duration.h"

robot_arm::robot_arm()
{
    this->n.getParam("number_of_links", this->number_of_links);
    this->loopTimer = this->n.createTimer(ros::Duration(0.01), std::bind(&robot_arm::__timerCB,this));
}

void robot_arm::__timerCB()
{
    this->br.sendTransform(init_link("link0"));
    this->br.sendTransform(init_link("link1"));
    this->br.sendTransform(init_link("link2"));
    this->br.sendTransform(init_link("link3"));
    this->br.sendTransform(init_link("link4"));
    this->br.sendTransform(init_link("link5"));
    this->br.sendTransform(init_link("link6"));
}

geometry_msgs::TransformStamped robot_arm::init_link(std::string link_name)
{

    geometry_msgs::TransformStamped temp;

    temp.header.stamp = ros::Time::now();

    this->n.getParam("links/" + link_name +"/parent",temp.header.frame_id);

    this->n.getParam("links/"+ link_name +"/name",temp.child_frame_id);

    double alpha, th, a, d;

    this->n.getParam("links/" + link_name + "/alpha", alpha);
    this->n.getParam("links/" + link_name + "/th", th);
    this->n.getParam("links/" + link_name + "/a", a);
    this->n.getParam("links/" + link_name + "/d", d);

    temp.transform = dh_to_transform(alpha,th,a,d);

    return temp;

}

geometry_msgs::Transform robot_arm::dh_to_transform(double alpha, double a, double r, double d)
{

    geometry_msgs::Transform sol;
   
    double rot[3][3];

    double roll, pitch, yaw, x, y, z;

    tf2::Quaternion q;

    rot[0][0] = std::cos(a);

    rot[0][1] = -(std::sin(a))*(std::cos(alpha));

    rot[0][2] = std::sin(a)*std::sin(alpha);

    rot[1][0] = std::sin(a);

    rot[1][1] = std::cos(a)*std::cos(alpha);

    rot[1][2] = -std::cos(a)*std::sin(alpha);

    rot[2][0] = 0;

    rot[2][1] = std::sin(alpha);

    rot[2][2] = std::cos(alpha);

    roll = -std::asin(rot[2][0]);

    pitch = std::atan2((rot[2][1]/std::cos(roll)),(rot[2][2]/std::cos(roll)));

    yaw = std::atan2((rot[1][0]/std::cos(roll)),(rot[0][0]/std::cos(roll)));

    q.setRPY(roll, pitch, yaw);

    q.normalize();

    x = r*std::cos(a);

    y = r*std::sin(a);

    z = d;

    sol.rotation.w = q.w();
    sol.rotation.x = q.x();
    sol.rotation.y = q.y();
    sol.rotation.z = q.z();

    sol.translation.x = x;
    sol.translation.y = y;
    sol.translation.z = z;

    return sol;
}

