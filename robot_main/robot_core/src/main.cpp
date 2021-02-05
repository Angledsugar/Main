#include "life_ros.h"

int main(int argc,char** argv){
	ros::init(argc,argv,"ROBOT_CORE");
	ros::NodeHandle nh;
	Life life(nh);
	enum State{TURN_ON , DROPPED , CLOSE , GRAPPED};
	State state = TURN_ON;
	while(ros::ok()){
		switch(state){
			case TURN_ON:
				if(life.is_drop())
					state = DROPPED;
			break;
			
			case DROPPED:
			break;
			
			default:
				state = TURN_ON;
				break;
				
		}
		
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}
	return 0;
}
