#!/usr/bin/env python3
import rospy

	
import numpy as np
import math as m
#from imu_kalman import Imu_kalman
from imu_madgwick import Imu_madgwick
from life_msgs.msg import Imu
import math

class Imu_ros:
    def __init__(self) :
        self.imu_sensor = Imu_madgwick()
        rospy.init_node('IMU', anonymous=True)
        self.imu_data = Imu()
        self.pub = rospy.Publisher('/life/Imu', Imu, queue_size=11)
        self.f_x = 0
        self.f_y = 0
        self.f_z = 0
        self.pre_x = 0
        self.pre_y = 0
        self.pre_z = 0
    def imu_data_pub(self) :
        self.imu_data.accel.x,self.imu_data.accel.y,self.imu_data.accel.z,self.imu_data.pose.roll,self.imu_data.pose.pitch,self.imu_data.pose.yaw  = self.imu_sensor.read_imu()
        self.R = self.Rz(0) *self.Ry(m.radians(self.imu_data.pose.pitch)) * self.Rx(m.radians(self.imu_data.pose.roll))
        self.imu_data.accel.x = self.R.item(0,0)*self.imu_data.accel.x + self.R.item(0,1)*self.imu_data.accel.y + self.R.item(0,2)*self.imu_data.accel.y
        self.imu_data.accel.y = self.R.item(1,0)*self.imu_data.accel.x + self.R.item(1,1)*self.imu_data.accel.y + self.R.item(1,2)*self.imu_data.accel.z
        self.imu_data.accel.z = self.R.item(2,0)*self.imu_data.accel.x + self.R.item(2,1)*self.imu_data.accel.y + self.R.item(2,2)*self.imu_data.accel.z
        self.imu_data.accel.z -= 11.5
         
        self.f_x = 0.9*(self.f_x + self.imu_data.accel.x  - self.pre_x)
        self.f_y = 0.9*(self.f_y + self.imu_data.accel.y  - self.pre_y)
        self.f_z = 0.9*(self.f_z + self.imu_data.accel.z  - self.pre_z)
        self.pre_x = self.imu_data.accel.x
        self.pre_y = self.imu_data.accel.y
        self.pre_z = self.imu_data.accel.z 
        self.imu_data.accel.y = self.f_x
        self.imu_data.accel.x = self.f_y
        self.imu_data.accel.z = self.f_z
        self.Force = (abs(self.imu_data.accel.x) + abs(self.imu_data.accel.y) + abs(self.imu_data.accel.z))*0.25
        if self.Force > 18 : 
            self.imu_data.state = 1
        else :
            self.imu_data.state = 0
        print("Force : ",self.Force)
        
        self.pub.publish(self.imu_data)
    def Rx(self,theta):
        return np.matrix([[1,0,0],[ 0, m.cos(theta),-m.sin(theta)],[ 0, m.sin(theta), m.cos(theta)]])

    def Ry(self,theta):
        return np.matrix([[ m.cos(theta), 0, m.sin(theta)],[ 0, 1, 0],[-m.sin(theta), 0, m.cos(theta)]])

    def Rz(self,theta):
        return np.matrix([[ m.cos(theta), -m.sin(theta), 0 ],[ m.sin(theta), m.cos(theta) , 0 ],[ 0, 0,1 ]])

if __name__=='__main__':
    print ("SETTING IMU...")
    imu_ros = Imu_ros()
    print("NODE IS UP!!")
    while not rospy.is_shutdown():
        imu_ros.imu_data_pub() 
