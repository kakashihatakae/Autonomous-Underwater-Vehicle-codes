
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"

class height
{
    private:

    //float goalHeight = 0;
    float thrust;
    
    //Float64 thrustMatrix[5] ;
    
    ros::Publisher pub;
    ros::Subscriber sub;

    std_msgs::Float64MultiArray Array;
    std_msgs::Float64 vertThrust;
    //Array.data.resize(5);
    float goalHeight ;
    
    

    public: 
    
    
    height();
    void heightMaintain(const geometry_msgs::Pose::ConstPtr& msg);
    
    void goalCallback(const geometry_msgs::Pose::ConstPtr& msg);

    float getThrust();

    /*void toThruster(Float64 thru)
    {
        thrustMatrix[5] = {0.0, 0.0, thru, thru,0.0};
    }*/
};
