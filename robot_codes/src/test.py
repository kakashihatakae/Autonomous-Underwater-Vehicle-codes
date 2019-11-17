#!/usr/bin/env python

import rospy
from robot_codes.srv import*



class test:
    def __init__(self):
        self.align = rospy.ServiceProxy("PID_ya", PID)
        self.error = 30.0

    def execute(self):
        rospy.wait_for_service("PID_ya")
        print "service called"
        try:
            while self.error > 1:
                omega = self.align(self.error)

        except rospy.ServiceException, e:
            print' failed to call %s' %e

if __name__ == "__main__":
    rospy.init_node("test")
    t = test()
    print "starting execute"
    t.execute()