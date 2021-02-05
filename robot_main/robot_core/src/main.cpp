#include "life_ros.h"

int main(int argc,char** argv){
	ros::init(argc,argv,"ROBOT_CORE");
	ros::NodeHandle nh;
	Life life(nh);
	while(ros::ok()){
	}
	return 0;
}
