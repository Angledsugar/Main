#ifndef LIFE_
#define LIFE_

#include "ros/ros.h"
#include "life_msgs/Status.h"
#include "life_msgs/Cam.h"
#include "life_msgs/IR.h"
#include "life_msgs/Motor_set.h"
#include "life_msgs/Imu.h"

namespace Life{

	struct Person{
		bool result;
		float angle;
		float is_close;
	};
	
	const float CAM_FOV  = 57;
	
	class Robot
	{

		public:		
			Robot();
			~Robot();
			
			// message clab
			void IR_CB(const life_msgs::IR &msg);
			void Cam_CB(const life_msgs::Cam &msg);
			void Imu_CB(const life_msgs::Imu &msg);
			void Sensor_CB(const life_msgs::Status &msg);
			
			// robot funtion
			void send_gps(bool mode);
			void motor_move(float left,float right);
			
			// Robot data
			Person person;
			bool robot_state;
			int imu_state;
			
		private:
			// Node handler
			ros::NodeHandle nh_;
			
			// Subscriber
			ros::Subscriber ir_sub_;
			ros::Subscriber cam_sub_;
			ros::Subscriber imu_sub_;
			ros::Subscriber state_sub_;
			
			// Pusblisher
			ros::Publisher motor_pub_;
			
			// Robot messages
			life_msgs::Motor_set motor_msg_;
	};
}
#endif
