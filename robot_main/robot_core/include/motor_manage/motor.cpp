#include "motor.h"
using namespace LIFE;
Motor::Motor(ros::NodeHandle& nh) : _nh(nh) {
	_motor_pub = _nh.advertise<life_msgs::Motor>("/life/Motor",1);
	_motor_msg.angle = 0;
	_motor_msg.linear = 0;	
}

void Motor::move(float angle,float linear){
	_motor_msg.angle = angle;
	_motor_msg.linear = linear;
	_motor_pub.publish(_motor_msg);
}
