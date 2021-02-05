#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rospy
from flir_lepton_msgs.msg import TemperatureRaw
from life_msgs.msg import Cam, Status
from sensor_msgs.msg import Image
import numpy as np
import cv2
from matplotlib import pyplot as plt
from cv_bridge import CvBridge, CvBridgeError
from threading import Thread
global status
status = Status()
pub_status = rospy.Publisher('/Status/Cam', Status, queue_size=2)

class ThermalImageProcessor(object):

    def __init__(self):
        self.t = 0
        self.raw_topic = rospy.get_param('raw_topic', 'raw')
        self.image_topic = rospy.get_param('image_topic', 'image')
	
        self.sub_raw = rospy.Subscriber(self.raw_topic, TemperatureRaw, self.callback)

        self.pub_cam = rospy.Publisher('Cam', Cam, queue_size=2)
        self.pub_image = rospy.Publisher(self.image_topic, Image, queue_size=2)
        self.bridge = CvBridge()
        rospy.Timer(rospy.Duration(0.02), self.stat_pub)

    def callback(self, data):
        self.t = 0
        self.raw_to_image(data)

    def raw_to_image(self, data):
        cam = Cam()
        header = data.header
        mask, c_mean, detected = self.detect_people(data)
        cam.result = detected
        if detected:
            h = data.height
            w = data.width
            data = np.array(data.data, dtype=np.uint16).reshape(data.height, data.width)
            minVal, maxVal, minLoc, maxLoc = cv2.minMaxLoc(data)
            maxVal = self.raw_to_c(maxVal)
            img = self.raw_to_8bit(data)
            contours, _ = cv2.findContours(mask, 1, 2)
            cv2.circle(img, maxLoc, 1, (255, 0, 0), -1)
            global band
            cxs = []
            cys = []
            if len(contours) != 0:
                for i in contours:
                    cx = 0
                    cy = 0
                    for j in i:
                        cx += j[0][0]
                        cy += j[0][1]
                    cxs.append(cx / len(i))
                    cys.append(cy / len(i))
                    cv2.drawContours(img, [i], 0, (0, 0, 255), 1)
                tcx = int(sum(cxs)/len(cxs))
                tcy = int(sum(cys)/len(cys))
                cv2.circle(img, (tcx, tcy), 1, (0, 255, 0), -1)
                #human detected
                x_band = tcx - w/2
                y_band = h/2 - tcy
                cam.x = np.int32(x_band)
                cam.y = np.int32(y_band)
                cam.temperature = np.float64(c_mean)
                self.pub_cam.publish(cam)	    
            try: 
                img_msg = self.bridge.cv2_to_imgmsg(img, 'bgr8')
                img_msg.header = header
                self.pub_image.publish(img_msg)
            except CvBridgeError() as e:
                rospy.logerr(e)
        else:
            self.pub_cam.publish(cam)

    @staticmethod
    def raw_to_c(val):
        return (val - 27315) / 100.0

    @staticmethod
    def raw_to_8bit(data):
        cv2.normalize(data, data, 0, 65535, cv2.NORM_MINMAX)
        np.right_shift(data, 8, data)
        return cv2.cvtColor(np.uint8(data), cv2.COLOR_GRAY2RGB)
        
    def detect_people(self, data):
        c_val = self.raw_to_c(np.array(data.data, dtype=np.uint16))
        c_val = c_val.reshape(data.height, data.width)
        c_val = c_val.astype(np.float32)
        c_val = c_val * 100 + 27315
        c_minVal, c_maxVal, c_minLoc, c_maxLoc = cv2.minMaxLoc(c_val)
        hist = cv2.calcHist([c_val], [0], None, [65536], [0, 65535])
        people = []
        for i in range(31315, 25315, -1):  #40C to -20C
            if hist[i][0] != 0:
                people.append(i)
        i_pre = people[0]
        people_segmentation = [[]]
        people_segmentation[0].append(i_pre)
        j = 0
        for i in range(1, len(people)):
            c_data = people[i]
            if i_pre - c_data < 300:     #segmentation theshold
                people_segmentation[j].append(c_data)
            else:
                j += 1
                people_segmentation.append([])
                people_segmentation[j].append(c_data)
                i_pre = c_data
        #canny 
        c_val = (c_val - 27315) / 100
        mask = cv2.inRange(c_val, (people_segmentation[0][-1] - 27315) / 100, (people_segmentation[0][0] - 27315) / 100)
        c_mean = (sum(people_segmentation[0])/len(people_segmentation[0]) - 27315) / 100
        if c_mean > (sum(people_segmentation[-1])/len(people_segmentation[-1]) - 27315) / 100 + 2:    #Separation value from floor
            detected = True
        else:
            detected = False
        return mask, c_mean, detected
        
    def stat_pub(self, event):
        self.t += 1
        if self.t < 10:
            status.good = True
        else:
            status.good = False
        pub_status.publish(status)
    
if __name__ == '__main__':
    rospy.init_node('thermal_image_processor', anonymous=True)
    ThermalImageProcessor()
    rospy.spin()
