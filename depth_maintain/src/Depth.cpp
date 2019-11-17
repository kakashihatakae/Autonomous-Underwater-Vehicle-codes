
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"
#include "depth_maintain/Depth.h"
#include "depth_maintain/ParametreStorage.h"

height::height()
    {
        
        Array.data.resize(5);
        ROS_INFO("Initialized");
        ros::NodeHandle n;
        sub = n.subscribe("/g500/pose", 100, &height::heightMaintain,this);
        pub = n.advertise<std_msgs::Float64>("to_thrust_collector_vert", 100);
        /*
        un comment for simulator
        pub = n.advertise<std_msgs::Float64MultiArray>("/g500/thrusters_input", 100);*/
        
        goalHeight = 6.5;
    }

void height::heightMaintain(const geometry_msgs::Pose::ConstPtr& msg)
{
        float error ;
        
        /* un comment for simulator
        Array.data.resize(5);
        */

        
        error = goalHeight - msg->position.z;
        thrust = 0.199*error;
        vertThrust.data = thrust;
        pub.publish(vertThrust);

        /* un comment for simulator
        //toThruster(thrust);
        Array.data[0] = 0;
        Array.data[1] = 0;
        Array.data[2] = -thrust;
        Array.data[3] = -thrust;
       Array.data[4] = 0;
       ROS_INFO("thrust: %f", -thrust);
        pub.publish(Array);
*/
}
/*
    void goalCallback(const geometry_msgs::Pose::ConstPtr& msg)
    {
        ROS_INFO("Recieved goal");
        goalHeight = msg.position.z;

    }
*/
float height::getThrust()
    {
        return thrust;
    }

    /*void toThruster(Float64 thru)
    {
        thrustMatrix[5] = {0.0, 0.0, thru, thru,0.0};
    }*/

