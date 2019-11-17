#!/usr/bin/env python


import rospy
import smach
import smach_ros
from geometry_msgs.msg import Pose
import tf
from robot_codes.srv import PID  
from std_msgs.msg import Float64MultiArray
from robot_codes.srv import angle
import threading


class Storage:
    def __init__(self):
        self.Yaw = 0
        self.Goal = 0




#goal
class Find_strip(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes = ['calculated'])



    def execute(self, userdata):
        rospy.wait_for_service('find_angle')
        try:
            service_var = rospy.ServiceProxy('find_angle', angle)
            result = service_var()

            #global goal
            Storage.Goal = result.theta_goal
            rospy.loginfo("goal assigned %lf" %Storage.Goal)
        except rospy.ServiceException, e:
            print' failed to call %s' %e

        if Storage.Goal:
            return 'calculated'


class Align(smach.State):
    def __init__(self):

        #callback.__init__(self)
        smach.State.__init__(self, outcomes = ['aligned'])
        #Find_strip.__init__(self)
        #callback.__init__(self)
        self.pub = rospy.Publisher("/g500/to_thust_collector_lin", Float64MultiArray, queue_size = 5) 

        self.vel_omega = Float64MultiArray()
        rospy.loginfo("initialised")
        rospy.loginfo("desired variable is assigned")


    def execute(self, userdata):
        rospy.loginfo("starting Align state")
        rospy.wait_for_service("/PID_yaw_server/PID_yaw_server")

        print Storage.Goal
        self.desired = Storage.Goal
        #desired angle from opencv service

        try: 
            align = rospy.ServiceProxy("/PID_yaw_server/PID_yaw_server", PID)
            self.strt = align(self.desired, 0)
            rospy.loginfo('entered try')

            while self.strt.errorFeed > 0.01:
                self.strt = align(self.desired, 0)

        except rospy.ServiceException, e:
            print "servce call failed: %s"%e
                #break

        if self.strt.error < 0.01:
            return 'aligned'
        else :
            rospy.loginfo("service did not invoke")

class StrtLineMotion(smach.State):
    def __init__(self):
        pass

    def execute(self, userdata):
        pass 


def main():
    sm = smach.StateMachine(outcomes=['outcome1'])
    with sm:
        #sm.userdata.sm_counter = 0

        smach.StateMachine.add('find_strip', Find_strip(), 
                                transitions = {'calculated': 'align'})

        smach.StateMachine.add('align', Align(), 
                                transitions = {'aligned':'outcome1'})

    sis = smach_ros.IntrospectionServer('server_name', sm, '/sm_root')
    sis.start()
    sm.execute()
    #rospy.spin()
    sis.stop()


if __name__ == "__main__":
    rospy.init_node('PLanner_node')
    rospy.loginfo("starting Planner")
    main()


