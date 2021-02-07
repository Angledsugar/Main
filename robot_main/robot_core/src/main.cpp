#include "life_ros.h"
#include "filter.h"
#include "life_pid.h"
#include "motor.h"
int main(int argc,char** argv){
	ros::init(argc,argv,"ROBOT_CORE");
	ros::NodeHandle nh;
	LIFE::Life life(nh);
	LIFE::Filter filter(0.7);
	LIFE::PID angle_pid(0.4,0.01,0),linear_pid(1,0.1,0);
	LIFE::Motor motor(nh);
	angle_pid.init(90,0);
	linear_pid.init(30,0);
	enum State{TURN_ON , DROPPED ,GO , CLOSE , GRAPPED};
	State state = GO;
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
				angle_pid.set_target(90);
				linear_pid.set_target(0);
				now_force = 0;
			}
		}
		else if(state == DROPPED){
				if(life.is_sensor_good(LIFE::Life::ALL_SENSOR)){
					angle_pid.set_target(90);
					if(!life.is_find_person()){
						LIFE::L_VECTOR angle_spd = life.get_angle_vel();
						float angle_gain = angle_pid.calculate(angle_spd.z);
						float now_force = life.get_force(LIFE::Life::X_FORCE);
						float filter_force = filter.low_pass(now_force);
						static float force_sum = 0;
						force_sum += filter_force;
						float linear_gain = linear_pid.calculate(now_force);
						motor.move(angle_gain,linear_gain);
						ROS_INFO("angle_gain : %f , linear_gain : %f , FORCE : %f",angle_gain,linear_gain,now_force);
					}
					else{
						LIFE::L_VECTOR person = life.get_person_position();
						angle_pid.set_target(person.x);
						linear_pid.set_target(5);
						state = GO;
					}
				}
				else{
					angle_pid.set_target(0);
				}
		}
		else if(state == GO){
			if(!life.is_close_person()){
				float now_force = life.get_force(LIFE::Life::X_FORCE);
				float filter_force = filter.low_pass(now_force);
				static float force_sum = 0;
				force_sum += filter_force;
				float linear_gain = linear_pid.calculate(now_force);
				if(life.is_sensor_good(LIFE::Life::CAM)){
					LIFE::L_VECTOR angle_spd = life.get_angle_vel();
					LIFE::L_VECTOR person = life.get_person_position();
					angle_pid.set_target(person.x);
					float angle_gain = angle_pid.calculate(angle_spd.z);
					motor.move(angle_gain,linear_gain);
				}
				else{
					motor.move(0,linear_gain);
				}
			}
			else{
				motor.move(0,0);
				state = CLOSE;
			}
		}
		else if(state == CLOSE){
			float now_force = life.get_force(LIFE::Life::FULL_FORCE);
			float filter_low_pass = filter.low_pass(now_force);
			now_force -= filter_low_pass;
			float filter_high_force = filter.high_pass(now_force);
			if(abs(filter_high_force) > 30){
				ROS_INFO("GRAPPED!!");
				state = GRAPPED;
			}
			
		}
		else if(state == GRAPPED){
			//lora
		}
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	return 0;
}
