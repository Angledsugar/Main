#!/bin/bash
source /opt/ros/noetic/setup.bash 
source /home/ubuntu/life_ws/devel/setup.bash

cd /home/ubuntu/life_ws/src/test/test_record
rosbag record -a --duration=10m
