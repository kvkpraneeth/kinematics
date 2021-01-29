#include "robotics/tf.h"

int main(int argc, char** argv)
{

    ros::init(argc,argv, "tf");

    robot_arm r;

    while(ros::ok())
    {
        r.loop();
    }

    return 0;
}

