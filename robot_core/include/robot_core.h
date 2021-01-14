#ifndef LIFE_
#define LIFE_

#include "ros/ros.h"
#include "life_msgs/Status.h"
#include "life_msgs/Cam.h"
#include "life_msgs/IR.h"
#include "life_msgs/Motor_set.h"
#include "life_msgs/Robot_state.h"

namespace Life{

	struct Person{
		float angle;
		float is_close;
	};
	
	
	class Robot
	{

		public:
			const float CAM_FOV  = 57;		
			
			Robot();
			~Robot();
			
			// message clab
			void IR_CB(const life_msgs::IR &msg);
			void Cam_CB(const life_msgs::Cam &msg);
			void Imu_CB(const life_msgs::Robot_state &msg);
			
			// robot funtion
			void send_gps(bool mode);
			void motor_move(float left,float right);
			
			// person data
			Person person_;
			
		private:
			// Node handler
			ros::NodeHandle nh_;
			
			// Subscriber
			ros::Subscriber ir_sub_;
			ros::Subscriber cam_sub_;
			ros::Subscriber state_sub_;
			
			// Pusblisher
			ros::Publisher motor_pub_;
			ros::Publisher st_pub_;
			
			// Robot messages
			life_msgs::Motor_set motor_msg_;
	    		life_msgs::Status state_;
	    		life_msgs::Robot_state robot_;
	    		
	    		// Robot data
			

	};
}
#endif
