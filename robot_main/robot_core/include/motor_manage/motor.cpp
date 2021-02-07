#include "motor.h"
using namespace LIFE;
Motor::Motor(ros::NodeHandle& nh) : _nh(nh) {
	_motor_pub = _nh.advertise<life_msgs::Motor_set>("/life/motor",1);
	_motor_msg.left.dir = MOTOR_FRONT_DIR;
	_motor_msg.left.speed = 0;
	_motor_msg.right.dir = MOTOR_FRONT_DIR;
	_motor_msg.right.speed = 0;	
}

void Motor::move(float angle,float linear){
	
	_motor_pub.publish(_motor_msg);
}
