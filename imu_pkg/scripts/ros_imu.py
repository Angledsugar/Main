#!/usr/bin/env python3
import rospy
from imu_kalman import Imu_kalman
from life_msgs.msg import Imu
import math
class Imu_ros:
    def __init__(self) :
        self.imu_sensor = Imu_kalman()
        rospy.init_node('IMU', anonymous=True)
        self.imu_data = Imu()
        self.pub = rospy.Publisher('/life/Imu', Imu, queue_size=11)
    def imu_data_pub(self) :
        self.imu_data.accel.x,self.imu_data.accel.y,self.imu_data.accel.z,self.imu_data.pose.roll,self.imu_data.pose.pitch,self.imu_data.pose.yaw  = self.imu_sensor.read_imu()
        #self.imu_data.pose.roll , self.imu_data.pose.pitch , self.imu_data.pose.yaw = self.rotation()
        self.pub.publish(self.imu_data)
    def rotation(self) :
        self.x = math.cos(self.imu_data.pose.roll) * math.sin(self.imu_data.pose.pitch) * math.cos(self.imu_data.pose.yaw) + math.sin(self.imu_data.pose.roll) * math.sin(self.imu_data.pose.yaw)
        self.y = math.sin(self.imu_data.pose.roll) * math.sin(self.imu_data.pose.pitch) * math.cos(self.imu_data.pose.yaw) - math.cos(self.imu_data.pose.roll) * math.sin(self.imu_data.pose.yaw)
        self.z = math.cos(self.imu_data.pose.pitch)*math.cos(self.imu_data.pose.yaw)
        return self.x,self.y,self.z

if __name__=='__main__':
    print ("SETTING IMU...")
    imu_ros = Imu_ros()
    print("NODE IS UP!!")
    while not rospy.is_shutdown():
        imu_ros.imu_data_pub() 
