#include "core.h"

using namespace Life;

Core::Core() : Robot(){
    step_set_(TURN_ON);
	wiringPiSetupGpio();
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,LOW);
};


Core::~Core(){
}


void Core::prepare(){
	if(robot_state){
		digitalWrite(RED,LOW);
        digitalWrite(GREEN,LOW);
        digitalWrite(BLUE,HIGH);
        if(imu_state == IMU_DROPPED){
            //step_set_(DROPPED);
            digitalWrite(RED,LOW);
            digitalWrite(GREEN,HIGH);
            digitalWrite(BLUE,LOW);
            ros::Duration(1).sleep();
		}
	}
	else{
	    digitalWrite(RED,HIGH);
        digitalWrite(GREEN,LOW);
        digitalWrite(BLUE,LOW);
	}
}


void Core::find_person(){
	if(person.result){
		step_set_(MOVE_PERSON);
	}
	else{
		motor_move(2,-2);
	}
}


void Core::go_to_person(){
	if(person.is_close){
		ROS_INFO("person is close");
		step_set_(WAIT_FOR_PERSON_GRAPPING);
	}
}


void Core::person_grap(){
	if(imu_state == IMU_GRAPPED){
		step_set_(WAIT_LIFE_GUARD);
	}
}


void Core::maintain(){
}


void Core::clear_step(){
	ROS_INFO("STATE RESET");
	step_ = TURN_ON;
}

const int Core::get_step(){
	return step_;
}


void Core::step_set_(int n){
	switch(n){
		case TURN_ON : 
			ROS_INFO("NOW ROBOT IS TURN ON ...");
			step_ = TURN_ON;
			break;
		case DROPPED:
			ROS_INFO("NOW ROBOT IS DROPPED ...");
			step_ = DROPPED;
			break;
		case MOVE_PERSON:
			ROS_INFO("NOW ROBOT IS MOVE TO PERSON ...");
			step_ = MOVE_PERSON;
			break;
		case WAIT_FOR_PERSON_GRAPPING :
			ROS_INFO("NOW ROBOT IS FONT OF PERSON ...");
			step_ = WAIT_FOR_PERSON_GRAPPING;
			break;
		case WAIT_LIFE_GUARD :
			ROS_INFO("NOW ROBOT WAIT FOR GUARD ...");
			step_ = WAIT_LIFE_GUARD;
			break;
		default :
			ROS_INFO("ERROR STATE : %d ", n );
			ROS_INFO("STATE RESET");
			step_ = TURN_ON;
			break;
	}
}



