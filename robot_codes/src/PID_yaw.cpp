#include <ros/ros.h>
#include <robot_codes/PID.h>
#include <geometry_msgs/Pose.h>
#include <stdlib.h>
#include <math.h>
#include <std_msgs/Float64MultiArray.h>

namespace localisation{
class PID
{
    bool flag ;

    ros::ServiceServer service;
    ros::Subscriber sub;
    ros::Publisher pub;

    float kp ;
    double euler;
    double error;
    double desired;

    std_msgs::Float64MultiArray vel_omega;

    public:
    PID()
    {
        ros::NodeHandle n;

        //publishers and subscribers
        service = n.advertiseService("PID_ya", &PID::PID_yaw, this);
        sub = n.subscribe("/g500/pose", 1000, &PID::PoseCb, this);
        // pub =   publish data on thrust collector
        pub = n.advertise<std_msgs::Float64MultiArray>("/g500/to_thust_collector_lin",100);
        
        euler = 0.0;
        error = 2.0;
        kp = 5.0/110.0;
        desired = 0;
        flag = 0;

        vel_omega.data.resize(2);
    }


    bool PID_yaw(robot_codes::PID::Request &req,
                 robot_codes::PID::Response &res)
    {   
        
        //res.omega = kp * req.error;
       // ROS_WARN("error: %f",req.error);
        
        if (flag != 1)
        {
            desired = req.error + euler;
            flag = 1;
        }
        /* while error is less than 0.001 
                execute the PID controller
                take vel, omega and publish on the thrust collector
                and publish data to the thrust collector
            */
       
        //std::cout <<euler<<std::endl;
        error = desired - euler;
            //publish vel, omega
        vel_omega.data[0] = req.velocity;
        vel_omega.data[1] = kp*error;
        pub.publish(vel_omega);
        
        res.errorFeed = error;
        return true;
    }

    void PoseCb(const geometry_msgs::Pose & msg)
    {   
        /* convert the quaternion to euler */
        quat_to_euler(msg.orientation.x, msg.orientation.y, msg.orientation.z, msg.orientation.w);
        ROS_INFO("yaw : %lf", euler);
    }

    double quat_to_euler(double x, double y, double z, double w)
    {
        //convert quat to euler as long as -90 < euler < 90
        // return reference
        if ((euler < 90) && (euler > -90))
        {
            double num = w*z + x*y;
            double den = 1 - 2*(y*y + z*z);
            euler = atan2( num , den);
            return euler;
        }
    }

};





}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "PID_yaw_server");
    ROS_INFO("sarted PID_yaw"); 
    ros::NodeHandle n;
 
    localisation::PID pi;

    ROS_INFO("end");
    ros::spin();
    return 0;
}