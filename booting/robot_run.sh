#!/bin/bash
source /opt/ros/noetic/setup.bash 
source /home/ubuntu/life_ws/devel/setup.bash
gpio -g mode 17 output
gpio -g mode 22 output
gpio -g mode 27 output
gpio -g write 17 0
gpio -g write 27 0
gpio -g write 22 0
sleep 1

gpio -g write 17 1
sleep 0.2
roscore 


#gpio -g write 17 0
#sleep 0.2
#gpio -g write 27 1


