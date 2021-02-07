#!/bin/bash
source /opt/ros/noetic/setup.bash 
source /home/ubuntu/life_ws/devel/setup.bash


./home/ubuntu/life_ws/src/booting/sensor_test.sh &

rosrun gps_n_lora gps_n_lora_node 




