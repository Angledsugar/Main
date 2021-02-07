#!/bin/bash
source /opt/ros/noetic/setup.bash 
source /home/ubuntu/life_ws/devel/setup.bash

sudo chmod 777 /dev/ttyUSB*



gpio -g write 17 0
sleep 0.2
gpio -g write 17 1


sleep 2

rosrun sensor_check sensor_check_node
