#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"


class thruster{
    ros::Subscriber sub_thrustLinear;
    ros::Subscriber sub_thrustVertical;
    //ros::Subscriber sub_thrustY;
    
    struct linear_thrust{
        double linLeft;
        double linRight;
    }lin;

    struct vertical_thrust{
        double vertFront;
        double vertBack;
    }vert;

    std_msgs::Float64MultiArray Linear, Vertical;  

    public:
    ros::Publisher pub;

    thruster(void)
    {
        ros::NodeHandle n;

        sub_thrustLinear = n.subscribe("/g500/to_thust_collector_lin", 10, &thruster::thrustLinearCB, this);
        sub_thrustVertical = n.subscribe("to_thrust_collector_vert", 10, &thruster::thrustVerticalCB, this);
        //sub_thrustY = n.subscribe()

        pub = n.advertise<std_msgs::Float64MultiArray>("/g500/thrusters_input",100);
        std_msgs::Float64MultiArray thrust_mat;

        Linear.data.resize(2);
        Vertical.data.resize(1);
        ROS_INFO("initialised thrust collector node");
    }
    
    void thrustLinearCB(const std_msgs::Float64MultiArrayConstPtr & msg)
    {
        lin.linLeft = msg->data[0] - msg->data[1];
        lin.linRight = msg->data[0] + msg->data[1];
        ROS_INFO("left: %lf  right: %lf",lin.linLeft, lin.linRight);
    }

    void thrustVerticalCB(const std_msgs::Float64ConstPtr & msg)
    {   
        vert.vertFront = vert.vertBack = msg->data;
        ROS_INFO("VertThrust: %lf", vert.vertFront);
    }

    /*void thrustYCB(const std_msgs::Float64 & msg)
    {

    }*/
    
    linear_thrust get_linear_thruster()
    {
        return lin;
    }

    vertical_thrust get_vertical_thruster()
    {
        return vert;
    }

};

int main(int argc, char** argv)
{
    ros::init(argc, argv,"thrustColledtor");
    ROS_INFO("starting thrustCollector node");

    thruster th;
    std_msgs::Float64MultiArray thrust_mat;
    thrust_mat.data.resize(5);
    ros::Rate looprate(8);

    while(ros::ok())
    {
        thrust_mat.data[0] = th.get_linear_thruster().linLeft;
        thrust_mat.data[1] = th.get_linear_thruster().linRight;
        thrust_mat.data[2] = - th.get_vertical_thruster().vertBack;
        thrust_mat.data[3] = - th.get_vertical_thruster().vertFront;
        thrust_mat.data[4] = 0;
        th.pub.publish(thrust_mat);
        ros::spinOnce();
        looprate.sleep();
    }
    
    return 0;
}