#include "ros/ros.h"
#include "life_msgs/Status.h"
#include "life_msgs/Cam.h"
#include "life_msgs/IR.h"
#include "life_msgs/Motor_set.h"
#include "life_msgs/Robot_state.h"


life_msgs::IR IR_data;
life_msgs::Cam Cam_data;
life_msgs::Robot_state robot;

void IR_CB(const life_msgs::IR &msg){
	IR_data = msg;
}

void Cam_CB(const life_msgs::Cam &msg){
	Cam_data = msg;
}

void Imu_CB(const life_msgs::Robot_state &msg){
	robot = msg;
}
