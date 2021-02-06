#include "life_ros.h"
using namespace LIFE;
Life::Life(ros::NodeHandle& nh) : _nh(nh){
	_imu = _nh.subscribe("/life/imu", 1,&Life::Imu_CB,this);
	_cam = _nh.subscribe("/life/Cam", 1,&Life::Cam_CB,this);
	_std_vector.x = 0;
	_std_vector.y = 0;
	_std_vector.z = 1;
	_roted_person.x = 0;
	_roted_person.y = 0;
	_roted_person.z = 0;
}

Life::~Life(){};

float Life::get_force(){
	float force = (_roted_lin_acc.x + _roted_lin_acc.y + _roted_lin_acc.z)*6.5;
	return force;
};
float Life::get_cross(){
	_rb_vetor = transform(_rot,_std_vector);
	return _rb_vetor.z*_std_vector.z;
}

L_VECTOR Life::get_person_posinton(){
	return _roted_person;
}

void Life::Imu_CB(const sensor_msgs::Imu &msg){
	_rot = msg.orientation;
	_rot.z = 0;
	_ag_vel = msg.angular_velocity;
	_lin_acc = msg.linear_acceleration;
	_roted_lin_acc = inv_transform(_rot,_lin_acc);
	_roted_ag_vel = inv_transform(_rot,_ag_vel);
	_roted_lin_acc.z++;
	
};

void Life::Cam_CB(const life_msgs::Cam &msg){
	if(msg.result){
		L_VECTOR person;
		person.x = msg.x*CAM_FOV_HORIZON/CAM_X_RANGE;
		person.y = 0;
		person.z = msg.y*CAM_FOV_VERTICAL/CAM_Y_RANGE;
		_roted_person = inv_transform(_rot,person);
		_roted_person.y = 20;
	}
}
