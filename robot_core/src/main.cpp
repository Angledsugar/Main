#include "core.h"
#include <iostream>

int main(int argc,char** argv){
	ros::init(argc,argv,"Core");
	Life::Core life;
    	std::cout<<"ROBOT MAIN IS READY\n";
	while(ros::ok()){
		switch(life.get_step()){
			case TURN_ON :
				life.prepare();
				break;
			case DROPPED :
				life.find_person();
				break;
			case MOVE_PERSON :
				life.go_to_person();
				break;
			case WAIT_FOR_PERSON_GRAPPING :
				life.person_grap();
				break;
			case WAIT_LIFE_GUARD :
				life.maintain();
				break;
			default :
				life.clear_step();
				break;
		}
		ros::spinOnce();
	}
	return 0;
}


