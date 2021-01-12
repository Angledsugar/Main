#!/bin/bash
source /opt/ros/noetic/setup.bash 
source /home/ubuntu/life_ws/devel/setup.bash
for ((i = 0; i<10;i++))
do
rostopic pub -1 /life/Status/IR life_msgs/Status "good: true" & 
rostopic pub -1 /life/Status/Cam life_msgs/Status "good: true" &
rostopic pub -1 /life/Status/Imu life_msgs/Status "good: true" &
rostopic pub -1 /life/Status/Motor life_msgs/Status "good: true" 

sleep 2

rostopic pub -1 /life/Status/IR life_msgs/Status "good: true" & 
rostopic pub -1 /life/Status/Cam life_msgs/Status "good: false" &
rostopic pub -1 /life/Status/Imu life_msgs/Status "good: true" &
rostopic pub -1 /life/Status/Motor life_msgs/Status "good: true" 
sleep 2

done
