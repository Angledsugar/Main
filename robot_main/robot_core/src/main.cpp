#include "life_ros.h"
#include "filter.h"
int main(int argc,char** argv){
	ros::init(argc,argv,"ROBOT_CORE");
	ros::NodeHandle nh;
	LIFE::Life life(nh);
	LIFE::Filter filter(0.7);
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
				ROS_INFO("PERSON : %f , %f , %f",person.x,person.y,person.z);
		};
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	return 0;
}
