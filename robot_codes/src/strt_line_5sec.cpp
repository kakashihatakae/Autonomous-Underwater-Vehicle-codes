#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "sensor_msgs/Imu.h"

float accel;
void ImuCall(const sensor_msgs::ImuConstPtr & msg)
{
    accel = msg->linear_acceleration.x;
    ROS_INFO("acceleration data : %f", msg->linear_acceleration.x);
}


int main(int argc, char** argv)
{
    
    ros::init(argc, argv,"test");
    ros::NodeHandle n;
    ros::Duration ten_sec(10.0), one_sec(1.0);
    ros::Publisher pub = n.advertise<std_msgs::Float64MultiArray>("/g500/thrusters_input",100);
    ros::Subscriber sub = n.subscribe("/g500/imu", 1000, ImuCall);

    int flag = 0;
    std_msgs::Float64MultiArray thrust;
    thrust.data.resize(5);

    std::cout << "===========================================";
    ROS_INFO("starting forward");
    std::cout << "===========================================";
    one_sec.sleep();

        thrust.data[0] = 0.5;
        thrust.data[1] = 0.5;
        thrust.data[2] = 0;
        thrust.data[3] = 0;
        thrust.data[4] = 0;
        pub.publish(thrust);
        ten_sec.sleep();
    

    std::cout << "===========================================";
    ROS_INFO("starting backward");
    std::cout << "===========================================";
    one_sec.sleep();

    while (abs(accel) > 0.1)
    {
        thrust.data[0] = - 0.5;
        thrust.data[1] = - 0.5;
        thrust.data[2] = 0;
        thrust.data[3] = 0;
        thrust.data[4] = 0;
        pub.publish(thrust);
    }
    return 0;
}