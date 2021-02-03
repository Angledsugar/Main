#include "imu.h"
#include "ros/ros.h"
#include "life_msgs/Imu.h"
int main(int argc, char** argv){
	ros::init(argc,argv,"IMU_NODE");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<life_msgs::Imu>("/Imu",1);
	life_msgs::Imu imu_msg;
	IMU my_ahrs("/dev/ttyACM0");
	if(!my_ahrs.initialize())
		handle_error("Can't initialize imu");
	while(ros::ok()){
		imu_msg.vel.x = 0;
		imu_msg.vel.y = 0;
		imu_msg.vel.z = 0;

		imu_msg.accel.x = my_ahrs.rotated.r_ax;
		imu_msg.accel.y = my_ahrs.rotated.r_ay;
		imu_msg.accel.z = my_ahrs.rotated.r_az;

		imu_msg.pose.roll = my_ahrs.e.roll;		
		imu_msg.pose.pitch = my_ahrs.e.pitch;
		imu_msg.pose.yaw = my_ahrs.e.yaw;

		pub.publish(imu_msg);
	}
	return 0;
}