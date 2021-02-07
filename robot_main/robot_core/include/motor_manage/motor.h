#ifndef _LIFE_MOTOR
#define _LIFE_MOTOR
#include "ros/ros.h"
#include "life_msgs/Motor.h"
namespace LIFE{
	class Motor{
		public:
			Motor(ros::NodeHandle& nh);
			~Motor(){};
			void move(float angle,float linear);
		private:
			ros::NodeHandle _nh;
			ros::Publisher _motor_pub;
			life_msgs::Motor _motor_msg;
	};
};
#endif
