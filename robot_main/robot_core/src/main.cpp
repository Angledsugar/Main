#include "life_ros.h"
#include "filter.h"
#include "life_pid.h"
int main(int argc,char** argv){
	ros::init(argc,argv,"ROBOT_CORE");
	ros::NodeHandle nh;
	LIFE::Life life(nh);
	LIFE::Filter filter(0.7);
	LIFE::PID angle_pid(5,0,0) , linear_pid(5,0,0);
	angle_pid.init(1.57,0);
	linear_pid.init(3,0);
	enum State{TURN_ON , DROPPED , CLOSE , GRAPPED};
	State state = TURN_ON;
	while(ros::ok()){
		if(state ==  TURN_ON){
			float now_force = life.get_force();
			float filter_force = filter.high_pass(now_force);
			float now_cross = life.get_cross();				
			float filter_cross = filter.low_pass(now_cross);
			float valid_force =  abs(filter_force);
			ROS_INFO("FORCE : %f , CROSS : %f",valid_force,filter_cross);
			if(filter_force>100 && filter_cross > 0.6){
				ROS_INFO("DROPPED!!");
				state = DROPPED;
			}
		}
		else if(state == DROPPED){
				LIFE::L_VECTOR person = life.get_person_posinton();
				
		};
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	return 0;
}
