#ifndef _LIFE_ROS
#define _LIFE_ROS
#include "ros/ros.h"
#include "life_msgs/IR.h"
#include "life_msgs/Imu.h"
#include "sensor_msgs/Imu.h"
#include <queue>
#include <algorithm>
#include "rotation.h"
	class Life{
		typedef geometry_msgs::Vector3 L_VECTOR;
		public:
			Life(ros::NodeHandle& nh);
			~Life();
			bool is_drop();
			void find_person();
			void go_to_person();
			void wait_lifeguard();
		private:
			L_VECTOR _std_vector;
			geometry_msgs::Quaternion _rot;
			L_VECTOR _ag_vel;
			L_VECTOR _lin_acc;
			L_VECTOR _rb_vetor;
			L_VECTOR _roted_lin_acc,_roted_ag_vel;
			ros::NodeHandle _nh;
			ros::Subscriber _imu;
			void Imu_CB(const sensor_msgs::Imu &msg);
	};
#endif
