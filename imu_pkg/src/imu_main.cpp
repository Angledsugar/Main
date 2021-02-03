#include "imu.h"
#include "ros/ros.h"
int main(int argc, char** argv){
	ros::init(argc,argv,"IMU_NODE");
	ros::NodeHandle nh;
	IMU my_ahrs("/dev/ttyACM0");
	if(!my_ahrs.initialize())
		handle_error("Can't initialize imu");
	while(ros::ok()){
		
	}
	return 0;
}