#include "life_ros.h"
Life::Life(ros::NodeHandle& nh) : _nh(nh){
	_imu = _nh.subscribe("/life/imu", 1,&Life::Imu_CB,this);
}

Life::~Life(){};

void Life::Imu_CB(const sensor_msgs::Imu &msg){
	rot = msg.orientation;
	ag_vel = msg.angular_velocity;
	lin_acc = msg.linear_acceleration;
};

