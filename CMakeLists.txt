cmake_minimum_required(VERSION 2.8.3)

project(robotics1)

find_package(catkin REQUIRED roscpp rospy rviz tf2 tf2_ros geometry_msgs rosparam)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})
include_directories(include)

add_library(tf_broadcaster_core src/tf.cpp)
target_link_libraries(tf_broadcaster_core ${catkin_LIBRARIES})

add_executable(tf_broadcaster src/main.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES} tf_broadcaster_core)
add_dependencies(tf_broadcaster tf_broadcaster_core)
