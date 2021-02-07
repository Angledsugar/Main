#!/bin/bash
source /opt/ros/melodic/setup.bash
source /home/ubuntu/life_ws/devel/setup.bash

roscore &

sleep 2

rosrun hello hello 
