#ifndef _LIFE_MOTOR
#define _LIFE_MOTOR
#include "ros/ros.h"
#include "life_msgs/Motor_set.h"
namespace LIFE{
	class Motor{
		const bool MOTOR_FRONT_DIR = true;
		const bool MOTOR_BACK_DIR = false;
		public:
			Motor(ros::NodeHandle& nh);
			~Motor(){};
			void move(float angle,float linear);
		private:
			ros::NodeHandle _nh;
			ros::Publisher _motor_pub;
			life_msgs::Motor_set _motor_msg;
	};
};
#endif
