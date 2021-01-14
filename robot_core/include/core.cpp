#include "core.h"

using namespace Life;

Core::Core() : Robot() , step_(2){

};


Core::~Core(){
}


void Core::prepare(){
}


void Core::find_person(){
	ROS_INFO("FIND PERSON...");
}


void Core::go_to_person(){
	if(person_.is_close){
		ROS_INFO("person is close");
	}
	else{
		ROS_INFO("person is far away");
	}
}


void Core::person_grap(){
}


void Core::maintain(){

}


void Core::clear_step(){
	step_ = 0;
}

const int Core::get_step(){
	return step_;
}


void Core::step_set(int n){
	step_ = n;
}



