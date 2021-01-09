#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc , char** argv){

	ros::init(argc,argv,"HI_NODE");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<std_msgs::String>("HI",1);
	std_msgs::String msg;
	msg.data = "Hello";
	while(ros::ok()){
		pub.publish(msg);
		ros::Duration(1).sleep();
	}
	return 0;
}
