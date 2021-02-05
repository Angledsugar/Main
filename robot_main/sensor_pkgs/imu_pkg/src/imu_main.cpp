#include "imu.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
int main(int argc, char** argv){
	ros::init(argc,argv,"IMU_NODE");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<sensor_msgs::Imu>("/life/imu",1);
	sensor_msgs::Imu imu_msg;
	IMU my_ahrs("/dev/ttyACM0");
	ROS_INFO("SETTING IMU...");
	if(!my_ahrs.initialize())
		handle_error("Can't initialize imu");
	ROS_INFO("START NODE");
	while(ros::ok()){
		imu_msg.header.stamp = ros::Time::now();
		
		imu_msg.orientation.x = my_ahrs.e.roll;
		imu_msg.orientation.y = my_ahrs.e.pitch;
		imu_msg.orientation.z = my_ahrs.e.yaw;
		imu_msg.orientation.w = 0;
		
		imu_msg.angular_velocity.x = my_ahrs.imu.gx;
		imu_msg.angular_velocity.y = my_ahrs.imu.gy;
		imu_msg.angular_velocity.z = my_ahrs.imu.gz;

		imu_msg.linear_acceleration.x = my_ahrs.imu.ax;
		imu_msg.linear_acceleration.y = my_ahrs.imu.ay;
		imu_msg.linear_acceleration.z = my_ahrs.imu.az;
		
		pub.publish(imu_msg);
	}
	return 0;
}
