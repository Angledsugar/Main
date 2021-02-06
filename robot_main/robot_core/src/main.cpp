#include "life_ros.h"
#include "filter.h"
#include "life_pid.h"
int main(int argc,char** argv){
	ros::init(argc,argv,"ROBOT_CORE");
	ros::NodeHandle nh;
	LIFE::Life life(nh);
	LIFE::Filter filter(0.7);
	LIFE::PID angle_pid(5,0,0),linear_pid(5,0,0);
	angle_pid.init(1.57,0);
	linear_pid.init(3,0);
	enum State{TURN_ON , DROPPED ,GO,CLOSE , GRAPPED};
	State state = TURN_ON;
	while(ros::ok()){
		if(state ==  TURN_ON){
			float now_force = life.get_force(LIFE::Life::FULL_FORCE);
			float filter_force = filter.high_pass(now_force);
			float now_cross = life.get_cross();				
			float filter_cross = filter.low_pass(now_cross);
			float valid_force =  abs(filter_force);
			ROS_INFO("FORCE : %f , CROSS : %f",valid_force,filter_cross);
			if(filter_force>100 && filter_cross > 0.6){
				ROS_INFO("DROPPED!!");
				state = DROPPED;
				filter.reset();
				filter.set_cutting_frequency(0.9);
				angle_pid.set_target(1.5);
			}
		}
		else if(state == DROPPED){
				if(!life.is_find_person()){
					LIFE::L_VECTOR angle_spd = life.get_angle_vel();
					float pid_gain = angle_pid.calculate(angle_spd.z);
					
				}
				else{
					LIFE::L_VECTOR person = get_person_posinton();
					state = GO;
				}
				
		}
		else if(state == GO){
			float now_force = life.get_force(LIFE::Life::X_FORCE);
			float filter_force = filter.low_pass(now_force);
		}
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	return 0;
}
