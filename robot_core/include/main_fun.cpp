#include "ros_fun.cpp"
int step = 0;
void ready_sensor(){
	if(robot.state == 0){
		ROS_INFO("ROBOT IS NOW PREPARING...");
	}
	else{
		ROS_INFO("ROBOT IS NOW FALLING...");
		step++;
	}
}

void find_person(){
	ROS_INFO("ROBOT IS NOW FINDING PERSON...");
};
