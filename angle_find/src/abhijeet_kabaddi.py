#!/usr/bin/env python

import numpy as np
import cv2
import rospy
from cv_bridge import CvBridge, CvBridgeError
from angle_find.srv import* 
from geometry_msgs.msg import Pose
from sensor_msgs.msg import Image 


'''
---------------------------
im = cv2.imread('picture121.jpg')
---------------------------
'''
class Image_kaka(object):
    def __init__(self):
        self.image_sub = rospy.Subscriber("/g500/camera1", Image, self.image_callback)
        self.bridge = CvBridge()

        self.COLOR_MIN = np.array([59, 88, 125],np.uint8)
        self.COLOR_MAX = np.array([95, 255, 255],np.uint8)
        self.angle = 0
        print 'suck'

    def image_callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
            print "done"
        except CvBridgeError as e:
            print(e)
            print "not_done"
        hsv_img = cv2.cvtColor(cv_image, cv2.COLOR_BGR2HSV)
        sho = cv2.namedWindow('Show', cv2.WINDOW_NORMAL)
        cv2.imshow('Show', cv_image)
        #thresholding
        frame_threshed = cv2.inRange(hsv_img, self.COLOR_MIN, self.COLOR_MAX)

        #ret,thresh = cv2.threshold(frame_threshed, 127,255,0)
        contours, hierarchy = cv2.findContours(frame_threshed ,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        #v2.imshow("Show",thresh)
        print len(contours)
        # Find the index of the largest contour
        areas = [cv2.contourArea(c) for c in contours]
        max_index = np.argmax(areas)
        cnt = contours[max_index]
        #M = cv2.moments(cnt)
#        print M


        #cx = int(M['m10']/M['m00'])
        #cy = int(M['m01']/M['m00'])

        x,y,w,h = cv2.boundingRect(cnt)
        cv2.rectangle(cv_image,(x,y), (x+w,y+h), (0, 255, 0), 10)

        rows,cols = cv_image.shape[:2]
        [vx,vy,x,y] = cv2.fitLine(cnt, cv2.cv.CV_DIST_L2,0, 0.01, 0.01)
        lefty = int((-x*vy/vx) + y)
        righty = int(((cols-x)*vy/vx)+y)
        cv_image = cv2.line(cv_image, (cols-1,righty), (0,lefty),(0, 255, 0), 1)

        rect = cv2.minAreaRect(cnt)[-1]

        print rect
        self.angle = rect
        cv2.waitKey(3)

    def server_callback(self, req):
        rospy.loginfo(" calculated and returning angle")
        return self.angle


if __name__ == '__main__':
    rospy.init_node('find_angle_strip_server')
    rospy.loginfo('entered the main of the service')
    ig = Image_kaka()
    service = rospy.Service('find_angle', angle, ig.server_callback )
    rospy.spin()
