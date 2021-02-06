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
		const int FULL_FORCE = 0;
		const int X_FORCE = 1;
		const int Y_FORCE = 2;
		const int Z_FORCE = 3;
		typedef geometry_msgs::Vector3 L_VECTOR;
		public:
			Life(ros::NodeHandle& nh);
			~Life();
			float get_force(int mode = 0);
			float get_cross();
			L_VECTOR get_angle_vel();
			L_VECTOR get_person_posinton();
			bool is_find_person();
		private:
			L_VECTOR _std_vector;
			geometry_msgs::Quaternion _rot;
			L_VECTOR _ag_vel;
			L_VECTOR _lin_acc;
			L_VECTOR _rb_vetor;
			L_VECTOR _roted_lin_acc,_roted_ag_vel;
			L_VECTOR _roted_person;
			bool _is_person;
			ros::NodeHandle _nh;
			ros::Subscriber _imu,_cam;
			void Imu_CB(const sensor_msgs::Imu &msg);
			void Cam_CB(const life_msgs::Cam &msg);
	};
};
#endif
