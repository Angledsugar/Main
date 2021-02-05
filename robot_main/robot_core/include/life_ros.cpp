#include "life_ros.h"
Life::Life(ros::NodeHandle& nh) : _nh(nh){
	_imu = _nh.subscribe("/life/imu", 1,&Life::Imu_CB,this);
	_std_vector.x = 0;
	_std_vector.y = 0;
	_std_vector.z = 1;
}

Life::~Life(){};

bool Life::is_drop(){
	_rb_vetor = transform(_rot,_std_vector);
	float cross = _rb_vetor.z*_std_vector.z;
	float force = (_roted_lin_acc.x + _roted_lin_acc.y + _roted_lin_acc.z)*6.5;

	ROS_INFO("force : %f",force);
	if(force > 124){
		ROS_INFO("DROPPED");
		return true;
	}
	return false;
};
void Life::Imu_CB(const sensor_msgs::Imu &msg){
	_rot = msg.orientation;
	_rot.z = 0;
	_ag_vel = msg.angular_velocity;
	_lin_acc = msg.linear_acceleration;
	_roted_lin_acc = inv_transform(_rot,_lin_acc);
	_roted_ag_vel = inv_transform(_rot,_ag_vel);
	_roted_lin_acc.z++;
	
};

