#include "robotics1/tf.h"
#include "ros/init.h"
#include "ros/rate.h"
#include "ros/spinner.h"

int main(int argc, char** argv)
{

    ros::init(argc,argv, "tf");

    robot_arm r;

    ros::AsyncSpinner spinner(0);

    spinner.start();

    ros::waitForShutdown();

    return 0;
}


