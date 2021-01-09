#!/bin/bash
source /opt/ros/noetic/setup.bash 
source /home/ubuntu/life_ws/devel/setup.bash

roscore &
sudo chmod 777 /dev/ttyUSB*

sleep 2


rosrun gps_n_lora gps_n_lora_node &

rosrun hello hello 
