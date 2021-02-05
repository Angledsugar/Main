#ifndef _LIFE_ROS
#define _LIFE_ROS
#include "ros/ros.h"
#include "life_msgs/IR.h"
#include "life_msgs/Imu.h"
#include "sensor_msgs/Imu.h"
	class Life{
		public:
			Life(ros::NodeHandle& nh);
			~Life();
			void turn_on();
			void find_person();
			void go_to_person();
			void wait_lifeguard();
		private:
			geometry_msgs::Quaternion rot;
			geometry_msgs::Vector3 ag_vel;
			geometry_msgs::Vector3 lin_acc;
			ros::NodeHandle _nh;
			ros::Subscriber _imu;
			void Imu_CB(const sensor_msgs::Imu &msg);
	};
#endif
