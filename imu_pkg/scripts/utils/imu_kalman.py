import os
import sys
import time
import smbus
import numpy as np

from imusensor.MPU9250 import MPU9250
from imusensor.filters import kalman 

class Imu_kalman():
    def __init__(self) :
        self.address = 0x68
        self.bus = smbus.SMBus(1)
        self.imu = MPU9250.MPU9250(self.bus, self.address)
        self.imu.begin()
        self.imu.loadCalibDataFromFile("/home/ubuntu/life_ws/src/imu_pkg/config/calib.json")
        self.sensorfusion = kalman.Kalman()
        self.imu.readSensor()
        self.imu.computeOrientation()
        self.sensorfusion.roll = imu.roll
        self.sensorfusion.pitch = imu.pitch
        self.sensorfusion.yaw = imu.yaw
        self.currTime = time.time()
    def read_imu(self) :
        self.imu.readSensor()
        self.imu.computeOrientation()
        self.newTime = time.time()
        self.dt = self.newTime - self.currTime
        self.currTime = self.newTime
        self.sensorfusion.computeAndUpdateRollPitchYaw(self.imu.AccelVals[0], self.imu.AccelVals[1], self.imu.AccelVals[2], self.imu.GyroVals[0], self.imu.GyroVals[1], self.imu.GyroVals[2],\
										            self.imu.MagVals[0], self.imu.MagVals[1], self.imu.MagVals[2], self.dt)

        return self.imu.AccelVals,self.sensorfusion.roll,self.sensorfusion.pitch,self.sensorfusion.yaw
	    
