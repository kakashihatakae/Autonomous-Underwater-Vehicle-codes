#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"
#include "depth_maintain/Depth.h"
#include "depth_maintain/ParametreStorage.h"


int main(int argc,char **argv)
{
    ROS_INFO("starting height node");
    ros::init(argc, argv, "height_maintain");
    ros::NodeHandle n;
   
    height h;
    

    ros::spin();

}
