#ifndef _LIFE_ROS
#define _LIFE_ROS
#include "ros/ros.h"
#include "life_msgs/IR.h"
#include "life_msgs/Cam.h"
#include "sensor_msgs/Imu.h"
#include "life_msgs/Status.h"
#include "rotation.hpp"
#define CAM_X_RANGE 160
#define CAM_Y_RANGE 120
#define CAM_FOV_HORIZON 57
#define CAM_FOV_VERTICAL 49.6492314863
#define ROBOT_MASS 8.5
#define IR_NUM 5
namespace LIFE{
	class Life{
		
		typedef geometry_msgs::Vector3 L_VECTOR;
		public:
			const static int FULL_FORCE = 0;
			const static int X_FORCE = 1;
			const static int Y_FORCE = 2;
			const static int Z_FORCE = 3;
			const static int ALL_SENSOR = 0;
			const static int CAM = 1;
			const static int MOTOR = 2;
			Life(ros::NodeHandle& nh);
			~Life();
			float get_force(int mode = FULL_FORCE);
			float get_cross();
			L_VECTOR get_angle_vel();
			L_VECTOR get_person_position();
			bool is_find_person();
			bool is_close_person();
			bool is_sensor_good(int mode = ALL_SENSOR);
		private:
			L_VECTOR _std_vector;
			geometry_msgs::Quaternion _rot;
			L_VECTOR _ag_vel;
			L_VECTOR _lin_acc;
			L_VECTOR _rb_vetor;
			L_VECTOR _roted_lin_acc,_roted_ag_vel;
			L_VECTOR _roted_person;
			bool _is_person,_is_close;
			bool _is_good_cam,_is_good_motor;
			ros::NodeHandle _nh;
			ros::Subscriber _imu,_cam,_ir;
			ros::Subscriber _st_cam,_st_motor;
			void Imu_CB(const sensor_msgs::Imu &msg);
			void Cam_CB(const life_msgs::Cam &msg);
			void IR_CB(const life_msgs::IR &msg);
			void ST_Cam_CB(const life_msgs::Status &msg);
			void ST_Motor_CB(const life_msgs::Status &msg);
	};
};
#endif
