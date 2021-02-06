#ifndef _LIFE_ROS
#define _LIFE_ROS
#include "ros/ros.h"
#include "life_msgs/IR.h"
#include "life_msgs/Imu.h"
#include "life_msgs/Cam.h"
#include "sensor_msgs/Imu.h"
#include <queue>
#include <algorithm>
#include "rotation.hpp"
#define CAM_X_RANGE 160
#define CAM_Y_RANGE 120
#define CAM_FOV_HORIZON 57
#define CAM_FOV_VERTICAL 49.6492314863
namespace LIFE{
	class Life{
		typedef geometry_msgs::Vector3 L_VECTOR;
		public:
			Life(ros::NodeHandle& nh);
			~Life();
			float get_force();
			float get_cross();
			L_VECTOR get_person_posinton();
		private:
			L_VECTOR _std_vector;
			geometry_msgs::Quaternion _rot;
			L_VECTOR _ag_vel;
			L_VECTOR _lin_acc;
			L_VECTOR _rb_vetor;
			L_VECTOR _roted_lin_acc,_roted_ag_vel;
			L_VECTOR _roted_person;
			ros::NodeHandle _nh;
			ros::Subscriber _imu,_cam;
			void Imu_CB(const sensor_msgs::Imu &msg);
			void Cam_CB(const life_msgs::Cam &msg);
	};
};
#endif
