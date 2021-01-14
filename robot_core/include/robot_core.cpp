#include "robot_core.h"
using namespace Life;

Robot::Robot() {
	// Subscriber setting
	ir_sub_ = nh_.subscribe("/life/IR", 1 , &Robot::IR_CB , this); 
	cam_sub_ = nh_.subscribe("/life/Cam", 1 , &Robot::Cam_CB , this);
	state_sub_ = nh_.subscribe("/life/Robot_state", 1 , &Robot::Imu_CB,this);
	
	// Publisher setting
	motor_pub_ = nh_.advertise<life_msgs::Motor_set>("/life/Motor",1); 
	st_pub_ = nh_.advertise<life_msgs::Motor_set>("/life/Status/Robot",1); 
	person_.is_close = false;
	ROS_INFO("Subscriber and Publisher is ok");
}


Robot::~Robot(){
}


void Robot::IR_CB(const life_msgs::IR &msg){
	ROS_INFO("IR MESSAGE GET");
	if(msg.ir1 < 700 || msg.ir2 < 700 || msg.ir3 < 700 || msg.ir4 < 700 || msg.ir5 < 700)
		person_.is_close = true;
	else
		person_.is_close = false;
}


void Robot::Cam_CB(const life_msgs::Cam &msg){
	ROS_INFO("CAMERA MESSAGE GET");
	person_.angle = msg.angle * CAM_FOV/2;
}


void Robot::Imu_CB(const life_msgs::Robot_state &msg){
	ROS_INFO("IMU MESSAGE GET");
	robot_ = msg;
}

void Robot::send_gps(bool mode){

}


void Robot::motor_move(float left,float right){
	if(left >= 0){
		motor_msg_.left.dir = true;
		motor_msg_.left.speed = left;
	}
	else{
		motor_msg_.left.dir = false;
		motor_msg_.left.speed = -left;
	}
	if(right >= 0){
		motor_msg_.right.dir = true;
		motor_msg_.right.speed = right;
	}
	else{
		motor_msg_.right.dir = false;
		motor_msg_.right.speed = -right;
	}
	motor_pub_.publish(motor_msg_);
}


