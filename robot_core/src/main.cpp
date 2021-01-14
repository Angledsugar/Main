#include "core.h"
#include <iostream>

int main(int argc,char** argv){
	ros::init(argc,argv,"Core");
	Life::Core life;
    	std::cout<<"ROBOT MAIN IS READY\n";
	while(ros::ok()){
		switch(life.get_step()){
			case 0 :
				life.prepare();
				break;
			case 1 :
				life.find_person();
				break;
			case 2 :
				life.go_to_person();
				break;
			case 3 :
				life.person_grap();
				break;
			case 4 :
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


